/**
 * @file
 * @brief Implementación de la evaluación de sentencias.
*/
#include "stmt.h"

#include <stddef.h>
#include <stdio.h> // fclose, stdin, ...
#include <stdlib.h>

#include "../global.h"
#include "../log.h"
#include "../str.h"
#include "../ast/stmt.h"
#include "../ast/id.h"
#include "../ast/expr.h"

#include "data.h"
#include "expr.h"
#include "sym.h"
#include "error.h"

extern bool g_exiting;

static ResNode *eval_aug_assign(ResNode *, ResNode *, AstNodeT);
static ResNode *eval_assign_to_id(AstNode *, ResNode *, AstNodeT);
static ResNode *eval_assign_to_elem(AstNode *, ResNode *, AstNodeT);
static ResNode *eval_del_elem(AstNode *);
static ResNode *eval_del_in(AstNode *);
static int compare_data_wrapper(ResNode *, ResNode *, bool);

ResNode *eval_stmt(AstNode *node) {
  DBG_FN_START;
  NULL_RETURN(node, "Interno", S("node == NULL"));
  ResNode *r = NULL;
  switch(node->type) {
    case EXPR_AST: r = eval(ast_stmt_a(node)); break;
    case DECL_AST: r = eval_decl(node); break;
    case ASSIGN_AST: r = eval_assign(node); break;
    case INSERT_AST: r = eval_insert(node); break;
    case RETURN_AST:
      r = eval(ast_stmt_a(node));
      if(res_is_error(r)) break;
      r = res_new_return(r);
      break;
    case DEL_AST: r = eval_del(node); break;
    case BREAK_AST: r = res_new_break(); break;
    case CONTINUE_AST: r = res_new_continue(); break;
    case EXIT_AST:
      // Permite al resto de funciones liberar recursos
      r = res_new_exit(); g_exiting = true; break;
    case IF_AST: r = eval_if(node); break;
    case WHILE_AST: r = eval_while(node); break;
    case FOR_AST: r = eval_for(node); break;
    case FN_AST: r = eval_fndef(node); break;
    default: return RAISE("Interno", S("Nodo inválido"));
  }
  return MAYBE_ERROR(r);
}

ResNode *eval_del(AstNode *del_node) {
  DBG_FN_START;
  NULL_RETURN(del_node, "Interno", S("del_node == NULL"));
  AstNode *target = ast_stmt_a(del_node);
  NULL_RETURN(target, "Interno", S("target == NULL"));
  ResNode *r = NULL;
  while(target) { // En caso de error, las eliminaciones previas no se "deshacen"
    AstNode *data = target->data;
    // Ver tipo de target
    if(data->type == ID_AST) {
      // Eliminar símbolo
      char *id = ast_id_str(data);
      r = scope_del_sym(id, ast_id_hash(data));
    } else if(data->type == ELEM_AST) {
      // Eliminar elemento en la posición indicada (listas)
      r = eval_del_elem(data);
    } else if(data->type == IN_AST) {
      // Eliminar elemento indicado del conjunto/lista
      r = eval_del_in(data);
    } else {
      r = RAISE("Tipo", S("Expresión inválida para 'del'"));
      break;
    }
    ERROR_RETURN(r);
    target = target->next;
  }
  return r;
}

/**
 * @return `NULL` o `ResErrorN`.
 */
ResNode *eval_del_elem(AstNode *elem_ast) {
  DBG_FN_START;
  NULL_RETURN(elem_ast, "Interno", S("elem_ast == NULL"));
  ResNode *a = eval(ast_expr_a(elem_ast));
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  ResNode *b = eval(ast_expr_b(elem_ast)); // si null o error, es necesario liberar 'a'
  ResNode *r = NULL;
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(b->type != INT_R) {
    r = RAISE("Tipo", S("El índice debe ser un número entero"));
    goto free_b;
  }
  if(a->type != LST_R) {
    r = RAISE("Tipo", S("Solo se puede usar índices en listas"));
    goto free_b;
  }
  r = lst_del_index(a, data_int(b)); // NULL == éxito
  free_b:
  res_free(b);
  free_a:
  res_free(a);
  return MAYBE_ERROR(r);
}

/**
 * @return `NULL` o `ResErrorN`.
 */
ResNode *eval_del_in(AstNode *in_ast) {
  DBG_FN_START;
  NULL_RETURN(in_ast, "Interno", S("in_ast == NULL"));
  ResNode *a = eval(ast_expr_a(in_ast));
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  ResNode *b = eval(ast_expr_b(in_ast)); // si null o error, es necesario liberar 'a'
  ResNode *r = NULL;
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(b->type != LST_R && b->type != SET_R) {
    r = RAISE("Tipo", S("El segundo operando debe ser una lista o un conjunto"));
    goto free_b;
  }
  bool sorted = b->type == SET_R ? true : false;
  ResDataN *iter = (ResDataN *)b;
  ResNode *now = iter->elems;
  ResNode *prev = NULL;
  int c = -1;
  // Búsqueda lineal
  while(now && (c = compare_data_wrapper(now->data, a, sorted))) {
    prev = now;
    now = now->next;
  }
  if(c == 0) {
    if(prev) prev->next = now->next;
    else iter->elems = now->next;
    iter->len -= 1;
    REF_DEC(now->data);
    now->next = NULL; // Evita eliminar todo el resto de iter->elems
    res_free(now);
  } else {
    // No se encontró. Es conveniente que sea un error? Si es un error, abortará
    // la ejecución del bloque por lo que el usuario siempre debería verificar
    // si lo que quiere eliminar efectivamente existe. Esto implica hacer dos
    // búsquedas del mismo elemento.
    print_dbg("(%s) Elemento a eliminar no encontrado", __func__);
  }
  return r;
  free_b:
  res_free(b);
  free_a:
  res_free(a);
  return r;
}

int compare_data_wrapper(ResNode *candidate, ResNode *searched, bool sorted) {
  if(sorted) return data_compare(candidate, searched) < 0;
  else return data_compare(candidate, searched) != 0;
}

// a: id_list, b: expr_list
ResNode *eval_decl(AstNode *ast_node) {
  DBG_FN_START;
  NULL_RETURN(ast_node, "Interno", S("ast_node == NULL"));
  AstNode *id_list = ast_stmt_a(ast_node);
  ResNode *value_list = eval(ast_stmt_b(ast_node));
  bool init = value_list != NULL;
  // si un elemento de expr_list genera un error entonces expr_list es un error
  ERROR_RETURN(value_list);
  while(id_list) {
    char *id = ast_id_str(id_list->data);
    unsigned hash = ast_id_hash(id_list->data);
    ResNode *new = init ? value_list->data : res_new_undef();
    ResNode *r = scope_add_sym(id, hash, new);
    if(r) { res_free(new); return MAYBE_ERROR(r); }
    id_list = id_list->next;
    if(init) value_list = value_list->next;
  }
  if(!id_list && !value_list) return NULL; // Sin errores
  return RAISE( // error de sintaxis?
    "Sintaxis", S("Cantidad de identificadores y de expresiones distinta")
  );
}
/**
 * La asignación tiene la forma:
 *
 *     assignable_list assign_op expr_list
*/
ResNode *eval_assign(AstNode *ast_node) {
  DBG_FN_START;
  NULL_RETURN(ast_node, "Interno", S("ast_node == NULL"));
  AstNode *lval_list = ast_stmt_a(ast_node);
  // Evaluación de valores
  ResNode *rval_list = eval(ast_stmt_b(ast_node));
  ERROR_RETURN(rval_list);
  REF_INC(rval_list); // Evita que el GC los libere durante la asignación

  ResNode *r = NULL; // resultado de evals
  ResNode *aux = rval_list; // es necesario liberar la lista en cualquier caso
  while(lval_list && rval_list) {
    // Actual
    AstNode *l_ast = lval_list->data;
    ResNode *r_val = rval_list->data;

    if(l_ast->type == ELEM_AST)
      r = eval_assign_to_elem(l_ast, r_val, ast_stmt_t(ast_node));
    else
      r = eval_assign_to_id(l_ast, r_val, ast_stmt_t(ast_node));
    ERROR_GOTO(r, r, error);
    /// @note Las asignaciones previas no se deshacen en caso de error. Deberían
    /// deshacerse? Cómo?
    // Siguientes
    lval_list = lval_list->next;
    rval_list = rval_list->next;
  } // Si no hubo error, r es NULL
  if(lval_list || rval_list) // error de sintaxis?
    r = RAISE("Sintaxis", S("Cantidad de identificadores y de expresiones distinta"));
  error:
  REF_DEC(aux);
  res_free(aux);
  return MAYBE_ERROR(r);
}

/**
 * @brief Asignación de un identificador.
 *
 * Forma:
 *
 *     id assign_op expr
 *
 * @param sym Nodo AST del identificador
 * @param value Nodo Resultado de evaluar `expr`
 * @param a_type Tipo de asignación
 * @return `NULL` o `ResErrorN`
*/
ResNode *eval_assign_to_id(AstNode *sym, ResNode *value, AstNodeT a_type) {
  DBG_FN_START;
  Symbol *saved = scope_get_sym(ast_id_str(sym), ast_id_hash(sym));
  NULL_RETURN(saved, "Símbolo", str_fmt("Símbolo '%s' no declarado", ast_id_str(sym)));
  // `value` existe porque está asegurado ser, al menos, un nodo `UNDEF_R`
  ResNode *prev = saved->value;
  ResNode *r;
  r = a_type == ASSIGN_AST ? value : eval_aug_assign(saved->value, value, a_type);
  ERROR_RETURN(r);
  REF_DEC(prev); // No se hace en `eval_assign` porque todavía no se opera
  saved->value = r;
  REF_INC(saved->value);
  garbage_collect(prev);
  return NULL; // Éxito
}
/**
 * @brief Asignación a un elemento de una lista.
 *
 * Este tipo de asignación tiene la forma:
 *
 *     primary[sum] assign_op expr
 *
 * @param ast_node Raíz del AST de `primary[sum]`
 * @param value Resultado de evaluar `expr`
 * @param a_type Tipo de asignación (`assign_op`)
 * @return `NULL` o `ResErrorN`
*/
ResNode *eval_assign_to_elem(AstNode *ast_node, ResNode *value, AstNodeT a_type) {
  DBG_FN_START;
  NULL_RETURN(ast_node, "Interno", S("ast_node == NULL"));
  ResNode *list = eval(ast_expr_a(ast_node));
  NULL_RETURN(list, "Interno", S("list == NULL"));
  ERROR_RETURN(list);
  ResNode *index = eval(ast_expr_b(ast_node));
  // si null o error, es necesario liberar list
  ResNode *r = NULL;
  NULL_GOTO(index, r, "Interno", S("index == NULL"), free_list);
  ERROR_GOTO(index, r, free_list);
  if(index->type != INT_R) { // liberar ambos
    r = RAISE("Tipo", S("El índice debe ser un número entero")); goto free;
  }
  if(list->type != LST_R) {
    r = RAISE("Tipo", S("Solo se puede usar índices en listas")); goto free;
  }
  ResNode *current = lst_get_elem(data_int(index), list);
  ERROR_GOTO(current, r, free);
  ResNode *prev = current->data;
  // a += b => no se asigna un nuevo valor a 'a', se modifica el actual.
  r = a_type == ASSIGN_AST ? value : eval_aug_assign(current->data, value, a_type);
  ERROR_GOTO(r, r, free);
  REF_DEC(prev);
  current->data = r;
  REF_INC(current->data);
  garbage_collect(prev);
  r = NULL; // Éxito
  free:
  res_free(index);
  free_list:
  res_free(list);
  return MAYBE_ERROR(r);
}
/**
 * @brief Asignación "aumentada" o compuesta.
 *
 * Tiene la forma:
 *
 *     assignable assign_op expr
 *
 * donde `assign_op` es cualquiera excepto `=`
 *
 * En el caso de iterables, modifica al mismo. Para el resto de tipos es
 * simplemente "syntactic sugar" para `assignable = assignable assign_op expr`
 *
 * @param var_value Valor de `assignable`
 * @param other_value Valor de `expr`
 * @param type Tipo de asignación
 * @return Puntero al resultado de la operación o `ResErrorN`.
*/
ResNode *eval_aug_assign(ResNode *var_value, ResNode *other_value, AstNodeT type) {
  DBG_FN_START;
  NULL_RETURN(var_value, "Interno", S("var_value == NULL"));
  NULL_RETURN(other_value, "Interno", S("other_value == NULL"));
  ResDataN *a = (ResDataN *)var_value;
  ResDataN *b = (ResDataN *)other_value;
  if(a->type != b->type) // En todas las operaciones implementadas deben ser iguales
    return RAISE("Tipo", S("Operandos de tipos incompatibles"));
  switch(a->type) {
    case INT_R: // Crea un nuevo entero
      switch(type) {
        case ADD_AST:
          return res_new_int(a->int_ + b->int_);
        case SUB_AST:
          return res_new_int(a->int_ - b->int_);
        case MUL_AST:
          return res_new_int(a->int_ * b->int_);
        case DIV_AST:
          if(b->int_ == 0) return RAISE("Valor", S("División por cero"));
          return res_new_int(a->int_ / b->int_);
        default: goto end;
      }
    case LST_R: // Modifica la misma lista
      switch(type) {
        case ADD_AST:
          a->len = a->len + b->len;
          a->elems = lst_mod_concat(a->elems, b->elems);
          return var_value;
        default: goto end;
      }
    case SET_R: // Modifica el mismo conjunto
      switch(type) {
        case ADD_AST:
          a->elems = set_mod_union(a->elems, b->elems, &(a->len));
          return var_value;
        case SUB_AST:
          a->elems = set_mod_diff(a->elems, b->elems, &(a->len));
          return var_value;
        case MUL_AST:
          a->elems = set_mod_inters(a->elems, b->elems, &(a->len));
          return var_value;
        default: goto end;
      }
    default: goto end;
  }
  end: // En este punto no coincidió con ningún case
  return RAISE("Interno", str_fmt("El nodo %s es inválido", ast_enum_str(type)));
}

ResNode *eval_insert(AstNode *ast_node) {
  DBG_FN_START;
  NULL_RETURN(ast_node, "Interno", S("ast_node == NULL"));
  ResNode *r = NULL;
  ResNode *list = eval(ast_stmt_a(ast_node));
  NULL_RETURN(list, "Interno", S("list == NULL"));
  ERROR_RETURN(list);
  ResNode *index = eval(ast_stmt_c(ast_node));
  NULL_GOTO(index, r, "Interno", S("index == NULL"), free_list);
  ERROR_GOTO(index, r, free_list);
  if(index->type != INT_R) {
    r = RAISE("Interno", S("El índice debe ser un número entero"));
    goto free_index;
  }
  ResNode *elem = eval(ast_stmt_b(ast_node));
  NULL_GOTO(elem, r, "Interno", S("elem == NULL"), free_index);
  ERROR_GOTO(elem, r, free_index);
  if(list->type != LST_R) {
    r = RAISE("Interno", S("Solo se puede insertar en listas"));
    goto free_elem;
  }
  r = lst_insert_elem(list, data_int(index), ast_stmt_side(ast_node), elem);
  free_elem:
  res_free(elem);
  free_index:
  res_free(index);
  free_list:
  res_free(list);
  return MAYBE_ERROR(r);
}
/**
 * Primero se evalúa la condición fuera del alcance del bloque. Su resultado se
 * convierte a un valor lógico (ver @ref bool_cast). Se crea el alcance para el
 * bloque, se evalúa la lista de sentencias correspondiente al valor lógico y se
 * abandona el alcance creado. Finalmente se devuelve el resultado, que podría
 * ser `NULL`, un error o alguna interrupción (`return`, `break`, `continue`,
 * `exit`).
 */
ResNode *eval_if(AstNode *if_ast) {
  DBG_FN_START;
  NULL_RETURN(if_ast, "Interno", S("if_ast == NULL"));
  ResNode *r = eval(ast_stmt_a(if_ast));
  NULL_RETURN(r, "Interno", S("r == NULL"));// Lo detecta antes Bison
  ERROR_RETURN(r);
  bool c = bool_cast(r);
  res_free(r);
  scope_push();
  if(c) {
    r = eval(ast_stmt_b(if_ast));
  } else {
    r = eval(ast_stmt_c(if_ast));
  }
  scope_pop();
  return MAYBE_ERROR(r);
}
/**
 * El primer paso es evaluar la condición y obtener su valor lógico (ver @ref
 * bool_cast). Si es falso, el ciclo se detiene y se devuelve `NULL` indicando
 * que no hubo interrupciones ni errores. SI es verdadero, se crea el alcance
 * del bloque y se evalúa la lista de sentencias. Al terminar, se elimina el
 * alcance creado y se analiza el resultado.
 *
 * - Si la lista de sentencias devuelve `NULL`, no hubo errores ni interrupciones,
 * por lo que el ciclo continúa.
 * - Si devuelve un error, el ciclo se detiene y el error se propaga al
 *   exterior.
 * - Si devuelve un `break` entonces se libera, para evitar que afecte a ciclos
 *   exteriores, y el ciclo se detiene.
 * - Si devuelve un `return` o `exit`, el ciclo se detiene y el resultado se
 *   propaga al exterior. `return` debe detener la ejecución de la función que
 *   "envuelve" al ciclo y `exit` debe detener la ejecución de todo el programa.
 * - En cualquier otro caso, incluyendo `continue`, se libera el resultado y se
 *   pasa a la siguiente iteración.
 */
ResNode *eval_while(AstNode *while_ast) {
  DBG_FN_START;
  NULL_RETURN(while_ast, "Interno", S("while_ast == NULL"));
  AstNode *condition = ast_stmt_a(while_ast);
  AstNode *body = ast_stmt_b(while_ast);
  ResNode *r = NULL;
  while(true) {
    // condición
    r = eval(condition);
    NULL_RETURN(r, "Interno", S("r == NULL")); // Lo detecta antes Bison
    ERROR_RETURN(r);
    bool c = bool_cast(r);
    res_free(r);
    if(!c) { r = NULL; break; }
    // cuerpo
    scope_push();
    r = eval(body);
    scope_pop();
    if(!r) continue; // puede ser NULL (ninguna interrupción)
    // error = finaliza el ciclo y propaga el error
    if(r->type == ERROR_R) break;
    // break = finaliza solo el ciclo actual
    if(r->type == BREAK_R) { // evitar que se propague a ciclos exteriores.
      res_free(r); r = NULL; break;
    }
    // return = finaliza la función que contiene esta sentencia
    // exit - finaliza el intérprete
    if(r->type == RETURN_R || r->type == EXIT_R) break; // propaga return o exit
    // cualquier otro caso (ej. continue), liberar y continuar
    res_free(r);

    /* NOTE
    ¿Habrá forma más eficiente (que recrear todo el scope en cada iteración)?

    Sí, si la línea de la declaración es la misma en la nueva y en la guardada,
    entonces no es error de re-declaración y no es necesario limpiar todo antes
    de cada iteración

    ¿Pero qué pasa con el scope de la condición? Podría implementarse un cambio
    de scope que vuelva al anterior sin perder el actual
    */
  }
  return MAYBE_ERROR(r);
}
/**
 * La sentencia tiene la forma:
 *
 *     for id in iter block
 *         a     b    c
 *
 * Para comenzar, se evalúa la expresión que resultará en una lista o un
 * conjunto de elementos para recorrer y se verifica que efectivamente sea un
 * iterable.
 *
 * Puede ocurrir que no sea referenciado en ningún lugar fuera del encabezado
 * del `for`, por lo que se incrementa su `refcnt` para evitar que sus elementos
 * sean liberados al final de cada iteración.
 *
 * Antes de evaluar la lista de sentencias se crea un nuevo alcance.
 *
 * Si el iterable es una lista, se declara un símbolo especial `_i` con el
 * índice del elemento actual.
 *
 * Se crea el símbolo con el elemento actual y se evalúa el cuerpo del `for`. Al
 * terminar, se elimina el alcance del bloque.
 *
 * El análisis del resultado es exactamente igual al de @ref eval_while.
 *
 * Antes de finalizar el `for` se decrementa el `refcnt` del iterable y se
 * libera si no posee más referencias.
 */
ResNode *eval_for(AstNode *for_ast) {
  DBG_FN_START;
  NULL_RETURN(for_ast, "Interno", S("for_ast == NULL"));
  ResNode *r = NULL;
  ResNode *iter = eval(ast_stmt_b(for_ast)); // sus elementos van en id
  NULL_RETURN(iter, "Interno", S("iter == NULL")); // Lo detecta antes Bison
  ERROR_RETURN(iter);
  if(iter->type != LST_R && iter->type != SET_R) { // Esto es un error de sintaxis?
    r = RAISE("Tipo", S("Solo se puede iterar sobre listas o conjuntos"));
    goto free_iter;
  }
  // si iter no es un símbolo, su refcnt es 0 y sus elementos serían liberados
  // en cada pop_scope. Para evitarlo, se lo incrementa
  REF_INC(iter);
  ResNode *elem = data_elems(iter);
  AstNode *s = ast_stmt_a(for_ast); // id para elementos
  AstNode *body = ast_stmt_c(for_ast);
  char *i_str = "_i"; unsigned i_hash = str_hash(i_str); int i = 1;
  while(elem) {
    scope_push();
    if(iter->type == LST_R) { // variable para el índice de listas
      ResNode *i_res = res_new_int(i);
      r = scope_add_sym(i_str, i_hash, i_res);
      if(res_is_error(r)) {
        res_free(i_res); scope_pop(); goto free_iter;
      }
    }
    // id para elemento
    r = scope_add_sym(ast_id_str(s), ast_id_hash(s), elem->data);
    if(r) { scope_pop(); goto free_iter; }
    // stmts
    r = eval(body);
    scope_pop(); // habrá forma más eficiente?
    elem = elem->next;
    i += 1;
    if(!r) continue; // puede ser NULL (ninguna interrupción)
    // error = finaliza el ciclo y propaga el error
    if(r->type == ERROR_R) break;
    // break = finaliza solo el ciclo actual
    if(r->type == BREAK_R) { // evitar que se propague a ciclos exteriores.
      res_free(r); r = NULL; break;
    }
    // exit - finaliza el intérprete
    if(r->type == RETURN_R || r->type == EXIT_R) break; // propaga return o exit
    // cualquier otro caso (ej. continue), liberar y continuar
    res_free(r);
  }
  free_iter:
  REF_DEC(iter); // vuelve a su refcnt original
  res_free(iter);
  return MAYBE_ERROR(r);
}
/**
 * La sentencia tiene la forma:
 *
 *     fn id(params) block
 *
 * La evaluación es simplemente declarar un símbolo con el identificador de la
 * función y asignarle como valor un dato de tipo `fn`, que no es más que un
 * "envoltorio" para el AST de la definición.
 *
 * Si el agregado del símbolo falla, se libera el dato de tipo `fn` y se propaga
 * el error.
 *
 * Para llamadas ver @ref eval_fncall.
*/
ResNode *eval_fndef(AstNode *fn_def_ast) {
  DBG_FN_START;
  NULL_RETURN(fn_def_ast, "Interno", S("fn_def_ast == NULL"));
  AstNode *sym = ast_stmt_a(fn_def_ast);
  ResNode *val = res_new_fn(fn_def_ast);
  ResNode *r = scope_add_sym(ast_id_str(sym), ast_id_hash(sym), val);
  if(!r) res_free(val);
  return MAYBE_ERROR(r);
}

ResNode *res_new_return(ResNode *data) {
  DBG_FN_START;
  ResNode *r = malloc(sizeof(ResNode));
  // esto impide que el valor de retorno se libere antes de salir de fncall
  REF_INC(data); // se debe decrementar al salir del scope
  r->data = data;
  r->next = NULL;
  r->type = RETURN_R;
  return r;
}

ResNode *res_new_break(void) {
  DBG_FN_START;
  ResNode *r = malloc(sizeof(ResNode));
  r->data = NULL;
  r->next = NULL;
  r->type = BREAK_R;
  return r;
}

ResNode *res_new_continue(void) {
  DBG_FN_START;
  ResNode *r = malloc(sizeof(ResNode));
  r->data = NULL;
  r->next = NULL;
  r->type = CONTINUE_R;
  return r;
}

ResNode *res_new_exit(void) {
  DBG_FN_START;
  ResNode *r = malloc(sizeof(ResNode));
  r->type = EXIT_R;
  r->next = NULL;
  r->data = NULL;
  return r;
}

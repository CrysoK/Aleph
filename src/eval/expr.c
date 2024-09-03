/**
 * @file
 * @brief Implementación de la evaluación de expresiones.
*/
#include "expr.h"

#include <stddef.h>
#include <string.h>

#include "../global.h"
#include "../log.h"
#include "../str.h"
#include "../ast/expr.h"
#include "../ast/stmt.h"
#include "../ast/id.h"
#include "data.h"
#include "sym.h"
#include "error.h"

// Añade elemento a la lista de elementos de un conjunto. Auxiliar para
// intersección y diferencia
static ResNode *aux_inters_diff(ResNode *ll_n, ResNode *elem, int *new_len);
static ResNode *eval_expr_a(AstNode *ast);
static ResNode *eval_expr_b(AstNode *ast);
static ResNode *eval_expr_x(AstNode *ast);
static bool valid_operand(ResNode *node);
/**
 * @brief Asigna los argumentos de la llamada a su correspondiente parámetro.
 * @param args Argumentos de la llamada.
 * @param fndef_ast AST de la definición de la función.
 * @param a_cnt Cantidad de argumentos.
 * @param fname Nombre de la función.
 * @return `NULL` o `ResErrorN`.
 */
ResNode *eval_fncall_params(ResNode *args, AstNode *fndef_ast, int a_cnt, char *fname);

// No devuelve `NULL`
ResNode *eval_expr(AstNode *node) {
  DBG_FN_START;
  NULL_RETURN(node, "Interno", S("node == NULL"));
  ResNode *r = NULL;
  switch(node->type) {
    case OR_AST:
      r = eval_or(node);
      break;
    case AND_AST:
      r = eval_and(node);
      break;
    case EQUAL_AST:
      r = eval_equal(node);
      break;
    case LESS_AST:
      r = eval_less(node);
      break;
    case IN_AST:
      r = eval_in(node);
      break;
    case ELEM_AST:
      r = eval_elem(node);
      break;
    case ADD_AST:
      r = eval_add(node);
      break;
    case SUB_AST:
      r = eval_sub(node);
      break;
    case MUL_AST:
      r = eval_mul(node);
      break;
    case DIV_AST:
      r = eval_div(node);
      break;
    case CALL_AST:
      r = eval_fncall(node);
      break;
    case NOT_AST:
    case NEG_AST:
    case LEN_AST:
      r = eval_unary(node);
      break;
    default:
      return RAISE("Interno", S("Nodo inválido"));
  }
  return MAYBE_ERROR(r);
}

ResNode *eval_expr_a(AstNode *ast) {
  return eval(ast_expr_a(ast));
  //     eval_expr_a(ast);
}

ResNode *eval_expr_b(AstNode *ast) {
  return eval(ast_expr_b(ast));
}

ResNode *eval_expr_x(AstNode *ast) {
  return eval(ast_expr_x(ast));
}

bool valid_operand(ResNode *node) {
  if(node && INT_R <= node->type && node->type <= LST_R) return true;
  else return false;
}
// No devuelve `NULL`
ResNode *eval_or(AstNode *or_ast) {
  NULL_RETURN(or_ast, "Interno", S("or_ast == NULL"));
  ResNode *a, *b, *r = NULL;
  a = eval_expr_a(or_ast);
  ERROR_RETURN(a);
  if(bool_cast(a)) { r = res_new_int(true); goto free_a; }
  b = eval_expr_b(or_ast);
  ERROR_GOTO(b, r, free_b);
  if(bool_cast(b)) { r = res_new_int(true); goto free_b; }
  r = res_new_int(false);
  free_b: res_free(b);
  free_a: res_free(a);
  return MAYBE_ERROR(r);
}
// No devuelve `NULL`
ResNode *eval_and(AstNode *and_ast) {
  NULL_RETURN(and_ast, "Interno", S("and_ast == NULL"));
  ResNode *a, *b, *r = NULL;
  a = eval_expr_a(and_ast);
  ERROR_RETURN(a);
  if(!bool_cast(a)) { r = res_new_int(false); goto free_a; }
  b = eval_expr_b(and_ast);
  ERROR_GOTO(b, r, free_b);
  if(!bool_cast(b)) { r = res_new_int(false); goto free_b; }
  r = res_new_int(true);
  free_b: res_free(b);
  free_a: res_free(a);
  return MAYBE_ERROR(r);
}
// No devuelve `NULL`
ResNode *eval_equal(AstNode *equal_ast) {
  NULL_RETURN(equal_ast, "Interno", S("equal_ast == NULL"));
  ResNode *r = NULL;
  ResNode *a = eval_expr_a(equal_ast);
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  ResNode *b = eval_expr_b(equal_ast);
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(a->type != b->type) {
    r = RAISE("Tipo", S("Los operandos deben ser del mismo tipo"));
    goto free_b;
  }
  if(!(INT_R <= a->type && a->type <= LST_R)) {
    r = RAISE("Tipo", str_fmt(
      "'==' no está definido para el tipo '%s'", res_enum_str(a->type)));
    goto free_b;
  }
  r = res_new_int(data_compare(a, b) == 0);
  free_b: res_free(b);
  free_a: res_free(a);
  return MAYBE_ERROR(r);
}
// No devuelve `NULL`
ResNode *eval_less(AstNode *less_ast) {
  NULL_RETURN(less_ast, "Interno", S("less_ast == NULL"));
  ResNode *a = eval_expr_a(less_ast);
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  ResNode *r = NULL;
  ResNode *b = eval_expr_b(less_ast);
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(!valid_operand(a) || !valid_operand(b)) {
    r = RAISE("Tipo", S("Operandos inválidos")); goto free_b;
  }
  if(a->type != b->type) {
    r = RAISE("Tipo", S("Los operandos deben ser del mismo tipo")); goto free_b;
  }
  r = res_new_int(data_compare(a, b) < 0);
  // ¿Contención en el caso de conjuntos?
  free_b: res_free(b);
  free_a: res_free(a);
  return MAYBE_ERROR(r);
}

ResNode *eval_in(AstNode *in_ast) {
  NULL_RETURN(in_ast, "Interno", S("in_ast == NULL"));
  ResNode *a = eval_expr_a(in_ast);
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  ResNode *r = NULL;
  ResNode *b = eval_expr_b(in_ast);
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(!valid_operand(a)) {
    r = RAISE("Tipo", S("Operando izquierdo inválido")); goto free_b;
  }
  switch(b->type) {
    case LST_R: r = res_new_int(lst_search_elem(a, b)); break;
    case SET_R: r = res_new_int(set_search_elem(a, b)); break;
    default:
      r = RAISE("Tipo", S("El operando derecho debe ser una lista o un conjunto"));
  }
  free_b: res_free(b);
  free_a: res_free(a);
  return MAYBE_ERROR(r);
}

ResNode *eval_elem(AstNode *elem_ast) {
  NULL_RETURN(elem_ast, "Interno", S("elem_ast == NULL"));
  ResNode *a = eval(ast_expr_a(elem_ast));
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  bool data = false;
  ResNode *r = NULL;
  ResNode *b = eval(ast_expr_b(elem_ast));
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(b->type != INT_R) {
    r = RAISE("Tipo", S("El índice debe ser un número entero")); goto free_b;
  }
  if(a->type != LST_R) {
    r = RAISE("Tipo", S("Solo se puede usar índices en listas")); goto free_b;
  }
  r = lst_get_elem(data_int(b), a); // Nunca devuelve NULL
  ERROR_GOTO(r, r, free_b);
  r = r->data; data = true;
  free_b: res_free(b);
  if(data) REF_INC(r); // Evita que se libere al liberar 'a'
  free_a: res_free(a);
  if(data) REF_DEC(r);
  return MAYBE_ERROR(r);
}

ResNode *eval_add(AstNode *add_ast) {
  NULL_RETURN(add_ast, "Interno", S("add_ast == NULL"));
  ResNode *a = eval_expr_a(add_ast);
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  ResNode *r = NULL;
  ResNode *b = eval_expr_b(add_ast);
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(a->type != b->type) {
    r = RAISE("Tipo", S("Los operandos deben ser del mismo tipo")); goto free_b;
  }
  int new_len = 0;
  switch(a->type) {
    case INT_R: r = res_new_int(data_int(a) + data_int(b)); break;
    case LST_R:
      r = lst_new_concat(data_elems(a), data_elems(b));
      r = res_new_lst(r, data_len(a) + data_len(b));
      break;
    case SET_R:
      r = set_new_union(data_elems(a), data_elems(b), &new_len);
      r = res_new_set(r, new_len);
      break;
    default:
      r = RAISE("Tipo",
        str_fmt("Operación no definida para '%s'", res_enum_str(a->type)));
      goto free_b;
  }
  free_b: res_free(b);
  free_a: res_free(a);
  return MAYBE_ERROR(r);
}

ResNode *eval_sub(AstNode *sub_ast) {
  NULL_RETURN(sub_ast, "Interno", S("sub_ast == NULL"));
  ResNode *a = eval_expr_a(sub_ast);
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  ResNode *r = NULL;
  ResNode *b = eval_expr_b(sub_ast);
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(a->type != b->type) {
    r = RAISE("Tipo", S("Los operandos deben ser del mismo tipo")); goto free_b;
  }
  int new_len = 0;
  switch(a->type) {
    case INT_R: r = res_new_int(data_int(a) - data_int(b)); break;
    case SET_R:
      r = set_new_diff(data_elems(a), data_elems(b), &new_len);
      r = res_new_set(r, new_len);
      break;
    default:
      r = RAISE("Tipo",
        str_fmt("Operación no definida para '%s'", res_enum_str(a->type)));
  }
  free_b: res_free(b);
  free_a: res_free(a);
  return MAYBE_ERROR(r);
}

ResNode *eval_mul(AstNode *mul_ast) {
  NULL_RETURN(mul_ast, "Interno", S("mul_ast == NULL"));
  ResNode *a = eval_expr_a(mul_ast);
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  ResNode *r = NULL;
  ResNode *b = eval_expr_b(mul_ast);
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(a->type != b->type) {
    r = RAISE("Tipo", S("Los operandos deben ser del mismo tipo")); goto free_b;
  }
  int new_len = 0;
  switch(a->type) {
    case INT_R: r = res_new_int(data_int(a) * data_int(b)); break;
    case SET_R:
      r = set_new_inters(data_elems(a), data_elems(b), &new_len);
      r = res_new_set(r, new_len);
      break;
    default: r = RAISE("Tipo",
        str_fmt("Operación no definida para '%s'", res_enum_str(a->type)));
  }
  free_b: res_free(b);
  free_a: res_free(a);
  return MAYBE_ERROR(r);
}

ResNode *eval_div(AstNode *div_ast) {
  NULL_RETURN(div_ast, "Interno", S("div_ast == NULL"));
  ResNode *a = eval_expr_a(div_ast);
  NULL_RETURN(a, "Interno", S("a == NULL"));
  ERROR_RETURN(a);
  ResNode *r = NULL;
  ResNode *b = eval_expr_b(div_ast);
  NULL_GOTO(b, r, "Interno", S("b == NULL"), free_a);
  ERROR_GOTO(b, r, free_a);
  if(a->type != INT_R) {
    r = RAISE("Tipo", S("Los operandos deben ser enteros")); goto free_b;
  }
  if(a->type != b->type) {
    r = RAISE("Tipo", S("Los operandos deben ser del mismo tipo")); goto free_b;
  }
  if(data_int(b) == 0) {
    r = RAISE("Valor", S("División por cero")); goto free_b;
  }
  r = res_new_int(data_int(a) / data_int(b));
  free_b: res_free(b);
  free_a: res_free(a);
  return MAYBE_ERROR(r);
}
/**
 * Se crea un símbolo para cada parámetro y asigna como valor al argumento
 * correspondiente. También reporta detalladamente el error si la cantidad de
 * argumentos no coincide con los requeridos.
 *
 * El parámetro especial `...` permite recibir un número variable de argumentos.
 * Estos se guardan en el símbolo especial `_args` como una lista.
 */
ResNode *eval_fncall_params(
  ResNode *args, AstNode *fndef_ast, int a_cnt, char *fname
) {
  DBG_FN_START;
  int p_cnt = 0; // cantidad de parámetros
  bool varargs = false; // cantidad de parámetros indeterminada
  ERROR_RETURN(args); // puede ser NULL
  ResNode *arg = args;
  AstNode *param = ast_stmt_b(fndef_ast);
  ResNode *r = NULL;
  while(param) {
    char *id = ast_id_str(param->data);
    unsigned hash = ast_id_hash(param->data);
    if(strcmp(id, "...") == 0) { varargs = true; break; }
    if(arg) { // permite seguir contando parámetros aunque no queden argumentos
      if(!arg->data) // args puede ser nulo (llamada sin argumentos) pero UN arg no.
        return RAISE("Valor", S("Argumento inválido"));
      r = scope_add_sym(id, hash, arg->data);
      if(res_is_error(r)) return MAYBE_ERROR(r);
      arg = arg->next;
    }
    param = param->next; p_cnt++;
  }
  if(varargs && p_cnt <= a_cnt) { // Guarda todos los argumentos restantes en `_args`
    // <= porque debe poder se una lista vacía (ej. print())
    ResNode * _args = res_new_lst(arg, a_cnt - p_cnt);
    r = scope_add_sym("_args", str_hash("_args"), _args);
    if(res_is_error(r)) {
      ((ResDataN *)_args)->elems = NULL; // deja el trabajo para free_args
      res_free(_args);
      return MAYBE_ERROR(r);
    }
    p_cnt = a_cnt;
  }
  if(p_cnt != a_cnt) {
    r = RAISE("Tipo", str_fmt(
      "'%s' necesita %s %d argumento%s (%d dado%s)", fname,
      varargs ? "al menos" : "exactamente", p_cnt,
      p_cnt > 1 ? "s" : "", a_cnt, a_cnt > 1 ? "s" : "")
    );
  }
  return r;
}
/**
 * Primero se evalúa el símbolo de la función para obtener el AST de su
 * definición, luego de asegurarse de que efectivamente lo sea.
 *
 * Después se evalúa la lista de expresiones que conforman los argumentos. Si no
 * hay errores, se procede a guardar el ámbito en el que se realiza la llamada y
 * se establece el ámbito global como actual.q
 *
 * Se crea un ámbito local para la función y se asignan los argumentos a su
 * respectivo parámetro (ver @ref eval_fncall_params).
 *
 * Lo siguiente es evaluar la lista de sentencias del cuerpo de la función . Al
 * terminar, se elimina el alcance local y se regresa al ámbito donde se hizo la
 * llamada.
 *
 * Finalmente se analiza el resultado: si es un `return`, se devuelve el dato
 * que contiene; si es un `exit` o un error, se propaga; y en cualquier otro
 * caso, se devuelve nulo, representado por un nodo de tipo `VOID_R`.
 */
ResNode *eval_fncall(AstNode *fncall_ast) {
  DBG_FN_START;
  NULL_RETURN(fncall_ast, "Interno", S("fncall_ast == NULL"));
  ResNode *r = NULL;
  ResNode *sym_val = eval(ast_expr_a(fncall_ast)); // liberar
  NULL_RETURN(sym_val, "Interno", S("sym_val == NULL"));
  ERROR_RETURN(sym_val);
  if(sym_val->type != FN_R) {
    r = RAISE("Tipo", S("No es una función"));
    goto free_sym_val;
  }
  AstNode *fndef_ast = data_fn(sym_val);
  NULL_GOTO(fndef_ast, r, "Interno", S("fndef_ast == NULL"), free_sym_val);
  int a_cnt = 0; // cantidad de argumentos
  ResNode *args = eval_expr_list(ast_stmt_b(fncall_ast), &a_cnt); // liberar
  ERROR_GOTO(args, r, free_sym_val);
  int calling_depth = scope_depth(); // Establece el scope global como actual
  SymTab *calling_scope = scope_change(NULL, 0);
  scope_push(); // Scope local de la función
  r = eval_fncall_params(
    args, fndef_ast, a_cnt, ast_id_str(ast_expr_a(fncall_ast)));
  ERROR_GOTO(r, r, end_scope);
  // Evaluación de sentencias
  r = eval(ast_stmt_c(fndef_ast));
  print_dbg("fncall = %s", r ? res_enum_str(r->type) : "NULL");
  ERROR_GOTO(r, r, end_scope); // Incluye `exit`
  scope_pop(); // Fin scope local.
  scope_change(calling_scope, calling_depth); // Restablece el scope previo
  ResNode *aux = r;
  if(r && r->type == RETURN_R && r->data) {
    r = r->data; // return con algún dato
    REF_DEC(r); // el correspondiente +1 está en eval_stmt
    aux->data = NULL;// deja de referenciar el dato, para que res_free no lo libere
  } else r = res_new_void();
  res_free(aux);
  return r;

  end_scope:
  res_free(args);
  scope_pop(); // Fin scope local
  scope_change(calling_scope, calling_depth); // Restablece el scope previo
  free_sym_val:
  res_free(sym_val);
  return r;
}

bool bool_cast(ResNode *node) {
  bool r = false;
  if(!node) goto dbg;
  ResDataN *data = (ResDataN *)node;
  switch(data->type) {
    case INT_R:
      r = (data->int_ != 0) ? true : false;
      break;
    case STR_R:
      r = (strcmp(data->str, "") != 0) ? true : false;
      break;
    case LST_R: case SET_R:
      r = (data->len > 0) ? true : false;
      break;
    case UNDEF_R:
      r = false;
      break;
    case VOID_R:
      r = false;
      break;
    default:
      print_error("Interno", "(%s) Nodo inválido: %s", __func__, res_enum_str(data->type));
      r = false;
  }
  dbg:
  print_dbg("(%s) %s", __func__, r ? "true" : "false");
  return r;
}
// No devuelve `NULL`
ResNode *eval_unary(AstNode * node) {
  DBG_FN_START;
  NULL_RETURN(node, "Interno", S("node == NULL"));
  ResNode *x = eval(ast_expr_x(node));
  ResNode *r = NULL;
  NULL_RETURN(x, "Interno", S("x == NULL"));
  ERROR_RETURN(x);
  switch(node->type) {
    case NOT_AST: r = res_new_int(!bool_cast(x)); break;
    case NEG_AST:
      switch(x->type) {
        case INT_R: r = res_new_int(-data_int(x)); break;
        default: r = RAISE("Tipo", S("No es un entero"));
      } break;
    case LEN_AST:
      switch(x->type) {
        case SET_R: case LST_R: r = res_new_int(data_len(x)); break;
        default: r = RAISE("Tipo", S("No es una lista o conjunto"));
      } break;
    default: r = RAISE("Interno", S("Operación unaria indefinida"));
  }
  return MAYBE_ERROR(r);
}

/**
 * Todos los `refcnt` se incrementan.
 */
ResNode *lst_new_concat(ResNode *a, ResNode *b) {
  DBG_FN_START;

  ResNode *aux = res_new_ll_n(NULL);
  ResNode *r = aux;
  while(a) {
    REF_INC(a->data);
    r->next = res_new_ll_n(a->data);
    r = r->next;
    a = a->next;
  }
  while(b) {
    REF_INC(b->data);
    r->next = res_new_ll_n(b->data);
    r = r->next;
    b = b->next;
  }
  r = aux->next;
  aux->next = NULL;
  res_free(aux);
  return r;
}

/**
 * Agrega los elementos de una lista (`b`) al final de otra (`a`). No devuelve
 * errores. Puede devolver `NULL` (lista vacía). Los elementos de `b`
 * incrementan su `refcnt`.
*/
ResNode *lst_mod_concat(ResNode *a, ResNode *b) {
  DBG_FN_START;
  if(!a && b) { // Si 'a' es [] y 'b' no
    REF_INC(b->data);
    a = res_new_ll_n(b->data);
    b = b->next;
  }
  ResNode *r = a; // Se guarda el primer nodo
  // Búsqueda del último elemento de 'a'
  while(a && a->next) a = a->next;
  while(b) { // Concatenación desde el último elemento de 'a'
    // Debería copiarse en vez de referenciar?
    REF_INC(b->data);
    a->next = res_new_ll_n(b->data);
    a = a->next; b = b->next;
  }
  return r;
}

ResNode *set_new_union(ResNode *a, ResNode *b, int *new_len) {
  DBG_FN_START;
  ResNode *r = NULL;
  // ResNode *elem = NULL;
  // if(a) {
  //   elem = a; a = a->next;
  // } else if(b) {
  //   elem = b; b = b->next;
  // }
  // if(elem) {
  //   REF_INC(elem->data);
  //   r = res_new_ll_n(elem->data);
  //   (*new_len)++;
  //   elem->next;
  // }
  while(a) {
    if(set_insert_elem(a->data, &r)) {
      REF_INC(a->data);
      (*new_len)++;
    } a = a->next;
  }
  while(b) {
    if(set_insert_elem(b->data, &r)) {
      REF_INC(b->data);
      (*new_len)++;
    } b = b->next;
  }
  return r;

  // if(a) {
  //   REF_INC(a->data);
  //   r = res_new_ll_n(a->data);
  //   (*new_len)++;
  // } else if(b) {
  //   REF_INC(b->data);
  //   r = res_new_ll_n(b->data);
  //   (*new_len)++;
  // }
  // a = a ? a->next : NULL;
  // while(a) {
  //   if(set_insert_elem(a->data, &r)) {
  //     REF_INC(a->data);
  //     (*new_len)++;
  //   }
  //   a = a->next;
  // }
  // while(b) {
  //   if(set_insert_elem(b->data, &r)) {
  //     REF_INC(b->data);
  //     (*new_len)++;
  //   }
  //   b = b->next;
  // }
  // return r;
}

/**
 * Añade los elementos del conjunto `b` al conjunto `a` sin repetidos. No
 * devuelve errores. Puede devolver NULL (conjunto vacío).
*/
ResNode *set_mod_union(ResNode *a, ResNode *b, int *new_len) {
  DBG_FN_START;
  ResNode *r = a;
  while(b) {
    if(set_insert_elem(b->data, &r)) (REF_INC(b->data), (*new_len)++);
    b = b->next;
  }
  return r;
}

ResNode *aux_inters_diff(ResNode *ll_n, ResNode *elem, int *new_len) {
  DBG_FN_START;
  if(!ll_n) {
    REF_INC(elem);
    ll_n = res_new_ll_n(elem);
    (*new_len)++;
  } else {
    if(set_insert_elem(elem, &ll_n)) {
      REF_INC(elem);
      (*new_len)++;
    }
  }
  return ll_n;
}

// Como los conjuntos están ordenados, se puede decir que un elemento de 'a' no
// está en 'b' si es menor al que se comparó
// - {(1), 3, 4} * {(2), 3, 5} = {}
// - 1 no puede estar en 'b' porque 2 es mayor
// - {1, (3), 4} * {(2), 3, 5} = {}
// - 2 no puede estar en 'a' porque 3 es mayor
// - {1, (3), 4} * {2, (3), 5} = {3}
// - {1, 3, (4)} * {2, 3, (5)} = {3}
// - 4 no puede estar en 'b' porque 5 es mayor
// - {1, 3, 4} * {2, 3, 5} = {3}
ResNode *set_new_inters(ResNode *a, ResNode *b, int *new_len) {
  DBG_FN_START;
  ResNode *r = NULL;
  *new_len = 0;
  while(a && b) {
    int c = data_compare(a->data, b->data);
    if(c == 0) {
      // Usar data de 'a' o de 'b'? Por qué?
      r = aux_inters_diff(r, a->data, new_len);
    }
    a = c <= 0 ? a->next : a;
    b = c >= 0 ? b->next : b;
  }
  return r;
}

ResNode *set_mod_inters(ResNode *dest, ResNode *other, int *new_len) {
  res_free(RAISE("Interno", S("No implementado")));
  return dest; // No puede devolver un `ResErrorN`
}

// Como los conjuntos están ordenados, se puede decir que un elemento de 'a' no
// está en 'b' si es menor al que se comparó (similar a la intersección, pero
// cambia la condición de comparación)
// - {(1), 3, 4} - {(2), 3, 5} = {1}
// - 1 se agrega porque no está en 'b' (1 < 2)
// - {1, (3), 4} - {(2), 3, 5} = {1}
// - 3 no se agrega porque podría estar en 'b' (3 > 2)
// - {1, (3), 4} - {2, (3), 5} = {1}
// - 3 no se agrega porque está en 'b' (3 == 3)
// - {1, 3, (4)} - {2, 3, (5)} = {3, 4}
// - 4 se agrega porque ya no puede estar en 'b' (4 < 5)
// - {1, 3, 4} - {2, 3, 5} = {3, 4}
// - Si c > 0 al finalizar, agregar al resultado ({8} - {1})
ResNode *set_new_diff(ResNode *a, ResNode *b, int *new_len) {
  DBG_FN_START;
  ResNode *r = NULL;
  *new_len = 0;
  int c = 0;
  while(a && b) { // Mientras ambos tengan elementos
    c = data_compare(a->data, b->data);
    if(c < 0) {
      r = aux_inters_diff(r, a->data, new_len);
    }
    a = c <= 0 ? a->next : a;
    b = c >= 0 ? b->next : b;
  }
  while(a) { // Si 'a' todavía tiene elementos
    r = aux_inters_diff(r, a->data, new_len);
    a = a->next;
  }
  // if(c > 0) {
  //   r = aux_inters_diff(r, a->data, new_len);
  // }
  return r;
}

ResNode *set_mod_diff(ResNode *dest, ResNode *other, int *new_len) {
  res_free(RAISE("Interno", S("No implementado")));
  return dest; // No puede devolver un `ResErrorN`
}

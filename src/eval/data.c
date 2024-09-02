#include "data.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ast/data.h"
#include "../ast/stmt.h"

#include "../global.h"
#include "../log.h"
#include "../str.h"

#include "error.h"

extern bool g_debug;
extern char *g_filename;
extern bool g_exiting;

static int compare_data_list(ResNode *a, ResNode *b);


int data_refcnt(ResNode *node) {
  if(!node) {
    print_error("Interno", "(%s) Intentando acceder a NULL->refcnt", __func__);
    return -1;
  }
  return ((ResDataN *)node)->refcnt;
}
char *data_str(ResNode *node) {
  if(!node) {
    print_error("Interno", "(%s) Intentando acceder a NULL->str", __func__);
    return NULL;
  }
  return ((ResDataN *)node)->str;
}
long data_int(ResNode *node) {
  if(!node) {
    print_error("Interno", "(%s) Intentando acceder a NULL->int", __func__);
    return 0;
  }
  return ((ResDataN *)node)->int_;
}
ResNode *data_elems(ResNode *node) {
  if(!node) {
    print_error("Interno", "(%s) Intentando acceder a NULL->elems", __func__);
    return NULL;
  }
  return ((ResDataN *)node)->elems;
}
int data_len(ResNode *node) {
  if(!node) {
    print_error("Interno", "(%s) Intentando acceder a NULL->len", __func__);
    return -1;
  }
  return ((ResDataN *)node)->len;
}
AstNode *data_fn(ResNode *node) {
  if(!node) {
    print_error("Interno", "(%s) Intentando acceder a NULL->fn", __func__);
    return NULL;
  }
  return ((ResDataN *)node)->fn;
}

// int data_mod_refcnt(ResNode *node, int add) {
//   int r = -1;
//   if(node) {
//     r = ((ResDataN *)node)->refcnt += add;
//   }
//   print_dbg("(%s) refcnt = %d", __func__, r);
//   return r;
// }

int  data_mod_refcnt(ResNode *node, int add) {
  int r = -1;
  if(!node) return r; // No es un error
  ResDataN *data = (ResDataN *)node;
  switch(data->type) {
    case SET_R: case LST_R: {
        ResNode *elem = data->elems;
        while(elem) {
          data_mod_refcnt(elem->data, add);
          elem = elem->next;
        }
      } // Fallthrough
    case UNDEF_R: case VOID_R: case INT_R: case STR_R: case FN_R:
      r = data->refcnt += add;
      break;
    case RES_LL:
      while(node) {
        data_mod_refcnt(node->data, add);
        node = node->next;
      } break;
    default:
      print_error("Interno", LOC_S"Nodo '%s' inválido", LOC, res_enum_str(data->type));
  }
  print_dbg("refcnt: %d (%p)", r, data);
  return r;
}

ResNode *res_new_void(void) {
  ResDataN *new = (ResDataN *)malloc(sizeof(ResDataN));
  if(!new) return out_of_mem(LOC);
  new->type = VOID_R;
  new->refcnt = 0;
  return (ResNode *)new;
}
ResNode *res_new_undef(void) {
  ResDataN *new = malloc(sizeof(ResDataN));
  if(!new) return out_of_mem(LOC);
  new->type = UNDEF_R;
  new->refcnt = 0;
  return (ResNode *)new;
}
ResNode *res_new_int(long value) {
  ResDataN *new = malloc(sizeof(ResDataN));
  if(!new) return out_of_mem(LOC);
  new->type = INT_R;
  new->refcnt = 0;
  new->int_ = value;
  return (ResNode *)new;
}
ResNode *res_new_str(char *value) {
  ResDataN *new = malloc(sizeof(ResDataN));
  if(!new) return out_of_mem(LOC);
  new->type = STR_R;
  new->refcnt = 0;
  new->str = str_dup(value);
  return (ResNode *)new;
}
ResNode *res_new_set(ResNode *elems, int len) {
  ResDataN *new = malloc(sizeof(ResDataN));
  if(!new) return out_of_mem(LOC);
  new->type = SET_R;
  new->refcnt = 0;
  new->elems = elems;
  new->len = len;
  return (ResNode *)new;
}
ResNode *res_new_lst(ResNode *elems, int len) {
  ResDataN *new = malloc(sizeof(ResDataN));
  if(!new) return out_of_mem(LOC);
  new->type = LST_R;
  new->refcnt = 0;
  new->elems = elems;
  new->len = len;
  return (ResNode *)new;
}

/**
 * Crea una referencia a una función. Básicamente es un "envoltorio" para el AST
 * de definición de la función.
*/
ResNode *res_new_fn(AstNode *fn_ast) {
  ResDataN *new = malloc(sizeof(ResDataN));
  if(!new) return out_of_mem(LOC);
  new->type = FN_R;
  new->refcnt = 0;
  // ¿Realmente es necesario hacer una copia? No, el AST completo se libera al
  // final, incluyendo el AST de la función. Al liberar FN_R se ignora ->fn
  new->fn = fn_ast;
  return (ResNode *)new;
}

bool res_is_data(ResNode *node) {
  if(node && UNDEF_R <= node->type && node->type <= FN_R) return true;
  else return false;
}

ResNode *eval_data(AstNode *node) {
  DBG_FN_START;
  NULL_RETURN(node, "Interno", S("node == NULL"));
  ResNode *new = NULL;
  int len = 0;
  switch(node->type) {
    case SET_AST:
      new = eval_set_elems(ast_data_elems(node), &len);
      if(new && new->type == EXIT_R) return new;
      if(!res_is_error(new)) new = res_new_set(new, len);
      break;
    case LST_AST:
      new = eval_expr_list(ast_data_elems(node), &len);
      if(new && new->type == EXIT_R) return new;
      if(!res_is_error(new)) new = res_new_lst(new, len);
      break;
    case INT_AST:
      new = res_new_int(ast_data_int(node));
      break;
    case STR_AST:
      new = res_new_str(ast_data_str(node));
      break;
    default:
      return RAISE("Interno", S("Nodo inválido"));
  }
  return MAYBE_ERROR(new);
}

void data_print_elems(ResNode *node_list, ResNode *container, bool quotes, bool comma) {
  // print_dbg("data_print_elems");
  if(!node_list) {
    // No es un error. Ej: el atributo elems de [] o {} es NULL
    // print_error("(data_print_elems) Argumento NULL");
    return;
  }
  while(node_list) {
    if(container && container == node_list->data) {
      // Referencia recursiva
      if(container->type == SET_R) printf("{...}");
      else printf("[...]");
    } else data_print(node_list->data, quotes);
    if(comma && node_list->next) printf(", ");
    node_list = node_list->next;
  }
}

void data_print(ResNode *node, bool quotes) {
  // print_dbg("data_print");
  if(!node) {
    print_error("Interno", "(%s) Argumento NULL", __func__);
    return;
  }
  ResDataN *data = (ResDataN *)node;
  switch(data->type) {
    case UNDEF_R:
      printf("Indefinido");
      break;
    case INT_R:
      printf("%ld", data->int_);
      break;
    case STR_R:
      if(quotes) {
        char quote = strchr(data->str, '\'') ? '"' : '\'';
        printf("%c%s%c", quote, data->str, quote);
      } else printf("%s", data->str);
      break;
    case SET_R:
      printf("{");
      data_print_elems(data->elems, node, true, true);
      printf("}");
      break;
    case LST_R:
      printf("[");
      data_print_elems(data->elems, node, true, true);
      printf("]");
      break;
    case FN_R:
      printf("Función: ");
      ast_print_fn(data->fn);
      break;
    case VOID_R:
      printf("Nulo");
      break;
    case ERROR_R:
      printf("ErrorNode");
      break;
    default:
      printf("(ResNodeT %d: %p)", data->type, (void *)data);
  }
}

int compare_data_list(ResNode *a, ResNode *b) {
  DBG_FN_START;
  int r = 0;
  // No es un error. Ej: el atributo elems de [] o {} es NULL
  if(a && !b) { r = 1; goto end; }
  if(!a && b) { r = -1; goto end; }
  if(!a && !b) goto end;

  if(a->type != RES_LL || b->type != RES_LL) { // ¿Es posible este caso?
    print_error(
      "Interno", "(compare_data_list) Algún parámetro no es lista de nodos"
    );
    goto end;
  }
  // Mientras ambos elementos sean iguales, comparar el siguiente par
  while(r == 0 && a && b) {
    r = data_compare(a->data, b->data);
    a = a->next;
    b = b->next;
  }
  if(a && !b) { r = 1; goto end; }
  if(!a && b) { r = -1; goto end; }

  end:
  // Se usa una variable de retorno para poder mostrarla al final
  print_dbg("(%s) r = %d", __func__, r);
  return r;
}

// a > b return > 0
// a < b return < 0
// a = b return = 0
int data_compare(ResNode *res_a, ResNode *res_b) {
  int r = 0;
  // Chequeo de nulos
  if(!res_a || !res_b) {
    print_error("Interno", "(%s) Algún parámetro es NULL", __func__);
    goto end;
  }
  if(!res_is_data(res_a) || !res_is_data(res_b)) {
    print_error("Interno", "(%s) Algún parámetro es inválido", __func__);
    goto end;
  }
  // ¿Son el mismo dato?
  if(res_a == res_b) { r = 0; goto end; }
  // Orden si el tipo es diferente
  r = (int)res_a->type - (int)res_b->type;
  if(r != 0) goto end;
  // Orden si son del mismo tipo
  switch(res_a->type) {
    case LST_R: case SET_R: // Si son iterables
      // Orden si el tamaño es diferente
      r = data_len(res_a) - data_len(res_b);
      if(r != 0) break;
      // Orden si el tamaño es igual (comparar lista de elementos)
      r = compare_data_list(data_elems(res_a), data_elems(res_b));
      break;
    case INT_R: // Si son elementos (enteros)
      r = data_int(res_a) - data_int(res_b);
      break;
    case STR_R: // Si son elementos (cadenas)
      r = strcmp(data_str(res_a), data_str(res_b));
      break;
    case VOID_R: case UNDEF_R: // Si es Void o Undef
      r = 0; // Void == Void e Undef == Undef
      break;
    default:
      // En este punto, el tipo es inválido
      print_error("Interno", "(%s) Nodo inválido", __func__);
  }

  end:
  // Se usa una variable de retorno para poder mostrarla al final
  if(g_debug) {
    printf("DEBUG: (%s) ", __func__);
    data_print(res_a, true);
    if(r == 0) printf(" == ");
    else if(r < 0) printf(" < ");
    else printf(" > ");
    data_print(res_b, true);
    printf("\n");
    fflush(stdout);
  }
  return r;
}

// Búsqueda lineal en una lista enlazada sin ordenar
int lst_search_elem(ResNode *elem, ResNode *lst) {
  if(!lst) return 0;
  ResNode *now = ((ResDataN *)lst)->elems;
  int r = 1;
  // Búsqueda lineal simple
  while(now && data_compare(now->data, elem) != 0) {
    now = now->next;
    r += 1;
  }
  if(r > ((ResDataN *)lst)->len) r = 0;
  // Se usa una variable de retorno para poder mostrarla al final
  print_dbg("(%s) r = %d", __func__, r);
  return r;
}

// Búsqueda lineal en una lista enlazada ordenada
int set_search_elem(ResNode *elem, ResNode *set) {
  DBG_FN_START;
  if(!set) return false;
  ResNode *now = ((ResDataN *)set)->elems;
  int c = -1;
  // Búsqueda lineal en lista enlazada ordenada (now->data < data)
  while(now && (c = data_compare(now->data, elem)) < 0) {
    now = now->next;
  }
  if(!c) return true;
  else return false;
}

// Insertar elemento en una lista enlazada ordenada.
bool set_insert_elem(ResNode *data, ResNode **elems) {
  DBG_FN_START;
  if(!data) return false;
  ResNode *new = res_new_ll_n(data);
  int cmp;
  // Si el primer elemento es nulo o es mayor al nuevo, insertar en primera
  // posición
  if(!(*elems) || (cmp = data_compare((*elems)->data, data)) > 0) {
    new->next = *elems;
    *elems = new;
    return true;
  }
  if(!cmp) goto free;
  // Buscar el nodo anterior a la posición de inserción
  ResNode *current = *elems;
  while(current->next && (cmp = data_compare(current->next->data, data)) < 0) {
    current = current->next;
  }
  if(!cmp) goto free;
  new->next = current->next;
  current->next = new;
  return true;

  free:
  print_dbg("(%s) Elemento repetido", __func__);
  new->data = NULL;
  res_free(new);
  return false;
}

/**
 * Nunca devuelve `NULL` ya que si se queda sin memoria usa `abort()`.
 *
 * @note Qué otras funciones nunca devuelven `NULL`? 🤔
 */
ResNode *lst_get_elem(int index, ResNode *lst) {
  NULL_RETURN(lst, "Interno", S("lst == NULL"));
  int len = data_len(lst);
  // Índices negativos se cuentan desde el último elemento
  if(index < 0) {
    index = len + index + 1;
  }
  if(index <= 0 || index > len) {
    return RAISE("Índice", str_fmt("Índice %d fuera del rango válido", index));
  }
  ResNode *now = data_elems(lst);
  int pos = 1;
  while(pos < index && now) {
    now = now->next;
    pos += 1;
  }
  NULL_RETURN(now, "Interno", S("now == NULL"));
  return now;
}

/**
 * Un `index` mayor al último índice equivale al último indice.
 *
 * `side` indica el lado de inserción respecto al elemento existente ubicado en
 * `index`.
 *
 * - `side == -1`: insertar a la izquierda del elemento en `index`. El nuevo
 *   elemento pasa a tener índice `index`.
 * - `side == 1`: insertar a la derecha del elemento en `index`. El nuevo
 *   elemento pasa a tener índice `index + 1`.
 */
ResNode *lst_insert_elem(ResNode *lst, int index, int side, ResNode *elem) {
  NULL_RETURN(lst, "Interno", S("lst == NULL"));
  ResDataN *data = (ResDataN *)lst;
  int len = data->len;
  // Índices negativos se cuentan desde el último elemento
  if(index < 0) index = len + index + 1;
  if(index <= 0) index = 1;
  if(index > len) index = len;
  ResNode *now = data->elems;
  ResNode *prev = NULL;
  int pos = 1;
  while(pos < index && now->next) {
    prev = now;
    now = now->next;
    pos += 1;
  }
  ResNode *new = res_new_ll_n(elem);
  if(side == -1) { // insertar en index
    new->next = now;
    // Si prev es NULL entonces se inserta al inicio
    if(!prev) data->elems = new;
    else prev->next = new;
  } else { // insertar a la derecha de index
    new->next = now->next;
    now->next = new;
  }
  data->len += 1;
  REF_INC(elem);
  return NULL;
}

ResNode *lst_del_index(ResNode *lst, int index) {
  DBG_FN_START;
  NULL_RETURN(lst, "Interno", S("lst == NULL"));
  ResDataN *data = (ResDataN *)lst;
  // Índices negativos se cuentan desde el último elemento
  if(index < 0) index = data->len + index + 1;
  if(index <= 0 || index > data->len)
    return RAISE("Índice", str_fmt("Índice %d fuera del rango válido", index));
  ResNode *now = data->elems;
  ResNode *prev = NULL;
  int pos = 1;
  while(pos < index && now) {
    prev = now;
    now = now->next;
    pos += 1;
  }
  if(!now)
    return RAISE("Interno", S("Lista con menos elementos de lo que debería"));
  if(prev) prev->next = now->next;
  else data->elems = now->next;
  data->len -= 1;
  REF_DEC(now->data);
  now->next = NULL; // Evita eliminar todo el resto de data->elems
  res_free(now);
  return NULL;
}

/**
 * Si se produce un error en alguna de las expresiones se detiene la evaluación,
 * se descarta la lista de nodos evaluados y se devuelve el error.
 */
ResNode *eval_set_elems(AstNode *ast_ll, int *len) {
  DBG_FN_START;
  NULL_RETURN(len, "Interno", S("len == NULL"));
  // El conjunto es vacío <=> ast_list_n == NULL
  if(!ast_ll) { *len = 0; return NULL; }
  // El primer elemento nunca está repetido
  ResNode *data = eval(ast_ll->data);
  NULL_RETURN(data, "Interno", S("data == NULL"));
  ERROR_RETURN(data);
  ResNode *rl = res_new_ll_n(data);
  (*len) += 1;
  while((ast_ll = ast_ll->next)) {
    data = eval(ast_ll->data);
    NULL_GOTO(data, data, "Interno", S("data == NULL"), discard);
    ERROR_GOTO(data, data, discard);
    // Si está repetido, liberar (no se inserta)
    if(!set_insert_elem(data, &rl)) { res_free(data); continue; }
    (*len) += 1;
  }
  return rl;
  discard:
  res_free(rl);
  return MAYBE_ERROR(data);
}

/**
 * Crea un dato completamente independiente del original.
*/
ResNode *data_copy(ResNode *node) {
  DBG_FN_START;
  if(!node) return NULL;

  if(node->type == RES_LL) { // Copiar dato y siguiente.
    ResNode *elem = res_new_ll_n(data_copy(node->data));
    elem->next = data_copy(node->next);
    return elem;
  }
  ResDataN *data = (ResDataN *)node;
  switch(node->type) {
    case INT_R:
      return res_new_int(data->int_);
      break;
    case STR_R:
      return res_new_str(data->str);
      break;
    case LST_R:
      return res_new_lst(data_copy(data->elems), data->len);
      break;
    case SET_R:
      return res_new_set(data_copy(data->elems), data->len);
      break;
    default:
      print_error("Interno", "(%s) No se puede copiar este tipo de dato", __func__);
      return NULL;
  }
}

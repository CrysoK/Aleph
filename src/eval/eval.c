#include "eval.h"

#include <stddef.h> // NULL
#include <stdlib.h>
#include <stdio.h>

#include "../global.h"
#include "../log.h"
#include "../str.h"
#include "data.h"
#include "expr.h"
#include "stmt.h"
#include "ifn.h"
#include "error.h"

extern bool g_debug;
extern bool g_exiting;
extern char *g_filename;

static void res_free_ll(ResNode *node);

char *res_enum_str(ResNodeT type) {
  switch(type) {
    case UNDEF_R: return "undef";
    case VOID_R: return "void";
    case INT_R: return "int";
    case STR_R: return "atom";
    case SET_R: return "set";
    case LST_R: return "list";
    case FN_R: return "fn";
    case RETURN_R: return "return";
    case BREAK_R: return "break";
    case CONTINUE_R: return "continue";
    case ERROR_R: return "error";
    case EXIT_R: return "exit";
    case RES_LL: return "ll";
    default: return "unknown";
  }
}

ResNode *res_new_ll_n(ResNode *data) {
  ResNode *new = (ResNode *)malloc(sizeof(ResNode));
  if(!new) return out_of_mem(LOC);
  new->type = RES_LL;
  new->data = data;
  new->next = NULL;
  return new;
}

ResNode *res_last_ll_n(ResNode *node) {
  if(!node) return NULL;
  while(node->next) {
    node = node->next;
  }
  return node;
}

bool res_is_ll(ResNode *node) {
  if(node && node->type == RES_LL) return true;
  else return false;
}

/**
 * La ventaja de hacerlo en una función diferente a `eval` es que puede devolver
 * la cantidad de nodos evaluados.
 *
 * Si se produce un error en alguna de las expresiones se detiene la evaluación,
 * se descarta la lista de nodos evaluados y se devuelve el error.
 */
ResNode *eval_expr_list(AstNode *ast_ll, int *counter) {
  DBG_FN_START;
  if(!ast_ll) { return NULL; } // No es un error
  ResNode *aux = eval(ast_ll->data);
  NULL_RETURN(aux, "Interno?", S("aux == NULL"));
  ERROR_RETURN(aux);
  ResNode *rl = res_new_ll_n(aux);
  if(counter) (*counter) += 1;
  ResNode *last = rl;
  while((ast_ll = ast_ll->next)) {
    aux = eval(ast_ll->data);
    NULL_GOTO(aux, aux, "Interno?", S("aux == NULL"), discard);
    ERROR_GOTO(aux, aux, discard);
    last->next = res_new_ll_n(aux);
    last = last->next;
    if(counter) (*counter) += 1;
  }
  return rl;

  discard:
  res_free(rl);
  return MAYBE_ERROR(aux);
}

/**
 * @note Para una lista de expresiones se deben conservar todos los resultados
 * mientras que para sentencias solo una interrupción o NULL.
 *
 * ~~Si se está en modo REPL se podrían mostrar los resultados de las sentencias
 * que son expresiones.~~ NO, porque tales expresiones se liberan una vez
 * terminado el bloque. La única forma de conservarlas es con `return`.
*/
ResNode *eval_stmt_list(AstNode *ast_node) {
  DBG_FN_START;
  NULL_RETURN(ast_node, "Interno", S("ast_node == NULL"));
  ResNode *last = eval(ast_node->data);
  while(!eval_stmt_list_stop(last) && (ast_node = ast_node->next)) {
    res_free(last);
    last = eval(ast_node->data);
  }
  if(eval_stmt_list_stop(last)) return MAYBE_ERROR(last);
  res_free(last);
  return NULL;
}

bool eval_stmt_list_stop(ResNode *stmt) {
  bool r = stmt && (
    stmt->type == BREAK_R || stmt->type == CONTINUE_R ||
    stmt->type == RETURN_R || stmt->type == ERROR_R || stmt->type == EXIT_R
  );
  print_dbg("(%s) %s", __func__, r ? "true" : "false");
  return r;
}

void garbage_collect(ResNode *res) {
  if(!res) return;
  if(res->type < UNDEF_R || res->type > FN_R) return;
  if(data_refcnt(res) > 0) return;
  if(g_debug) { printf("DEBUG GC: "); data_print(res, true); printf("\n"); }
  ResDataN *data = (ResDataN *)res;
  ResNode *elem = NULL;
  switch(res->type) {
    case UNDEF_R: case VOID_R:
      free(data); break;
    case INT_R:
      free(data);
      break;
    case STR_R:
      free(data->str);
      data->str = NULL;
      free(data);
      break;
    case SET_R: case LST_R:
      elem = data->elems;
      while(elem) {
        ResNode *next = elem->next;
        // REF_DEC(elem->data);
        garbage_collect(elem->data);
        elem->data = NULL;
        elem->next = NULL;
        free(elem);
        elem = next;
      }
      free(data);
      break;
    case FN_R:
      // ast_free se encarga de liberar data->fn al final de la ejecución
      free(data);
      break;
    default:
      print_error("Interno", "Inalcanzable (tipo %s)", res_enum_str(res->type));
  }
}

ResNode *eval(AstNode *ast_node) {
  // DBG_FN_START;
  if(!ast_node) return NULL; // No es un error
  ResNode *r = NULL;
  if(ast_is_data(ast_node)) {
    r = eval_data(ast_node);
  } else if(ast_is_expr(ast_node)) {
    r = eval_expr(ast_node);
  } else if(ast_is_stmt(ast_node)) {
    r = eval_stmt(ast_node);
  } else if(ast_is_sym(ast_node)) {
    r = eval_sym(ast_node);
  } else if(ast_is_ifn(ast_node)) {
    r = eval_ifn(ast_node);
  } else if(ast_is_ll(ast_node)) {
    if(ast_is_stmt(ast_node->data)) {
      r = eval_stmt_list(ast_node);
    } else {
      r = eval_expr_list(ast_node, NULL);
    }
  } else {
    return RAISE("Interno", S("Nodo inválido"));
  }
  return MAYBE_ERROR(r);
}

void res_free(ResNode *node) {
  print_dbg("(%s) %s", __func__, node ? res_enum_str(node->type) : "NULL");
  if(!node) return;
  switch(node->type) {
    case UNDEF_R: case VOID_R: case INT_R: case STR_R: case SET_R: case LST_R: case FN_R:
      garbage_collect(node); // depende de su refcnt
      break;
    case RETURN_R: garbage_collect(node->data); free(node); node = NULL; break;
    case BREAK_R: case CONTINUE_R: case EXIT_R: free(node); break;
    case ERROR_R: res_free_error(node); break;
    case RES_LL: res_free_ll(node); break;
  }
}

void res_free_ll(ResNode *node) {
  DBG_FN_START;
  while(node) {
    ResNode *next = node->next;
    res_free(node->data);
    node->data = NULL;
    node->next = NULL;
    free(node);
    node = next;
  }
}

// en bloques {if, while, for, fn} mostrar solo expresiones
void repl_eval(AstNode *node) {
  DBG_FN_START;
  ResNode *r = eval(node);
  if(!r) return;
  if(res_is_error(r)) goto end;
  bool list = r->type == RES_LL;
  ResNode *elem = r;
  while(elem) {
    ResNode *x = list ? elem->data : r;
    if(x->type != VOID_R && res_is_data(x)) {
      data_print(x, true);
      repl_print("\n");
    }
    elem = list ? elem->next : NULL;
  }
  end:
  res_free(r);
}

void file_eval(AstNode *node) {
  DBG_FN_START;
  ResNode *r = eval(node);
  res_free(r);
}

// void dbg_stmt(AstNode *expr_ast, AstNode *id_ast, bool eval_) {
//   if(!id_ast) return;
//   char *s = ((AstIdN *)id_ast)->str;
//   ResNode *r = NULL;

//   bool tmp = g_debug;
//   g_debug = false;
//   if(expr_ast && eval_) r = eval(expr_ast);
//   g_debug = tmp;

//   if(!expr_ast) {
//     // Info global
//     if(!strcmp(s, "sym_tab_size"))
//       print_dbg("g_sym_tab_size = %zu", g_sym_tab_size);
//     else if(!strcmp(s, "stack_depth"))
//       print_dbg("g_max_stack_depth = %zu", g_max_stack_depth);
//     else if(!strcmp(s, "scope"))
//       print_dbg("scope_reset = %d", g_symtab->curr_scope);
//     return;
//   }
//   // Info de una expresión
//   if(!strcmp(s, "refcnt"))
//     print_dbg("refcnt = %d", ((ResDataN *)r)->refcnt);
//   else if(!strcmp(s, "scope"))
//     print_dbg(
//       "scope = %d",
//       scope_get_sym(
//         ((AstIdN *)expr_ast)->str, ((AstIdN *)expr_ast)->hash
//       )->sym_scope
//     );
// }

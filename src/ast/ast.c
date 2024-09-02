#include "ast.h"

#include <stddef.h> // NULL
#include <stdlib.h>

#include "../global.h" // LOC_S, LOC
#include "../log.h"

#include "data.h"
#include "expr.h"
#include "stmt.h"
#include "ifn.h"
#include "id.h"

static AstNode *ast_copy(AstNode *node); // Eliminar?

char *ast_enum_str(AstNodeT type) {
  switch(type) {
    case INT_AST: return "INT";
    case STR_AST: return "STR";
    case SET_AST: return "SET";
    case LST_AST: return "LST";
    case OR_AST: return "OR";
    case AND_AST: return "AND";
    case EQUAL_AST: return "EQUAL";
    case LESS_AST: return "LESS";
    case IN_AST: return "IN";
    case ELEM_AST: return "ELEM";
    case ADD_AST: return "ADD";
    case SUB_AST: return "SUB";
    case MUL_AST: return "MUL";
    case DIV_AST: return "DIV";
    case CALL_AST: return "CALL";
    case NOT_AST: return "NOT";
    case NEG_AST: return "NEG";
    case LEN_AST: return "LEN";
    case EXPR_AST: return "EXPR";
    case DECL_AST: return "DECL";
    case ASSIGN_AST: return "ASSIGN";
    case INSERT_AST: return "INSERT";
    case RETURN_AST: return "RETURN";
    case DEL_AST: return "DEL";
    case BREAK_AST: return "BREAK";
    case CONTINUE_AST: return "CONTINUE";
    case EXIT_AST: return "EXIT";
    case IF_AST: return "IF";
    case WHILE_AST: return "WHILE";
    case FOR_AST: return "FOR";
    case FN_AST: return "FN";
    case ID_AST: return "SYM";
    case IFN_AST: return "IFN";
    case AST_LL: return "AST_LL";
    default: return "UNKNOWN";
  }
}

void ast_free(AstNode *node) {
  print_dbg("(%s) liberando %s", __func__, node ? ast_enum_str(node->type) : "NULL");
  if(!node) return;
  AstDataN *data = (AstDataN *)node;
  AstExprN *expr = (AstExprN *)node;
  AstStmtN *stmt = (AstStmtN *)node;
  AstIdN *id = (AstIdN *)node;
  AstIfnN *ifn = (AstIfnN *)node;
  switch(node->type) {
    case STR_AST:
      free(data->str); data->str = NULL;
      // fallthrough
    case INT_AST:
      free(data);
      break;
    case SET_AST: case LST_AST:
      ast_free(data->elems); data->elems = NULL;
      free(data);
      break;
    case OR_AST: case AND_AST: case EQUAL_AST: case LESS_AST: case IN_AST:
    case ELEM_AST: case ADD_AST: case SUB_AST: case MUL_AST: case DIV_AST:
    case CALL_AST:
      ast_free(expr->a); expr->a = NULL;
      ast_free(expr->b); expr->b = NULL;
      free(expr);
      break;
    case NOT_AST: case NEG_AST: case LEN_AST:
      ast_free(expr->x); expr->x = NULL;
      free(expr);
      break;
    case INSERT_AST: case IF_AST: case FOR_AST: case FN_AST:
      ast_free(stmt->c); stmt->c = NULL;
      // fallthrough
    case DECL_AST: case ASSIGN_AST: case WHILE_AST:
      ast_free(stmt->b); stmt->b = NULL;
      // fallthrough
    case EXPR_AST: case RETURN_AST: case DEL_AST:
      ast_free(stmt->a); stmt->a = NULL;
      // fallthrough
    case BREAK_AST: case CONTINUE_AST: case EXIT_AST:
      free(stmt);
      break;
    case ID_AST: free(id->str); free(id); break;
    case IFN_AST: free(ifn); break;
    case AST_LL:
      ast_free(node->data); node->data = NULL;
      ast_free(node->next); node->next = NULL;
      free(node);
      break;
    default:
      print_error(
        NULL, "Interno", "No se pudo liberar el tipo %s", ast_enum_str(node->type));
  }
}

bool ast_is_ll(AstNode *node) {
  if(node && node->type == AST_LL) return true;
  else return false;
}

bool ast_is_data(AstNode *node) {
  if(node && INT_AST <= node->type && node->type <= LST_AST) return true;
  else return false;
}

bool ast_is_expr(AstNode *node) {
  if(node && OR_AST <= node->type && node->type <= LEN_AST) return true;
  else return false;
}

bool ast_is_stmt(AstNode *node) {
  if(node && EXPR_AST <= node->type && node->type <= FN_AST) return true;
  else return false;
}

bool ast_is_sym(AstNode *node) {
  if(node && ID_AST == node->type) return true;
  else return false;
}

bool ast_is_ifn(AstNode *node) {
  if(node && IFN_AST == node->type) return true;
  else return false;
}

AstNode *ast_new_ll_n(AstNode *elem, YYLTYPE loc) {
  // Este nodo no puede tener un dato nulo
  if(!elem) return NULL;
  AstNode *new = malloc(sizeof(AstNode));
  if(!new) return out_of_mem(LOC);
  new->type = AST_LL;
  new->loc = loc;
  new->data = elem;
  new->next = NULL;
  return new;
}

AstNode *ast_add_next_ll_n(AstNode *node_list, AstNode *next) {
  if(!node_list) return next;
  if(node_list->type != AST_LL || (next && next->type != AST_LL)) {
    print_error("Interno", LOC_S"Nodo inválido", LOC);
    return NULL;
  }
  AstNode *last = ast_get_last_ll_n(node_list);
  if(next) last->next = next;
  return node_list;
}

AstNode *ast_get_last_ll_n(AstNode *node) {
  if(!node) return NULL;
  while(node->next) {
    node = node->next;
  }
  return node;
}

AstNode *ast_reverse_ll(AstNode *node_list) {
  // DBG_FN_START;
  if(!node_list) return NULL;
  if(node_list->type != AST_LL) {
    print_error("Interno", LOC_S"No es una lista", LOC);
    return NULL;
  }
  AstNode *next = NULL;
  while(node_list) {
    AstNode *temp = node_list->next;
    node_list->next = next;
    next = node_list;
    node_list = temp;
  }
  return next;
}

/**
 * Ejemplo:
 *
 *     ((((a)))) => (a), (a,b,((b,2))) => (a,b,(b,2))
 *
 * Si la lista tiene solo un elemento, lo devuelve y libera el nodo. Sino,
 * devuelve la lo pasado como argumento (de qué función es esto?)
 */
AstNode *ast_flatten_ll(AstNode *ast_list) {
  DBG_FN_START;
  AstNode *elem = ast_list;
  while(elem && elem->type == AST_LL && !elem->next) {
    AstNode *aux = elem->data;
    // free(sub_list);
    elem = aux;
  }
  return elem;
}

// AstNode *ast_copy(AstNode *node) {
//   print_dbg("(%s) copiando %s", __func__, node ? ast_enum_str(node->type) : "NULL");
//   if(!node) return NULL;
//   AstDataN *data = (AstDataN *)node;
//   AstExprN *expr = (AstExprN *)node;
//   AstStmtN *stmt = (AstStmtN *)node;
//   AstIdN *id = (AstIdN *)node;
//   switch(node->type) {
//     case INT_AST: return ast_new_int(data->int_);
//     case STR_AST: return ast_new_str(data->str);
//     case SET_AST: return ast_new_set(ast_copy(data->elems));
//     case LST_AST: return ast_new_lst(ast_copy(data->elems));
//     case OR_AST: return ast_new_or(ast_copy(expr->a), ast_copy(expr->b));
//     case AND_AST: return ast_new_and(ast_copy(expr->a), ast_copy(expr->b));
//     case EQUAL_AST: return ast_new_equal(ast_copy(expr->a), ast_copy(expr->b));
//     case LESS_AST: return ast_new_less(ast_copy(expr->a), ast_copy(expr->b));
//     case IN_AST: return ast_new_in(ast_copy(expr->a), ast_copy(expr->b));
//     case ELEM_AST: return ast_new_getelem(ast_copy(expr->a), ast_copy(expr->b));
//     case ADD_AST: return ast_new_add(ast_copy(expr->a), ast_copy(expr->b));
//     case SUB_AST: return ast_new_sub(ast_copy(expr->a), ast_copy(expr->b));
//     case MUL_AST: return ast_new_mul(ast_copy(expr->a), ast_copy(expr->b));
//     case DIV_AST: return ast_new_div(ast_copy(expr->a), ast_copy(expr->b));
//     case CALL_AST: return ast_new_fncall(ast_copy(expr->a), ast_copy(expr->b));
//     case NOT_AST: return  ast_new_not(ast_copy(expr->x));
//     case NEG_AST: return ast_new_neg(ast_copy(expr->x));
//     case LEN_AST: return ast_new_len(ast_copy(expr->x));
//     case EXPR_AST: return ast_new_exprst(ast_copy(stmt->a));
//     case DECL_AST: return ast_new_decl(ast_copy(stmt->a), ast_copy(stmt->b));
//     case ASSIGN_AST: return ast_new_assign(
//       ast_copy(stmt->a), stmt->t, ast_copy(stmt->b)
//     );
//     case INSERT_AST: return ast_new_insert(
//       ast_copy(stmt->a), ast_copy(stmt->c), stmt->side, ast_copy(stmt->b)
//     );
//     case RETURN_AST: return ast_new_return(ast_copy(stmt->a));
//     case DEL_AST: return ast_new_del(ast_copy(stmt->a));
//     case BREAK_AST: return ast_new_break();
//     case CONTINUE_AST: return ast_new_continue();
//     case EXIT_AST: return ast_new_exit();
//     case IF_AST: return ast_new_if(ast_copy(stmt->a), ast_copy(stmt->b), ast_copy(stmt->c));
//     case WHILE_AST: return ast_new_while(ast_copy(stmt->a), ast_copy(stmt->b));
//     case FOR_AST: return ast_new_for(ast_copy(stmt->a), ast_copy(stmt->b), ast_copy(stmt->c));
//     case FN_AST: return ast_new_fndef(ast_copy(stmt->a), ast_copy(stmt->b), ast_copy(stmt->c));
//     case ID_AST: return ast_new_id_copy(id->str, id->hash);
//     case AST_LL: { // Copiar dato y siguiente.
//         AstNode *elem = ast_new_ll_n(ast_copy(node->data));
//         elem->next = ast_copy(node->next);
//         return elem;
//       }
//     default: // IFN no debería copiarse (?)
//       print_error("Interno", "No se puede copiar el tipo %s", ast_enum_str(node->type));
//       return NULL;
//   }
// }

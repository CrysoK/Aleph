#include "expr.h"

#include <stdlib.h>

#include "../global.h"
#include "../log.h"

static AstExprN *ast_new_expr_n(AstNodeT type);

AstNode *ast_expr_x(AstNode *expr) {
  if(!expr) {
    print_error("Interno", "(%s) Intentando acceder a NULL->x", __func__);
    return NULL;
  }
  return ((AstExprN *)expr)->x;
}
AstNode *ast_expr_a(AstNode *expr) {
  if(!expr) {
    print_error("Interno", "(%s) Intentando acceder a NULL->a", __func__);
    return NULL;
  }
  return ((AstExprN *)expr)->a;
}
AstNode *ast_expr_b(AstNode *expr) {
  if(!expr) {
    print_error("Interno", "(%s) Intentando acceder a NULL->b", __func__);
    return NULL;
  }
  return ((AstExprN *)expr)->b;
}

AstExprN *ast_new_expr_n(AstNodeT type) {
  AstExprN *new = malloc(sizeof(AstExprN));
  if(!new) return out_of_mem(LOC);
  new->type = type;
  return new;
}

AstNode *ast_new_or(AstNode *a, AstNode *b) {
  AstExprN *new = ast_new_expr_n(OR_AST);
  new->a = a;
  new->b = b;
  return (AstNode *)new;
}

AstNode *ast_new_and(AstNode *a, AstNode *b) {
  AstExprN *new = ast_new_expr_n(AND_AST);
  new->a = a;
  new->b = b;
  return (AstNode *)new;
}

AstNode *ast_new_not(AstNode *a) {
  AstExprN *new = ast_new_expr_n(NOT_AST);
  new->x = a;
  return (AstNode *)new;
}

AstNode *ast_new_equal(AstNode *a, AstNode *b) {
  AstExprN *new = ast_new_expr_n(EQUAL_AST);
  new->a = a;
  new->b = b;
  return (AstNode *)new;
}

AstNode *ast_new_less(AstNode *a, AstNode *b) {
  AstExprN *new = ast_new_expr_n(LESS_AST);
  new->a = a;
  new->b = b;
  return (AstNode *)new;
}

AstNode *ast_new_in(AstNode *elem, AstNode *iter) {
  AstExprN *new = ast_new_expr_n(IN_AST);
  new->a = elem;
  new->b = iter;
  return (AstNode *)new;
}

AstNode *ast_new_add(AstNode *a, AstNode *b) {
  AstExprN *new = ast_new_expr_n(ADD_AST);
  new->a = a;
  new->b = b;
  return (AstNode *)new;
}

AstNode *ast_new_sub(AstNode *a, AstNode *b) {
  AstExprN *new = ast_new_expr_n(SUB_AST);
  new->a = a;
  new->b = b;
  return (AstNode *)new;
}

AstNode *ast_new_mul(AstNode *a, AstNode *b) {
  AstExprN *new = ast_new_expr_n(MUL_AST);
  new->a = a;
  new->b = b;
  return (AstNode *)new;
}

AstNode *ast_new_div(AstNode *a, AstNode *b) {
  AstExprN *new = ast_new_expr_n(DIV_AST);
  new->a = a;
  new->b = b;
  return (AstNode *)new;
}

AstNode *ast_new_neg(AstNode *a) {
  AstExprN *new = ast_new_expr_n(NEG_AST);
  new->x = a;
  return (AstNode *)new;
}

AstNode *ast_new_len(AstNode *a) {
  AstExprN *new = ast_new_expr_n(LEN_AST);
  new->x = a;
  return (AstNode *)new;
}

AstNode *ast_new_fncall(AstNode *symbol, AstNode *args) {
  AstExprN *new = ast_new_expr_n(CALL_AST);
  new->a = symbol;
  new->b = args;
  return (AstNode *)new;
}

AstNode *ast_new_getelem(AstNode *list, AstNode *index) {
  AstExprN *new = ast_new_expr_n(ELEM_AST);
  new->a = list;
  new->b = index;
  return (AstNode *)new;
}

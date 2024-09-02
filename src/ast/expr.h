#pragma once

#include "ast.h"

/// Nodo para expresiones
typedef struct s_ast_expr_n AstExprN;

struct s_ast_expr_n {
  AstNodeT type;
  union {
    AstNode *x; // Unarias, datos, símbolos
    struct { // Binarias
      AstNode *a;
      AstNode *b;
    };
  };
};

AstNode *ast_expr_x(AstNode *expr);
AstNode *ast_expr_a(AstNode *expr);
AstNode *ast_expr_b(AstNode *expr);

AstNode *ast_new_or(AstNode *a, AstNode *b);
AstNode *ast_new_and(AstNode *a, AstNode *b);
AstNode *ast_new_not(AstNode *a);
AstNode *ast_new_equal(AstNode *a, AstNode *b);
AstNode *ast_new_less(AstNode *a, AstNode *b);
AstNode *ast_new_in(AstNode *elem, AstNode *iter);
AstNode *ast_new_add(AstNode *a, AstNode *b);
AstNode *ast_new_sub(AstNode *a, AstNode *b);
AstNode *ast_new_mul(AstNode *a, AstNode *b);
AstNode *ast_new_div(AstNode *a, AstNode *b);
AstNode *ast_new_neg(AstNode *a);
AstNode *ast_new_len(AstNode *iter);
AstNode *ast_new_fncall(AstNode *symbol, AstNode *args);
AstNode *ast_new_getelem(AstNode *list, AstNode *index);

#pragma once

#include "ast.h"
#include "../eval/sym.h"

/// Nodo para sentencias
typedef struct s_ast_stmt_n AstStmtN;

struct s_ast_stmt_n {
  AstNodeT type;
  AstNode *a;
  AstNode *b;
  AstNode *c;
  union {
    AstNodeT t;
    int side;
  };
};

AstNode *ast_stmt_a(AstNode *stmt);
AstNode *ast_stmt_b(AstNode *stmt);
AstNode *ast_stmt_c(AstNode *stmt);
AstNodeT ast_stmt_t(AstNode *stmt);
int ast_stmt_side(AstNode *stmt);

AstNode *ast_new_exprst(AstNode *expr);
AstNode *ast_new_decl(AstNode *ids, AstNode *values);
AstNode *ast_new_assign(AstNode *ids, AstNodeT type, AstNode *values);
AstNode *ast_new_del(AstNode *targets);
AstNode *ast_new_insert(AstNode *list, AstNode *index, int side, AstNode *elem);
AstNode *ast_new_if(AstNode *cond, AstNode *then, AstNode *else_);
AstNode *ast_new_while(AstNode *cond, AstNode *stmts);
AstNode *ast_new_for(AstNode *id, AstNode *iterable, AstNode *stmts);
AstNode *ast_new_fndef(AstNode *id, AstNode *params, AstNode *stmts);
AstNode *ast_new_return(AstNode *expr);
AstNode *ast_new_break(void);
AstNode *ast_new_continue(void);
AstNode *ast_new_exit(void);

void ast_print_fn(AstNode *ast);

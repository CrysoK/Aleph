#include "stmt.h"

#include <stdlib.h>
#include <stdio.h>

#include "id.h"
#include "expr.h"
#include "../global.h"
#include "../log.h"

static AstStmtN *new_stmt_node(AstNodeT type);

AstNode *ast_stmt_a(AstNode *stmt) {
  if(!stmt) {
    print_error("Interno", "(%s) Intentando acceder a NULL->a", __func__);
    return NULL;
  }
  return ((AstStmtN *)stmt)->a;
}
AstNode *ast_stmt_b(AstNode *stmt) {
  if(!stmt) {
    print_error("Interno", "(%s) Intentando acceder a NULL->b", __func__);
    return NULL;
  }
  return ((AstStmtN *)stmt)->b;
}
AstNode *ast_stmt_c(AstNode *stmt) {
  if(!stmt) {
    print_error("Interno", "(%s) Intentando acceder a NULL->c", __func__);
    return NULL;
  }
  return ((AstStmtN *)stmt)->c;
}
AstNodeT ast_stmt_t(AstNode *stmt) {
  if(!stmt) {
    print_error("Interno", "(%s) Intentando acceder a NULL->t", __func__);
    return -1;
  }
  return ((AstStmtN *)stmt)->t;
}
int ast_stmt_side(AstNode *stmt) {
  if(!stmt) {
    print_error("Interno", "(%s) Intentando acceder a NULL->side", __func__);
    return 0;
  }
  return ((AstStmtN *)stmt)->side;
}

AstStmtN *new_stmt_node(AstNodeT type) {
  AstStmtN *new = malloc(sizeof(AstStmtN));
  if(!new) return out_of_mem(LOC);
  new->type = type;
  return new;
}

AstNode *ast_new_decl(AstNode *ids, AstNode *values) {
  AstStmtN *new = new_stmt_node(DECL_AST);
  new->a = ids;
  new->b = values;
  return (AstNode *)new;
}

AstNode *ast_new_assign(AstNode *ids, AstNodeT type, AstNode *values) {
  AstStmtN *new = new_stmt_node(ASSIGN_AST);
  new->a = ids;
  new->b = values;
  new->t = type;
  return (AstNode *)new;
  // if(type == ASSIGN_AST) return (AstNode *)new;
  // AstNode *val = values;
  // AstNode *id = ids;
  // while(val && id) {
  //   switch(type) {
  //     case ADD_AST:
  //       val->data = ast_new_add(id->data, val->data);
  //       break;
  //     case SUB_AST:
  //       val->data = ast_new_sub(id->data, val->data);
  //       break;
  //     case MUL_AST:
  //       val->data = ast_new_mul(id->data, val->data);
  //       break;
  //     case DIV_AST:
  //       val->data = ast_new_div(id->data, val->data);
  //       break;
  //     default:
  //       print_error("Fatal", LOC_S"Inalcanzable", LOC);
  //       abort();
  //   }
  //   id = id->next;
  //   val = val->next;
  // }
  // if(val || id) {
  //   yyerror("La cantidad de IDs y expresiones debe ser igual.");
  //   YYERROR;
  // }
}

AstNode *ast_new_insert(AstNode *list, AstNode *index, int side, AstNode *elem) {
  AstStmtN *new = new_stmt_node(INSERT_AST);
  new->a = list;
  new->c = index;
  new->b = elem;
  new->side = side; // 1 = derecha, -1 = izquierda
  return (AstNode *)new;
}

AstNode *ast_new_exprst(AstNode *targets) {
  AstStmtN *new = new_stmt_node(EXPR_AST);
  new->a = targets;
  return (AstNode *)new;
}

AstNode *ast_new_return(AstNode *targets) {
  AstStmtN *new = new_stmt_node(RETURN_AST);
  new->a = targets;
  return (AstNode *)new;
}

AstNode *ast_new_del(AstNode *targets) {
  AstStmtN *new = new_stmt_node(DEL_AST);
  new->a = targets;
  return (AstNode *)new;
}

AstNode *ast_new_break(void) {
  AstStmtN *new = new_stmt_node(BREAK_AST);
  return (AstNode *)new;
}

AstNode *ast_new_continue() {
  AstStmtN *new = new_stmt_node(CONTINUE_AST);
  return (AstNode *)new;
}

AstNode *ast_new_exit() {
  AstStmtN *new = new_stmt_node(EXIT_AST);
  return (AstNode *)new;
}

AstNode *ast_new_if(AstNode *cond, AstNode *then, AstNode *else_) {
  AstStmtN *new = new_stmt_node(IF_AST);
  new->a = cond;
  new->b = then;
  new->c = else_;
  return (AstNode *)new;
}

AstNode *ast_new_while(AstNode *cond, AstNode *stmts) {
  AstStmtN *new = new_stmt_node(WHILE_AST);
  new->a = cond;
  new->b = stmts;
  return (AstNode *)new;
}

AstNode *ast_new_for(AstNode *id, AstNode *iterable, AstNode *stmts) {
  AstStmtN *new = new_stmt_node(FOR_AST);
  new->a = id;
  new->b = iterable;
  new->c = stmts;
  return (AstNode *)new;
}

AstNode *ast_new_fndef(AstNode *id, AstNode *params, AstNode *stmts) {
  AstStmtN *new = new_stmt_node(FN_AST);
  new->a = id;
  new->b = params;
  new->c = stmts;
  return (AstNode *)new;
}

void ast_print_fn(AstNode *ast) {
  AstNode *sym = ast_stmt_a(ast);
  AstNode *params = ast_stmt_b(ast);

  printf("%s(", ast_id_str(sym));
  while(params) {
    printf("%s%s", ast_id_str(params->data), params->next ? ", " : "");
    params = params->next;
  }
  printf(")");
}

#include "data.h"

#include <stdlib.h>

#include "../global.h"
#include "../log.h"
#include "../str.h"

static AstDataN *ast_new_data_n(AstNodeT type);

char *ast_data_str(AstNode *data) {
  if(!data) {
    print_error("Interno", "(%s) Intentando acceder a NULL->str", __func__);
    return NULL;
  }
  return ((AstDataN *)data)->str;
}
long ast_data_int(AstNode *data) {
  if(!data) {
    print_error("Interno", "(%s) Intentando acceder a NULL->int_", __func__);
    return 0;
  }
  return ((AstDataN *)data)->int_;
}
AstNode *ast_data_elems(AstNode *data) {
  if(!data) {
    print_error("Interno", "(%s) Intentando acceder a NULL->elems", __func__);
    return NULL;
  }
  return ((AstDataN *)data)->elems;
}

AstDataN *ast_new_data_n(AstNodeT type) {
  AstDataN *new = malloc(sizeof(AstDataN));
  if(!new) return out_of_mem(LOC);
  new->type = type;
  return new;
}

AstNode *ast_new_int(long value) {
  AstDataN *new = ast_new_data_n(INT_AST);
  new->int_ = value;
  return (AstNode *)new;
}

AstNode *ast_new_str(char *value) {
  AstDataN *new = ast_new_data_n(STR_AST);
  new->str = str_dup(value);
  return (AstNode *)new;
}

AstNode *ast_new_set(AstNode *elems) {
  AstDataN *new = ast_new_data_n(SET_AST);
  new->elems = elems;
  return (AstNode *)new;
}

AstNode *ast_new_lst(AstNode *elems) {
  AstDataN *new = ast_new_data_n(LST_AST);
  new->elems = elems;
  return (AstNode *)new;
}

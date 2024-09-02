#pragma once

#include "ast.h"

/// Nodo para datos
typedef struct s_ast_data_n AstDataN;

struct s_ast_data_n {
  AstNodeT type;
  union {
    char *str;
    long int_;
    AstNode *elems;
  };
};

char *ast_data_str(AstNode *data);
long ast_data_int(AstNode *data);
AstNode *ast_data_elems(AstNode *data);

AstNode *ast_new_set(AstNode *elems);
AstNode *ast_new_lst(AstNode *elems);
AstNode *ast_new_str(char *value);
AstNode *ast_new_int(long value);

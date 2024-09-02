#pragma once

#include "ast.h"

/// Nodo para identificadores
typedef struct s_ast_id_n AstIdN;
struct s_ast_id_n {
  AstNodeT type;
  char *str;
  unsigned hash;
};

char *ast_id_str(AstNode *sym);
unsigned ast_id_hash(AstNode *sym);
AstNode *ast_new_id(char *id);
// utilidad para ast_copy
// AstNode *ast_new_id_copy(char *id, unsigned hash);

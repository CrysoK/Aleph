#pragma once

#include "ast.h"
#include "../eval/sym.h"

typedef enum e_ifn_t {
  CAST_SET_IFN,
  CAST_LST_IFN,
  CAST_INT_IFN,
  CAST_STR_IFN,
  REFCNT_IFN,
  TIME_IFN,
  ID_IFN,
  RANGE_IFN,
  COPY_IFN,
  TYPE_IFN,
  PRINTLN_IFN,
  PRINT_IFN
} InBuiltFnT;

/// Nodo especial para funciones integradas
typedef struct s_ast_ifn_n AstIfnN;

struct s_ast_ifn_n {
  AstNodeT type;
  InBuiltFnT ifn;
};

InBuiltFnT ast_ifn_type(AstNode *ifn);

AstNode *ast_new_ifn(InBuiltFnT ifn);

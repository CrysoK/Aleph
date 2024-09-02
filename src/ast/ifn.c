#include "ifn.h"

#include <stdlib.h>
#include "../global.h"
#include "../log.h"
#include "id.h"
#include "stmt.h"

static AstNode *ast_new_ifn_mark(InBuiltFnT ifn);

InBuiltFnT ast_ifn_type(AstNode *ifn) {
  if(!ifn) {
    print_error("Interno", "(%s) Intentando acceder a NULL->ifn", __func__);
    return -1;
  }
  return ((AstIfnN *)ifn)->ifn;
}

AstNode *ast_new_ifn(InBuiltFnT ifn) {
  AstNode *id = NULL;
  AstNode *params = NULL;
  YYLTYPE loc = (YYLTYPE) { 0, 0, 0, 0 };
  switch(ifn) {
    case PRINT_IFN:
      id = ast_new_id("print");
      params = ast_new_ll_n(ast_new_id("..."), loc);
      break;
    case PRINTLN_IFN:
      id = ast_new_id("println");
      params = ast_new_ll_n(ast_new_id("..."), loc);
      break;
    case TIME_IFN:
      id = ast_new_id("time");
      params = NULL;
      break;
    case ID_IFN:
      id = ast_new_id("id");
      params = ast_new_ll_n(ast_new_id("x"), loc);
      break;
    case RANGE_IFN:
      id = ast_new_id("range");
      params = ast_new_ll_n(ast_new_id("desde"), loc);
      AstNode *temp = params->next = ast_new_ll_n(ast_new_id("paso"), loc);
      temp->next = ast_new_ll_n(ast_new_id("hasta"), loc);
      break;
    case TYPE_IFN:
      id = ast_new_id("type");
      params = ast_new_ll_n(ast_new_id("x"), loc);
      break;
    case REFCNT_IFN:
      id = ast_new_id("refcnt");
      params = ast_new_ll_n(ast_new_id("x"), loc);
      break;
    case CAST_SET_IFN:
      id = ast_new_id("set");
      params = ast_new_ll_n(ast_new_id("x"), loc);
      break;
    case CAST_LST_IFN:
      id = ast_new_id("lst");
      params = ast_new_ll_n(ast_new_id("x"), loc);
      break;
    case CAST_INT_IFN:
      id = ast_new_id("int");
      params = ast_new_ll_n(ast_new_id("x"), loc);
      break;
    case CAST_STR_IFN:
      id = ast_new_id("str");
      params = ast_new_ll_n(ast_new_id("x"), loc);
      break;
    case COPY_IFN:
      id = ast_new_id("copy");
      params = ast_new_ll_n(ast_new_id("x"), loc);
      break;
    default:
      print_error("Interno", "(%s) Nodo inválido", __func__);
  }
  return ast_new_fndef(id, params, ast_new_ifn_mark(ifn));
}

AstNode *ast_new_ifn_mark(InBuiltFnT ifn) {
  AstIfnN *new = malloc(sizeof(AstIfnN));
  if(!new) return out_of_mem(LOC);
  new->type = IFN_AST;
  new->ifn = ifn;
  return (AstNode *)new;
}

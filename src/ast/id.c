#include "id.h"

#include <stdlib.h>

#include "../global.h"
#include "../log.h"
#include "../str.h"

char *ast_id_str(AstNode *id) {
  if(!id) {
    print_error("Interno", "(%s) Intentando acceder a NULL->str", __func__);
    return NULL;
  }
  return ((AstIdN *)id)->str;
}
unsigned ast_id_hash(AstNode *id) {
  if(!id) {
    print_error("Interno", "(%s) Intentando acceder a NULL->hash", __func__);
    return 0;
  }
  return ((AstIdN *)id)->hash;
}

AstNode *ast_new_id(char *id) {
  AstIdN *new = malloc(sizeof(AstIdN));
  if(!new) return out_of_mem(LOC);
  new->type = ID_AST;
  new->str = str_dup(id);
  new->hash = str_hash(id);
  return (AstNode *)new;
}

// AstNode *ast_new_sym_copy(char *id, unsigned hash) {
//   AstIdN *new = malloc(sizeof(AstIdN));
//   if(!new) return out_of_mem(LOC);
//   new->type = ID_AST;
//   new->str = str_dup(str);
//   new->hash = hash;
//   return (AstNode *)new;
// }

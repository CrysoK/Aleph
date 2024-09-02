#include "error.h"

#include <stdio.h> // fprintf, stderr
#include <stdlib.h>

#include "../global.h"
#include "../log.h"

extern bool g_err_loc;

static ResNode *new_error_node(void);
static int res_error_depth(ResNode *node, int sum);

ResNode *new_error_node(void) {
  ResErrorN *new = (ResErrorN *)malloc(sizeof(ResErrorN));
  if(!new) return out_of_mem(LOC);
  new->type = ERROR_R;
  return (ResNode *)new;
}

void res_free_error(ResNode *node) {
  DBG_FN_START;
  free(node);
}

bool res_is_error(ResNode *node) {
  return (node && (node->type == ERROR_R || node->type == EXIT_R));
  // `exit` se trata como un error (sin mensajes) para aprovechar el manejo de
  // errores existente.
}

/**
 * Que `msg` sea dinámica permite omitir la liberación en la función
 * invocadora y hacerla aquí. Esto para lograr líneas como:
 *
 *   res_raise_error("Algún tipo", S("Alguna descripción"), LOC);
 */
ResNode *res_raise_error(char *type, char *msg, char *file, int ln, const char *fn) {
  print_error(type, "%s", msg);
  if(g_err_loc) fprintf(stderr, "Traza: %s (%s:%d)\n", fn, file, ln);
  free(msg);
  return new_error_node();
}
/**
 * Esta función permite añadir detalles a la traza si `r` es un error.
 * Facilitando la escritura de returns.
 */
ResNode *res_continue_error(ResNode *r, char *file, int ln, const char *fn) {
  if(!r || r->type != ERROR_R) return r;
  if(g_err_loc) fprintf(stderr, "       %s (%s:%d)\n", fn, file, ln);
  return r;
}

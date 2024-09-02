#include "log.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h> // Manejo de número de argumentos/parámetros variable

#include "global.h"
#include "ast/ast.h"

// https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
#define RED "\x1b[0;31m"
#define BLU "\x1b[0;34m"
#define BRED "\x1b[1;31m"
#define URED "\x1b[4;31m"
#define RESET "\x1b[0m"

extern bool g_exiting;
extern bool g_repl;
extern bool g_debug;
extern bool g_color;
int g_debug_padding = -2; // Para que `main` sea 0

extern char *g_filename;

extern int g_scope;

extern int yynerrs; // Cantidad de errores de sintaxis en Bison

#ifdef __GNUC__
#ifndef __clang__
__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site) {
  g_debug_padding++;
}
__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site) {
  g_debug_padding--;
}
#endif
#endif

static void v_print_error(
  const char *prefix, const char *type, const char *fmt, va_list args
);

void *out_of_mem(char* file, int ln, const char *fn) {
  print_error("Fatal", LOC_S"Memoria insuficiente", file, ln, fn);
  abort();
}

void v_print_error(
  const char *prefix, const char *type, const char *fmt, va_list args
) {
  if(g_color) fprintf(stderr, URED"%s"RESET, prefix);
  else fprintf(stderr, "%s", prefix);
  if(type) fprintf(stderr, " [%s]", type);
  if(!g_repl)
    fprintf(stderr, " (%s:%d:%d)", g_filename,
    g_prev_loc.first_line, g_prev_loc.first_column);
  else if(g_prev_loc.first_column > 0)
    fprintf(stderr, " (col %d)", g_prev_loc.first_column);
  if(type) fprintf(stderr, ": ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
}

void yyerror(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  v_print_error("ERROR", "Sintaxis", fmt, ap);
  // Bison se encarga de incrementar yynerrs cuando llama yyerror
  va_end(ap);
}

void print_error(char *type, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  v_print_error("ERROR", type, fmt, ap);
  yynerrs += 1;
  va_end(ap);
}

void print_dbg(char *fmt, ...) {
  if(!g_debug) return;
  va_list ap;
  va_start(ap, fmt);
  if(g_color) fprintf(stdout, BLU"DEBUG"RESET);
  else fprintf(stdout, "DEBUG");
  if(!g_repl)
    fprintf(stdout, " (%s:%02d:%02d)", g_filename,
    g_prev_loc.first_line, g_prev_loc.first_column);
  fprintf(stdout, ": %*s", g_debug_padding, "");
  // fprintf(stdout, ": %*s%d", g_debug_padding, "", g_debug_padding);
  vfprintf(stdout, fmt, ap);
  fprintf(stdout, "\n");
  fflush(stdout);
  va_end(ap);
}

void repl_print(char *fmt, ...) {
  if(!g_repl) return;
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stdout, fmt, ap);
  va_end(ap);
}

void repl_prompt(void) {
  if(!g_repl || g_exiting) return;
  if(g_scope) printf("... ");
  else printf(">>> ");
}

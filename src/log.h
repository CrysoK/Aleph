#pragma once

extern int g_debug_padding;

// Imprime mensajes de error de sintaxis (usado por Bison)
// NO usar directamente, usar 'print_error'
void yyerror(const char *fmt, ...);

void print_error(char *type, char *fmt, ...); // Imprime mensajes de error
void print_dbg(char *fmt, ...); // Imprime mensajes para debugging

void repl_print(char *fmt, ...); // Imprime mensajes solo en modo REPL
void repl_prompt(void); // >>> o ...

// Imprime un mensaje si no se puede reservar memoria y aborta la ejecución
void *out_of_mem(char* file, int ln, const char *fn);

#define DBG_FN_START print_dbg("(%s)", __func__)

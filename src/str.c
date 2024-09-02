/**
 * @file
 * @brief Implementación de utilidades para el manejo de cadenas.
*/

#include "str.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h> // snprintf
#include <stdarg.h>

#include "global.h"
#include "log.h"

/**
 * @brief Elimina las comillas de una cadena.
 * @param src La cadena fuente con comillas.
 * @return Un puntero a la nueva cadena sin comillas.
*/
static char *no_quotes(char *src);

char *str_dup(const char *src) {
  char *dst = malloc(strlen(src) + 1); // Espacio para la cadena y '\0'
  if(dst == NULL) return out_of_mem(LOC);
  strcpy(dst, src);
  return dst;
}

/// @todo No usada. Eliminar?
char *str_dup_no_quotes(const char *src) {
  int len = strlen(src);
  char *dst = malloc(len - 1);
  if(!dst) return out_of_mem(LOC);
  strncpy(dst, &src[1], len - 2);
  dst[len - 2] = '\0';
  return dst;
}

char *no_quotes(char *src) {
  int len = strlen(src);
  char *dst = malloc(len - 1);
  if(!dst) return out_of_mem(LOC);
  strncpy(dst, &src[1], len - 2);
  dst[len - 2] = '\0';
  free(src);
  return dst;
}

char *str_concat(char *source, const char *concat) {
  int len_a = strlen(source);
  int len_b = strlen(concat);
  int new_len = len_a + len_b;
  char *new = realloc(source, new_len + 1);
  if(new == NULL) return NULL;
  char *temp = new;
  new += len_a;
  while((*new++ = *concat++));
  return temp;
}

char *str_fmt(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  va_list aux;
  va_copy(aux, args);
  int len = vsnprintf(NULL, 0, fmt, aux);
  va_end(aux);
  char *str = malloc(len + 1);
  if(!str) return out_of_mem(LOC);
  vsnprintf(str, len + 1, fmt, args);
  va_end(args);
  return str;
}

unsigned str_hash(char * str) {
  unsigned hash = 0;
  unsigned c;

  while((c = *str++)) hash = hash * 9 ^ c;

  return hash;
}

/**
 * @file
 * Declaraciones para el manejo de errores en la evaluación.
*/
#pragma once

#include "eval.h"

/// Nodo para errores durante la evaluación.
typedef struct s_error_n {
  ResNodeT type;
} ResErrorN;

/**
 * @brief Libera la memoria de un nodo de error.
 * @param node Puntero al nodo de error
 */
void res_free_error(ResNode *node);
/**
 * @brief Crea un nuevo error y muestra un mensaje asociado.
 * @param type Tipo de error
 * @param msg Descripción del error. La cadena debe ser dinámica.
 * @param file (debug) Nombre del archivo donde se invoca
 * @param ln (debug) Número de la línea en que se invoca
 * @param fn (debug) Nombre de la función en la que se invoca
 * @return El nuevo error
 */
ResNode *res_raise_error(char *type, char *msg, char *file, int ln, const char *fn);
/**
 * @brief "Continúa" un error y añade información a la traza.
 * @param r Resultado que podría ser un error
 * @param file (debug) Nombre del archivo donde se invoca
 * @param ln (debug) Número de la línea en que se invoca
 * @param fn (debug) Nombre de la función en la que se invoca
 * @return `r`
 */
ResNode *res_continue_error(ResNode *r, char *file, int ln, const char *fn);
/**
 * @brief Comprueba si un nodo resultado es un error.
 * @param node Puntero al nodo
 */
bool res_is_error(ResNode *node);

// Macros útiles ///////////////////////////////////////////////////////////////

/// Llama a `res_continue_error` con los datos necesarios para la traza.
#define MAYBE_ERROR(res) res_continue_error(res, LOC)
/// Llama a `res_raise_error` con los datos necesarios para la traza.
#define RAISE(type, msg) res_raise_error(type, msg, LOC)
/// Si `res` es `NULL` entonces devuelve un error.
#define NULL_RETURN(res, type, msg) if(!(res)) return RAISE(type, msg)
/// Si `res` es un error entonces aborta la evaluación.
#define ERROR_RETURN(res) if(res_is_error(res)) return MAYBE_ERROR(res)
/// Si `res` es `NULL`, asigna un error a `ret` y salta a `tag`.
#define NULL_GOTO(res, ret, type, msg, tag) do { \
  if(!(res)) { (ret) = RAISE(type, msg); goto tag; } \
} while(0)
/// Si `res` es un error, lo "continúa" en `ret` y salta a `tag`.
#define ERROR_GOTO(res, ret, tag) do { \
  if(res_is_error(res)) { (ret) = MAYBE_ERROR(res); goto tag; } \
} while(0)

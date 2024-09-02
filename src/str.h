#pragma once

/**
 * @file
 * @brief Utilidades para el manejo de cadenas.
*/

/**
 * @brief Duplica una cadena de caracteres.
 * @param source La cadena fuente a duplicar.
 * @return Un puntero a la nueva cadena duplicada.
*/
char *str_dup(const char *source);
/**
 * @brief Duplica una cadena de caracteres eliminando las comillas iniciales y
 * finales.
 * @param source La cadena fuente a duplicar (con comillas).
 * @return Un puntero a la nueva cadena duplicada sin comillas.
*/
char *str_dup_no_quotes(const char *source);
/**
 * @brief Concatena dos cadenas de caracteres.
 * @param a La cadena inicial.
 * @param b La cadena a concatenar.
 * @return Un puntero a la nueva cadena concatenada.
 */
char *str_concat(char *a, const char *b);
/**
 * @brief Formatea una cadena según el formato especificado.
 * @param fmt La cadena de formato.
 * @param ... Argumentos variables para el formato.
 * @return Un puntero a la nueva cadena formateada.
 */
char *str_fmt(const char *fmt, ...);
/**
 * @brief Calcula el hash de una cadena de caracteres.
 * @param str La cadena de entrada.
 * @return El valor hash calculado.
 */
unsigned str_hash(char *str);

/**
 * @brief Macro para crear cadenas dinámicas a partir de constantes.
 * @param str Cadena constante o literal.
 */
#define S(str) (str_dup(str))

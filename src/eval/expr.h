/**
 * @file
 * @brief Declaraciones para la evaluación de expresiones.
 */
#pragma once

#include "eval.h"

 // Evaluación //////////////////////////////////////////////////////////////////

ResNode *eval_expr(AstNode *node);

ResNode *eval_unary(AstNode *node);

ResNode *eval_or(AstNode *node);
ResNode *eval_and(AstNode *node);
ResNode *eval_equal(AstNode *node);
ResNode *eval_less(AstNode *node);
ResNode *eval_in(AstNode *node);
ResNode *eval_elem(AstNode *node);
ResNode *eval_add(AstNode *node);
ResNode *eval_sub(AstNode *node);
ResNode *eval_mul(AstNode *node);
ResNode *eval_div(AstNode *node);
ResNode *eval_fncall(AstNode *node);

// Operaciones /////////////////////////////////////////////////////////////////

/**
 * @brief Concatena dos listas en una nueva lista.
 * @param a Primer elemento de una lista.
 * @param b Primer elemento de otra lista.
 * @return Primer elemento de la nueva lista o `NULL`.
 */
ResNode *lst_new_concat(ResNode *a, ResNode *b);
/**
 * @brief Concatena dos listas modificando la primera.
 * @param a Primer elemento de la primera lista.
 * @param b Primer elemento de la segunda lista.
 * @return Primer elemento de la primera lista modificada o `NULL`.
 */
ResNode *lst_mod_concat(ResNode *a, ResNode *b);
/**
 * @brief Unión de dos conjuntos en un nuevo conjunto.
 * @param a Primer elemento de un conjunto.
 * @param b Primer elemento de otro conjunto.
 * @param new_len Tamaño del nuevo conjunto.
 * @return Primer elemento de un nuevo conjunto o `NULL`.
 */
ResNode *set_new_union(ResNode *a, ResNode *b, int *new_len);
/**
 * @brief Unión de dos conjuntos, modificando el primero.
 * @param a Primer elemento del primer conjunto.
 * @param b Primer elemento del segundo conjunto.
 * @param new_len Tamaño del primer conjunto modificado.
 * @return Primer elemento del primer conjunto modificado o `NULL`.
 */
ResNode *set_mod_union(ResNode *a, ResNode *b, int *new_len);
/**
 * @brief Intersección de dos conjuntos en un nuevo conjunto.
 * @param a Primer elemento de un conjunto.
 * @param b Primer elemento de otro conjunto.
 * @param new_len Tamaño del nuevo conjunto.
 * @return Primer elemento de un nuevo conjunto o `NULL`.
 */
ResNode *set_new_inters(ResNode *a, ResNode *b, int *new_len);
/**
 * @brief Intersección de dos conjuntos, modificando el primero.
 * @param a Primer elemento del primer conjunto.
 * @param b Primer elemento del segundo conjunto.
 * @param new_len Tamaño del primer conjunto modificado.
 * @return Primer elemento del primer conjunto modificado o `NULL`.
 * @todo Implementar.
 */
ResNode *set_mod_inters(ResNode *dest, ResNode *other, int *new_len);
/**
 * @brief Diferencia de dos conjuntos en un nuevo conjunto.
 * @param a Primer elemento de un conjunto.
 * @param b Primer elemento de otro conjunto.
 * @param new_len Tamaño del nuevo conjunto.
 * @return Primer elemento de un nuevo conjunto o `NULL`.
 */
ResNode *set_new_diff(ResNode *a, ResNode *b, int *new_len);
/**
 * @brief Diferencia de dos conjuntos, modificando el primero.
 * @param a Primer elemento del primer conjunto.
 * @param b Primer elemento del segundo conjunto.
 * @param new_len Tamaño del primer conjunto modificado.
 * @return Primer elemento del primer conjunto modificado o `NULL`.
 * @todo Implementar.
 */
ResNode *set_mod_diff(ResNode *dest, ResNode *other, int *new_len);
/**
 * @brief Convierte un resultado en un valor lógico.
 * @param node Valor a convertir.
 * @return `true` o `false`.
 */
bool bool_cast(ResNode *node);

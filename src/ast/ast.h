#pragma once

/**
 * @file
 * Especificación del nodo genérico del AST y sus operaciones.
*/

#include <stdbool.h>
#include "../bison/loc.h"

/**
 * Tipos de nodos del AST
 *
 * @warning No confundir el tipo #AST_LL (para listas del AST) con el tipo
 * #LST_AST (para listas de Aleph).
*/
typedef enum e_ast_node_t {
  // AstDataN //////////////////////////////////////////////////////////////////
  INT_AST, ///< Nodo para enteros
  STR_AST, ///< Nodo para átomos
  SET_AST, ///< Nodo para conjuntos
  LST_AST, ///< Nodo para listas
  // AstExprN //////////////////////////////////////////////////////////////////
  // left x right
  OR_AST, ///< Nodo para `or`
  AND_AST, ///< Nodo para `and`
  EQUAL_AST, ///< Nodo para `==`
  LESS_AST, ///< Nodo para `<`
  IN_AST, ///< Nodo para `in`
  ELEM_AST, ///< Nodo para `[]`
  ADD_AST, ///< Nodo para `+`
  SUB_AST, ///< Nodo para `-`
  MUL_AST, ///< Nodo para `*`
  DIV_AST, ///< Nodo para `/`
  // id x expr
  CALL_AST, ///< Nodo para llamadas
  // x expr
  NOT_AST, ///< Nodo para `not`
  NEG_AST, ///< Nodo para `-` (unario)
  LEN_AST, ///< Nodo para `len`
  // AstStmtN //////////////////////////////////////////////////////////////////
  EXPR_AST, ///< Nodo para expresiones
  DECL_AST, ///< Nodo para declaraciones
  ASSIGN_AST, ///< Nodo para asignaciones
  INSERT_AST, ///< Nodo para inserción
  RETURN_AST, ///< Nodo para `return`
  DEL_AST, ///< Nodo para `del`
  BREAK_AST, ///< Nodo para `break`
  CONTINUE_AST, ///< Nodo para `continue`
  EXIT_AST, ///< Nodo para `exit`
  IF_AST, ///< Nodo para `if`
  WHILE_AST, ///< Nodo para `while`
  FOR_AST, ///< Nodo para `for`
  FN_AST, ///< Nodo para `fn`
  // AstIdN ///////////////////////////////////////////////////////////////////
  ID_AST, ///< Nodo para identificadores
  // AstIfnN ///////////////////////////////////////////////////////////////////
  IFN_AST, ///< Nodo para *in-built functions*
  // AstNode ///////////////////////////////////////////////////////////////////
  AST_LL, ///< Nodo para listas del AST.
} AstNodeT;
/**
 * Nodo genérico del AST.
 *
 * También es usado para listas de nodos del AST. Todos los nodos del AST tienen
 * un campo #type.
 */
typedef struct s_ast_n AstNode;
struct s_ast_n {
  AstNodeT type; ///< Determina qué otros campos tiene el nodo.
  YYLTYPE loc; ///< Ubicación en el código.
  AstNode *next; ///< Siguiente nodo (si es #AST_LL).
  AstNode *data; ///< Contenido del nodo (si es #AST_LL).
};

char *ast_enum_str(AstNodeT type);
void ast_free(AstNode *node);
/**
 * Crea un nodo que puede ser enlazado para formar listas.
 *
 * @param elem Dato del nodo No puede ser `NULL`.
 * @param loc Ubicación en el código.
 * @return Puntero al nuevo nodo. `NULL` en caso de error.
 */
AstNode *ast_new_ll_n(AstNode *elem, YYLTYPE loc);
/// Enlazar elemento (puede ser un nodo de lista) a un nodo de lista
AstNode *ast_add_next_ll_n(AstNode *node_list, AstNode *elem);
/// Devuelve el último nodo de una lista de nodos
AstNode *ast_get_last_ll_n(AstNode *node_list);
/// Invierte el orden de una lista de nodos
AstNode *ast_reverse_ll(AstNode *node_list);
/**
 * @brief Extrae el elemento de sub-listas con un único elemento (devuelve una
 * lista), eliminando anidamiento innecesario.
 */
AstNode *ast_flatten_ll(AstNode *ast_list);
/// ¿Es un nodo que puede enlazarse para formar listas?
bool ast_is_ll(AstNode *node);
bool ast_is_data(AstNode *node);
bool ast_is_expr(AstNode *node);
bool ast_is_stmt(AstNode *node);
bool ast_is_sym(AstNode *node);
bool ast_is_ifn(AstNode *node);

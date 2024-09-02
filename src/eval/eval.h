#pragma once

#include "../ast/ast.h"

typedef enum e_res_node_t {
  // Datos /////////////////////////////////////////////////////////////////////

  /// @warning El orden de estos tipos afecta el orden en conjuntos.

  UNDEF_R, // Se usa como marca en variables declaradas pero no inicializadas.
  VOID_R, // Valor devuelto por una función sin return o con return vacío.
  INT_R, // Enteros
  STR_R, // Cadenas
  SET_R, // Conjuntos
  LST_R, // Listas
  FN_R, // Funciones

  // Interrupciones ////////////////////////////////////////////////////////////

  // Detener la ejecución (funciones)
  RETURN_R,
  // Detener la ejecución (for/while).
  BREAK_R,
  // Omitir el resto del bloque y pasar a la siguiente iteración (for/while).
  CONTINUE_R,
  // Error durante la ejecución
  ERROR_R,
  // Detener la ejecución del programa
  EXIT_R,

  RES_LL // Nodo para listas de resultados
} ResNodeT;

typedef struct s_res_n ResNode;

struct s_res_n {
  ResNodeT type;
  ResNode *data;
  ResNode *next;
};

char *res_enum_str(ResNodeT type);

ResNode *res_new_ll_n(ResNode *data);
ResNode *res_last_ll_n(ResNode *node);

bool res_is_ll(ResNode *node);

// Libera un resultado
void res_free(ResNode *node);

// Todas las funciones eval deben devolver un dato completamente evaluado (o
// lista de datos). Un stmt podría devolver nada. Un symbol podría estar
// indefinido.
ResNode *eval(AstNode *node);
// NOTE: Realmente no devuelve un dato, sino una lista de resultados que puede
// contener uno o más datos. ¿Por qué? Esto está especialmente pensado para el
// modo REPL (¿hacer dos evals?). Cuando el usuario escribe un bloque (ya sea
// una función, un if, etc.) se deben mostrar el resultado de la evaluación de
// cada ExprStmt. Inspirado en la evaluación de Python.
// Sería más sencillo devolver directamente un dato o una interrupción.


/**
 * Evalúa una lista de nodos AST de expresiones.
 *
 * @param ast_ll Nodo inicial de la lista a evaluar.
 * @param counter Puntero al contador de nodos evaluados.
 * @return Lista de nodos resultado.
*/
ResNode *eval_expr_list(AstNode *ast_ll, int *counter);
/**
 * Evalúa una lista de nodos AST de sentencias.
 *
 * @param ast_ll Nodo inicial de la lista a evaluar.
 * @return `NULL` o una interrupción.
 */
ResNode *eval_stmt_list(AstNode *ast_ll);
bool eval_stmt_list_stop(ResNode *stmt);

void repl_eval(AstNode *node); // Eval para el "modo REPL"
void file_eval(AstNode *node); // Eval para el "modo archivo"

// Enlazar elemento (puede ser un nodo de lista) a un nodo de lista
// AstNode *add_next_res_n(ResNode *node_list, ResNode *data);
// Devuelve el último nodo de una lista de nodos
// AstNode *res_last_ll_n(ResNode *node_list);

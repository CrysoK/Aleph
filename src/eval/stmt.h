/**
 * @file
 * @brief Declaraciones para la evaluación de sentencias.
*/
#pragma once

#include "eval.h"

// Interrupciones //////////////////////////////////////////////////////////////

ResNode *res_new_return(ResNode *value);
ResNode *res_new_break(void);
ResNode *res_new_continue(void);
ResNode *res_new_exit(void);

// Evaluación //////////////////////////////////////////////////////////////////

ResNode *eval_stmt(AstNode *node);

ResNode *eval_decl(AstNode *decl_ast);
ResNode *eval_del(AstNode *del_ast);
/**
 * @brief Evalúa una asignación.
 * @param assign_ast AST de la asignación.
 * @return `NULL` o `ResErrorN`.
 */
ResNode *eval_assign(AstNode *assign_ast);
ResNode *eval_insert(AstNode *insert_ast);
/**
 * @brief Evalúa la sentencia `if`.
 * @param if_ast AST de la sentencia `if`.
 * @return `NULL`, `ResErrorN` o alguna interrupción.
 */
ResNode *eval_if(AstNode *if_ast);
/**
 * @brief Evalúa la sentencia `while`.
 * @param while_ast AST de la sentencia `while`.
 * @return `NULL`, `ResErrorN` o alguna interrupción.
 */
ResNode *eval_while(AstNode *while_ast);
/**
 * @brief Evalúa la sentencia `for`.
 * @param for_ast AST de la sentencia `for`.
 * @return `NULL`, `ResErrorN` o alguna interrupción.
 */
ResNode *eval_for(AstNode *for_ast);
/**
 * @brief Evalúa la definición de una función.
 * @param fn_def_ast AST de la definición de una función.
 * @return `NULL` o `ResErrorN`.
 */
ResNode *eval_fndef(AstNode *fn_def_ast);

#pragma once

#define YYDEBUG 1 // Define la variable yydebug (esto no basta para activar el modo debug)

#include "../ast/ast.h"
#include "../ast/data.h"
#include "../ast/expr.h"
#include "../ast/stmt.h"

#include "../eval/eval.h"
#include "../log.h"
#include "../str.h"

#include "loc.h"

extern int yylex(void); // Función principal de Flex

extern bool g_repl;
extern AstNode *g_ast;

extern int g_scope; // Se incrementa al entrar en un bloque y decrementa al salir
extern int g_loops; // g_loops > 0 entonces permite break y continue
extern int g_fns; // g_fns > 0 entonces permite return
extern int g_exiting;

#define CHECK_EXIT(ast) if(g_exiting) { g_ast = ast_reverse_ll(ast); YYACCEPT; }

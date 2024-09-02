#pragma once

#include "../ast/ast.h"
#include "../ast/data.h"
#include "../ast/id.h"
#include "../log.h"

#include "../bison/parser.tab.h"

extern int yynerrs; // Cantidad de errores de sintaxis en Bison

// extern int g_scope;

// Indica si se usó EOL antes de un error, para evitar repetición
bool f_eol = true;

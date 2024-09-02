#pragma once

#include <stdio.h>
#include "ast/ast.h"

void graphviz(AstNode *ast);
void ast_to_dotfile(AstNode *ast);

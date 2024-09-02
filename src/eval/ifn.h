#pragma once

#include "eval.h"

#include "../ast/ifn.h"

// Evaluación //////////////////////////////////////////////////////////////////

ResNode *eval_ifn(AstNode *node);

ResNode *eval_print(bool ln);
ResNode *eval_time(void);
ResNode *eval_id(void);
ResNode *eval_type(void);
ResNode *eval_range(void);
ResNode *eval_cast(InBuiltFnT type);
ResNode *eval_copy(void);
ResNode *eval_refcnt(void);

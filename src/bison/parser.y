/**
 * @file
 * @brief Archivo de entrada para `bison`.
 *
 * Esta versión soluciona el problema de múltiples `stmt` en una línea. Ej:
 *     
 *     if 1 {print(2); print(4)} fn F(n) { n + 1 }
*/

%require "3.8.2"

// https://www.gnu.org/software/bison/manual/html_node/Token-Decl.html
// https://www.gnu.org/software/bison/manual/html_node/Precedence-Decl.html
// https://www.gnu.org/software/bison/manual/html_node/Shift_002fReduce.html
// https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html

%{
  #include "bison.h"
  YYLTYPE g_prev_loc;
  int g_scope = 0;
  int g_loops = 0;
  int g_fns = 0;
%}

%locations
%define api.location.type {YYLTYPE}
%define parse.error custom // Mensajes de error personalizados
// %define parse.error verbose // Información extra en los mensajes de error
// %define parse.error detailed
/* %define parse.lac full // Ayuda con la información extra en errores  */

/* %define api.token.prefix {TK_} */

%union {
  AstNode *ast;
  AstNodeT ast_t;
}

%token
  LET       "let"
  IF        "if"
  ELIF      "elif"
  ELSE      "else"
  WHILE     "while"
  FOR       "for"
  IN        "in"
  FN        "fn"
  RETURN    "return"
  BREAK     "break"
  CONTINUE  "continue"
  EXIT      "exit"
  DEL       "del"
  OR        "or"
  AND       "and"
  NOT       "not"
  EQ        "=="
  NE        "!="
  LE        "<="
  GE        ">="
  ADD_A     "+="
  SUB_A     "-="
  MUL_A     "*="
  DIV_A     "/="
  EOL       "fin de línea"

%token <ast>
  ID        "identificador"
  ATOM_LIT  "átomo"
  INT_LIT   "entero"
  DOTS      "..."

%type <ast>
  stmt_list
  stmt
  block
  fn
  params
  if
  elif
  for
  while
  decl
  assign
  assignable
  assignable_list
  id_list
  expr_list
  del
  del_target_list
  del_target
  insert
  return
  expr
  and
  not
  cmp
  sum
  term
  factor
  primary
  call
  args
  elem

%type <ast_t>
  assign_op

%destructor {
  print_dbg("%%destructor: <ast>");
  ast_free($$);
} <ast>

%expect 2 // token: error

%start program

%%
  program
    : stmt_list eos { g_ast = ast_reverse_ll($1); }
    ;
  stmt_list
    : stmt_list eos stmt {
      // printf("stmt_list -> stmt_list eos stmt\n");

      if($1) $$ = $[stmt] ? ast_add_next_ll_n(ast_new_ll_n($[stmt], @[stmt]), $1) : $1;
      else $$ = ast_new_ll_n($[stmt], @[stmt]);

      // Si no se está en un bloque
      if($[stmt] && !g_scope) {
        if(g_repl) repl_eval($[stmt]);
        // En archivos también se evalúa stmt por stmt para un mejor reporte de errores
        else file_eval($[stmt]);
      }
      CHECK_EXIT($$);
    }
    | stmt  {
      // printf("stmt_list -> stmt\n");
      $$ = ast_new_ll_n($[stmt], @[stmt]);

      if($[stmt] && !g_scope) {
        if(g_repl) repl_eval($[stmt]);
        else file_eval($[stmt]);
      }
      CHECK_EXIT($$);
    }
    | stmt_list error eos stmt { // Captura errores y evita perder el AST
      // printf("stmt_list -> stmt_list error eos stmt\n");
      if($1) $$ = $[stmt] ? ast_add_next_ll_n(ast_new_ll_n($[stmt], @[stmt]), $1) : $1;
      else $$ = ast_new_ll_n($[stmt], @[stmt]);

      // Si no se está en un bloque
      if($[stmt] && !g_scope) {
        if(g_repl) repl_eval($[stmt]);
        // En archivos también se evalúa stmt por stmt para un mejor reporte de errores
        else file_eval($[stmt]);
      }
      CHECK_EXIT($$);
    }
    | error { $$ = NULL; }
    ;
  eos
    : EOL { yyerrok; repl_prompt(); }
    | ';' { yyerrok; }
    ;
  stmt
    : %empty { $$ = NULL; }
    | decl
    | assign
    | del
    | insert
    | if
    | for
    | while
    | fn
    | expr { $$ = ast_new_exprst($1); }
    | "exit" { $$ = ast_new_exit(); }
    | "break" { 
      if(g_loops <= 0) {
        yyerror("'break' fuera de un ciclo.");
        YYERROR;
      } else $$ = ast_new_break();
    }
    | "continue" {
      if(g_loops <= 0) {
        yyerror("'continue' fuera de un ciclo.");
        YYERROR;
      } else $$ = ast_new_continue();
    }
    | return {
      if(g_fns <= 0) {
        yyerror("'return' fuera de una función.");
        YYERROR;
      } else $$ = $1;
    }
    ;
  /*
  debug
    : '.' ID { dbg_stmt(NULL, $2, false); }
    | expr '.' ID { dbg_stmt($1, $3, false); }
    | stmt '.' ID { dbg_stmt($1, $3, false); }
    | ID '.' ID { dbg_stmt($1, $3, false); }
    | expr '.' ID '!' { dbg_stmt($1, $3, true); }
    | stmt '.' ID '!' { dbg_stmt($1, $3, true); }
    | ID '.' ID '!' { dbg_stmt($1, $3, true); }
    ;
  */
  block
    : '{' { g_scope++; } stmt_list '}' { g_scope--;
      $$ = ast_reverse_ll($[stmt_list]);
    }
    ;
  fn
    : "fn" ID '(' { g_scope++; } params ')' { g_scope--; g_fns++; } block {
      g_fns--;
      if(g_scope > 0) { yyerror("Definición de función dentro de un bloque"); YYERROR; }
      else $$ = ast_new_fndef($[ID], ast_reverse_ll($[params]), $[block]);
    }
    ;
  params
    : id_list { $$ = $1; }
    | id_list ',' "..." {
      $$ = ast_add_next_ll_n(ast_new_ll_n($3, @3), $1);
      
    }
    | "..." { $$ = ast_new_ll_n($1, @1); }
    | %empty { $$ = NULL; }
    ;
  if
    : "if" expr block elif {
      $$ = ast_new_if($2, $3, $4);
    }
    ;
  elif
    : "elif" expr block elif {
      $$ = ast_new_ll_n(ast_new_if($2, $[block], $4), @1);
    }
    | "else" block { $$ = $2; }
    | %empty { $$ = NULL; }
    ;
  for
    : "for" { g_scope++; } ID { g_scope--; } "in" expr { g_loops++; } block {
      g_loops--;
      $$ = ast_new_for($[ID], $[expr], $[block]);
    }
    ;
  while
    : "while" expr { g_loops++; } block {
      g_loops--;
      $$ = ast_new_while($2, $[block]);
    }
    ;
  decl
    : "let" id_list { $$ = ast_new_decl(ast_reverse_ll($2), NULL); }
    // Declaración e inicialización
    | "let" id_list '=' expr_list {
      $$ = ast_new_decl(ast_reverse_ll($2), ast_reverse_ll($4));
    }
    ;
  assign
    : assignable_list assign_op expr_list {
       $$ = ast_new_assign(ast_reverse_ll($1), $2, ast_reverse_ll($3));
    }
    ;
  assignable_list
    : assignable_list ',' assignable {
      // La lista se construye en orden inverso
      $$ = ast_add_next_ll_n(ast_new_ll_n($3, @3), $1);
    }
    | assignable  { $$ = ast_new_ll_n($1, @1); }
    ;
  assignable
    : ID
    /* | ID '[' sum ']' { $$ = ast_new_getelem($1, $3); } */
    | elem
    ;
  insert
    : primary '[' '!' expr ']' '=' expr { $$ = ast_new_insert($1, $4, -1, $7); }
    | primary '[' expr '!' ']' '=' expr { $$ = ast_new_insert($1, $3, 1, $7); }
    ;
  id_list
    : id_list ',' ID {
      // La lista se construye en orden inverso
      $$ = ast_add_next_ll_n(ast_new_ll_n($3, @3), $1); // ID nunca es NULL
    }
    | ID { $$ = ast_new_ll_n($1, @1); }
    ;
  expr_list
    : expr_list ',' expr {
      // La lista se construye en orden inverso
      $$ = ast_add_next_ll_n(ast_new_ll_n($3, @3), $1); // expr nunca es NULL
    }
    | expr { $$ = ast_new_ll_n($1, @1); }
    ;
  assign_op
    : '=' { $$ = ASSIGN_AST; }
    | "+=" { $$ = ADD_AST; }
    | "-=" { $$ = SUB_AST; }
    | "*=" { $$ = MUL_AST; }
    | "/=" { $$ = DIV_AST; }
    ;
  del
    : "del" del_target_list { $$ = ast_new_del($2); } 
    ;
  del_target_list
    : del_target_list ',' del_target { $$ = ast_add_next_ll_n(ast_new_ll_n($3, @3), $1); }
    | del_target { $$ = ast_new_ll_n($1, @1); }
    ;
  del_target
    : ID
    | elem
    | cmp "in" sum {
      $$ = ast_new_in($1, $3);
    }
    ;
  return
    : "return" expr { $$ = ast_new_return($2); }
    | "return" { $$ = ast_new_return(NULL); }
    ;
  expr
    : expr "or" and { $$ = ast_new_or($1, $3); }
    | and
    ; 
  and
    : and "and" not { $$ = ast_new_and($1, $3); }
    | not
    ;
  not
    : "not" not { $$ = ast_new_not($2); }
    | cmp
    ;
  cmp
    : cmp "==" sum { $$ = ast_new_equal($1, $3); }
    | cmp "!=" sum { $$ = ast_new_not(ast_new_equal($1, $3)); }
    | cmp '<' sum { $$ = ast_new_less($1, $3); }
    | cmp '>' sum { $$ = ast_new_less($3, $1); }
    | cmp "<=" sum { $$ = ast_new_not(ast_new_less($3, $1)); }
    | cmp ">=" sum { $$ = ast_new_or(ast_new_less($3, $1), ast_new_equal($3, $1)); }
    | cmp "not" "in" sum {
      // Negación de pertenencia (permite "x not in X" en vez de "not x in X")
      $$ = ast_new_not(ast_new_in($1, $4));
    }
    | cmp "in" sum { // Pertenencia | Posición de un elemento
      $$ = ast_new_in($1, $3);
    }
    | sum
    ;
  sum
    : sum '+' term { // Suma | Unión | Concatenación
      $$ = ast_new_add($1, $3);
    }
    | sum '-' term { // Resta | Diferencia
      $$ = ast_new_sub($1, $3);
    }
    | term
    ;
  term
    : term '*' factor { // Producto | Intersección
      $$ = ast_new_mul($1, $3);
    }
    | term '/' factor { $$ = ast_new_div($1, $3); }
    | factor
    ;
  factor
    : '-' factor { $$ = ast_new_neg($2); } // Opuesto
    | '#' primary { $$ = ast_new_len($2); } // Cardinal | Largo
    | primary
    ;
  primary
    : '(' expr ')' { $$ = $2; }
    | call
    | elem
    | ID
    | INT_LIT
    | ATOM_LIT
    // Literal "iterable", "secuencia" o "colección"
    | '[' { g_scope++; } args']' { g_scope--; // Literal lista
      $$ = ast_new_lst($[args]);
    }
    | '{' { g_scope++; } args '}' { g_scope--; // Literal conjunto
      $$ = ast_new_set($[args]);
    }
    ;
  call
    : primary '(' args ')' { $$ = ast_new_fncall($1, $3); } // Llamada a función
    ;
  args
    : expr_list { $$ = ast_reverse_ll($1); }
    | %empty { $$ = NULL; }
    ;
  elem
    : primary '[' expr ']' { // Elemento según posición
      $$ = ast_new_getelem($1, $3);
    }
    ;
%%

static int yyreport_syntax_error(const yypcontext_t *ctx) {
  int res = 0;
  char *msg = str_dup("");
  // Indica el token inesperado
  yysymbol_kind_t lookahead = yypcontext_token(ctx);
  if(lookahead != YYSYMBOL_YYEMPTY) {
    msg = str_concat(msg, "Inesperado: ");
    bool dots = yysymbol_name(lookahead)[0] == '.';
    if(dots) msg = str_concat(msg, "'");
    msg = str_concat(msg, yysymbol_name(lookahead));
    if(dots) msg = str_concat(msg, "'");
  }
  // Indica los tokens esperados
  enum { TOKENMAX = 5 };
  yysymbol_kind_t expected[TOKENMAX];
  int n = yypcontext_expected_tokens(ctx, expected, TOKENMAX);
  if(n < 0) {
    // Informa el error a yyparse
    res = n;
  } else {
    for(int i = 0; i < n; ++i) {
      if(i == 0) {
        msg = str_concat(msg, ". Se esperaba: ");
        msg = str_concat(msg, yysymbol_name(expected[i]));
        /* msg = str_concat(msg, "'"); */
      } else {
        msg = str_concat(msg, ", ");
        msg = str_concat(msg, yysymbol_name(expected[i]));
        /* msg = str_concat(msg, "'"); */
      }
    }
  }
  msg = str_concat(msg, ".");
  yyerror(msg);
  free(msg);
  return res;
}

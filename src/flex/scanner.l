/**
 * @file
 * @brief Archivo de entrada para `flex`.
*/

%option noyywrap
%option nodefault
%option yylineno
/* %option always-interactive */

%{
  #include "flex.h"
  #include "../bison/loc.h"
%}

/* Este estado permite evitar más de un EOL seguido  */
%x ignore

/*https://www.rkdouglas.co.uk/articles/95/flex-and-line-endings/ */
EOL (\n|\r\n?)

%%

  LOC_STEP(yylloc); /* marca como inicio la posición actual en cada llamado a `yylex` */

{EOL}      { BEGIN(ignore); f_eol = true; LOC_EOL(yylloc); LOC_STEP(yylloc); return EOL; }
<*>[ \t]   { LOC_STEP(yylloc); } /* Ignora espacios en blanco */
<*>\\{EOL} {
  /* Ignora el fin de línea después del caracter '\', permitiendo continuar en
  la siguiente línea */
  repl_print("... ");
  LOC_EOL(yylloc); LOC_STEP(yylloc);
}
<*>"//".*  /* Ignora comentarios */
<ignore>{EOL} { repl_prompt(); LOC_EOL(yylloc); LOC_STEP(yylloc); }

  /* Sale del estado y reescanea el caracter */
<ignore>.     { BEGIN(0); yyless(0); LOC_LESS(yylloc); f_eol = true; }

"let"      { return LET; }
"if"       { return IF; }
"elif"     { return ELIF; }
"else"     { return ELSE; }
"while"    { return WHILE; }
"for"      { return FOR; }
"fn"       { return FN; }
"return"   { return RETURN; }
"break"    { return BREAK; }
"continue" { return CONTINUE; }
"exit"     { return EXIT; }
"del"      { return DEL; }
"in"       { return IN; }
"or"       { return OR; }
"and"      { return AND; }
"not"      { return NOT; }

"=="       { return EQ; }
"!="       { return NE; }
"<="       { return LE; }
">="       { return GE; }
"+="       { return ADD_A; }
"-="       { return SUB_A; }
"*="       { return MUL_A; }
"/="       { return DIV_A; }

"<"        { return '<'; }
">"        { return '>'; }
";"        { return ';'; }
","        { return ','; }
"="        { return '='; }
"+"        { return '+'; }
"-"        { return '-'; }
"*"        { return '*'; }
"/"        { return '/'; }
"#"        { return '#'; }
"!"        { return '!'; }
"{"        { return '{'; }
"}"        { return '}'; }
"("        { return '('; }
")"        { return ')'; }
"["        { return '['; }
"]"        { return ']'; }
  /*"."        { return '.'; } // Para debugging */

[a-zA-Z_][a-zA-Z0-9_]* { yylval.ast = ast_new_id(yytext); return ID; }
[0-9]+                 { yylval.ast = ast_new_int(atol(yytext)); return INT_LIT; }
"..."                  { yylval.ast = ast_new_id("..."); return DOTS; }

["]([ -~]{-}["])*["]|[']([ -~]{-}['])*['] { // "..." | '...'

  yytext[yyleng - 1] = '\0'; // Elimina las comillas de cierre
  yylval.ast = ast_new_str(&yytext[1]); // Ignora las comillas de apertura
  return ATOM_LIT;
}

["][^"\n]*["]|['][^'\n]*['] {
  /* Patrón que detecta caracteres no ASCII en una cadena */
  yyerror("Caracteres inválidos (no ASCII) en literal cadena");
  yynerrs += 1;
  return YYerror;
}

['"] {
  /* Patrón que detecta comillas sin cerrar */
  yyerror("Literal cadena sin delimitador de cierre");
  yynerrs += 1;
  return YYerror;
}

. {
  /* Patrón que detecta caracteres no ASCII */
  if(yytext[0] < ' ' || yytext[0] > '~') { /* [32, 126] */
    if(f_eol) {
      yyerror("Uno o más caracteres inválidos (no ASCII)");
      yynerrs += 1;
      f_eol = false;
    }
  } else {
    yyerror("Caracter inválido '%s'", yytext);
    yynerrs += 1;
  }
  // print_dbg("yytext = %s",yytext);
  /* LOC_STEP(yylloc); */
  return YYerror; /* YYUNDEF - YYerror */
}

%%

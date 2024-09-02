#pragma once

typedef struct YYLTYPE {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;

extern YYLTYPE g_prev_loc;

#define YYLOC_S "%s:%d:%d"
#define YYLOC(ast)\
  g_filename ? g_filename : "stdin", (ast)->loc.first_line, (ast)->loc.first_column

// Initialize the location: first and last cursor are set to the first line, first column.
#define LOC_RESET(loc) \
  (loc).first_column = (loc).first_line = 1; \
  (loc).last_column =  (loc).last_line = 1;

// Advance the end cursor of num lines, and of course reset its column. A macro
// LOCATION_COLUMN is less needed, since it would consist simply in increasing
// the last_column member.
#define LOC_EOL(loc) \
  (loc).last_column = 1;      \
  (loc).last_line += 1;

#define LOC_LESS(loc) \
  (loc).last_column = 1;

// Move the start cursor to the end cursor. This is used when we read a new
// token.
#define LOC_STEP(loc)                 \
  (loc).first_column = (loc).last_column;\
  (loc).first_line = (loc).last_line;

#define LOC_IGNORE(loc) \
  (loc).first_column = (loc).last_column;\
  (loc).first_line = (loc).last_line;

#define YY_USER_ACTION \
  g_prev_loc = yylloc; yylloc.last_column += yyleng;

// static void update_yylloc(YYLTYPE *loc, char *txt) {
//   g_prev_loc = *loc;
//   loc->first_line = loc->last_line;
//   loc->first_column = loc->last_column;
//   for(int i = 0; txt[i] != '\0'; i++) {
//     if(txt[i] == '\n') {
//       loc->last_line++;
//       loc->last_column = 1;
//     } else {
//       loc->last_column++;
//     }
//   }
// }

// #define YY_USER_ACTION update_yylloc(&yylloc, yytext);

#include "graph.h"

#include <stdlib.h>
#include <stdbool.h>

#include "ast/data.h"
#include "ast/expr.h"
#include "ast/stmt.h"
#include "ast/id.h"

#include "str.h"
#include "log.h"

static void node_to_dot(FILE *file, AstNode *ast, int *id, int parent_id, char *parent_tag);

void graphviz(AstNode *ast) {
  DBG_FN_START;

#ifdef _WIN32
  char *no_echo = "1>nul 2>nul";
  char *start_viewer = str_concat(str_dup(""), "start ast.png ");
  start_viewer = str_concat(start_viewer, no_echo);
#else
  char *no_echo = "1>/dev/null 2>/dev/null";
  char *start_viewer = str_concat(str_dup(""), "open ast.png ");
  start_viewer = str_concat(start_viewer, no_echo);
#endif

  char *cmd = str_concat(
    str_dup(""), "dot -Tpng -Gdpi=300 ast.dot -o ast.png "
  );
  cmd = str_concat(cmd, no_echo);
  ast_to_dotfile(ast);
  int r = system(cmd);
  print_dbg("El comando \"%s\" retorna: %d", cmd, r);
  switch(r) {
    case 0:
      printf("Imagen generada. Abriendo...\n");
      r = system(start_viewer);
      print_dbg("El comando \"%s\" retorna: %d", start_viewer, r);
      if(!r) break;
      print_error("Graphviz", "Algo salio mal");
      break;
    case 1: case 127: case 9009: case 32512:
      printf(
        "Graphviz no encontrado. Para generar el gráfico, instale Graphviz: "
        "https://graphviz.org/download\n"
      );
      break;
    default:
      print_error("Graphviz", "Error al generar la imagen");
  }
  free(start_viewer);
  free(cmd);
}

void ast_to_dotfile(AstNode *ast) {
  DBG_FN_START;
  char *filename = "ast.dot";
  printf("Generando archivo %s\n", filename);
  // open file in write mode
  FILE *file = fopen(filename, "w");
  if(file == NULL) {
    print_error("Dot", "No se pudo crear el archivo");
    return;
  }
  fprintf(
    file,
    "digraph AST {\n\t"
      "graph ["
        "center=true "
        "splines=true "
        "bgcolor=\"grey20\" "
        "fontcolor=\"white\" "
        "fontname=\"Consolas\" "
        "label=\"AST\""
      "]\n\t"
      "node["
        "shape=record "
        "color=\"white\" "
        "fontcolor=\"white\" "
        "fontname=\"Consolas\""
      "]\n\t"
      "edge["
        "color=\"white\""
      "]\n"
  );
  // int id = 0;
  // dot_nodes(file, ast, &id, NULL, 0);
  int id = 0;
  node_to_dot(file, ast, &id, -1, "");
  fprintf(file, "}");
  fclose(file);
  printf("Archivo %s generado\n", filename);
}

void node_to_dot(FILE *file, AstNode *ast, int *id, int p_id, char *p_tag) {
  DBG_FN_START;
  const int c_id = *id; // id del nodo actual
  *id += 1; // id del nodo siguiente

  if(!ast) {
    fprintf(file, "\tnodo%d[label=\"NULL\" shape=none]\n", c_id);
    if(p_id >= 0) fprintf(file, "\tnodo%d%s->nodo%d\n", p_id, p_tag, c_id);
    return;
  }

  bool t_tag = true;
  fprintf(file, "\t");
  switch(ast->type) {
    case IFN_AST: break;
    case INT_AST:
      {
        long n = ast_data_int(ast);
        fprintf(file, "nodo%d[label=\"<t>INT|<int>%ld\"]\n", c_id, n);
      }
      break;
    case STR_AST:
      {
        char *s = ast_data_str(ast);
        fprintf(file, "nodo%d[label=\"<t>STR|<x>\\\"%s\\\"\"]\n", c_id, s);
      }
      break;
    case SET_AST:
      fprintf(file, "nodo%d[label=\"<t>SET|<x>elems\"]\n", c_id);
      node_to_dot(file, ast_data_elems(ast), id, c_id, ":x");
      break;
    case LST_AST:
      fprintf(file, "nodo%d[label=\"<t>LST|<x>elems\"]\n", c_id);
      node_to_dot(file, ast_data_elems(ast), id, c_id, ":x");
      break;

    case OR_AST:
      fprintf(file, "nodo%d[label=\"<t>OR|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case AND_AST:
      fprintf(file, "nodo%d[label=\"<t>AND|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case EQUAL_AST:
      fprintf(file, "nodo%d[label=\"<t>EQUAL|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case LESS_AST:
      fprintf(file, "nodo%d[label=\"<t>LESS|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case IN_AST:
      fprintf(file, "nodo%d[label=\"<t>IN|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case ELEM_AST:
      fprintf(file, "nodo%d[label=\"<t>ELEM|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case ADD_AST:
      fprintf(file, "nodo%d[label=\"<t>ADD|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case SUB_AST:
      fprintf(file, "nodo%d[label=\"<t>SUB|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case MUL_AST:
      fprintf(file, "nodo%d[label=\"<t>MUL|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case DIV_AST:
      fprintf(file, "nodo%d[label=\"<t>DIV|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case CALL_AST:
      fprintf(file, "nodo%d[label=\"<t>CALL|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_expr_b(ast), id, c_id, ":b");
      break;
    case NOT_AST:
      fprintf(file, "nodo%d[label=\"<t>NOT|<x>a\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":x");
      break;
    case NEG_AST:
      fprintf(file, "nodo%d[label=\"<t>NEG|<x>a\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":x");
      break;
    case LEN_AST:
      fprintf(file, "nodo%d[label=\"<t>LEN|<x>a\"]\n", c_id);
      node_to_dot(file, ast_expr_a(ast), id, c_id, ":x");
      break;

    case BREAK_AST:
      fprintf(file, "nodo%d[label=\"BREAK\"]\n", c_id);
      t_tag = false;
      break;
    case CONTINUE_AST:
      fprintf(file, "nodo%d[label=\"CONTINUE\"]\n", c_id);
      t_tag = false;
      break;
    case EXIT_AST:
      fprintf(file, "nodo%d[label=\"EXIT\"]\n", c_id);
      t_tag = false;
      break;
    case EXPR_AST:
      fprintf(file, "nodo%d[label=\"<t>EXPR|<x>a\"]\n", c_id);
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":x");
      break;
    case RETURN_AST:
      fprintf(file, "nodo%d[label=\"<t>RETURN|<x>a\"]\n", c_id);
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":x");
      break;
    case DEL_AST:
      fprintf(file, "nodo%d[label=\"<t>DEL|<x>a\"]\n", c_id);
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":x");
      break;
    case DECL_AST:
      fprintf(file, "nodo%d[label=\"<t>DECL|<a>a|<b>b\"]\n", c_id);
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_stmt_b(ast), id, c_id, ":b");
      break;
    case ASSIGN_AST:
      fprintf(
        file, "nodo%d[label=\"<t>ASSIGN|<a>a|<b>b|<x>%d\"]\n",
        c_id, (int)ast_stmt_t(ast)
      );
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_stmt_b(ast), id, c_id, ":b");
      break;
    case WHILE_AST:
      fprintf(
        file, "nodo%d[label=\"<t>WHILE|<a>a|<b>b\"]\n", c_id
      );
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_stmt_b(ast), id, c_id, ":b");
      break;
    case IF_AST:
      fprintf(
        file, "nodo%d[label=\"<t>IF|<a>a|<b>b|<c>c\"]\n", c_id
      );
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_stmt_b(ast), id, c_id, ":b");
      node_to_dot(file, ast_stmt_c(ast), id, c_id, ":c");
      break;
    case FOR_AST:
      fprintf(
        file, "nodo%d[label=\"<t>FOR|<a>a|<b>b|<c>c\"]\n", c_id
      );
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_stmt_b(ast), id, c_id, ":b");
      node_to_dot(file, ast_stmt_c(ast), id, c_id, ":c");
      break;
    case FN_AST:
      fprintf(
        file, "nodo%d[label=\"<t>FN|<a>a|<b>b|<c>c\"]\n", c_id
      );
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_stmt_b(ast), id, c_id, ":b");
      node_to_dot(file, ast_stmt_c(ast), id, c_id, ":c");
      break;
    case INSERT_AST:
      fprintf(
        file, "nodo%d[label=\"<t>INSERT|<a>a|<b>b|<c>c|<x>%d\"]\n",
        c_id, ast_stmt_side(ast)
      );
      node_to_dot(file, ast_stmt_a(ast), id, c_id, ":a");
      node_to_dot(file, ast_stmt_b(ast), id, c_id, ":b");
      node_to_dot(file, ast_stmt_c(ast), id, c_id, ":c");
      break;

    case ID_AST:
      fprintf(
        file, "nodo%d[label=\"<t>ID|<a>%s|<b>%d\"]\n",
        c_id, ast_id_str(ast), ast_id_hash(ast)
      );
      break;
    case AST_LL:
      fprintf(
        file, "nodo%d[label=\"<t>AST_LL|<a>data|<b>next\"]\n", c_id
      );
      node_to_dot(file, ast->data, id, c_id, ":a");
      node_to_dot(file, ast->next, id, c_id, ":b");
      break;
  }
  if(p_id >= 0) {
    fprintf(
      file, "\tnodo%d%s->nodo%d%s\n", p_id, p_tag, c_id, t_tag ? ":t" : ""
    );
  }
}

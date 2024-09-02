/**
 * @file
 * @brief Archivo principal del intérprete de Aleph
 *
 * Este archivo contiene el análisis de argumentos, la configuración y la
 * ejecución del intérprete.
*/

#include <getopt.h>
#include <stdlib.h> // Macros EXIT
#include <stddef.h>

#include "eval/sym.h"
#include "global.h"
#include "log.h"
#include "graph.h" // graphviz

/** @brief Valor especial para indicar que el programa no debe salir */
#define DO_NOT_EXIT (-EXIT_FAILURE - EXIT_SUCCESS)

extern int yydebug; ///< Activa mensajes para debugging de Bison
extern int yynerrs; ///< Cantidad de errores de sintaxis en Bison
extern FILE *yyin; ///< Archivo de entrada de Flex
extern int yyparse(void); ///< Función principal de Bison

bool g_exiting = false; ///< Indica que el intérprete está finalizando
bool g_repl = true; ///< Modo Read–Eval–Print Loop
bool g_err_loc = false; ///< Activa la ubicación de los mensajes de error
bool g_debug = false; ///< Activa los mensajes de la función 'print_dbg'
bool g_color = true; ///< Activa color en la salida
char *g_filename = NULL; ///< Nombre del archivo de entrada

size_t g_sym_tab_size = 9973; ///< Capacidad máxima de la tabla de símbolos
size_t g_max_stack_depth = 100; ///< Evita recursión infinita o demasiado larga

AstNode *g_ast = NULL; ///< AST resultante del análisis sintáctico
SymTab *g_symtab = NULL; ///< Tabla de símbolos

/**
 * @brief Imprime el mensaje de ayuda
 *
 * Esta función imprime un mensaje de ayuda que explica el uso y las opciones
 * del intérprete.
 */
static void print_help(void);
/**
 * @brief Analiza los argumentos de la línea de comandos
 *
 * Esta función procesa los argumentos de la línea de comandos pasados al
 * intérprete.
 *
 * @param argc Número de argumentos de la línea de comandos
 * @param argv Array de cadenas de argumentos de la línea de comandos
 * @param graph Puntero a una bandera booleana para la generación de gráficos
 * @return Código de salida o `DO_NOT_EXIT` si es exitoso
 */
static int args_parse(int argc, char *argv[], bool *graph);
/**
 * @brief Establece el modo de depuración
 *
 * Esta función establece el modo de depuración basado en el argumento
 * proporcionado.
 *
 * @param debug_mode El modo de depuración a establecer
 *
 * @deprecated Actualizar documentación
 */
static bool set_debug_mode(char *debug_mode);
/**
 * @brief Configura el archivo de entrada para el intérprete
 *
 * Esta función configura el archivo de entrada (`yyin`) para el intérprete
 * basado en los argumentos de la línea de comandos.
 *
 * @param argc Número de argumentos de la línea de comandos
 * @param argv Array de cadenas de argumentos de la línea de comandos
 * @return Código de salida o `DO_NOT_EXIT` si es exitoso
 */
static int setup_yyin(int argc, char *argv[]);

/**
 * @brief Función principal del intérprete
 *
 * Esta función inicializa el intérprete, analiza los argumentos de la línea de
 * comandos, configura la tabla de símbolos y ejecuta el intérprete.
 *
 * @param argc Número de argumentos de la línea de comandos
 * @param argv Array de cadenas de argumentos de la línea de comandos
 * @return Código de salida del programa
 */
int main(int argc, char **argv) {
  // Opciones no globales
  bool graph = false;

  int exit_code = args_parse(argc, argv, &graph);

  if(exit_code != DO_NOT_EXIT) return exit_code;

  // Crea e inicializa la tabla de símbolos
  scope_init();
  if(!g_symtab || !(g_symtab->hash_tab)) {
    print_error("Interno", LOC_S"Error al crear tabla de símbolos", LOC);
    return EXIT_FAILURE;
  }

  repl_print(">>> ");
  exit_code = yyparse();

  if(graph) graphviz(g_ast);

  ast_free(g_ast);

  if(g_repl) return exit_code;

  fclose(yyin);
  if(yynerrs > 0) {
    printf(
      "AVISO: %d error%s encontrado%s\n",
      yynerrs,
      yynerrs > 1 ? "es" : "",
      yynerrs > 1 ? "s" : ""
    );
  }
  return exit_code;
}

void print_help(void) {
  printf("Uso: aleph [opciones] [archivo]\n");
  printf("Si no se indica un archivo, se ejecuta en modo interactivo (REPL)\n");
  printf("Opciones:\n");
  printf("-h Muestra este mensaje de ayuda.\n");
  printf("-c Desactiva el color en mensajes de error y depuración.\n");
  printf("-d MODOS Establece los modos de depuración:\n");
  printf("    -d e Muestra dónde se crean los mensajes de error.\n");
  printf("    -d i Activa mensajes de depuración del intérprete.\n");
  printf("    -d b Activa la depuración incluida en Bison.\n");
  printf("    Ejemplo:\n");
  printf("        -d bie Combina los 3 modos.\n");
  printf("-t N Establece la capacidad máxima de la tabla de símbolos:\n");
  printf("    -t %zu Valor por defecto.\n", g_sym_tab_size);
  printf("    -t N Capacidad para un máximo de N símbolos.\n");
  printf("-s N Establece la cantidad máxima de 'scopes' activos a la vez:\n");
  printf("    -s %zu Valor por defecto.\n", g_max_stack_depth);
  printf("    -s N Máximo de N scopes activos a la vez.\n");
  printf("-g Genera un gráfico del AST (ast.dot, ast.png).\n");
  printf("-p F Imprime código generado por el AST en el archivo F.\n");
}

int args_parse(int argc, char *argv[], bool *graph) {
  int opt = 0;
  opterr = 0; // desactiva mensajes de error por defecto
  while((opt = getopt(argc, argv, "d:t:s:gp:hc")) != -1) {
    switch(opt) {
      case 'd':
        if(!set_debug_mode(optarg)) goto error;
        break;
      case 't':
        // NOTE no se verifica un input correcto
        g_sym_tab_size = strtoull(optarg, NULL, 10);
        break;
      case 's':
        // NOTE no se verifica un input correcto
        g_max_stack_depth = strtoull(optarg, NULL, 10);
        break;
      case 'g':
        *graph = true;
        break;
      case 'p':
        print_error("CLI", "Opción no implementada.");
        return EXIT_FAILURE;
      case 'h':
        print_help();
        return EXIT_SUCCESS;
      case 'c':
        g_color = false;
        break;
      default:
        error:
        print_error("CLI", "Argumento inválido. Usa -h para más información.");
        return EXIT_FAILURE;
    }
  }
  return setup_yyin(argc, argv);
}

bool set_debug_mode(char *debug_mode) {
  while(*debug_mode) {
    switch(*debug_mode) {
      case 'e': g_err_loc = true; break;
      case 'i': g_debug = true; break;
      case 'b': yydebug = 1; break;
      default: return false;
    }
    debug_mode++;
  }
  return true;
}

int setup_yyin(int argc, char *argv[]) {
  if(optind < argc) {
    if(optind + 1 < argc) {
      print_error("CLI", "Más de un archivo indicado");
      return EXIT_FAILURE;
    }
    g_filename = argv[optind];
    // Comprueba existencia del archivo
    if(!(yyin = fopen(g_filename, "r"))) {
      print_error("CLI", "El archivo '%s' no existe", g_filename);
      return EXIT_FAILURE;
    }
    fclose(yyin); // Fin comprobación
    if(!(yyin = fopen(g_filename, "a+"))) {
      print_error("CLI", "Hubo un error al abrir '%s'", g_filename);
      return EXIT_FAILURE;
    }
    fseek(yyin, -1, SEEK_END); // Cursor en el último carácter
    // Se agrega EOL al final si es necesario
    if(fgetc(yyin) != '\n') fputc('\n', yyin);
    fseek(yyin, 0, SEEK_SET); // Cursor en el primer carácter

    g_repl = false;
  }
  return DO_NOT_EXIT;
}

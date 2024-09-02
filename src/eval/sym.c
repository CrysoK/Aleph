/**
 * @file sym.c
 * @brief Implementación del manejo de símbolos.
 *
 * Este archivo contiene las implementaciones de las funciones declaradas en
 * @ref sym.h, proporcionando la lógica para manejar símbolos, tablas de
 * símbolos y alcances.
 */

#include "sym.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../ast/id.h"
#include "../ast/stmt.h"
#include "../ast/ifn.h"
#include "../str.h"
#include "../log.h"
#include "../global.h"

#include "data.h"
#include "error.h"

extern SymTab *g_symtab;
extern size_t g_sym_tab_size;
extern size_t g_max_stack_depth;

static size_t stack_depth = 0;

/**
 * @brief Obtiene la posición de un símbolo en la tabla actual.
 * @param symtab Puntero a la tabla de símbolos.
 * @param id Identificador del símbolo.
 * @param hash Valor hash del identificador.
 * @return Posición del símbolo en la tabla o -1 si no se encuentra.
 */
static int get_sym_pos(SymTab * symtab, char *id, int hash);
/**
 * @brief Añade un identificador a la lista de variables para liberar.
 * @param id Identificador a añadir.
 * @param hash Valor hash del identificador.
 */
static void id_list_add(char *id, int hash);
/**
 * @brief Libera la memoria de una tabla de símbolos.
 * @param symtab Puntero al puntero de la tabla de símbolos a liberar.
 */
static void free_symtab(SymTab **symtab);

////////////////////////////////////////////////////////////////// DEFINICIONES

Symbol *res_new_sym(char *id, ResNode *value) {
  Symbol *new = malloc(sizeof(Symbol));
  if(!new) return out_of_mem(LOC);
  new->id = str_dup(id);
  new->value = value;
  return new;
}

void res_free_sym(Symbol **sym) {
  if(!sym) { print_dbg("(%s) sym == NULL", __func__); return; }
  print_dbg("(%s) id = %s", __func__, (*sym)->id);
  free((*sym)->id);
  free(*sym);
  *sym = NULL;
}

// Devuelve el valor de un símbolo. Puede devolver un ResErrorN, nunca NULL.
ResNode *eval_sym(AstNode *ast) {
  DBG_FN_START;
  NULL_RETURN(ast, "Interno", S("ast == NULL"));
  Symbol *saved = scope_get_sym(ast_id_str(ast), ast_id_hash(ast));
  NULL_RETURN(saved, "Símbolo", str_fmt("Símbolo '%s' no declarado", ast_id_str(ast)));
  return saved->value;
}

SymTab *res_new_symtab(SymTab *prev) {
  SymTab *new = malloc(sizeof(SymTab));
  if(!new) out_of_mem(LOC);
  new->hash_tab = calloc(g_sym_tab_size, sizeof(Symbol *));
  new->id_list = NULL;
  new->prev = prev;
  return new;
}

// Requiere ejecutar previamente `scope_clear`.
void free_symtab(SymTab **symtab) {
  DBG_FN_START;
  if(!symtab || !*symtab) return;
  free((*symtab)->hash_tab);
  (*symtab)->hash_tab = NULL; // evita acceder a memoria liberada
  free(*symtab);
  *symtab = NULL;
}

void scope_clear(SymTab *symtab) {
  DBG_FN_START;
  IdListN *sym = symtab->id_list;
  while(sym) {
    IdListN *aux = sym->next;
    sym->next = NULL; // evita acceder a memoria liberada
    scope_del_sym(sym->id, sym->hash); // libera Symbol y valores no referenciados
    free(sym->id);
    sym->id = NULL;
    free(sym);
    sym = aux;
  }
  symtab->id_list = NULL;
}

void scope_init(void) {
  // Funciones integradas
  scope_push();
  // Aquí se crean los símbolos integrados y se añaden
  // Funciones nativas
  for(int i = 0; i <= PRINT_IFN; i++) {
    AstNode *fn = ast_new_ifn(i);
    AstNode *sym = ast_stmt_a(fn);
    scope_add_sym(ast_id_str(sym), ast_id_hash(sym), res_new_fn(fn));
  }
  // Otros símbolos
  // scope_add_sym("...", str_hash("..."), new_vararg_n());
  // scope_add_sym("true", str_hash("true"), res_new_int(1));
  // scope_add_sym("false", str_hash("false"), res_new_int(0));
  // Tabla de símbolos global
  scope_push();
}

SymTab *scope_change(SymTab *to_symtab, int depth) {
  print_dbg("(%s) new_depth = %d", __func__, depth);
  SymTab *aux = g_symtab;
  if(to_symtab) {
    g_symtab = to_symtab;
    stack_depth = depth + 2;
    return aux;
  }
  while(stack_depth - 2 > (size_t)depth) {
    g_symtab = g_symtab->prev;
    stack_depth--;
  }
  return aux;
}

SymTab *scope_get(void) {
  return g_symtab;
}

int scope_depth(void) {
  return stack_depth - 2;
}

void scope_push(void) {
  if(stack_depth >= g_max_stack_depth) {
    print_error("Fatal", LOC_S"Límite de entornos activos alcanzado", LOC);
    abort();
  }
  g_symtab = res_new_symtab(g_symtab);
  stack_depth++;
  print_dbg("(%s) depth = %d", __func__, scope_depth());
}

void scope_pop(void) {
  scope_clear(g_symtab);
  SymTab *aux = g_symtab->prev;
  free_symtab(&g_symtab);
  g_symtab = aux;
  stack_depth--;
  print_dbg("(%s) depth = %d", __func__, scope_depth());
}

int get_sym_pos(SymTab *symtab, char *id, int hash) {
  if(!id) {
    print_error("Interno", LOC_S"'id' = NULL", LOC);
    return -1;
  }
  if(!symtab) {
    print_error("Fatal", LOC_S"Tabla de símbolos nula", LOC);
    abort();
  }
  // Posición inicial según hashing
  int init = hash % g_sym_tab_size;
  int pos = init;
  // Puntero de la posición inicial
  Symbol *elem = (symtab->hash_tab)[init];
  // Si no es NULL, ver si el ID es igual
  while(elem) {
    // Si el ID coincide, símbolo encontrado
    if(strcmp(elem->id, id) == 0) {
      print_dbg("(%s) pos = %d", __func__, pos);
      return pos;
    }
    print_dbg(LOC_S"Colisión en el hashing", LOC);
    // Si el ID es distinto, buscar en la siguiente posición
    pos = (pos + 1) % g_sym_tab_size;
    if(pos != init) elem = (symtab->hash_tab)[pos];
    // Colisión en toda la tabla (¿posible?)
    else break;
  }
  // Si es NULL, el símbolo nunca se agregó en la tabla actual
  return -1;
}

// No retorna ResErrorN pero retorna NULL si el símbolo NO se encuentra
Symbol *scope_get_sym(char *id, int hash) {
  print_dbg("(%s) id = %s", __func__, id ? id : "NULL");
  if(!id) return NULL;
  if(!g_symtab) { // Podría ocurrir?
    res_free(RAISE("Fatal", S("Tabla de símbolos nula")));
    abort();
  }
  SymTab *s_tab = g_symtab;
  int pos = get_sym_pos(s_tab, id, hash);
  while(s_tab->prev && pos < 0) { // Buscar en alcances anteriores
    s_tab = s_tab->prev;
    pos = get_sym_pos(s_tab, id, hash);
  }
  if(pos >= 0) {
    return (s_tab->hash_tab)[pos];
  }
  return NULL;
}

void id_list_add(char *id, int hash) {
  // Nuevo nodo de la lista de símbolos
  IdListN *new_list_n = malloc(sizeof(IdListN));
  if(!new_list_n) { out_of_mem(LOC); return; }
  new_list_n->id = str_dup(id);
  new_list_n->hash = hash;
  new_list_n->next = g_symtab->id_list;
  g_symtab->id_list = new_list_n;
}

ResNode *scope_add_sym(char *id, int hash, ResNode * value) {
  DBG_FN_START;
  NULL_RETURN(id, "Interno", S("id == NULL"));
  NULL_RETURN(value, "Interno", S("value == NULL"));
  if(!g_symtab) { // "fatal" o no?
    res_free(RAISE("Fatal", S("Tabla de símbolos nula")));
    abort();
  }
  // Posición inicial según hashing
  int init = hash % g_sym_tab_size;
  int pos = init;
  // Puntero de la posición inicial
  Symbol *elem = g_symtab->hash_tab[init];
  // Hasta que no se encuentre una posición válida, repetir
  while(true) {
    // Si es NULL, es una posición válida
    if(!elem) {
      g_symtab->hash_tab[pos] = res_new_sym(id, value);
      REF_INC(value);
      id_list_add(id, hash);
      print_dbg("(%s) Símbolo '%s' añadido", __func__, id);
      return NULL;
    } // Sino, ya hay algo con el mismo hash
    // Si el ID coincide es una re-declaración
    if(strcmp(elem->id, id) == 0) { // es error de sintaxis?
      return RAISE("Sintaxis", str_fmt("Re-declaración del símbolo '%s'", id));
    } // Si los ID no coinciden, hay una colisión. Buscar sig. pos. válida
    print_dbg("Colisión en el hashing");
    pos = (pos + 1) % g_sym_tab_size;
    if(pos != init) elem = g_symtab->hash_tab[pos];
    else { // Si pos == init, entonces se recorrió toda la tabla
      return RAISE("Interno", S("Tabla de símbolos llena"));
    }
  }
}

ResNode *scope_del_sym(char *id, int hash) {
  print_dbg("(%s) id: %s", __func__, id ? id : "NULL");
  int pos = get_sym_pos(g_symtab, id, hash);
  if(pos < 0)
    return RAISE("Símbolo", str_fmt("Símbolo '%s' no declarado", id));
  Symbol *elem = g_symtab->hash_tab[pos];
  REF_DEC(elem->value);
  garbage_collect(elem->value);
  res_free_sym(&elem);
  g_symtab->hash_tab[pos] = NULL;
  return NULL;
}


/**
 * @file sym.h
 * @brief Manejo de símbolos.
 *
 * Este archivo contiene las definiciones de estructuras y declaraciones de
 * funciones para manejar símbolos, tablas de símbolos y alcances en el
 * intérprete.
 *
 * @remarks *Símbolo* es un par `(nombre, valor)`. *Identificador* es sinónimo de
 * *nombre*. *Variable* es un símbolo cuyo valor puede cambiar.
*/
#pragma once

#include "eval.h"

/**
 * @brief Representa un símbolo en la tabla de símbolos.
*/
typedef struct s_symbol {
  char *id;
  ResNode *value;
} Symbol;

/**
 * @brief Nodo de una lista de identificadores.
 *
 * Esta estructura se utiliza para mantener una lista de identificadores
 * declarados, facilitando su eliminación.
 */
typedef struct s_id_list_n IdListN;
struct s_id_list_n {
  IdListN *next;
  char *id;
  int hash;
};

/**
 * @brief Representa una tabla de símbolos.
 *
 * La tabla de símbolos mantiene un registro de los símbolos declarados en un
 * alcance particular y proporciona acceso al alcance anterior.
 */
typedef struct s_sym_tab SymTab;
struct s_sym_tab { // "struct symbol table"
  Symbol **hash_tab; ///< Array de símbolos declarados
  IdListN *id_list; ///< Lista de identificadores declarados
  SymTab *prev; ///< Tabla de símbolos del alcance previo
};

// Símbolos ////////////////////////////////////////////////////////////////////

/**
 * @brief Crea un nuevo símbolo.
 *
 * Crea un nuevo símbolo. Listo para ser añadido a la tabla de símbolos.
 *
 * @param id Identificador del símbolo.
 * @param value Valor asociado al símbolo.
 * @return Puntero al nuevo símbolo creado.
 */
Symbol *res_new_sym(char *id, ResNode *value);
/**
 * @brief Libera la memoria de un símbolo.
 * @param sym Puntero al puntero del símbolo a liberar.
 * @note Esta función NO libera el valor asociado al símbolo.
 */
void res_free_sym(Symbol **sym);
/**
 * @brief Evalúa un símbolo a partir de su nodo AST.
 * @param node Nodo AST del identificador.
 * @return Valor asociado al símbolo en el alcance actual.
 */
ResNode *eval_sym(AstNode *node);


// Tabla de símbolos ///////////////////////////////////////////////////////////

/**
 * @brief Crea una nueva tabla de símbolos.
 * @param prev Puntero a la tabla de símbolos del alcance anterior.
 * @return Puntero a la nueva tabla de símbolos creada.
 */
SymTab *res_new_symtab(SymTab *prev);

// Alcance /////////////////////////////////////////////////////////////////////

/**
 * @brief Obtiene un símbolo del alcance actual o de los alcances previos.
 * @param id Identificador del símbolo.
 * @param hash Valor hash del identificador.
 * @return Puntero al símbolo encontrado o `NULL` si no existe.
 */
Symbol *scope_get_sym(char *id, int hash);
/**
 * @brief Añade un símbolo al alcance actual.
 * @param id Identificador del símbolo.
 * @param hash Valor hash del identificador.
 * @param value Valor a asociar con el símbolo.
 * @return `NULL` en caso de éxito, o un `ResNode` de error si falla.
 */
ResNode *scope_add_sym(char *id, int hash, ResNode *value);
/**
 * @brief Elimina un símbolo de la tabla actual.
 * @param id Identificador del símbolo a eliminar.
 * @param hash Valor hash del identificador.
 * @return `NULL` en caso de éxito, o un `ResNode` de error si falla.
 * @note Esta función no elimina el valor asociado al símbolo.
 */
ResNode *scope_del_sym(char *id, int hash);
/**
 * @brief Crea e inicializa la tabla de símbolos del alcance global o base.
 *
 * Primero crea una tabla para funciones "in-built", luego una tabla "global"
 * que apunte como anterior a la primera.
 */
void scope_init(void);
/**
 * @brief Obtiene la profundidad actual de los alcances.
 * @return Número de alcances activos actualmente.
 */
int scope_depth(void);
/**
 * @brief Cambia el alcance actual.
 * @param new Nueva tabla de símbolos a establecer como actual.
 * @param depth Profundidad del alcance a establecer si `new` es `NULL`.
 * @return Puntero a la tabla de símbolos anterior.
 */
SymTab *scope_change(SymTab *new, int depth);
/**
 * @brief Obtiene la tabla de símbolos del alcance actual.
 * @return Puntero a la tabla de símbolos actual.
 */
SymTab *scope_get(void);

/**
 * @brief Inicia un nuevo alcance.
 *
 * Crea una nueva tabla de símbolos y la establece como la actual,
 * enlazando la tabla anterior como su predecesor.
 */
void scope_push(void);
/**
 * @brief Finaliza el alcance actual.
 *
 * Elimina la tabla de símbolos actual y establece la anterior como la actual.
 */
void scope_pop(void);
/**
 * @brief Limpia todos los símbolos de una tabla de símbolos.
 * @param symtab Puntero a la tabla de símbolos a limpiar.
 * @note Esta función no elimina la tabla en sí, solo su contenido.
 */
void scope_clear(SymTab *symtab);

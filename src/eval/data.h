/**
 * @file
 * @brief Declaraciones para la evaluación de datos.
 */
#pragma once

#include "eval.h"

typedef struct {
  ResNodeT type;
  int refcnt; ///< Cantidad de lugares que apuntan a este nodo
  union {
    char *str;
    long int_;
    struct {
      /// @note Los conjuntos/listas vacíos se representan como `x->elems = NULL`
      ResNode *elems; ///< Lista enlazada (también podría ser un array, por ejemplo)
      /// Evita recorrer toda la lista cada vez que se consulte la cantidad de elementos
      int len;
    };
    AstNode *fn; ///< Nodo AST de la definición de una función.
  };
} ResDataN;

// Atributos de ResDataN ///////////////////////////////////////////////////////

int data_refcnt(ResNode *node);
char *data_str(ResNode *node);
long data_int(ResNode *node);
ResNode *data_elems(ResNode *node);
int data_len(ResNode *node);
AstNode *data_fn(ResNode *node);
/// Modifica el contador de referencias de un dato.
int data_mod_refcnt(ResNode *node, int add);
bool res_is_data(ResNode *node);

#define REF_INC(x) data_mod_refcnt(x, +1)
#define REF_DEC(x) data_mod_refcnt(x, -1)

// Nuevos nodos ////////////////////////////////////////////////////////////////

ResNode *res_new_undef(void);
ResNode *res_new_void(void);
ResNode *res_new_int(long value);
ResNode *res_new_str(char *value);
ResNode *res_new_set(ResNode *elems, int len);
ResNode *res_new_lst(ResNode *elems, int len);
ResNode *res_new_fn(AstNode *fn_ast);

// Evaluación //////////////////////////////////////////////////////////////////

ResNode *eval_data(AstNode *node);
/// Similar a `eval_expr_list` pero omite repetidos
ResNode *eval_set_elems(AstNode *elems, int *len);
// Si `res->refcnt` es 0 entonces se libera.
void garbage_collect(ResNode *res);

// Funciones para datos ////////////////////////////////////////////////////////

void data_print(ResNode *node, bool quotes);
void data_print_elems(ResNode *node_list, ResNode *container, bool quotes, bool comma);

ResNode *data_copy(ResNode *node);
int data_compare(ResNode *a, ResNode *b);

int lst_search_elem(ResNode *elem, ResNode *lst);
/**
 * @brief Obtiene el elemento en la posición `index` de una lista.
 * @param index Índice del elemento a obtener. Puede ser negativo.
 * @param iter Lista (nodo `LST_R`).
 * @return Puntero al elemento o `ResErrorN`.
 */
ResNode *lst_get_elem(int index, ResNode *iter);
/**
 * @brief Inserta un elemento en la posición indicada de una lista.
 * @param lst Lista (nodo `LST_R`).
 * @param index Posición de inserción. Puede ser negativa.
 * @param side `-1` o `1`. Ver descripción detallada.
 * @param elem Elemento a insertar.
 * @return `NULL` o `ResErrorN`.
 */
ResNode *lst_insert_elem(ResNode *lst, int index, int side, ResNode *elem);
/**
 * @brief Elimina el elemento en la posición `index` de una lista.
 * @param lst Lista (nodo `LST_R`).
 * @param index Índice del elemento a eliminar. Puede ser negativo.
 */
ResNode *lst_del_index(ResNode *lst, int index);

int set_search_elem(ResNode *elem, ResNode *set);
/**
 * @brief Inserta un elemento en un conjunto.
 * @param data Elemento (dato) a insertar.
 * @param elems Puntero al primer elemento del conjunto. Puede ser `NULL`.
 * @return `true` si se insertó o `false` si no.
 */
bool set_insert_elem(ResNode *elem, ResNode **elems);
// ResNode *get_set_list_node(int index, ResNode *iter);

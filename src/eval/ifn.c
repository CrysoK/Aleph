#include "ifn.h"

#include <stdio.h>
#include <time.h>

#include "../str.h"
#include "../log.h"
#include "../global.h"
#include "../ast/ifn.h"
#include "data.h"
#include "stmt.h"
#include "error.h"

ResNode *eval_ifn(AstNode *ifn_ast) {
  DBG_FN_START;
  NULL_RETURN(ifn_ast, "Interno", S("ifn_ast == NULL"));
  switch(ast_ifn_type(ifn_ast)) {
    case PRINT_IFN: return eval_print(false);
    case PRINTLN_IFN: return eval_print(true);
    case TIME_IFN: return eval_time();
    case ID_IFN: return eval_id();
    case RANGE_IFN: return eval_range();
    case TYPE_IFN: return eval_type();
    case CAST_SET_IFN:
    case CAST_LST_IFN:
    case CAST_INT_IFN:
    case CAST_STR_IFN: return eval_cast(ast_ifn_type(ifn_ast));
    case COPY_IFN: return eval_copy();
    case REFCNT_IFN: return eval_refcnt();
    default: return RAISE("Interno", S("Nodo inválido"));
  }
  return RAISE("Interno", S("Inalcanzable"));
}

ResNode *eval_print(bool ln) {
  DBG_FN_START;
  Symbol *sym = scope_get_sym("_args", str_hash("_args"));
  NULL_RETURN(sym, "Interno", S("_args == NULL"));
  ResDataN *arg_lst = (ResDataN *)sym->value;
  ResNode *arg = arg_lst->elems;
  data_print_elems(arg, NULL, false, false);
  if(ln) printf("\n");
  fflush(stdout);
  return NULL;
}

ResNode *eval_time(void) {
  DBG_FN_START;
  return res_new_return(res_new_int((long)time(NULL)));
}

ResNode *eval_id(void) {
  DBG_FN_START;
  Symbol *sym = scope_get_sym("x", str_hash("x"));
  if(!sym) return RAISE("Interno", S("Error al obtener 'x'"));
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"
  return res_new_return(res_new_int((sym->value)));
#pragma GCC diagnostic pop
}

ResNode *eval_type(void) {
  DBG_FN_START;
  Symbol *sym = scope_get_sym("x", str_hash("x"));
  if(!sym) return RAISE("Interno", S("Error al obtener 'x'"));
  ResDataN *data = (ResDataN *)sym->value;
  if(!data) return RAISE("Interno", S("Dato nulo"));
  switch(data->type) {
    case UNDEF_R: case INT_R: case STR_R:
    case SET_R: case LST_R: case FN_R: case VOID_R:
      return res_new_return(res_new_str(res_enum_str(data->type)));
    default: return RAISE("Interno", S("Nodo inválido"));
  }
}

ResNode *eval_range(void) {
  DBG_FN_START;
  Symbol *from_sym = scope_get_sym("desde", str_hash("desde"));
  Symbol *step_sym = scope_get_sym("paso", str_hash("paso"));
  Symbol *to_sym = scope_get_sym("hasta", str_hash("hasta"));
  long from = 0;
  long step = 1;
  long to = 0;
  if(from_sym) {
    ResDataN *data = (ResDataN *)from_sym->value;
    if(data && data->type == INT_R) from = data->int_;
    else goto error_missing_from;
  } else goto error_missing_from;
  if(step_sym) {
    ResDataN *data = (ResDataN *)step_sym->value;
    if(data && data->type == INT_R) step = data->int_;
    else goto error_missing_step;
    if(step == 0) goto error_step_zero;
  } else goto error_missing_step;
  if(to_sym) {
    ResDataN *data = (ResDataN *)to_sym->value;
    if(data && data->type == INT_R) to = data->int_;
    else goto error_missing_to;
  } else goto error_missing_to;
  if((step < 0 && from < to) || (step > 0 && from > to)) {
    return res_new_return(res_new_lst(NULL, 0));
  }

  ResNode * r = res_new_ll_n(NULL);
  ResNode * last = r;

  long left = from < to ? from : to;
  long right = from < to ? to : from;
  long i = from;

  while(left <= i && i <= right) {
    last->data = res_new_int(i);
    i += step;
    if(left <= i && i <= right) last->next = res_new_ll_n(NULL);
    last = last->next;
  }

  return res_new_return(res_new_lst(r, right - left + 1));

  error_missing_from:
  return RAISE("Valor", S("Se debe indicar un entero como inicio del rango."));
  error_missing_step:
  return RAISE("Valor", S("Se debe indicar un entero como \"paso\" del rango."));
  error_missing_to:
  return RAISE("Valor", S("Se debe indicar un entero como final del rango."));
  error_step_zero:
  return RAISE("Valor", S("El valor 'paso' no puede ser 0"));
  // Valor, Tipo, Argumento u otro?
}

ResNode *eval_cast(InBuiltFnT to) {
  DBG_FN_START;
  Symbol *sym = scope_get_sym("x", str_hash("x"));
  NULL_RETURN(sym, "Interno", S("sym == NULL"));
  ResDataN *data = (ResDataN *)sym->value;
  NULL_RETURN(data, "Interno", S("data == NULL"));
  if(!(INT_R <= data->type && data->type <= LST_R)) {
    return RAISE("Tipo", S("Argumento inválido"));
  }
  ResNodeT from = data->type;
  ResNode *r = NULL;
  if(from == LST_R && to == CAST_SET_IFN) {                    // set([1]) = {1}
    int new_len = 0;
    ResNode *old_elem = data->elems;
    ResNode *new_elem = NULL;
    while((old_elem)) {
      // Si está repetido, liberar (no se inserta)
      if(!set_insert_elem(old_elem->data, &new_elem)) {
        // La liberación se hace fuera de esta función
      } else new_len += 1;
      old_elem = old_elem->next;
    }
    r = res_new_set(new_elem, new_len);
  } else if(from == INT_R && to == CAST_SET_IFN) {               // set(1) = {1}
    r = res_new_set(res_new_ll_n(res_new_int(data->int_)), 1);
  } else if(from == SET_R && to == CAST_SET_IFN) {         // set({"1"}) = {"1"}
    ResNode *new_elem, *old_elem, *new_ll = NULL;
    if((old_elem = data->elems)) {
      new_ll = new_elem = res_new_ll_n(old_elem->data);
      while((old_elem = old_elem->next)) {
        new_elem->next = res_new_ll_n(old_elem->data);
      }
    }
    r = res_new_set(new_ll, data->len);
  } else {
    return RAISE("Interno", S("No implementado"));
  }
  // set("[1]") = {"[1]"}
  // set("{'1'}") = {"{'1'}"}
  // lst(1) = [1]
  // lst("{1}") = ["{1}"]
  // lst("['1']") = ["['1']"]
  // lst({1}) = [1]
  // lst(["1"]) = ["1"]
  // str(1) = "1"
  // str("[1]") = "[1]"
  // str("{'1'}") = "{'1'}"
  // str([1]) = "[1]"
  // str({"1"}) = '{"1"}'
  // int(1) = 1
  // int("1") = 1
  // int("a") = error
  // int([1]) = error
  // int({"1"}) = error
  // otros?
  // '{1}' => {1} <!> Requiere de "reentrant parser" y otras modificaciones
  return res_new_return(MAYBE_ERROR(r));
}

ResNode *eval_copy(void) {
  DBG_FN_START;
  Symbol *sym = scope_get_sym("x", str_hash("x"));
  NULL_RETURN(sym, "Interno", S("sym == NULL"));
  ResNode *data = sym->value;
  NULL_RETURN(data, "Interno", S("data == NULL"));
  return res_new_return(data_copy(data));
}

ResNode *eval_refcnt(void) {
  DBG_FN_START;
  Symbol *sym = scope_get_sym("x", str_hash("x"));
  NULL_RETURN(sym, "Interno", S("sym == NULL"));
  ResDataN *data = (ResDataN *)sym->value;
  NULL_RETURN(data, "Interno", S("data == NULL"));
  return res_new_return(res_new_int(data->refcnt - 1));
}

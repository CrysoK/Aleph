#pragma once

// Macros para mensajes de la forma: print(LOC_S "... %s ...", ..., LOC, ...);
#define LOC_S "(%s:%d %s) "
#define LOC __FILE__,__LINE__,__func__

/*
#define MALLOC(type, size) ({ \
  type *_x = (type *)malloc(size); \
  if(!_x) return out_of_mem(LOC);\
  _x; \
})
*/

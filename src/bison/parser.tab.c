/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 17 "src/bison/parser.y"

  #include "bison.h"
  YYLTYPE g_prev_loc;
  int g_scope = 0;
  int g_loops = 0;
  int g_fns = 0;

#line 79 "src/bison/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LET = 3,                        /* "let"  */
  YYSYMBOL_IF = 4,                         /* "if"  */
  YYSYMBOL_ELIF = 5,                       /* "elif"  */
  YYSYMBOL_ELSE = 6,                       /* "else"  */
  YYSYMBOL_WHILE = 7,                      /* "while"  */
  YYSYMBOL_FOR = 8,                        /* "for"  */
  YYSYMBOL_IN = 9,                         /* "in"  */
  YYSYMBOL_FN = 10,                        /* "fn"  */
  YYSYMBOL_RETURN = 11,                    /* "return"  */
  YYSYMBOL_BREAK = 12,                     /* "break"  */
  YYSYMBOL_CONTINUE = 13,                  /* "continue"  */
  YYSYMBOL_EXIT = 14,                      /* "exit"  */
  YYSYMBOL_DEL = 15,                       /* "del"  */
  YYSYMBOL_OR = 16,                        /* "or"  */
  YYSYMBOL_AND = 17,                       /* "and"  */
  YYSYMBOL_NOT = 18,                       /* "not"  */
  YYSYMBOL_EQ = 19,                        /* "=="  */
  YYSYMBOL_NE = 20,                        /* "!="  */
  YYSYMBOL_LE = 21,                        /* "<="  */
  YYSYMBOL_GE = 22,                        /* ">="  */
  YYSYMBOL_ADD_A = 23,                     /* "+="  */
  YYSYMBOL_SUB_A = 24,                     /* "-="  */
  YYSYMBOL_MUL_A = 25,                     /* "*="  */
  YYSYMBOL_DIV_A = 26,                     /* "/="  */
  YYSYMBOL_EOL = 27,                       /* "fin de línea"  */
  YYSYMBOL_ID = 28,                        /* "identificador"  */
  YYSYMBOL_ATOM_LIT = 29,                  /* "átomo"  */
  YYSYMBOL_INT_LIT = 30,                   /* "entero"  */
  YYSYMBOL_DOTS = 31,                      /* "..."  */
  YYSYMBOL_32_ = 32,                       /* ';'  */
  YYSYMBOL_33_ = 33,                       /* '{'  */
  YYSYMBOL_34_ = 34,                       /* '}'  */
  YYSYMBOL_35_ = 35,                       /* '('  */
  YYSYMBOL_36_ = 36,                       /* ')'  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_ = 38,                       /* '='  */
  YYSYMBOL_39_ = 39,                       /* '['  */
  YYSYMBOL_40_ = 40,                       /* '!'  */
  YYSYMBOL_41_ = 41,                       /* ']'  */
  YYSYMBOL_42_ = 42,                       /* '<'  */
  YYSYMBOL_43_ = 43,                       /* '>'  */
  YYSYMBOL_44_ = 44,                       /* '+'  */
  YYSYMBOL_45_ = 45,                       /* '-'  */
  YYSYMBOL_46_ = 46,                       /* '*'  */
  YYSYMBOL_47_ = 47,                       /* '/'  */
  YYSYMBOL_48_ = 48,                       /* '#'  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_stmt_list = 51,                 /* stmt_list  */
  YYSYMBOL_eos = 52,                       /* eos  */
  YYSYMBOL_stmt = 53,                      /* stmt  */
  YYSYMBOL_block = 54,                     /* block  */
  YYSYMBOL_55_1 = 55,                      /* $@1  */
  YYSYMBOL_fn = 56,                        /* fn  */
  YYSYMBOL_57_2 = 57,                      /* $@2  */
  YYSYMBOL_58_3 = 58,                      /* $@3  */
  YYSYMBOL_params = 59,                    /* params  */
  YYSYMBOL_if = 60,                        /* if  */
  YYSYMBOL_elif = 61,                      /* elif  */
  YYSYMBOL_for = 62,                       /* for  */
  YYSYMBOL_63_4 = 63,                      /* $@4  */
  YYSYMBOL_64_5 = 64,                      /* $@5  */
  YYSYMBOL_65_6 = 65,                      /* $@6  */
  YYSYMBOL_while = 66,                     /* while  */
  YYSYMBOL_67_7 = 67,                      /* $@7  */
  YYSYMBOL_decl = 68,                      /* decl  */
  YYSYMBOL_assign = 69,                    /* assign  */
  YYSYMBOL_assignable_list = 70,           /* assignable_list  */
  YYSYMBOL_assignable = 71,                /* assignable  */
  YYSYMBOL_insert = 72,                    /* insert  */
  YYSYMBOL_id_list = 73,                   /* id_list  */
  YYSYMBOL_expr_list = 74,                 /* expr_list  */
  YYSYMBOL_assign_op = 75,                 /* assign_op  */
  YYSYMBOL_del = 76,                       /* del  */
  YYSYMBOL_del_target_list = 77,           /* del_target_list  */
  YYSYMBOL_del_target = 78,                /* del_target  */
  YYSYMBOL_return = 79,                    /* return  */
  YYSYMBOL_expr = 80,                      /* expr  */
  YYSYMBOL_and = 81,                       /* and  */
  YYSYMBOL_not = 82,                       /* not  */
  YYSYMBOL_cmp = 83,                       /* cmp  */
  YYSYMBOL_sum = 84,                       /* sum  */
  YYSYMBOL_term = 85,                      /* term  */
  YYSYMBOL_factor = 86,                    /* factor  */
  YYSYMBOL_primary = 87,                   /* primary  */
  YYSYMBOL_88_8 = 88,                      /* $@8  */
  YYSYMBOL_89_9 = 89,                      /* $@9  */
  YYSYMBOL_call = 90,                      /* call  */
  YYSYMBOL_args = 91,                      /* args  */
  YYSYMBOL_elem = 92                       /* elem  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   362

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    48,     2,     2,     2,     2,
      35,    36,    46,    44,    37,    45,     2,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
      42,    38,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   119,   119,   122,   136,   146,   159,   162,   163,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   183,   189,   208,   208,   213,   213,   213,   220,   221,
     225,   226,   229,   234,   237,   238,   241,   241,   241,   241,
     247,   247,   253,   255,   260,   265,   269,   272,   274,   277,
     278,   281,   285,   288,   292,   295,   296,   297,   298,   299,
     302,   305,   306,   309,   310,   311,   316,   317,   320,   321,
     324,   325,   328,   329,   332,   333,   334,   335,   336,   337,
     338,   342,   345,   348,   351,   354,   357,   360,   361,   364,
     365,   366,   369,   370,   371,   372,   373,   374,   376,   376,
     379,   379,   384,   387,   388,   391
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "let", "if", "elif", "else",
  "while", "for", "in", "fn", "return", "break", "continue", "exit", "del",
  "or", "and", "not", "==", "!=", "<=", ">=", "+=", "-=", "*=", "/=",
  "fin de línea", "identificador", "átomo", "entero", "...", "';'", "'{'",
  "'}'", "'('", "')'", "','", "'='", "'['", "'!'", "']'", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'#'", "$accept", "program", "stmt_list",
  "eos", "stmt", "block", "$@1", "fn", "$@2", "$@3", "params", "if",
  "elif", "for", "$@4", "$@5", "$@6", "while", "$@7", "decl", "assign",
  "assignable_list", "assignable", "insert", "id_list", "expr_list",
  "assign_op", "del", "del_target_list", "del_target", "return", "expr",
  "and", "not", "cmp", "sum", "term", "factor", "primary", "$@8", "$@9",
  "call", "args", "elem", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-90)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-66)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     182,   -90,    13,   292,   292,   -90,    19,   292,   -90,   -90,
     -90,   300,   292,    95,   -90,   -90,   -90,   292,   -90,   314,
     229,    51,    12,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     111,   -90,   -90,   -90,   -90,    50,    83,   -90,   258,   -23,
      65,   -90,    17,   -90,   181,   -90,    87,   -90,    38,    22,
     -90,    50,    42,    56,    50,    35,    85,   -90,   263,    76,
     -90,   292,     9,   292,   -90,    22,   -90,   -15,   -90,   -90,
      20,   -90,   -90,   -90,   -90,   322,   -90,   292,   292,   292,
     314,   118,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   292,   269,   101,   292,   -90,    79,   292,   110,
     -90,   -90,   300,   314,   108,    50,   125,   -90,   119,   221,
     -90,   -90,    22,   108,    83,   -90,   -23,   314,   -23,   -23,
     -23,   -23,   -23,   -23,    65,    65,   -90,   -90,   126,   292,
      47,   -90,   108,   143,   292,   110,   -90,    -1,   -90,   154,
      70,   -90,    72,   292,   -90,   -90,   -90,   -23,   -90,     2,
     123,   -90,    96,    38,   -90,   292,   -90,   131,   137,    50,
     141,   142,   -90,   221,    79,    50,   -90,    74,   292,   292,
     -90,   110,   110,   -90,    50,    50,   -90,   -90
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     6,     0,     0,     0,    36,     0,    67,    20,    21,
      19,     0,     0,    95,    97,    96,   100,     0,    98,     0,
       0,     0,     0,     4,    17,    14,    15,    16,    10,    11,
       0,    46,    13,    12,    22,    18,    69,    71,    73,    82,
      85,    88,    91,    93,    94,    52,    42,    95,     0,    91,
      94,    40,     0,     0,    66,    95,    60,    62,     0,    94,
      72,   104,     0,   104,    89,    90,     1,     0,     7,     8,
       9,    56,    57,    58,    59,     0,    55,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   104,     0,     0,     0,    23,    35,     0,     0,
      37,    25,     0,     0,   103,    54,     0,    92,     0,     9,
       3,    45,     0,    44,    68,    70,    81,     0,    74,    75,
      78,    79,    76,    77,    83,    84,    86,    87,     0,     0,
       0,    51,    43,     0,     0,     0,    32,     0,    41,     0,
      31,    61,    81,     0,   101,    99,     5,    80,   102,     0,
       0,   105,     0,     0,    34,     0,    30,     0,    28,    53,
       0,     0,    24,     9,    35,    38,    26,     0,     0,     0,
      33,     0,     0,    29,    49,    50,    39,    27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,    48,   -58,   -67,   -89,   -90,   -90,   -90,   -90,
     -90,   -90,    23,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   109,   -90,    58,   -66,   -90,   -90,   -90,    97,
     -90,    -3,   124,     7,    -9,   158,    53,   -12,     6,   -90,
     -90,   -90,   -55,     5
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    21,    22,    70,    23,    97,   133,    24,   140,   172,
     157,    25,   136,    26,    52,   139,   171,    27,    99,    28,
      29,    30,    31,    32,    46,   104,    77,    33,    56,    57,
      34,    35,    36,    37,    38,    39,    40,    41,    49,    63,
      61,    43,   106,    50
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,    51,    58,   110,    54,    44,    42,    64,   108,   109,
     138,   113,    68,    67,    62,    78,    59,    69,    78,    60,
      -2,    88,    89,     2,     3,    78,    65,     4,     5,   132,
       6,     7,     8,     9,    10,    11,   -63,   128,    12,    68,
     151,    45,   146,   160,    69,   107,   154,    53,    13,    14,
      15,    66,    92,    16,    78,    17,    93,    92,   105,    18,
     105,    98,   -63,    78,   164,    19,    78,   -63,    20,   -63,
     100,    96,   -63,   -65,   105,    44,    42,   -64,   126,   127,
      44,   112,   176,   177,   134,   135,   115,   150,   151,   105,
     130,   101,   105,    58,   163,   137,   110,    67,    45,   -65,
      79,   156,   131,   -64,   -65,   173,   -65,    59,   -64,   -65,
     -64,    90,    91,   -64,    44,    42,    88,    89,   -47,   -47,
     -47,   -47,   102,    68,    94,    95,   149,   117,    69,   131,
     162,   153,   -47,   -47,    71,    72,    73,    74,    44,    42,
     159,   124,   125,    96,     1,   143,     2,     3,    75,    76,
       4,     5,   165,     6,     7,     8,     9,    10,    11,   144,
     145,    12,   148,   155,   161,   174,   175,   166,    44,    42,
      -9,    13,    14,    15,   167,    -9,    16,    -9,    17,   168,
     169,   152,    18,     1,   111,     2,     3,   170,    19,     4,
       5,    20,     6,     7,     8,     9,    10,    11,   158,   141,
      12,     0,   114,     0,   -48,   -48,   -48,   -48,     0,    -9,
      13,    14,    15,     0,    -9,    16,     0,    17,   -48,   -48,
       0,    18,     0,     0,     2,     3,     0,    19,     4,     5,
      20,     6,     7,     8,     9,    10,    11,     0,   116,    12,
     118,   119,   120,   121,   122,   123,     0,     0,     0,    13,
      14,    15,     0,     0,    16,     0,    17,    47,    14,    15,
      18,   142,    16,     0,    17,     0,    19,    80,    18,    20,
       0,     0,   103,     0,     0,   147,    81,    82,    83,    84,
      85,    81,    82,    83,    84,    85,     0,    12,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,    14,    15,
      86,    87,    16,     0,    17,    86,    87,     0,    18,   129,
      12,     0,     0,     0,    19,     0,     0,    20,     0,     0,
      47,    14,    15,     0,     0,    16,     0,    17,    55,    14,
      15,    18,     0,    16,     0,    17,     0,    19,     0,    18,
      20,     0,    47,    14,    15,    19,     0,    16,    20,    17,
      13,    14,    15,    18,     0,    16,     0,    17,     0,    19,
       0,    18,    20
};

static const yytype_int16 yycheck[] =
{
       3,     4,    11,    70,     7,     0,     0,    19,    63,    67,
      99,    77,    27,     1,    17,    16,    11,    32,    16,    12,
       0,    44,    45,     3,     4,    16,    20,     7,     8,    95,
      10,    11,    12,    13,    14,    15,     1,    92,    18,    27,
      41,    28,   109,    41,    32,    36,   135,    28,    28,    29,
      30,     0,    35,    33,    16,    35,    39,    35,    61,    39,
      63,    39,    27,    16,   153,    45,    16,    32,    48,    34,
      28,    33,    37,     1,    77,    70,    70,     1,    90,    91,
      75,    75,   171,   172,     5,     6,    79,    40,    41,    92,
      93,    35,    95,   102,   152,    98,   163,     1,    28,    27,
      17,    31,    28,    27,    32,    31,    34,   102,    32,    37,
      34,    46,    47,    37,   109,   109,    44,    45,    23,    24,
      25,    26,    37,    27,    37,    38,   129,     9,    32,    28,
      34,   134,    37,    38,    23,    24,    25,    26,   133,   133,
     143,    88,    89,    33,     1,    37,     3,     4,    37,    38,
       7,     8,   155,    10,    11,    12,    13,    14,    15,    34,
      41,    18,    36,     9,    41,   168,   169,    36,   163,   163,
      27,    28,    29,    30,    37,    32,    33,    34,    35,    38,
      38,   133,    39,     1,    75,     3,     4,   164,    45,     7,
       8,    48,    10,    11,    12,    13,    14,    15,   140,   102,
      18,    -1,    78,    -1,    23,    24,    25,    26,    -1,    27,
      28,    29,    30,    -1,    32,    33,    -1,    35,    37,    38,
      -1,    39,    -1,    -1,     3,     4,    -1,    45,     7,     8,
      48,    10,    11,    12,    13,    14,    15,    -1,    80,    18,
      82,    83,    84,    85,    86,    87,    -1,    -1,    -1,    28,
      29,    30,    -1,    -1,    33,    -1,    35,    28,    29,    30,
      39,   103,    33,    -1,    35,    -1,    45,     9,    39,    48,
      -1,    -1,     9,    -1,    -1,   117,    18,    19,    20,    21,
      22,    18,    19,    20,    21,    22,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    30,
      42,    43,    33,    -1,    35,    42,    43,    -1,    39,    40,
      18,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,
      28,    29,    30,    -1,    -1,    33,    -1,    35,    28,    29,
      30,    39,    -1,    33,    -1,    35,    -1,    45,    -1,    39,
      48,    -1,    28,    29,    30,    45,    -1,    33,    48,    35,
      28,    29,    30,    39,    -1,    33,    -1,    35,    -1,    45,
      -1,    39,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     7,     8,    10,    11,    12,    13,
      14,    15,    18,    28,    29,    30,    33,    35,    39,    45,
      48,    50,    51,    53,    56,    60,    62,    66,    68,    69,
      70,    71,    72,    76,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    90,    92,    28,    73,    28,    80,    87,
      92,    80,    63,    28,    80,    28,    77,    78,    83,    92,
      82,    89,    80,    88,    86,    87,     0,     1,    27,    32,
      52,    23,    24,    25,    26,    37,    38,    75,    16,    17,
       9,    18,    19,    20,    21,    22,    42,    43,    44,    45,
      46,    47,    35,    39,    37,    38,    33,    54,    39,    67,
      28,    35,    37,     9,    74,    80,    91,    36,    91,    52,
      53,    71,    87,    74,    81,    82,    84,     9,    84,    84,
      84,    84,    84,    84,    85,    85,    86,    86,    91,    40,
      80,    28,    74,    55,     5,     6,    61,    80,    54,    64,
      57,    78,    84,    37,    34,    41,    53,    84,    36,    80,
      40,    41,    51,    80,    54,     9,    31,    59,    73,    80,
      41,    41,    34,    52,    54,    80,    36,    37,    38,    38,
      61,    65,    58,    31,    80,    80,    54,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    51,    52,    52,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    55,    54,    57,    58,    56,    59,    59,
      59,    59,    60,    61,    61,    61,    63,    64,    65,    62,
      67,    66,    68,    68,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    75,    75,    75,
      76,    77,    77,    78,    78,    78,    79,    79,    80,    80,
      81,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    84,    84,    84,    85,    85,    85,    86,
      86,    86,    87,    87,    87,    87,    87,    87,    88,    87,
      89,    87,    90,    91,    91,    92
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     1,     4,     1,     1,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     0,     8,     1,     3,
       1,     0,     4,     4,     2,     0,     0,     0,     0,     8,
       0,     4,     2,     4,     3,     3,     1,     1,     1,     7,
       7,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     1,     1,     3,     2,     1,     3,     1,
       3,     1,     2,     1,     3,     3,     3,     3,     3,     3,
       4,     3,     1,     3,     3,     1,     3,     3,     1,     2,
       2,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     4,     1,     0,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




/* The kind of the lookahead of this context.  */
static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx)
{
  return yyctx->yytoken;
}

/* The location of the lookahead of this context.  */
static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx)
{
  return yyctx->yylloc;
}

/* User defined function to report a syntax error.  */
static int
yyreport_syntax_error (const yypcontext_t *yyctx);

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_ID: /* "identificador"  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1220 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_ATOM_LIT: /* "átomo"  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1229 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_INT_LIT: /* "entero"  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1238 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_DOTS: /* "..."  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1247 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_stmt_list: /* stmt_list  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1256 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_stmt: /* stmt  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1265 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_block: /* block  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1274 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_fn: /* fn  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1283 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_params: /* params  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1292 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_if: /* if  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1301 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_elif: /* elif  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1310 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_for: /* for  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1319 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_while: /* while  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1328 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_decl: /* decl  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1337 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_assign: /* assign  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1346 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_assignable_list: /* assignable_list  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1355 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_assignable: /* assignable  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1364 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_insert: /* insert  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1373 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_id_list: /* id_list  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1382 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1391 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_del: /* del  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1400 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_del_target_list: /* del_target_list  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1409 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_del_target: /* del_target  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1418 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_return: /* return  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1427 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1436 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_and: /* and  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1445 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_not: /* not  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1454 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_cmp: /* cmp  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1463 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_sum: /* sum  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1472 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_term: /* term  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1481 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_factor: /* factor  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1490 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_primary: /* primary  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1499 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_call: /* call  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1508 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_args: /* args  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1517 "src/bison/parser.tab.c"
        break;

    case YYSYMBOL_elem: /* elem  */
#line 108 "src/bison/parser.y"
            {
  print_dbg("%%destructor: <ast>");
  ast_free(((*yyvaluep).ast));
}
#line 1526 "src/bison/parser.tab.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmt_list eos  */
#line 119 "src/bison/parser.y"
                    { g_ast = ast_reverse_ll((yyvsp[-1].ast)); }
#line 1821 "src/bison/parser.tab.c"
    break;

  case 3: /* stmt_list: stmt_list eos stmt  */
#line 122 "src/bison/parser.y"
                         {
      // printf("stmt_list -> stmt_list eos stmt\n");

      if((yyvsp[-2].ast)) (yyval.ast) = (yyvsp[0].ast) ? ast_add_next_ll_n(ast_new_ll_n((yyvsp[0].ast), (yylsp[0])), (yyvsp[-2].ast)) : (yyvsp[-2].ast);
      else (yyval.ast) = ast_new_ll_n((yyvsp[0].ast), (yylsp[0]));

      // Si no se está en un bloque
      if((yyvsp[0].ast) && !g_scope) {
        if(g_repl) repl_eval((yyvsp[0].ast));
        // En archivos también se evalúa stmt por stmt para un mejor reporte de errores
        else file_eval((yyvsp[0].ast));
      }
      CHECK_EXIT((yyval.ast));
    }
#line 1840 "src/bison/parser.tab.c"
    break;

  case 4: /* stmt_list: stmt  */
#line 136 "src/bison/parser.y"
            {
      // printf("stmt_list -> stmt\n");
      (yyval.ast) = ast_new_ll_n((yyvsp[0].ast), (yylsp[0]));

      if((yyvsp[0].ast) && !g_scope) {
        if(g_repl) repl_eval((yyvsp[0].ast));
        else file_eval((yyvsp[0].ast));
      }
      CHECK_EXIT((yyval.ast));
    }
#line 1855 "src/bison/parser.tab.c"
    break;

  case 5: /* stmt_list: stmt_list error eos stmt  */
#line 146 "src/bison/parser.y"
                               { // Captura errores y evita perder el AST
      // printf("stmt_list -> stmt_list error eos stmt\n");
      if((yyvsp[-3].ast)) (yyval.ast) = (yyvsp[0].ast) ? ast_add_next_ll_n(ast_new_ll_n((yyvsp[0].ast), (yylsp[0])), (yyvsp[-3].ast)) : (yyvsp[-3].ast);
      else (yyval.ast) = ast_new_ll_n((yyvsp[0].ast), (yylsp[0]));

      // Si no se está en un bloque
      if((yyvsp[0].ast) && !g_scope) {
        if(g_repl) repl_eval((yyvsp[0].ast));
        // En archivos también se evalúa stmt por stmt para un mejor reporte de errores
        else file_eval((yyvsp[0].ast));
      }
      CHECK_EXIT((yyval.ast));
    }
#line 1873 "src/bison/parser.tab.c"
    break;

  case 6: /* stmt_list: error  */
#line 159 "src/bison/parser.y"
            { (yyval.ast) = NULL; }
#line 1879 "src/bison/parser.tab.c"
    break;

  case 7: /* eos: "fin de línea"  */
#line 162 "src/bison/parser.y"
          { yyerrok; repl_prompt(); }
#line 1885 "src/bison/parser.tab.c"
    break;

  case 8: /* eos: ';'  */
#line 163 "src/bison/parser.y"
          { yyerrok; }
#line 1891 "src/bison/parser.tab.c"
    break;

  case 9: /* stmt: %empty  */
#line 166 "src/bison/parser.y"
             { (yyval.ast) = NULL; }
#line 1897 "src/bison/parser.tab.c"
    break;

  case 18: /* stmt: expr  */
#line 175 "src/bison/parser.y"
           { (yyval.ast) = ast_new_exprst((yyvsp[0].ast)); }
#line 1903 "src/bison/parser.tab.c"
    break;

  case 19: /* stmt: "exit"  */
#line 176 "src/bison/parser.y"
             { (yyval.ast) = ast_new_exit(); }
#line 1909 "src/bison/parser.tab.c"
    break;

  case 20: /* stmt: "break"  */
#line 177 "src/bison/parser.y"
              { 
      if(g_loops <= 0) {
        yyerror("'break' fuera de un ciclo.");
        YYERROR;
      } else (yyval.ast) = ast_new_break();
    }
#line 1920 "src/bison/parser.tab.c"
    break;

  case 21: /* stmt: "continue"  */
#line 183 "src/bison/parser.y"
                 {
      if(g_loops <= 0) {
        yyerror("'continue' fuera de un ciclo.");
        YYERROR;
      } else (yyval.ast) = ast_new_continue();
    }
#line 1931 "src/bison/parser.tab.c"
    break;

  case 22: /* stmt: return  */
#line 189 "src/bison/parser.y"
             {
      if(g_fns <= 0) {
        yyerror("'return' fuera de una función.");
        YYERROR;
      } else (yyval.ast) = (yyvsp[0].ast);
    }
#line 1942 "src/bison/parser.tab.c"
    break;

  case 23: /* $@1: %empty  */
#line 208 "src/bison/parser.y"
          { g_scope++; }
#line 1948 "src/bison/parser.tab.c"
    break;

  case 24: /* block: '{' $@1 stmt_list '}'  */
#line 208 "src/bison/parser.y"
                                       { g_scope--;
      (yyval.ast) = ast_reverse_ll((yyvsp[-1].ast));
    }
#line 1956 "src/bison/parser.tab.c"
    break;

  case 25: /* $@2: %empty  */
#line 213 "src/bison/parser.y"
                  { g_scope++; }
#line 1962 "src/bison/parser.tab.c"
    break;

  case 26: /* $@3: %empty  */
#line 213 "src/bison/parser.y"
                                            { g_scope--; g_fns++; }
#line 1968 "src/bison/parser.tab.c"
    break;

  case 27: /* fn: "fn" "identificador" '(' $@2 params ')' $@3 block  */
#line 213 "src/bison/parser.y"
                                                                          {
      g_fns--;
      if(g_scope > 0) { yyerror("Definición de función dentro de un bloque"); YYERROR; }
      else (yyval.ast) = ast_new_fndef((yyvsp[-6].ast), ast_reverse_ll((yyvsp[-3].ast)), (yyvsp[0].ast));
    }
#line 1978 "src/bison/parser.tab.c"
    break;

  case 28: /* params: id_list  */
#line 220 "src/bison/parser.y"
              { (yyval.ast) = (yyvsp[0].ast); }
#line 1984 "src/bison/parser.tab.c"
    break;

  case 29: /* params: id_list ',' "..."  */
#line 221 "src/bison/parser.y"
                        {
      (yyval.ast) = ast_add_next_ll_n(ast_new_ll_n((yyvsp[0].ast), (yylsp[0])), (yyvsp[-2].ast));
      
    }
#line 1993 "src/bison/parser.tab.c"
    break;

  case 30: /* params: "..."  */
#line 225 "src/bison/parser.y"
            { (yyval.ast) = ast_new_ll_n((yyvsp[0].ast), (yylsp[0])); }
#line 1999 "src/bison/parser.tab.c"
    break;

  case 31: /* params: %empty  */
#line 226 "src/bison/parser.y"
             { (yyval.ast) = NULL; }
#line 2005 "src/bison/parser.tab.c"
    break;

  case 32: /* if: "if" expr block elif  */
#line 229 "src/bison/parser.y"
                           {
      (yyval.ast) = ast_new_if((yyvsp[-2].ast), (yyvsp[-1].ast), (yyvsp[0].ast));
    }
#line 2013 "src/bison/parser.tab.c"
    break;

  case 33: /* elif: "elif" expr block elif  */
#line 234 "src/bison/parser.y"
                             {
      (yyval.ast) = ast_new_ll_n(ast_new_if((yyvsp[-2].ast), (yyvsp[-1].ast), (yyvsp[0].ast)), (yylsp[-3]));
    }
#line 2021 "src/bison/parser.tab.c"
    break;

  case 34: /* elif: "else" block  */
#line 237 "src/bison/parser.y"
                   { (yyval.ast) = (yyvsp[0].ast); }
#line 2027 "src/bison/parser.tab.c"
    break;

  case 35: /* elif: %empty  */
#line 238 "src/bison/parser.y"
             { (yyval.ast) = NULL; }
#line 2033 "src/bison/parser.tab.c"
    break;

  case 36: /* $@4: %empty  */
#line 241 "src/bison/parser.y"
            { g_scope++; }
#line 2039 "src/bison/parser.tab.c"
    break;

  case 37: /* $@5: %empty  */
#line 241 "src/bison/parser.y"
                              { g_scope--; }
#line 2045 "src/bison/parser.tab.c"
    break;

  case 38: /* $@6: %empty  */
#line 241 "src/bison/parser.y"
                                                       { g_loops++; }
#line 2051 "src/bison/parser.tab.c"
    break;

  case 39: /* for: "for" $@4 "identificador" $@5 "in" expr $@6 block  */
#line 241 "src/bison/parser.y"
                                                                            {
      g_loops--;
      (yyval.ast) = ast_new_for((yyvsp[-5].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 2060 "src/bison/parser.tab.c"
    break;

  case 40: /* $@7: %empty  */
#line 247 "src/bison/parser.y"
                   { g_loops++; }
#line 2066 "src/bison/parser.tab.c"
    break;

  case 41: /* while: "while" expr $@7 block  */
#line 247 "src/bison/parser.y"
                                        {
      g_loops--;
      (yyval.ast) = ast_new_while((yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 2075 "src/bison/parser.tab.c"
    break;

  case 42: /* decl: "let" id_list  */
#line 253 "src/bison/parser.y"
                    { (yyval.ast) = ast_new_decl(ast_reverse_ll((yyvsp[0].ast)), NULL); }
#line 2081 "src/bison/parser.tab.c"
    break;

  case 43: /* decl: "let" id_list '=' expr_list  */
#line 255 "src/bison/parser.y"
                                  {
      (yyval.ast) = ast_new_decl(ast_reverse_ll((yyvsp[-2].ast)), ast_reverse_ll((yyvsp[0].ast)));
    }
#line 2089 "src/bison/parser.tab.c"
    break;

  case 44: /* assign: assignable_list assign_op expr_list  */
#line 260 "src/bison/parser.y"
                                          {
       (yyval.ast) = ast_new_assign(ast_reverse_ll((yyvsp[-2].ast)), (yyvsp[-1].ast_t), ast_reverse_ll((yyvsp[0].ast)));
    }
#line 2097 "src/bison/parser.tab.c"
    break;

  case 45: /* assignable_list: assignable_list ',' assignable  */
#line 265 "src/bison/parser.y"
                                     {
      // La lista se construye en orden inverso
      (yyval.ast) = ast_add_next_ll_n(ast_new_ll_n((yyvsp[0].ast), (yylsp[0])), (yyvsp[-2].ast));
    }
#line 2106 "src/bison/parser.tab.c"
    break;

  case 46: /* assignable_list: assignable  */
#line 269 "src/bison/parser.y"
                  { (yyval.ast) = ast_new_ll_n((yyvsp[0].ast), (yylsp[0])); }
#line 2112 "src/bison/parser.tab.c"
    break;

  case 49: /* insert: primary '[' '!' expr ']' '=' expr  */
#line 277 "src/bison/parser.y"
                                        { (yyval.ast) = ast_new_insert((yyvsp[-6].ast), (yyvsp[-3].ast), -1, (yyvsp[0].ast)); }
#line 2118 "src/bison/parser.tab.c"
    break;

  case 50: /* insert: primary '[' expr '!' ']' '=' expr  */
#line 278 "src/bison/parser.y"
                                        { (yyval.ast) = ast_new_insert((yyvsp[-6].ast), (yyvsp[-4].ast), 1, (yyvsp[0].ast)); }
#line 2124 "src/bison/parser.tab.c"
    break;

  case 51: /* id_list: id_list ',' "identificador"  */
#line 281 "src/bison/parser.y"
                     {
      // La lista se construye en orden inverso
      (yyval.ast) = ast_add_next_ll_n(ast_new_ll_n((yyvsp[0].ast), (yylsp[0])), (yyvsp[-2].ast)); // ID nunca es NULL
    }
#line 2133 "src/bison/parser.tab.c"
    break;

  case 52: /* id_list: "identificador"  */
#line 285 "src/bison/parser.y"
         { (yyval.ast) = ast_new_ll_n((yyvsp[0].ast), (yylsp[0])); }
#line 2139 "src/bison/parser.tab.c"
    break;

  case 53: /* expr_list: expr_list ',' expr  */
#line 288 "src/bison/parser.y"
                         {
      // La lista se construye en orden inverso
      (yyval.ast) = ast_add_next_ll_n(ast_new_ll_n((yyvsp[0].ast), (yylsp[0])), (yyvsp[-2].ast)); // expr nunca es NULL
    }
#line 2148 "src/bison/parser.tab.c"
    break;

  case 54: /* expr_list: expr  */
#line 292 "src/bison/parser.y"
           { (yyval.ast) = ast_new_ll_n((yyvsp[0].ast), (yylsp[0])); }
#line 2154 "src/bison/parser.tab.c"
    break;

  case 55: /* assign_op: '='  */
#line 295 "src/bison/parser.y"
          { (yyval.ast_t) = ASSIGN_AST; }
#line 2160 "src/bison/parser.tab.c"
    break;

  case 56: /* assign_op: "+="  */
#line 296 "src/bison/parser.y"
           { (yyval.ast_t) = ADD_AST; }
#line 2166 "src/bison/parser.tab.c"
    break;

  case 57: /* assign_op: "-="  */
#line 297 "src/bison/parser.y"
           { (yyval.ast_t) = SUB_AST; }
#line 2172 "src/bison/parser.tab.c"
    break;

  case 58: /* assign_op: "*="  */
#line 298 "src/bison/parser.y"
           { (yyval.ast_t) = MUL_AST; }
#line 2178 "src/bison/parser.tab.c"
    break;

  case 59: /* assign_op: "/="  */
#line 299 "src/bison/parser.y"
           { (yyval.ast_t) = DIV_AST; }
#line 2184 "src/bison/parser.tab.c"
    break;

  case 60: /* del: "del" del_target_list  */
#line 302 "src/bison/parser.y"
                            { (yyval.ast) = ast_new_del((yyvsp[0].ast)); }
#line 2190 "src/bison/parser.tab.c"
    break;

  case 61: /* del_target_list: del_target_list ',' del_target  */
#line 305 "src/bison/parser.y"
                                     { (yyval.ast) = ast_add_next_ll_n(ast_new_ll_n((yyvsp[0].ast), (yylsp[0])), (yyvsp[-2].ast)); }
#line 2196 "src/bison/parser.tab.c"
    break;

  case 62: /* del_target_list: del_target  */
#line 306 "src/bison/parser.y"
                 { (yyval.ast) = ast_new_ll_n((yyvsp[0].ast), (yylsp[0])); }
#line 2202 "src/bison/parser.tab.c"
    break;

  case 65: /* del_target: cmp "in" sum  */
#line 311 "src/bison/parser.y"
                   {
      (yyval.ast) = ast_new_in((yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 2210 "src/bison/parser.tab.c"
    break;

  case 66: /* return: "return" expr  */
#line 316 "src/bison/parser.y"
                    { (yyval.ast) = ast_new_return((yyvsp[0].ast)); }
#line 2216 "src/bison/parser.tab.c"
    break;

  case 67: /* return: "return"  */
#line 317 "src/bison/parser.y"
               { (yyval.ast) = ast_new_return(NULL); }
#line 2222 "src/bison/parser.tab.c"
    break;

  case 68: /* expr: expr "or" and  */
#line 320 "src/bison/parser.y"
                    { (yyval.ast) = ast_new_or((yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2228 "src/bison/parser.tab.c"
    break;

  case 70: /* and: and "and" not  */
#line 324 "src/bison/parser.y"
                    { (yyval.ast) = ast_new_and((yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2234 "src/bison/parser.tab.c"
    break;

  case 72: /* not: "not" not  */
#line 328 "src/bison/parser.y"
                { (yyval.ast) = ast_new_not((yyvsp[0].ast)); }
#line 2240 "src/bison/parser.tab.c"
    break;

  case 74: /* cmp: cmp "==" sum  */
#line 332 "src/bison/parser.y"
                   { (yyval.ast) = ast_new_equal((yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2246 "src/bison/parser.tab.c"
    break;

  case 75: /* cmp: cmp "!=" sum  */
#line 333 "src/bison/parser.y"
                   { (yyval.ast) = ast_new_not(ast_new_equal((yyvsp[-2].ast), (yyvsp[0].ast))); }
#line 2252 "src/bison/parser.tab.c"
    break;

  case 76: /* cmp: cmp '<' sum  */
#line 334 "src/bison/parser.y"
                  { (yyval.ast) = ast_new_less((yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2258 "src/bison/parser.tab.c"
    break;

  case 77: /* cmp: cmp '>' sum  */
#line 335 "src/bison/parser.y"
                  { (yyval.ast) = ast_new_less((yyvsp[0].ast), (yyvsp[-2].ast)); }
#line 2264 "src/bison/parser.tab.c"
    break;

  case 78: /* cmp: cmp "<=" sum  */
#line 336 "src/bison/parser.y"
                   { (yyval.ast) = ast_new_not(ast_new_less((yyvsp[0].ast), (yyvsp[-2].ast))); }
#line 2270 "src/bison/parser.tab.c"
    break;

  case 79: /* cmp: cmp ">=" sum  */
#line 337 "src/bison/parser.y"
                   { (yyval.ast) = ast_new_or(ast_new_less((yyvsp[0].ast), (yyvsp[-2].ast)), ast_new_equal((yyvsp[0].ast), (yyvsp[-2].ast))); }
#line 2276 "src/bison/parser.tab.c"
    break;

  case 80: /* cmp: cmp "not" "in" sum  */
#line 338 "src/bison/parser.y"
                         {
      // Negación de pertenencia (permite "x not in X" en vez de "not x in X")
      (yyval.ast) = ast_new_not(ast_new_in((yyvsp[-3].ast), (yyvsp[0].ast)));
    }
#line 2285 "src/bison/parser.tab.c"
    break;

  case 81: /* cmp: cmp "in" sum  */
#line 342 "src/bison/parser.y"
                   { // Pertenencia | Posición de un elemento
      (yyval.ast) = ast_new_in((yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 2293 "src/bison/parser.tab.c"
    break;

  case 83: /* sum: sum '+' term  */
#line 348 "src/bison/parser.y"
                   { // Suma | Unión | Concatenación
      (yyval.ast) = ast_new_add((yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 2301 "src/bison/parser.tab.c"
    break;

  case 84: /* sum: sum '-' term  */
#line 351 "src/bison/parser.y"
                   { // Resta | Diferencia
      (yyval.ast) = ast_new_sub((yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 2309 "src/bison/parser.tab.c"
    break;

  case 86: /* term: term '*' factor  */
#line 357 "src/bison/parser.y"
                      { // Producto | Intersección
      (yyval.ast) = ast_new_mul((yyvsp[-2].ast), (yyvsp[0].ast));
    }
#line 2317 "src/bison/parser.tab.c"
    break;

  case 87: /* term: term '/' factor  */
#line 360 "src/bison/parser.y"
                      { (yyval.ast) = ast_new_div((yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2323 "src/bison/parser.tab.c"
    break;

  case 89: /* factor: '-' factor  */
#line 364 "src/bison/parser.y"
                 { (yyval.ast) = ast_new_neg((yyvsp[0].ast)); }
#line 2329 "src/bison/parser.tab.c"
    break;

  case 90: /* factor: '#' primary  */
#line 365 "src/bison/parser.y"
                  { (yyval.ast) = ast_new_len((yyvsp[0].ast)); }
#line 2335 "src/bison/parser.tab.c"
    break;

  case 92: /* primary: '(' expr ')'  */
#line 369 "src/bison/parser.y"
                   { (yyval.ast) = (yyvsp[-1].ast); }
#line 2341 "src/bison/parser.tab.c"
    break;

  case 98: /* $@8: %empty  */
#line 376 "src/bison/parser.y"
          { g_scope++; }
#line 2347 "src/bison/parser.tab.c"
    break;

  case 99: /* primary: '[' $@8 args ']'  */
#line 376 "src/bison/parser.y"
                                 { g_scope--; // Literal lista
      (yyval.ast) = ast_new_lst((yyvsp[-1].ast));
    }
#line 2355 "src/bison/parser.tab.c"
    break;

  case 100: /* $@9: %empty  */
#line 379 "src/bison/parser.y"
          { g_scope++; }
#line 2361 "src/bison/parser.tab.c"
    break;

  case 101: /* primary: '{' $@9 args '}'  */
#line 379 "src/bison/parser.y"
                                  { g_scope--; // Literal conjunto
      (yyval.ast) = ast_new_set((yyvsp[-1].ast));
    }
#line 2369 "src/bison/parser.tab.c"
    break;

  case 102: /* call: primary '(' args ')'  */
#line 384 "src/bison/parser.y"
                           { (yyval.ast) = ast_new_fncall((yyvsp[-3].ast), (yyvsp[-1].ast)); }
#line 2375 "src/bison/parser.tab.c"
    break;

  case 103: /* args: expr_list  */
#line 387 "src/bison/parser.y"
                { (yyval.ast) = ast_reverse_ll((yyvsp[0].ast)); }
#line 2381 "src/bison/parser.tab.c"
    break;

  case 104: /* args: %empty  */
#line 388 "src/bison/parser.y"
             { (yyval.ast) = NULL; }
#line 2387 "src/bison/parser.tab.c"
    break;

  case 105: /* elem: primary '[' expr ']'  */
#line 391 "src/bison/parser.y"
                           { // Elemento según posición
      (yyval.ast) = ast_new_getelem((yyvsp[-3].ast), (yyvsp[-1].ast));
    }
#line 2395 "src/bison/parser.tab.c"
    break;


#line 2399 "src/bison/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        if (yyreport_syntax_error (&yyctx) == 2)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 395 "src/bison/parser.y"


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

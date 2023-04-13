/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser.ypp"

#include "def.h"
extern int ErrorCharNum;
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
void yyerror(const char* fmt, ...);
extern "C" int yylex();
#define SavePosition t->Line=yylloc.first_line;t->Column=yylloc.first_column
typedef struct YYLVAL {
       int                  type_int;
	float                type_float;
	char                 type_id[32];

	ProgAST                     *program;
	vector <ExtDefAST *>        ExtDefList;  	    //外部定义（外部变量、函数）列表
       ExtDefAST                   *ExtDef;
       vector <VarDecAST*>         ExtDecList;        //外部、局部变量列表
       TypeAST                     *Specifier;
       VarDecAST                   *VarDec;
       CompStmAST                  *CompSt;
	vector <ParamAST *>         ParamList;         //形参列表
	ParamAST                    *ParamDec;

	vector <StmAST *>           StmList;
	StmAST                      *Stmt;
	vector <DefAST *>           DefList;
	DefAST                      *Def;
       vector <VarDecAST *>        DecList;
       VarDecAST                   *Dec;
       ExpAST                      *Exp;
	vector <ExpAST *>           Args;       	       //实参列表
       CaseStmAST                  *Case;
       vector <CaseStmAST *>       CaseList;
}YYLVAL;
#define YYSTYPE YYLVAL


#line 109 "parser.tab.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    ID = 259,
    TYPE = 260,
    FLOAT = 261,
    DPLUS = 262,
    DMINUS = 263,
    PLUSD = 264,
    MINUSD = 265,
    LP = 266,
    RP = 267,
    LB = 268,
    RB = 269,
    LC = 270,
    RC = 271,
    SEMI = 272,
    COMMA = 273,
    PLUS = 274,
    MINUS = 275,
    STAR = 276,
    DIV = 277,
    MOD = 278,
    GE = 279,
    GT = 280,
    LE = 281,
    LT = 282,
    NE = 283,
    EQ = 284,
    ASSIGN = 285,
    AND = 286,
    OR = 287,
    NOT = 288,
    IF = 289,
    ELSE = 290,
    WHILE = 291,
    RETURN = 292,
    FOR = 293,
    BREAK = 294,
    CONTINUE = 295,
    SWITCH = 296,
    CASE = 297,
    DEFAULT = 298,
    COLON = 299,
    EXT_DEF_LIST = 300,
    EXT_VAR_DEF = 301,
    FUNC_DEF = 302,
    FUNC_DEC = 303,
    EXT_DEC_LIST = 304,
    PARAM_LIST = 305,
    PARAM_DEC = 306,
    VAR_DEF = 307,
    DEC_LIST = 308,
    DEF_LIST = 309,
    COMP_STM = 310,
    STM_LIST = 311,
    EXP_STMT = 312,
    IF_THEN = 313,
    IF_THEN_ELSE = 314,
    FUNC_CALL = 315,
    ARGS = 316,
    FUNCTION = 317,
    PARAM = 318,
    ARG = 319,
    CALL = 320,
    CALL0 = 321,
    LABEL = 322,
    GOTO = 323,
    JLT = 324,
    JLE = 325,
    JGT = 326,
    JGE = 327,
    JEQ = 328,
    JNE = 329,
    END = 330,
    ARRASSIGN = 331,
    ARRLOAD = 332,
    UMINUS = 333,
    UPLUS = 334,
    LOWER_THEN_ELSE = 335
  };
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   587

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155

#define YYUNDEFTOK  2
#define YYMAXUTOK   335


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   100,   100,   110,   111,   114,   116,   117,   119,   125,
     126,   128,   129,   131,   134,   135,   136,   138,   141,   143,
     144,   146,   147,   149,   151,   152,   154,   155,   158,   160,
     161,   163,   164,   165,   166,   167,   168,   169,   170,   172,
     173,   175,   176,   177,   180,   183,   184,   185,   186,   187,
     188,   189,   190,   192,   193,   194,   196,   197,   198,   199,
     200,   201,   204,   205,   206,   207,   210,   211,   212,   213,
     214,   216,   217,   218,   221,   223,   224
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "TYPE", "FLOAT", "DPLUS",
  "DMINUS", "PLUSD", "MINUSD", "LP", "RP", "LB", "RB", "LC", "RC", "SEMI",
  "COMMA", "PLUS", "MINUS", "STAR", "DIV", "MOD", "GE", "GT", "LE", "LT",
  "NE", "EQ", "ASSIGN", "AND", "OR", "NOT", "IF", "ELSE", "WHILE",
  "RETURN", "FOR", "BREAK", "CONTINUE", "SWITCH", "CASE", "DEFAULT",
  "COLON", "EXT_DEF_LIST", "EXT_VAR_DEF", "FUNC_DEF", "FUNC_DEC",
  "EXT_DEC_LIST", "PARAM_LIST", "PARAM_DEC", "VAR_DEF", "DEC_LIST",
  "DEF_LIST", "COMP_STM", "STM_LIST", "EXP_STMT", "IF_THEN",
  "IF_THEN_ELSE", "FUNC_CALL", "ARGS", "FUNCTION", "PARAM", "ARG", "CALL",
  "CALL0", "LABEL", "GOTO", "JLT", "JLE", "JGT", "JGE", "JEQ", "JNE",
  "END", "ARRASSIGN", "ARRLOAD", "UMINUS", "UPLUS", "LOWER_THEN_ELSE",
  "$accept", "program", "ExtDefList", "ExtDef", "Specifier", "ExtDecList",
  "VarDec", "ParamVarDec", "ParamList", "ParamDec", "CompSt", "StmList",
  "DefList", "Def", "DecList", "Dec", "Case", "CaseList", "Stmt", "Exp",
  "Args", "Sub", "SubList", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335
};
# endif

#define YYPACT_NINF (-67)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-20)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,   -67,    17,   -67,     5,    56,   -67,   -67,    50,    51,
      46,     5,   -67,    66,    70,    74,    12,   -67,    77,   -67,
     -67,   -67,   -67,    14,     5,   -67,     5,   -67,   -67,   -67,
      70,   112,     5,    -4,    75,    65,    76,   -67,    54,   -67,
     206,   206,   206,   206,   206,   206,    83,    84,     8,    85,
      80,    87,   103,   -67,   101,    69,   221,   -67,   206,   -67,
      70,   -67,   206,   206,   -67,   111,    35,    35,   247,    35,
      35,    35,   206,   206,   -67,   273,   206,   -67,   -67,   206,
     -67,   -67,   -67,   -67,   -67,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   481,
     -67,   481,    26,   299,   -67,   -67,   325,   351,   -67,   377,
     403,    13,    13,    35,    35,   211,   558,   558,   558,   558,
     155,   155,   507,   114,   533,   -67,   206,   -67,   153,   153,
     206,   110,   481,    91,   -67,   429,    88,   153,   206,   206,
      88,    -3,   -67,   455,   176,   -67,   -67,   100,   153,    69,
     112,   -67,   -67,   113,   -67
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     8,     0,     2,     3,     0,     1,     4,    11,     0,
       9,    14,     5,     0,     0,     0,     0,    15,     0,    11,
      10,    13,    17,     0,     0,    12,    21,     7,     6,    16,
       0,     0,    21,    26,     0,    24,     0,    69,    67,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,     0,     0,     0,    22,     0,    23,
       0,    43,    71,     0,    75,    68,    62,    63,     0,    52,
      51,    55,     0,     0,    34,     0,     0,    41,    42,     0,
      18,    20,    64,    65,    31,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      25,    72,     0,     0,    76,    50,     0,     0,    33,     0,
       0,    45,    46,    47,    48,    49,    57,    56,    59,    58,
      60,    61,    44,    53,    54,    66,     0,    74,     0,     0,
       0,     0,    73,    35,    37,     0,     0,     0,     0,     0,
      29,     0,    36,     0,     0,    30,    39,     0,     0,     0,
       0,    38,    28,     0,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -67,   -67,   143,   -67,    55,   141,   -23,   -67,   -67,   134,
     142,   -49,   135,   -67,   106,   -67,   -67,    29,   -66,   -40,
     -67,   105,   -67
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,     5,     9,    10,    22,    16,    17,
      53,    54,    31,    32,    34,    35,   140,   141,    55,    56,
     102,    64,    65
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    67,    68,    69,    70,    71,    81,    33,    75,    13,
       1,    37,    38,   146,    39,    40,    41,     6,    99,    42,
      82,    83,   101,   103,    23,    74,    58,    43,    44,    26,
      24,    27,   106,   107,    87,    88,   109,    33,   125,   110,
     147,    45,    82,    83,   126,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,    13,
       8,    11,   133,   134,    14,    62,    15,    63,    12,    18,
      36,   142,    37,    38,    19,    39,    40,    41,    21,    15,
      42,    30,   151,    60,    26,   -19,   132,    30,    43,    44,
     135,    25,    59,    61,    72,    73,    76,    77,   143,   144,
     152,   153,    45,    46,    78,    47,    48,    49,    50,    51,
      52,   -19,   -19,    36,    79,    37,    38,    80,    39,    40,
      41,    82,    83,    42,    63,   136,   137,    26,   -19,   154,
     139,    43,    44,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,   150,    45,    46,     7,    47,    48,
      49,    50,    51,    52,    36,    20,    37,    38,    29,    39,
      40,    41,    82,    83,    42,    28,   100,    57,    26,   145,
     104,     0,    43,    44,    85,    86,    87,    88,    89,     0,
       0,     0,     0,    82,    83,     0,    45,    46,     0,    47,
      48,    49,    50,    51,    52,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    37,
      38,     0,    39,    40,    41,     0,     0,    42,    82,    83,
     149,     0,     0,     0,     0,    43,    44,     0,    82,    83,
      85,    86,    87,    88,     0,     0,     0,     0,    84,    45,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    82,    83,     0,     0,     0,   105,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      82,    83,     0,     0,     0,     0,     0,     0,     0,     0,
     108,     0,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    82,    83,     0,     0,
       0,     0,     0,   127,     0,     0,     0,     0,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    82,    83,     0,     0,     0,   128,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    82,    83,
       0,     0,     0,   129,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    82,    83,     0,     0,     0,     0,
       0,     0,     0,     0,   130,     0,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      82,    83,     0,     0,     0,   131,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    82,    83,     0,     0,
       0,     0,     0,     0,     0,     0,   138,     0,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    82,    83,     0,     0,     0,   148,     0,     0,
       0,     0,     0,     0,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    82,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    82,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,     0,    97,    98,
      82,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,     0,    97,    82,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,     0,     0,     0,     0,    94,    95
};

static const yytype_int16 yycheck[] =
{
      40,    41,    42,    43,    44,    45,    55,    30,    48,    13,
       5,     3,     4,    16,     6,     7,     8,     0,    58,    11,
       7,     8,    62,    63,    12,    17,    30,    19,    20,    15,
      18,    17,    72,    73,    21,    22,    76,    60,    12,    79,
      43,    33,     7,     8,    18,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    13,
       4,    11,   128,   129,    18,    11,    11,    13,    17,     3,
       1,   137,     3,     4,     4,     6,     7,     8,     4,    24,
      11,    26,   148,    18,    15,    16,   126,    32,    19,    20,
     130,    14,    17,    17,    11,    11,    11,    17,   138,   139,
     149,   150,    33,    34,    17,    36,    37,    38,    39,    40,
      41,    42,    43,     1,    11,     3,     4,    16,     6,     7,
       8,     7,     8,    11,    13,    15,    35,    15,    16,    16,
      42,    19,    20,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    44,    33,    34,     4,    36,    37,
      38,    39,    40,    41,     1,    14,     3,     4,    24,     6,
       7,     8,     7,     8,    11,    23,    60,    32,    15,   140,
      65,    -1,    19,    20,    19,    20,    21,    22,    23,    -1,
      -1,    -1,    -1,     7,     8,    -1,    33,    34,    -1,    36,
      37,    38,    39,    40,    41,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     3,
       4,    -1,     6,     7,     8,    -1,    -1,    11,     7,     8,
      44,    -1,    -1,    -1,    -1,    19,    20,    -1,     7,     8,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    17,    33,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     7,     8,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      17,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     7,     8,    -1,    -1,
      -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     7,     8,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       7,     8,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     7,     8,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    -1,    -1,    -1,    -1,    28,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    82,    83,    84,    85,     0,    83,     4,    86,
      87,    11,    17,    13,    18,    85,    89,    90,     3,     4,
      86,     4,    88,    12,    18,    14,    15,    17,    91,    90,
      85,    93,    94,    87,    95,    96,     1,     3,     4,     6,
       7,     8,    11,    19,    20,    33,    34,    36,    37,    38,
      39,    40,    41,    91,    92,    99,   100,    93,    30,    17,
      18,    17,    11,    13,   102,   103,   100,   100,   100,   100,
     100,   100,    11,    11,    17,   100,    11,    17,    17,    11,
      16,    92,     7,     8,    17,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,   100,
      95,   100,   101,   100,   102,    12,   100,   100,    17,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,    12,    18,    14,    12,    12,
      17,    12,   100,    99,    99,   100,    15,    35,    17,    42,
      97,    98,    99,   100,   100,    98,    16,    43,    12,    44,
      44,    99,    92,    92,    16
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    84,    85,    86,
      86,    87,    87,    88,    89,    89,    89,    90,    91,    92,
      92,    93,    93,    94,    95,    95,    96,    96,    97,    98,
      98,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   101,   101,   101,   102,   103,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     6,     6,     1,     1,
       3,     1,     4,     1,     0,     1,     3,     2,     4,     0,
       2,     0,     2,     3,     1,     3,     1,     3,     4,     1,
       2,     2,     1,     3,     2,     5,     7,     5,     9,     7,
      10,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     4,     1,     2,     1,
       1,     0,     1,     3,     3,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 100 "parser.ypp"
                     {(yyval.program)=new ProgAST(); (yyval.program)->ExtDefs=(yyvsp[0].ExtDefList);
                      if (Errors::IsEmpty() && ErrorCharNum==0)
                           { (yyval.program)->DisplayAST(0); }         //无词法、语法错误显示语法树
                      else {Errors::ErrorsDisplay();return 0;}
                      (yyval.program)->Semantics0();                   //静态语义检查
                      if (Errors::IsEmpty())
                          (yyval.program)->GenIR();                    //中间代码生成
                      exit(0);
                      }
#line 1729 "parser.tab.cpp"
    break;

  case 3:
#line 110 "parser.ypp"
            {(yyval.ExtDefList)=vector <ExtDefAST*>();}
#line 1735 "parser.tab.cpp"
    break;

  case 4:
#line 111 "parser.ypp"
                              {(yyvsp[0].ExtDefList).insert((yyvsp[0].ExtDefList).begin(),(yyvsp[-1].ExtDef));(yyval.ExtDefList)=(yyvsp[0].ExtDefList);}
#line 1741 "parser.tab.cpp"
    break;

  case 5:
#line 114 "parser.ypp"
                                      { ExtVarDefAST *t=new ExtVarDefAST();     //创建一个外部变量声明的对象
                                        t->Type=(yyvsp[-2].Specifier); t->ExtVars=(yyvsp[-1].ExtDecList); (yyval.ExtDef)=t; SavePosition;}
#line 1748 "parser.tab.cpp"
    break;

  case 6:
#line 116 "parser.ypp"
                                               {FuncDefAST *t=new FuncDefAST();t->Type=(yyvsp[-5].Specifier);t->Name=(yyvsp[-4].type_id);t->Params=(yyvsp[-2].ParamList); t->Body=(yyvsp[0].CompSt);(yyval.ExtDef)=t;SavePosition;}
#line 1754 "parser.tab.cpp"
    break;

  case 7:
#line 117 "parser.ypp"
                                               {FuncDefAST *t=new FuncDefAST();t->Type=(yyvsp[-5].Specifier);t->Name=(yyvsp[-4].type_id);t->Params=(yyvsp[-2].ParamList);(yyval.ExtDef)=t;SavePosition;}
#line 1760 "parser.tab.cpp"
    break;

  case 8:
#line 119 "parser.ypp"
                 {  BasicTypeAST *t=new BasicTypeAST(); ;
                    if (string((yyvsp[0].type_id))==string("int"))    t->Type=T_INT;
                    if (string((yyvsp[0].type_id))==string("float"))  t->Type=T_FLOAT;
                    if (string((yyvsp[0].type_id))==string("void"))   t->Type=T_VOID;  (yyval.Specifier)=t;SavePosition;}
#line 1769 "parser.tab.cpp"
    break;

  case 9:
#line 125 "parser.ypp"
                     {(yyval.ExtDecList)=vector < VarDecAST*>();(yyval.ExtDecList).push_back((yyvsp[0].VarDec));}
#line 1775 "parser.tab.cpp"
    break;

  case 10:
#line 126 "parser.ypp"
                                     {(yyvsp[0].ExtDecList).insert((yyvsp[0].ExtDecList).begin(),(yyvsp[-2].VarDec));(yyval.ExtDecList)=(yyvsp[0].ExtDecList);}
#line 1781 "parser.tab.cpp"
    break;

  case 11:
#line 128 "parser.ypp"
              {VarDecAST *t=new VarDecAST(); t->Name=string((yyvsp[0].type_id)); (yyval.VarDec)=t; SavePosition;}
#line 1787 "parser.tab.cpp"
    break;

  case 12:
#line 129 "parser.ypp"
                               {(yyvsp[-3].VarDec)->Dims.push_back((yyvsp[-1].type_int));(yyval.VarDec)=(yyvsp[-3].VarDec);}
#line 1793 "parser.tab.cpp"
    break;

  case 13:
#line 131 "parser.ypp"
                 {VarDecAST *t=new VarDecAST(); t->Name=string((yyvsp[0].type_id)); (yyval.VarDec)=t; SavePosition;}
#line 1799 "parser.tab.cpp"
    break;

  case 14:
#line 134 "parser.ypp"
           {(yyval.ParamList)=vector < ParamAST *>();}
#line 1805 "parser.tab.cpp"
    break;

  case 15:
#line 135 "parser.ypp"
                    {(yyval.ParamList)=vector < ParamAST *>(); (yyval.ParamList).push_back((yyvsp[0].ParamDec)); }
#line 1811 "parser.tab.cpp"
    break;

  case 16:
#line 136 "parser.ypp"
                                     {(yyvsp[-2].ParamList).push_back((yyvsp[0].ParamDec)); (yyval.ParamList)=(yyvsp[-2].ParamList);}
#line 1817 "parser.tab.cpp"
    break;

  case 17:
#line 138 "parser.ypp"
                                  {ParamAST* t=new ParamAST();t->Type=(yyvsp[-1].Specifier);t->ParamName=(yyvsp[0].VarDec); (yyval.ParamDec)=t; SavePosition;}
#line 1823 "parser.tab.cpp"
    break;

  case 18:
#line 141 "parser.ypp"
                                 {CompStmAST *t=new CompStmAST();t->Decls=(yyvsp[-2].DefList);t->Stms=(yyvsp[-1].StmList);(yyval.CompSt)=t;SavePosition;}
#line 1829 "parser.tab.cpp"
    break;

  case 19:
#line 143 "parser.ypp"
         {(yyval.StmList)=vector <StmAST *>(); }
#line 1835 "parser.tab.cpp"
    break;

  case 20:
#line 144 "parser.ypp"
                        {(yyval.StmList)=(yyvsp[0].StmList);(yyval.StmList).insert((yyval.StmList).begin(),(yyvsp[-1].Stmt));}
#line 1841 "parser.tab.cpp"
    break;

  case 21:
#line 146 "parser.ypp"
         {(yyval.DefList)=vector <DefAST *>();  }
#line 1847 "parser.tab.cpp"
    break;

  case 22:
#line 147 "parser.ypp"
                      {(yyval.DefList)=(yyvsp[0].DefList);(yyval.DefList).insert((yyval.DefList).begin(),(yyvsp[-1].Def));}
#line 1853 "parser.tab.cpp"
    break;

  case 23:
#line 149 "parser.ypp"
                              {DefAST *t=new DefAST();t->Type=(yyvsp[-2].Specifier);t->LocVars=(yyvsp[-1].DecList);(yyval.Def)=t;SavePosition;}
#line 1859 "parser.tab.cpp"
    break;

  case 24:
#line 151 "parser.ypp"
              {(yyval.DecList)=vector <VarDecAST *>(); (yyval.DecList).push_back((yyvsp[0].Dec));}
#line 1865 "parser.tab.cpp"
    break;

  case 25:
#line 152 "parser.ypp"
                            {(yyval.DecList)=(yyvsp[0].DecList);(yyval.DecList).insert((yyval.DecList).begin(),(yyvsp[-2].Dec));}
#line 1871 "parser.tab.cpp"
    break;

  case 26:
#line 154 "parser.ypp"
               {(yyval.Dec)=(yyvsp[0].VarDec);}
#line 1877 "parser.tab.cpp"
    break;

  case 27:
#line 155 "parser.ypp"
                            {(yyval.Dec)=(yyvsp[-2].VarDec);(yyval.Dec)->Exp=(yyvsp[0].Exp); }
#line 1883 "parser.tab.cpp"
    break;

  case 28:
#line 158 "parser.ypp"
                                {CaseStmAST *t=new CaseStmAST(); t->Cond=(yyvsp[-2].Exp); t->Body=(yyvsp[0].StmList); (yyval.Case)=t; SavePosition;}
#line 1889 "parser.tab.cpp"
    break;

  case 29:
#line 160 "parser.ypp"
                            {(yyval.CaseList)=vector <CaseStmAST *>(); (yyval.CaseList).push_back((yyvsp[0].Case)); }
#line 1895 "parser.tab.cpp"
    break;

  case 30:
#line 161 "parser.ypp"
                            {(yyval.CaseList)=(yyvsp[0].CaseList); (yyval.CaseList).insert((yyval.CaseList).begin(),(yyvsp[-1].Case)); }
#line 1901 "parser.tab.cpp"
    break;

  case 31:
#line 163 "parser.ypp"
                                {ExprStmAST *t=new ExprStmAST();t->Exp=(yyvsp[-1].Exp);(yyval.Stmt)=t;SavePosition;}
#line 1907 "parser.tab.cpp"
    break;

  case 32:
#line 164 "parser.ypp"
                                {(yyval.Stmt)=(yyvsp[0].CompSt);}
#line 1913 "parser.tab.cpp"
    break;

  case 33:
#line 165 "parser.ypp"
                                {ReturnStmAST *t=new ReturnStmAST();t->Exp=(yyvsp[-1].Exp);(yyval.Stmt)=t;SavePosition;}
#line 1919 "parser.tab.cpp"
    break;

  case 34:
#line 166 "parser.ypp"
                        {ReturnStmAST *t=new ReturnStmAST();t->Exp=NULL;(yyval.Stmt)=t;SavePosition;}
#line 1925 "parser.tab.cpp"
    break;

  case 35:
#line 167 "parser.ypp"
                                                {IfStmAST *t=new IfStmAST();t->Cond=(yyvsp[-2].Exp);t->ThenStm=(yyvsp[0].Stmt);(yyval.Stmt)=t; SavePosition;}
#line 1931 "parser.tab.cpp"
    break;

  case 36:
#line 168 "parser.ypp"
                                                    {IfElseStmAST *t=new IfElseStmAST();t->Cond=(yyvsp[-4].Exp);t->ThenStm=(yyvsp[-2].Stmt);t->ElseStm=(yyvsp[0].Stmt);(yyval.Stmt)=t;SavePosition;}
#line 1937 "parser.tab.cpp"
    break;

  case 37:
#line 169 "parser.ypp"
                                {WhileStmAST *t=new WhileStmAST();t->Cond=(yyvsp[-2].Exp);t->Body=(yyvsp[0].Stmt); (yyval.Stmt)=t; SavePosition; }
#line 1943 "parser.tab.cpp"
    break;

  case 38:
#line 171 "parser.ypp"
              {ForStmAST *t=new ForStmAST(); t->SinExp=(yyvsp[-6].Exp); t->Cond=(yyvsp[-4].Exp); t->EndExp=(yyvsp[-2].Exp); t->Body=(yyvsp[0].Stmt); (yyval.Stmt)=t; SavePosition;}
#line 1949 "parser.tab.cpp"
    break;

  case 39:
#line 172 "parser.ypp"
                                          {SwitchStmAST *t=new SwitchStmAST(); t->Exp=(yyvsp[-4].Exp); t->Cases=(yyvsp[-1].CaseList); t->containDefault=0; (yyval.Stmt)=t; SavePosition;}
#line 1955 "parser.tab.cpp"
    break;

  case 40:
#line 174 "parser.ypp"
              {SwitchStmAST *t=new SwitchStmAST(); t->Exp=(yyvsp[-7].Exp); t->Cases=(yyvsp[-4].CaseList); t->containDefault=1; t->Default=(yyvsp[-1].StmList); (yyval.Stmt)=t; SavePosition;}
#line 1961 "parser.tab.cpp"
    break;

  case 41:
#line 175 "parser.ypp"
                            {BreakStmAST *t=new BreakStmAST(); (yyval.Stmt)=t; SavePosition; }
#line 1967 "parser.tab.cpp"
    break;

  case 42:
#line 176 "parser.ypp"
                            {ContinueStmAST *t=new ContinueStmAST(); (yyval.Stmt)=t; SavePosition; }
#line 1973 "parser.tab.cpp"
    break;

  case 43:
#line 177 "parser.ypp"
                     {(yyval.Stmt)=NULL;}
#line 1979 "parser.tab.cpp"
    break;

  case 44:
#line 180 "parser.ypp"
                       {AssignAST *t=new AssignAST();t->Op=ASSIGN;
                t->LeftValExp=(yyvsp[-2].Exp);t->RightValExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 1986 "parser.tab.cpp"
    break;

  case 45:
#line 183 "parser.ypp"
                     {BinaryExprAST *t=new BinaryExprAST();t->Op=PLUS;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 1992 "parser.tab.cpp"
    break;

  case 46:
#line 184 "parser.ypp"
                     {BinaryExprAST *t=new BinaryExprAST();t->Op=MINUS;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 1998 "parser.tab.cpp"
    break;

  case 47:
#line 185 "parser.ypp"
                     {BinaryExprAST *t=new BinaryExprAST();t->Op=STAR;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2004 "parser.tab.cpp"
    break;

  case 48:
#line 186 "parser.ypp"
                     {BinaryExprAST *t=new BinaryExprAST();t->Op=DIV;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2010 "parser.tab.cpp"
    break;

  case 49:
#line 187 "parser.ypp"
                     {BinaryExprAST *t=new BinaryExprAST();t->Op=MOD;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2016 "parser.tab.cpp"
    break;

  case 50:
#line 188 "parser.ypp"
                     {(yyval.Exp)=(yyvsp[-1].Exp);}
#line 2022 "parser.tab.cpp"
    break;

  case 51:
#line 189 "parser.ypp"
                                {UnaryExprAST *t=new UnaryExprAST();t->Op=UMINUS;t->Exp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2028 "parser.tab.cpp"
    break;

  case 52:
#line 190 "parser.ypp"
                                {UnaryExprAST *t=new UnaryExprAST();t->Op=UPLUS;t->Exp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2034 "parser.tab.cpp"
    break;

  case 53:
#line 192 "parser.ypp"
                      {BinaryExprAST *t=new BinaryExprAST();t->Op=AND;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2040 "parser.tab.cpp"
    break;

  case 54:
#line 193 "parser.ypp"
                      {BinaryExprAST *t=new BinaryExprAST();t->Op=OR;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2046 "parser.tab.cpp"
    break;

  case 55:
#line 194 "parser.ypp"
                      {UnaryExprAST *t=new UnaryExprAST();t->Op=NOT;t->Exp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2052 "parser.tab.cpp"
    break;

  case 56:
#line 196 "parser.ypp"
                        {BinaryExprAST *t=new BinaryExprAST();t->Op=GT;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2058 "parser.tab.cpp"
    break;

  case 57:
#line 197 "parser.ypp"
                        {BinaryExprAST *t=new BinaryExprAST();t->Op=GE;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2064 "parser.tab.cpp"
    break;

  case 58:
#line 198 "parser.ypp"
                        {BinaryExprAST *t=new BinaryExprAST();t->Op=LT;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2070 "parser.tab.cpp"
    break;

  case 59:
#line 199 "parser.ypp"
                        {BinaryExprAST *t=new BinaryExprAST();t->Op=LE;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2076 "parser.tab.cpp"
    break;

  case 60:
#line 200 "parser.ypp"
                        {BinaryExprAST *t=new BinaryExprAST();t->Op=NE;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2082 "parser.tab.cpp"
    break;

  case 61:
#line 201 "parser.ypp"
                        {BinaryExprAST *t=new BinaryExprAST();t->Op=EQ;t->LeftExp=(yyvsp[-2].Exp);t->RightExp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2088 "parser.tab.cpp"
    break;

  case 62:
#line 204 "parser.ypp"
                        {UnaryExprAST *t=new UnaryExprAST();t->Op=DPLUS;t->Exp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2094 "parser.tab.cpp"
    break;

  case 63:
#line 205 "parser.ypp"
                        {UnaryExprAST *t=new UnaryExprAST();t->Op=DMINUS;t->Exp=(yyvsp[0].Exp);(yyval.Exp)=t;SavePosition;}
#line 2100 "parser.tab.cpp"
    break;

  case 64:
#line 206 "parser.ypp"
                        {UnaryExprAST *t=new UnaryExprAST();t->Op=PLUSD;t->Exp=(yyvsp[-1].Exp);(yyval.Exp)=t;SavePosition;}
#line 2106 "parser.tab.cpp"
    break;

  case 65:
#line 207 "parser.ypp"
                        {UnaryExprAST *t=new UnaryExprAST();t->Op=MINUSD;t->Exp=(yyvsp[-1].Exp);(yyval.Exp)=t;SavePosition;}
#line 2112 "parser.tab.cpp"
    break;

  case 66:
#line 210 "parser.ypp"
                        {FuncCallAST *t=new FuncCallAST();t->Name=(yyvsp[-3].type_id);t->Params=(yyvsp[-1].Args);(yyval.Exp)=t;SavePosition;}
#line 2118 "parser.tab.cpp"
    break;

  case 67:
#line 211 "parser.ypp"
                        {VarAST *t=new VarAST();t->Name=(yyvsp[0].type_id);(yyval.Exp)=t;SavePosition;}
#line 2124 "parser.tab.cpp"
    break;

  case 68:
#line 212 "parser.ypp"
                            {VarAST *t=new VarAST();t->Name=(yyvsp[-1].type_id);t->index=(yyvsp[0].Args);(yyval.Exp)=t;SavePosition;}
#line 2130 "parser.tab.cpp"
    break;

  case 69:
#line 213 "parser.ypp"
                        {ConstAST *t=new ConstAST();t->Type=T_INT;t->ConstVal.constINT=(yyvsp[0].type_int);(yyval.Exp)=t;SavePosition;}
#line 2136 "parser.tab.cpp"
    break;

  case 70:
#line 214 "parser.ypp"
                        {ConstAST *t=new ConstAST();t->Type=T_FLOAT;t->ConstVal.constFLOAT=(yyvsp[0].type_float);(yyval.Exp)=t;SavePosition;}
#line 2142 "parser.tab.cpp"
    break;

  case 71:
#line 216 "parser.ypp"
        {}
#line 2148 "parser.tab.cpp"
    break;

  case 72:
#line 217 "parser.ypp"
              {(yyval.Args)=vector <ExpAST *>(); (yyval.Args).push_back((yyvsp[0].Exp)); }
#line 2154 "parser.tab.cpp"
    break;

  case 73:
#line 218 "parser.ypp"
                            {(yyval.Args)=(yyvsp[-2].Args);(yyval.Args).push_back((yyvsp[0].Exp));}
#line 2160 "parser.tab.cpp"
    break;

  case 74:
#line 221 "parser.ypp"
                             {(yyval.Exp)=(yyvsp[-1].Exp); }
#line 2166 "parser.tab.cpp"
    break;

  case 75:
#line 223 "parser.ypp"
                             {(yyval.Args)=vector <ExpAST *>(); (yyval.Args).push_back((yyvsp[0].Exp)); }
#line 2172 "parser.tab.cpp"
    break;

  case 76:
#line 224 "parser.ypp"
                             {(yyval.Args)=(yyvsp[-1].Args); (yyval.Args).push_back((yyvsp[0].Exp));}
#line 2178 "parser.tab.cpp"
    break;


#line 2182 "parser.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 226 "parser.ypp"


int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return 0;
	yylineno=1;
	yyparse();
	return 0;
	}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    Errors::ErrorAdd(yylloc.first_line,yylloc.first_column,fmt);
}

/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "grammer.y" /* yacc.c:339  */

#include <fstream>
#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <unistd.h>

#define GetCurrentDir getcwd

using namespace std;

string inputFile;
ofstream fout("bytecode.java");	
int varCount = 1; 	
int labelsCount = 0;	
vector<string> codeList;
extern  int yylex();
extern  FILE *yyin;
extern int lineCounter;

typedef enum {INT_T, FLOAT_T, BOOL_T, VOID_T, ERROR_T} type_enum;
map<string, pair<int,type_enum> > symbTab;
map<string,string> inst_list = {
	{"+", "add"},
	{"-", "sub"},
	{"/", "div"},
	{"*", "mul"},
	{"==", "if_icmpeq"},
	{"<=", "if_icmple"},
	{">=", "if_icmpge"},
	{"!=", "if_icmpne"},
	{">",  "if_icmpgt"},
	{"<",  "if_icmplt"}
};

/* helping functions */

void yyerror(const char * s);
void genHeader(void);	
void genFooter(void);	
void cast(int from , int to, string op);
bool checkId(string id);
string getByteCode(string op);
void var(string name, int type);
string genNewLabel();
string getLabel(int n);
void writeLabel(vector<int> *list, int num);
vector<int> * concat (vector<int> *list1, vector<int>* list2);
void printCode(void);
void printLineNumber(int num)
{
	codeList.push_back(".line "+ to_string(num));
}


#line 124 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 61 "grammer.y" /* yacc.c:355  */

	#include <vector>
	using namespace std;

#line 159 "y.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    FOR = 261,
    INT = 262,
    FLOAT = 263,
    BOOLEAN = 264,
    SEMI_COLON = 265,
    ASSIGN = 266,
    LEFT_BRACKET = 267,
    RIGHT_BRACKET = 268,
    LEFT_CURLY_BRACKET = 269,
    RIGHT_CURLY_BRACKET = 270,
    COMMA = 271,
    PRINT = 272,
    I_NUM = 273,
    F_NUM = 274,
    BOOL = 275,
    ID = 276,
    ARITH_OP = 277,
    RELA_OP = 278,
    BOOL_OP = 279
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define INT 262
#define FLOAT 263
#define BOOLEAN 264
#define SEMI_COLON 265
#define ASSIGN 266
#define LEFT_BRACKET 267
#define RIGHT_BRACKET 268
#define LEFT_CURLY_BRACKET 269
#define RIGHT_CURLY_BRACKET 270
#define COMMA 271
#define PRINT 272
#define I_NUM 273
#define F_NUM 274
#define BOOL 275
#define ID 276
#define ARITH_OP 277
#define RELA_OP 278
#define BOOL_OP 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 66 "grammer.y" /* yacc.c:355  */

	/* values */
	int iVal, boolVal;
	char *idLexVal, *opLexVal;
	float fVal;	

	/* types */
	int sType;
	struct {
		vector<int> *nextList;
	} stmt_type;
	struct {
		int sType;
	} expr_type;
	struct {
		vector<int> *trueList, *falseList;
	} bexpr_type;

#line 238 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 255 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   92

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  30
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  83

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   110,   119,   121,   130,   131,   132,   133,
     134,   135,   138,   151,   152,   153,   156,   167,   177,   193,
     212,   213,   214,   215,   235,   238,   254,   269,   281,   310,
     316
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "INT",
  "FLOAT", "BOOLEAN", "SEMI_COLON", "ASSIGN", "LEFT_BRACKET",
  "RIGHT_BRACKET", "LEFT_CURLY_BRACKET", "RIGHT_CURLY_BRACKET", "COMMA",
  "PRINT", "I_NUM", "F_NUM", "BOOL", "ID", "ARITH_OP", "RELA_OP",
  "BOOL_OP", "$accept", "method_body", "$@1", "statement_list",
  "statement", "declaration", "primitive_type", "if", "while", "for",
  "assignment", "expression", "boolean_expr", "system_print", "label",
  "goto", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279
};
# endif

#define YYPACT_NINF -56

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

#define YYTABLE_NINF -31

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -56,     8,    52,   -56,    -2,     0,   -56,   -56,   -56,    26,
      24,   -56,   -56,   -56,    25,   -56,   -56,   -56,   -56,   -56,
      43,    58,    31,    53,    53,    10,    44,    54,    53,   -56,
     -56,   -56,   -56,   -18,    16,   -56,    17,    22,   -56,   -56,
      58,    40,    53,    53,    42,   -56,    58,    65,   -56,    23,
     -56,    59,    59,   -56,    58,    13,   -56,    66,    52,    60,
     -56,   -56,    67,    31,    52,    52,    68,   -56,    70,    82,
      74,   -56,    75,    76,   -56,   -56,    52,    52,    73,    67,
     -56,    77,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,    29,     1,     0,     0,    13,    14,    15,     0,
       0,    29,     4,     6,     0,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     3,     0,     0,     0,    20,
      21,    25,    23,     0,     0,    29,     0,     0,     5,    12,
       0,     0,     0,     0,     0,    29,     0,     0,    19,     0,
      24,    22,    27,    29,     0,     0,    28,     0,    29,    26,
      29,    29,    29,     0,    29,    29,     0,    30,    29,     0,
       0,    17,     0,     0,    29,    29,    29,    29,    29,    29,
      16,     0,    18
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -56,   -55,   -24,   -56,   -56,   -56,   -56,   -56,
     -20,   -17,   -26,   -56,   -11,   -34
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    11,    12,    13,    14,    15,    16,    17,
      18,    33,    34,    19,    20,    66
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      25,    38,    35,    62,    42,    43,    36,    37,     3,    68,
      21,    41,    22,     4,    49,   -29,     5,     6,     7,     8,
      55,    78,    79,    60,    46,    51,    52,     9,    59,    44,
      47,    10,    48,    70,    54,    24,    57,    45,    23,    42,
      45,    38,    58,    67,    42,    81,    26,    45,    27,    63,
      64,    65,    10,    50,    39,     4,    53,    65,     5,     6,
       7,     8,    42,    76,    77,    28,    40,    65,    65,     9,
      28,    29,    30,    10,    32,    56,    29,    30,    31,    32,
      61,    42,   -30,    69,    45,    71,    72,    73,    80,    74,
      75,     0,    82
};

static const yytype_int8 yycheck[] =
{
      11,    25,    22,    58,    22,    23,    23,    24,     0,    64,
      12,    28,    12,     3,    40,     5,     6,     7,     8,     9,
      46,    76,    77,    10,    35,    42,    43,    17,    54,    13,
      13,    21,    10,    67,    45,    11,    13,    24,    12,    22,
      24,    65,    53,    63,    22,    79,    21,    24,     5,    60,
      61,    62,    21,    13,    10,     3,    14,    68,     6,     7,
       8,     9,    22,    74,    75,    12,    12,    78,    79,    17,
      12,    18,    19,    21,    21,    10,    18,    19,    20,    21,
      14,    22,    15,    15,    24,    15,     4,    13,    15,    14,
      14,    -1,    15
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    27,     0,     3,     6,     7,     8,     9,    17,
      21,    28,    29,    30,    31,    32,    33,    34,    35,    38,
      39,    12,    12,    12,    11,    39,    21,     5,    12,    18,
      19,    20,    21,    36,    37,    35,    36,    36,    29,    10,
      12,    36,    22,    23,    13,    24,    39,    13,    10,    37,
      13,    36,    36,    14,    39,    37,    10,    13,    39,    37,
      10,    14,    28,    39,    39,    39,    40,    35,    28,    15,
      40,    15,     4,    13,    14,    14,    39,    39,    28,    28,
      15,    40,    15
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    25,    27,    26,    28,    28,    29,    29,    29,    29,
      29,    29,    30,    31,    31,    31,    32,    33,    34,    35,
      36,    36,    36,    36,    36,    37,    37,    37,    38,    39,
      40
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,    14,     9,    15,     4,
       1,     1,     3,     1,     3,     1,     4,     3,     5,     0,
       0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 110 "grammer.y" /* yacc.c:1646  */
    {	genHeader();	}
#line 1383 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 113 "grammer.y" /* yacc.c:1646  */
    {
		writeLabel((yyvsp[-1].stmt_type).nextList,(yyvsp[0].iVal));
		genFooter();
	}
#line 1392 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 124 "grammer.y" /* yacc.c:1646  */
    {
		writeLabel((yyvsp[-2].stmt_type).nextList,(yyvsp[-1].iVal));
		(yyval.stmt_type).nextList = (yyvsp[0].stmt_type).nextList;
	}
#line 1401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 130 "grammer.y" /* yacc.c:1646  */
    {vector<int> * v = new vector<int>(); (yyval.stmt_type).nextList =v;}
#line 1407 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 131 "grammer.y" /* yacc.c:1646  */
    {(yyval.stmt_type).nextList = (yyvsp[0].stmt_type).nextList;}
#line 1413 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 132 "grammer.y" /* yacc.c:1646  */
    {(yyval.stmt_type).nextList = (yyvsp[0].stmt_type).nextList;}
#line 1419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 133 "grammer.y" /* yacc.c:1646  */
    {(yyval.stmt_type).nextList = (yyvsp[0].stmt_type).nextList;}
#line 1425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 134 "grammer.y" /* yacc.c:1646  */
    {vector<int> * v = new vector<int>(); (yyval.stmt_type).nextList =v;}
#line 1431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 135 "grammer.y" /* yacc.c:1646  */
    {vector<int> * v = new vector<int>(); (yyval.stmt_type).nextList =v;}
#line 1437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 139 "grammer.y" /* yacc.c:1646  */
    {
		string str((yyvsp[-1].idLexVal));
		if((yyvsp[-2].sType) == INT_T)
		{
			var(str,INT_T);
		}else if ((yyvsp[-2].sType) == FLOAT_T)
		{
			var(str,FLOAT_T);
		}
	}
#line 1452 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 151 "grammer.y" /* yacc.c:1646  */
    {(yyval.sType) = INT_T;}
#line 1458 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 152 "grammer.y" /* yacc.c:1646  */
    {(yyval.sType) = FLOAT_T;}
#line 1464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 153 "grammer.y" /* yacc.c:1646  */
    {(yyval.sType) = BOOL_T;}
#line 1470 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 159 "grammer.y" /* yacc.c:1646  */
    {
		writeLabel((yyvsp[-11].bexpr_type).trueList,(yyvsp[-8].iVal));
		writeLabel((yyvsp[-11].bexpr_type).falseList,(yyvsp[-2].iVal));
		(yyval.stmt_type).nextList = concat((yyvsp[-7].stmt_type).nextList, (yyvsp[-1].stmt_type).nextList);
		(yyval.stmt_type).nextList->push_back((yyvsp[-6].iVal));
	}
#line 1481 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 169 "grammer.y" /* yacc.c:1646  */
    {
		codeList.push_back("goto " + getLabel((yyvsp[-8].iVal)));
		writeLabel((yyvsp[-1].stmt_type).nextList,(yyvsp[-8].iVal));
		writeLabel((yyvsp[-5].bexpr_type).trueList,(yyvsp[-2].iVal));
		(yyval.stmt_type).nextList = (yyvsp[-5].bexpr_type).falseList;
	}
#line 1492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 180 "grammer.y" /* yacc.c:1646  */
    {
		writeLabel((yyvsp[-10].bexpr_type).trueList,(yyvsp[-3].iVal));
		vector<int> * v = new vector<int> ();
		v->push_back((yyvsp[-6].iVal));
		writeLabel(v,(yyvsp[-11].iVal));
		v = new vector<int>();
		v->push_back((yyvsp[-1].iVal));
		writeLabel(v,(yyvsp[-8].iVal));
		writeLabel((yyvsp[-2].stmt_type).nextList,(yyvsp[-8].iVal));
		(yyval.stmt_type).nextList = (yyvsp[-10].bexpr_type).falseList;
	}
#line 1508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 194 "grammer.y" /* yacc.c:1646  */
    {
		string str((yyvsp[-3].idLexVal));
		if(checkId(str))
		{
			if((yyvsp[-1].expr_type).sType == INT_T)
			{
				codeList.push_back("istore " + to_string(symbTab[str].first));
			}else if ((yyvsp[-1].expr_type).sType == FLOAT_T)
			{
				codeList.push_back("fstore " + to_string(symbTab[str].first));
			}
		}else{
			string err = "identifier: "+str+" isn't declared in this scope";
			yyerror(err.c_str());
		}
	}
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 212 "grammer.y" /* yacc.c:1646  */
    {(yyval.expr_type).sType = INT_T;  codeList.push_back("ldc "+to_string((yyvsp[0].iVal)));}
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 213 "grammer.y" /* yacc.c:1646  */
    {(yyval.expr_type).sType = FLOAT_T; codeList.push_back("ldc "+to_string((yyvsp[0].fVal)));}
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 214 "grammer.y" /* yacc.c:1646  */
    {cast((yyvsp[-2].expr_type).sType, (yyvsp[0].expr_type).sType, string((yyvsp[-1].opLexVal)));}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 215 "grammer.y" /* yacc.c:1646  */
    {
		string str((yyvsp[0].idLexVal));
		if(checkId(str))
		{
			(yyval.expr_type).sType = symbTab[str].second;
			if(symbTab[str].second == INT_T)
			{
				codeList.push_back("iload " + to_string(symbTab[str].first));
			}else if (symbTab[str].second == FLOAT_T)
			{
				codeList.push_back("fload " + to_string(symbTab[str].first));
			}
		}
		else
		{
			string err = "id: "+str+" isn't declared in this scope";
			yyerror(err.c_str());
			(yyval.expr_type).sType = ERROR_T;
		}
	}
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 235 "grammer.y" /* yacc.c:1646  */
    {(yyval.expr_type).sType = (yyvsp[-1].expr_type).sType;}
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 239 "grammer.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].boolVal))
		{
			(yyval.bexpr_type).trueList = new vector<int> ();
			(yyval.bexpr_type).trueList->push_back(codeList.size());
			(yyval.bexpr_type).falseList = new vector<int>();
			codeList.push_back("goto ");
		}else
		{
			(yyval.bexpr_type).trueList = new vector<int> ();
			(yyval.bexpr_type).falseList= new vector<int>();
			(yyval.bexpr_type).falseList->push_back(codeList.size());
			codeList.push_back("goto ");
		}
	}
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 255 "grammer.y" /* yacc.c:1646  */
    {
		if(!strcmp((yyvsp[-2].opLexVal), "&&"))
		{
			writeLabel((yyvsp[-3].bexpr_type).trueList, (yyvsp[-1].iVal));
			(yyval.bexpr_type).trueList = (yyvsp[0].bexpr_type).trueList;
			(yyval.bexpr_type).falseList = concat((yyvsp[-3].bexpr_type).falseList,(yyvsp[0].bexpr_type).falseList);
		}
		else if (!strcmp((yyvsp[-2].opLexVal),"||"))
		{
			writeLabel((yyvsp[-3].bexpr_type).falseList,(yyvsp[-1].iVal));
			(yyval.bexpr_type).trueList = concat((yyvsp[-3].bexpr_type).trueList, (yyvsp[0].bexpr_type).trueList);
			(yyval.bexpr_type).falseList = (yyvsp[0].bexpr_type).falseList;
		}
	}
#line 1617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 270 "grammer.y" /* yacc.c:1646  */
    {
		string op ((yyvsp[-1].opLexVal));
		(yyval.bexpr_type).trueList = new vector<int>();
		(yyval.bexpr_type).trueList ->push_back (codeList.size());
		(yyval.bexpr_type).falseList = new vector<int>();
		(yyval.bexpr_type).falseList->push_back(codeList.size()+1);
		codeList.push_back(getByteCode(op)+ " ");
		codeList.push_back("goto ");
	}
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 282 "grammer.y" /* yacc.c:1646  */
    {
		/* expression is at top of stack now 
		** save it at the predefined temp syso var 
		*/
		if((yyvsp[-2].expr_type).sType == INT_T)
		{			
			codeList.push_back("istore " + to_string(symbTab["1syso_int_var"].first));
			/* call syso */			
			codeList.push_back("getstatic      java/lang/System/out Ljava/io/PrintStream;");
			/*insert param*/
			codeList.push_back("iload " + to_string(symbTab["1syso_int_var"].first ));
			/*invoke syso*/
			codeList.push_back("invokevirtual java/io/PrintStream/println(I)V");

		}else if ((yyvsp[-2].expr_type).sType == FLOAT_T)
		{
			codeList.push_back("fstore " + to_string(symbTab["1syso_float_var"].first));
			/* call syso */			
			codeList.push_back("getstatic      java/lang/System/out Ljava/io/PrintStream;");
			/*insert param*/
			codeList.push_back("fload " + to_string(symbTab["1syso_float_var"].first ));
			/*invoke syso*/
			codeList.push_back("invokevirtual java/io/PrintStream/println(F)V");
		}
	}
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 310 "grammer.y" /* yacc.c:1646  */
    {
	(yyval.iVal) = labelsCount;
	codeList.push_back(genNewLabel());
}
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 316 "grammer.y" /* yacc.c:1646  */
    {
	(yyval.iVal) = codeList.size();
	codeList.push_back("goto ");
}
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1683 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 322 "grammer.y" /* yacc.c:1906  */


/*		main function		*/

main (int argv, char * argc[])
{
	FILE *file;
	if(argv == 1) 
	{
		file = fopen("source.txt", "r");
		inputFile = "source.txt";
	}
	else 
	{
		file = fopen(argc[1], "r");
		inputFile = string(argc[1]);
	}
	if (!file) {
		printf("Error: can't open file!\n");
		return -1;
	}
	yyin = file;
	yyparse();
	printCode();
}

/*		helping functions		*/

void yyerror(const char * s)
{
	printf("error@%d: %s\n",lineCounter, s);
}

void genHeader()
{
	codeList.push_back(".source " + inputFile);
	codeList.push_back(".class public test\n.super java/lang/Object\n"); //code for defining class
	codeList.push_back(".method public <init>()V");
	codeList.push_back("aload_0");
	codeList.push_back("invokenonvirtual java/lang/Object/<init>()V");
	codeList.push_back("return");
	codeList.push_back(".end method\n");
	codeList.push_back(".method public static main([Ljava/lang/String;)V");
	codeList.push_back(".limit locals 100\n.limit stack 100");

	/* generate temporal vars for syso*/
	var("1syso_int_var",INT_T);
	var("1syso_float_var",FLOAT_T);

	/*generate line 1*/
	codeList.push_back(".line 1");
}

void genFooter()
{
	codeList.push_back("return");
	codeList.push_back(".end method");
}

bool checkId(string op)
{
	return (symbTab.find(op) != symbTab.end());
}

void var(string name, int type)
{
	if(checkId(name))
	{
		string err = name+" redeclared variable";
		yyerror(err.c_str());
	}else
	{
		if(type == INT_T)
		{
			codeList.push_back("iconst_0\nistore " + to_string(varCount));
		}
		else if ( type == FLOAT_T)
		{
			codeList.push_back("fconst_0\nfstore " + to_string(varCount));
		}
		symbTab[name] = make_pair(varCount++,(type_enum)type);
	}
}

string genNewLabel()
{
	return "l_"+to_string(labelsCount++) + ":";
}

string getLabel(int n)
{
	return "l_"+to_string(n);
}

void writeLabel(vector<int> *lists, int ind)
{
	if(lists)
	for(int i =0 ; i < lists->size() ; i++)
	{
		codeList[(*lists)[i]] = codeList[(*lists)[i]] + getLabel(ind);
	}
}

void printCode(void)
{
	for ( int i = 0 ; i < codeList.size() ; i++){
		fout<<codeList[i]<<endl;
	}
}

string getByteCode(string op)
{
	if(inst_list.find(op) != inst_list.end()){
		return inst_list[op];
	}
	return "";
}

void cast(int from , int to, string op)
{
	if(from == to)
	{
		if(from == INT_T)
		{
			codeList.push_back("i" + getByteCode(op));
		}else if (from == FLOAT_T)
		{
			codeList.push_back("f" + getByteCode(op));
		}
	}
}

vector<int> * concat(vector<int> *list1, vector<int> *list2)
{
	if(list1 && list2){
		vector<int> *list = new vector<int> (*list1);
		list->insert(list->end(), list2->begin(),list2->end());
		return list;
	}else if(list1)
	{
		return list1;
	}else if (list2)
	{
		return list2;
	}else
	{
		return new vector<int>();
	}
}

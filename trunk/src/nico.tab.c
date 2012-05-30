
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 3 "nico.y"

  /* Aqui, pode-se inserir qualquer codigo C necessario na compilacao
   * final do parser. Sera copiado tal como esta no inicio do y.tab.c
   * gerado por Yacc.
   */
    #include <stdio.h>
    #include <stdlib.h>
    #include "node.h"
    #include "lista.h"
    #include "symbol_table.h"

    #define UNDEFINED_SYMBOL_ERROR -21
    #define CHAR_TYPE   0
    #define INT_TYPE    1
    #define REAL_TYPE   2
    #define DOUBLE_TYPE 3
    #define CHAR_SIZE   1
    #define INT_SIZE    4
    #define REAL_SIZE   4
    #define DOUBLE_SIZE 8   

    typedef struct expr_attr {
        struct node_tac *code;
        char *local;
        int size;
    } EXPR_ATTR;
    
    extern symbol_t symbol_table;
    int tipo_idf = 0;
    int vars_size = 0;
    int temps_size = 0;
    
    char* gera_temp(int type) {
        int size = 0;
        switch (type) {
            case CHAR_TYPE:     size = CHAR_SIZE; break;
            case INT_TYPE:      size = INT_SIZE; break;
            case REAL_TYPE:     size = REAL_SIZE; break;
            case DOUBLE_TYPE:   size = DOUBLE_SIZE; break;
        }
        //uma variável temporária é, essencialmente, o seu deslocamento do registrador Rx.
        //isso gera uma string "ddd(Rx)", que possui tamanho 8 (7+\0) e ddd é o valor da variável temps_size
        char *ret = malloc(sizeof(char)*8);
        sprintf(ret, "%03d(Rx)", temps_size);
        temps_size += size;
        return ret;
    }
    
    void theBookIsOnTheTable(char *lexeme) {
        if(lookup(symbol_table, lexeme)){//testa se já existe uma entrada com esse nome na tabela
			printf("Símbolo %s foi definido múltiplas vezes. \n", lexeme);
			exit(0);

	}
	    else {
		    entry_t* new_entry=(entry_t *) malloc(sizeof(entry_t));
		    new_entry->name = lexeme;
		    new_entry->type = tipo_idf;
		    new_entry->desloc = vars_size;

		    switch(tipo_idf){
            	case INT_TYPE:		new_entry->size = INT_SIZE;
		            vars_size += INT_SIZE;
		            break;
            	case DOUBLE_TYPE:	new_entry->size = DOUBLE_SIZE;
			        vars_size += DOUBLE_SIZE;
			        break;
            	case REAL_TYPE:		new_entry->size = REAL_SIZE;
			        vars_size += REAL_SIZE;
			        break;
            	case CHAR_TYPE:		new_entry->size = CHAR_SIZE;
			        vars_size += CHAR_SIZE;
		    }
		    if(insert(&symbol_table, new_entry)) {
			    printf("Ocorreu um erro ao alocar o simbolo %s na tabela de simbolos.\n",lexeme);
			    exit(0);
		    }
	    }
    }
    
 /*
    Essa funcao consulta a tabela atras de um identificador e retorna o conteudo para 
    a string "local" caso o identificador esteja na tabela, caso contrario retorna o proprio identificador
    */
    char* consulta_tabela(char* identificador) {
        entry_t* entrada;
        entrada = lookup(symbol_table,identificador);
        if(entrada == NULL)
        	return (NULL);
        
        char *ret = malloc(sizeof(char)*8);
        sprintf(ret, "%03d(SP)", entrada->desloc);
        return ret;
    }      


/* Line 189 of yacc.c  */
#line 170 "nico.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AND = 258,
     CHAR = 259,
     CONST = 260,
     DOUBLE = 261,
     ELSE = 262,
     END = 263,
     EQ = 264,
     F_LIT = 265,
     FALSE = 266,
     FOR = 267,
     GE = 268,
     IDF = 269,
     IF = 270,
     INT = 271,
     INT_LIT = 272,
     LE = 273,
     NE = 274,
     NEXT = 275,
     NOT = 276,
     OR = 277,
     QUOTE = 278,
     REAL = 279,
     STR_LIT = 280,
     STRING = 281,
     SWAP = 282,
     THEN = 283,
     TRUE = 284,
     WHILE = 285,
     PRINTF = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 99 "nico.y"

  char* cadeia;
  struct _node * no;



/* Line 214 of yacc.c  */
#line 244 "nico.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 269 "nico.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   194

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNRULES -- Number of states.  */
#define YYNSTATES  123

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,    34,    32,    38,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    37,    36,
      47,    41,    46,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    15,    19,    21,    25,
      27,    29,    31,    33,    35,    37,    42,    47,    52,    57,
      61,    67,    69,    72,    77,    82,    85,    87,    91,    93,
      98,   100,   104,   108,   112,   116,   120,   124,   126,   128,
     130,   132,   137,   145,   153,   155,   159,   161,   163,   167,
     171,   175,   178,   182,   186,   190,   194,   198
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    57,    -1,    57,    -1,    51,    36,
      -1,    50,    51,    36,    -1,    53,    37,    52,    -1,    14,
      -1,    14,    38,    52,    -1,    54,    -1,    55,    -1,    16,
      -1,     6,    -1,    24,    -1,     4,    -1,    16,    39,    56,
      40,    -1,     6,    39,    56,    40,    -1,    24,    39,    56,
      40,    -1,     4,    39,    56,    40,    -1,    17,    37,    17,
      -1,    17,    37,    17,    38,    56,    -1,    58,    -1,    58,
      57,    -1,    59,    41,    61,    36,    -1,    59,    27,    59,
      36,    -1,    61,    36,    -1,    63,    -1,    31,    61,    36,
      -1,    14,    -1,    14,    42,    60,    43,    -1,    61,    -1,
      61,    38,    60,    -1,    61,    32,    61,    -1,    61,    33,
      61,    -1,    61,    34,    61,    -1,    61,    35,    61,    -1,
      39,    61,    40,    -1,    17,    -1,    10,    -1,    59,    -1,
      62,    -1,    14,    39,    60,    40,    -1,    15,    39,    65,
      40,    28,    57,    64,    -1,    30,    39,    65,    40,    44,
      57,    45,    -1,     8,    -1,     7,    57,     8,    -1,    29,
      -1,    11,    -1,    39,    65,    40,    -1,    65,     3,    65,
      -1,    65,    22,    65,    -1,    21,    65,    -1,    61,    46,
      61,    -1,    61,    47,    61,    -1,    61,    18,    61,    -1,
      61,    13,    61,    -1,    61,     9,    61,    -1,    61,    19,
      61,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   163,   163,   166,   171,   173,   177,   181,   184,   190,
     201,   213,   215,   217,   219,   223,   227,   231,   235,   242,
     246,   253,   255,   260,   267,   279,   282,   284,   293,   303,
     309,   310,   314,   321,   328,   335,   342,   346,   348,   350,
     353,   358,   365,   370,   379,   381,   387,   389,   391,   394,
     396,   398,   400,   402,   404,   406,   408,   410
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "CHAR", "CONST", "DOUBLE", "ELSE",
  "END", "EQ", "F_LIT", "FALSE", "FOR", "GE", "IDF", "IF", "INT",
  "INT_LIT", "LE", "NE", "NEXT", "NOT", "OR", "QUOTE", "REAL", "STR_LIT",
  "STRING", "SWAP", "THEN", "TRUE", "WHILE", "PRINTF", "'+'", "'-'", "'*'",
  "'/'", "';'", "':'", "','", "'('", "')'", "'='", "'['", "']'", "'{'",
  "'}'", "'>'", "'<'", "$accept", "code", "declaracoes", "declaracao",
  "listadeclaracao", "tipo", "tipounico", "tipolista", "listadupla",
  "acoes", "comando", "lvalue", "listaexpr", "expr", "chamaproc",
  "enunciado", "fiminstcontrole", "expbool", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    43,    45,    42,    47,    59,    58,    44,    40,
      41,    61,    91,    93,   123,   125,    62,    60
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    51,    52,    52,    53,
      53,    54,    54,    54,    54,    55,    55,    55,    55,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    59,    59,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    62,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,     3,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     4,     4,     4,     4,     3,
       5,     1,     2,     4,     4,     2,     1,     3,     1,     4,
       1,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     4,     7,     7,     1,     3,     1,     1,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    14,    12,    38,    28,     0,    11,    37,    13,     0,
       0,     0,     0,     0,     0,     0,     9,    10,     3,    21,
      39,     0,    40,    26,     0,     0,     0,     0,     0,     0,
       0,     0,    39,     0,     0,     1,     0,     2,     4,     0,
      22,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,     0,    30,     0,    47,     0,    46,     0,     0,     0,
       0,     0,     0,    27,    36,     5,     7,     6,    28,     0,
       0,    32,    33,    34,    35,     0,    18,    16,    41,     0,
      29,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    17,     0,     0,    24,    23,    19,
      31,    48,    56,    55,    54,    57,    52,    53,    49,    50,
       0,     0,     8,     0,     0,     0,    20,     0,    44,    42,
      43,     0,    45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    12,    13,    14,    67,    15,    16,    17,    49,    18,
      19,    32,    51,    21,    22,    23,   119,    59
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -28
static const yytype_int16 yypact[] =
{
     123,   -23,   -17,   -28,   -27,   -13,   -11,   -28,    -3,     1,
      13,    13,    14,   123,   -18,    27,   -28,   -28,   -28,    36,
     -24,   109,   -28,   -28,    21,    21,    13,    13,   155,    21,
      21,   155,   -28,   124,    -1,   -28,    37,   -28,   -28,    58,
     -28,    60,    13,    13,    13,    13,    13,   -28,    44,    46,
      47,    48,    68,    51,   -28,   155,   -28,   155,   117,     2,
      53,    55,     3,   -28,   -28,   -28,    66,   -28,    65,    72,
     145,   -14,   -14,   -28,   -28,    92,   -28,   -28,   -28,    13,
     -28,   -28,    50,     7,    13,    13,    13,    13,    13,    13,
     155,   155,    84,   -28,   -28,    70,    58,   -28,   -28,    77,
     -28,   -28,    23,    23,    23,    23,    23,    23,   -28,   113,
      36,    36,   -28,    21,    41,    83,   -28,    36,   -28,   -28,
     -28,   126,   -28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -28,   -28,   -28,   118,    52,   -28,   -28,   -28,   -21,   -12,
     -28,     0,   -25,    34,   -28,   -28,   -28,   -20
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      20,    37,    53,    41,    50,    90,    90,    40,    60,    61,
      90,    62,    26,    20,    35,    27,    24,    42,    38,    20,
      45,    46,    25,     3,    91,    91,    28,     4,    29,    91,
       7,    43,    44,    45,    46,    81,    30,    83,    48,    64,
      31,    69,    92,    95,    33,    34,     3,   101,   117,   118,
       4,     5,    11,     7,   100,    43,    44,    45,    46,    84,
      52,    52,    58,    85,    39,    58,     9,    10,    86,    87,
     108,   109,    66,    65,    68,    11,    70,    71,    72,    73,
      74,    75,    43,    44,    45,    46,    76,    77,    78,    58,
      64,    82,   116,    93,    80,    94,    88,    89,   114,   115,
      43,    44,    45,    46,    96,   121,    79,    27,    97,    99,
      20,    20,   110,    52,   111,   113,    90,    20,   102,   103,
     104,   105,   106,   107,    58,    58,    84,     1,   120,     2,
      85,    36,     0,     3,   122,    86,    87,     4,     5,     6,
       7,    43,    44,    45,    46,    47,     0,     8,   112,    43,
      44,    45,    46,     9,    10,     0,    43,    44,    45,    46,
      63,     0,    11,    88,    89,     3,    54,     0,     0,     4,
       0,     0,     7,     0,     0,     0,    55,    43,    44,    45,
      46,    98,     0,     0,    56,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57
};

static const yytype_int8 yycheck[] =
{
       0,    13,    27,    27,    25,     3,     3,    19,    29,    30,
       3,    31,    39,    13,     0,    42,    39,    41,    36,    19,
      34,    35,    39,    10,    22,    22,    39,    14,    39,    22,
      17,    32,    33,    34,    35,    55,    39,    57,    17,    40,
      39,    41,    40,    40,    10,    11,    10,    40,     7,     8,
      14,    15,    39,    17,    79,    32,    33,    34,    35,     9,
      26,    27,    28,    13,    37,    31,    30,    31,    18,    19,
      90,    91,    14,    36,    14,    39,    42,    43,    44,    45,
      46,    37,    32,    33,    34,    35,    40,    40,    40,    55,
      40,    57,   113,    40,    43,    40,    46,    47,   110,   111,
      32,    33,    34,    35,    38,   117,    38,    42,    36,    17,
     110,   111,    28,    79,    44,    38,     3,   117,    84,    85,
      86,    87,    88,    89,    90,    91,     9,     4,    45,     6,
      13,    13,    -1,    10,     8,    18,    19,    14,    15,    16,
      17,    32,    33,    34,    35,    36,    -1,    24,    96,    32,
      33,    34,    35,    30,    31,    -1,    32,    33,    34,    35,
      36,    -1,    39,    46,    47,    10,    11,    -1,    -1,    14,
      -1,    -1,    17,    -1,    -1,    -1,    21,    32,    33,    34,
      35,    36,    -1,    -1,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     6,    10,    14,    15,    16,    17,    24,    30,
      31,    39,    49,    50,    51,    53,    54,    55,    57,    58,
      59,    61,    62,    63,    39,    39,    39,    42,    39,    39,
      39,    39,    59,    61,    61,     0,    51,    57,    36,    37,
      57,    27,    41,    32,    33,    34,    35,    36,    17,    56,
      56,    60,    61,    60,    11,    21,    29,    39,    61,    65,
      56,    56,    65,    36,    40,    36,    14,    52,    14,    59,
      61,    61,    61,    61,    61,    37,    40,    40,    40,    38,
      43,    65,    61,    65,     9,    13,    18,    19,    46,    47,
       3,    22,    40,    40,    40,    40,    38,    36,    36,    17,
      60,    40,    61,    61,    61,    61,    61,    61,    65,    65,
      28,    44,    52,    38,    57,    57,    56,     7,     8,    64,
      45,    57,     8
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 163 "nico.y"
    {   (yyval.no) = create_node((yylsp[(1) - (2)]).first_line, code_node, NULL, (yyvsp[(1) - (2)].no), (yyvsp[(2) - (2)].no), NULL);
			                cat_tac(&((yyval.no)->code), &((yyvsp[(2) - (2)].no)->code));
                            syntax_tree = (yyval.no); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 166 "nico.y"
    {   (yyval.no) = (yyvsp[(1) - (1)].no);
            			    (yyval.no)->type = code_node; 
                            syntax_tree = (yyval.no); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 171 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (2)]).first_line, semicolon_node, ";", NULL);
						                    (yyval.no) = create_node((yylsp[(1) - (2)]).first_line, declaracoes_node, NULL, (yyvsp[(1) - (2)].no), n, NULL); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 173 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (3)]).first_line, semicolon_node, ";", NULL);
           					                (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, declaracoes_node, NULL, (yyvsp[(1) - (3)].no), (yyvsp[(2) - (3)].no), n, NULL); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 177 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (3)]).first_line, colon_node, ":", NULL);
			       			                (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, declaracao_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 181 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (1)]).first_line, idf_node, (yyvsp[(1) - (1)].cadeia), NULL);
							                    theBookIsOnTheTable((yyvsp[(1) - (1)].cadeia));
							                    (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, listadeclaracao_node, (yyvsp[(1) - (1)].cadeia), n, NULL);	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 184 "nico.y"
    {	Node* n1 = create_node((yylsp[(1) - (3)]).first_line, idf_node, (yyvsp[(1) - (3)].cadeia), NULL);
							                    Node* n2 = create_node((yylsp[(1) - (3)]).first_line, comma_node, ",", NULL);
							                    theBookIsOnTheTable((yyvsp[(1) - (3)].cadeia));
							                    (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, listadeclaracao_node, NULL, n1, n2, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 190 "nico.y"
    {   (yyval.no) = (yyvsp[(1) - (1)].no);
			        if(!strcmp((yyval.no)->lexeme,"int"))
				        tipo_idf = INT_TYPE;
			        if(!strcmp((yyval.no)->lexeme,"double"))
				        tipo_idf = DOUBLE_TYPE;
			        if(!strcmp((yyval.no)->lexeme,"real"))
				        tipo_idf = REAL_TYPE;
			        if(!strcmp((yyval.no)->lexeme,"char"))
				        tipo_idf = CHAR_TYPE;
    			    (yyval.no)->type = tipo_node; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 201 "nico.y"
    {   (yyval.no) = (yyvsp[(1) - (1)].no); 
                    if(!strcmp((yyval.no)->lexeme,"int"))
			            tipo_idf = INT_TYPE;
		            if(!strcmp((yyval.no)->lexeme,"double"))
			            tipo_idf = DOUBLE_TYPE;
		            if(!strcmp((yyval.no)->lexeme,"real"))
			            tipo_idf = REAL_TYPE;
		            if(!strcmp((yyval.no)->lexeme,"char"))
			            tipo_idf = CHAR_TYPE;
			        (yyval.no)->type = tipo_node; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 213 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (1)]).first_line, int_node, "int", NULL);
			            (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, tipounico_node, "int", n, NULL); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 215 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (1)]).first_line, double_node, "double", NULL);
			            (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, tipounico_node, "double", n, NULL); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 217 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (1)]).first_line, real_node, "real", NULL);
			            (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, tipounico_node, "real", n, NULL); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 219 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (1)]).first_line, char_node, "char", NULL);
			            (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, tipounico_node, "char", n, NULL); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 223 "nico.y"
    {   Node* n1 = create_node((yylsp[(1) - (4)]).first_line, int_node, "int", NULL);
						                    Node* n2 = create_node((yylsp[(1) - (4)]).first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node((yylsp[(1) - (4)]).first_line, r_parenteses_node, ")", NULL);
						                    (yyval.no) = create_node((yylsp[(1) - (4)]).first_line, tipolista_node, "int", n1, n2, (yyvsp[(3) - (4)].no), n4, NULL); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 227 "nico.y"
    {   Node* n1 = create_node((yylsp[(1) - (4)]).first_line, double_node, "double", NULL);
						                    Node* n2 = create_node((yylsp[(1) - (4)]).first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node((yylsp[(1) - (4)]).first_line, r_parenteses_node, ")", NULL);
						                    (yyval.no) = create_node((yylsp[(1) - (4)]).first_line, tipolista_node, "double", n1, n2, (yyvsp[(3) - (4)].no), n4, NULL); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 231 "nico.y"
    {   Node* n1 = create_node((yylsp[(1) - (4)]).first_line, real_node, "real", NULL);
						                    Node* n2 = create_node((yylsp[(1) - (4)]).first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node((yylsp[(1) - (4)]).first_line, r_parenteses_node, ")", NULL);
						                    (yyval.no) = create_node((yylsp[(1) - (4)]).first_line, tipolista_node, "real", n1, n2, (yyvsp[(3) - (4)].no), n4, NULL); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 235 "nico.y"
    {   Node* n1 = create_node((yylsp[(1) - (4)]).first_line, char_node, "char", NULL);
						                    Node* n2 = create_node((yylsp[(1) - (4)]).first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node((yylsp[(1) - (4)]).first_line, r_parenteses_node, ")", NULL);
						                    (yyval.no) = create_node((yylsp[(1) - (4)]).first_line, tipolista_node, "char", n1, n2, (yyvsp[(3) - (4)].no), n4, NULL); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 242 "nico.y"
    {	Node* n1 = create_node((yylsp[(1) - (3)]).first_line, int_lit_node, (yyvsp[(1) - (3)].cadeia), NULL);
                              						Node* n2 = create_node((yylsp[(1) - (3)]).first_line, colon_node, ":", NULL);
                              						Node* n3 = create_node((yylsp[(1) - (3)]).first_line, int_lit_node, (yyvsp[(3) - (3)].cadeia), NULL);
                              						(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, listadupla_node, NULL, n1, n2, n3, NULL); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 246 "nico.y"
    {	Node* n1 = create_node((yylsp[(1) - (5)]).first_line, int_lit_node, (yyvsp[(1) - (5)].cadeia), NULL);
                              						Node* n2 = create_node((yylsp[(1) - (5)]).first_line, colon_node, ":", NULL);
                              						Node* n3 = create_node((yylsp[(1) - (5)]).first_line, int_lit_node, (yyvsp[(3) - (5)].cadeia), NULL);
                              						Node* n4 = create_node((yylsp[(1) - (5)]).first_line, comma_node, ",", NULL);
                              						(yyval.no) = create_node((yylsp[(1) - (5)]).first_line, listadupla_node, NULL, n1, n2, n3, n4, (yyvsp[(5) - (5)].no), NULL); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 253 "nico.y"
    {   (yyval.no) = (yyvsp[(1) - (1)].no); 
            				(yyval.no)->type = acoes_node;;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 255 "nico.y"
    {   (yyval.no) = create_node((yylsp[(1) - (2)]).first_line, acoes_node, NULL, (yyvsp[(1) - (2)].no), (yyvsp[(2) - (2)].no), NULL); 
             				cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (2)].no)->code));
             				cat_tac(&((yyval.no)->code), &((yyvsp[(2) - (2)].no)->code)); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 260 "nico.y"
    {   Node* n2 = create_node((yylsp[(1) - (4)]).first_line, attr_node, "=", NULL);
                   					Node* n4 = create_node((yylsp[(1) - (4)]).first_line, semicolon_node, ";", NULL);
                   					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, comando_node, NULL, (yyvsp[(1) - (4)].no), n2, (yyvsp[(3) - (4)].no), n4, NULL);

            						struct tac* new_tac = create_inst_tac((yyvsp[(1) - (4)].no)->lexeme,(yyvsp[(3) - (4)].no)->lexeme,"","");
      			        			cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (4)].no)->code));
		           			        append_inst_tac(&((yyval.no)->code),new_tac); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 267 "nico.y"
    {   Node* n2 = create_node((yylsp[(1) - (4)]).first_line, swap_node, "<=>", NULL);
                   					Node* n4 = create_node((yylsp[(1) - (4)]).first_line, semicolon_node, ";", NULL);
                   					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, comando_node, NULL, (yyvsp[(1) - (4)].no), n2, (yyvsp[(3) - (4)].no), n4, NULL); 
               					
                   					char * temp = gera_temp(INT_TYPE);
                   					struct tac* new_tac1 = create_inst_tac(temp,(yyvsp[(1) - (4)].no)->lexeme,"","");
                   					struct tac* new_tac2 = create_inst_tac((yyvsp[(1) - (4)].no)->lexeme,(yyvsp[(3) - (4)].no)->lexeme,"","");
                   					struct tac* new_tac3 = create_inst_tac((yyvsp[(3) - (4)].no)->lexeme,temp,"","");
                       					
       			        			append_inst_tac(&((yyval.no)->code),new_tac1);
      			        			append_inst_tac(&((yyval.no)->code),new_tac2);
       			        			append_inst_tac(&((yyval.no)->code),new_tac3); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 279 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (2)]).first_line, semicolon_node, ";", NULL);
				                    (yyval.no) = create_node((yylsp[(1) - (2)]).first_line, comando_node, (yyvsp[(1) - (2)].no)->lexeme, (yyvsp[(1) - (2)].no), n, NULL);
				                    cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (2)].no)->code)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 282 "nico.y"
    {	(yyval.no) = (yyvsp[(1) - (1)].no); 
                   					(yyval.no)->type=comando_node;;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 284 "nico.y"
    {	Node* n1 = create_node((yylsp[(1) - (3)]).first_line, print_node, "print", NULL);
                   					Node* n3 = create_node((yylsp[(1) - (3)]).first_line, semicolon_node, ";", NULL);
                   					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, comando_node, NULL, n1, (yyvsp[(2) - (3)].no), n3, NULL);
                 					
                   					struct tac* new_tac = create_inst_tac("",(yyvsp[(2) - (3)].no)->lexeme,"PRINT","");
       			        			cat_tac(&((yyval.no)->code), &((yyvsp[(2) - (3)].no)->code));
			       			        append_inst_tac(&((yyval.no)->code),new_tac); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 293 "nico.y"
    {   char *temp = consulta_tabela((yyvsp[(1) - (1)].cadeia));
				                    if(temp) {
						                Node* n = create_node((yylsp[(1) - (1)]).first_line, idf_node, (yyvsp[(1) - (1)].cadeia), NULL);
						                (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, lvalue_node, temp, n, NULL);
				                    }
				                    else {
						                printf("UNDEFINED SYMBOL. A variavel %s nao foi declarada.\n", (yyvsp[(1) - (1)].cadeia));
							            return( UNDEFINED_SYMBOL_ERROR );
				                    } ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 303 "nico.y"
    {   Node* n1 = create_node((yylsp[(1) - (4)]).first_line, idf_node, (yyvsp[(1) - (4)].cadeia), NULL);
					                Node* n2 = create_node((yylsp[(1) - (4)]).first_line, l_colchetes_node, "[", NULL);
					                Node* n4 = create_node((yylsp[(1) - (4)]).first_line, r_colchetes_node, "]", NULL);
					                (yyval.no) = create_node((yylsp[(1) - (4)]).first_line, lvalue_node, NULL, n1, n2, (yyvsp[(3) - (4)].no), n4, NULL); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 309 "nico.y"
    { 	(yyval.no) = (yyvsp[(1) - (1)].no); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 310 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (3)]).first_line, comma_node, ",", NULL);
		       		            	(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, listaexpr_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 314 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (3)]).first_line, add_node, "+", NULL);
       			        (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, gera_temp(INT_TYPE), (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL);
				
       			        struct tac* new_tac = create_inst_tac((yyval.no)->lexeme,(yyvsp[(1) - (3)].no)->lexeme,"ADD",(yyvsp[(3) - (3)].no)->lexeme);
       			        cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (3)].no)->code));
       			        cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (3)].no)->code));
       			        append_inst_tac(&((yyval.no)->code),new_tac); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 321 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (3)]).first_line, sub_node, "-", NULL);
      			        (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, gera_temp(INT_TYPE), (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); 

       			        struct tac* new_tac = create_inst_tac((yyval.no)->lexeme,(yyvsp[(1) - (3)].no)->lexeme,"SUB",(yyvsp[(3) - (3)].no)->lexeme);
      			        cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (3)].no)->code));
      			        cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (3)].no)->code));
       			        append_inst_tac(&((yyval.no)->code),new_tac); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 328 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (3)]).first_line, mul_node, "*", NULL);
       			        (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, gera_temp(INT_TYPE), (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); 
				
				        struct tac* new_tac = create_inst_tac((yyval.no)->lexeme,(yyvsp[(1) - (3)].no)->lexeme,"MUL",(yyvsp[(3) - (3)].no)->lexeme);
       			        cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (3)].no)->code));
       			        cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (3)].no)->code));
       			        append_inst_tac(&((yyval.no)->code),new_tac); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 335 "nico.y"
    {	Node* n = create_node((yylsp[(1) - (3)]).first_line, div_node, "/", NULL);
       			        (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, gera_temp(INT_TYPE), (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); 
   			        
       			        struct tac* new_tac = create_inst_tac((yyval.no)->lexeme,(yyvsp[(1) - (3)].no)->lexeme,"DIV",(yyvsp[(3) - (3)].no)->lexeme);
       			        cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (3)].no)->code));
       			        cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (3)].no)->code));
       			        append_inst_tac(&((yyval.no)->code),new_tac); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 342 "nico.y"
    {   Node* n1 = create_node((yylsp[(1) - (3)]).first_line, l_parenteses_node, "(", NULL);
               			Node* n3 = create_node((yylsp[(1) - (3)]).first_line, r_parenteses_node, ")", NULL);
               			(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, (yyvsp[(2) - (3)].no)->lexeme, n1, (yyvsp[(2) - (3)].no), n3, NULL); 
               			cat_tac(&((yyval.no)->code), &((yyvsp[(2) - (3)].no)->code)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 346 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (1)]).first_line, int_lit_node, (yyvsp[(1) - (1)].cadeia), NULL); 
    			        (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, expr_node, (yyvsp[(1) - (1)].cadeia), n, NULL); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 348 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (1)]).first_line, float_node, (yyvsp[(1) - (1)].cadeia), NULL); 
    			        (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, expr_node, (yyvsp[(1) - (1)].cadeia), n, NULL); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 350 "nico.y"
    {   (yyval.no) = (yyvsp[(1) - (1)].no); 
    			        (yyval.no)->type = expr_node;;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 353 "nico.y"
    {   (yyval.no) = (yyvsp[(1) - (1)].no); 
    			        /*$$->type = expr_node;*/;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 358 "nico.y"
    {	Node* n1 = create_node((yylsp[(1) - (4)]).first_line, idf_node, (yyvsp[(1) - (4)].cadeia), NULL);
					                    Node* n2 = create_node((yylsp[(1) - (4)]).first_line, l_parenteses_node, "(", NULL);
                       					Node* n4 = create_node((yylsp[(1) - (4)]).first_line, r_parenteses_node, ")", NULL);
					                    (yyval.no) = create_node((yylsp[(1) - (4)]).first_line, chamaproc_node, NULL, n1, n2, (yyvsp[(3) - (4)].no), n4, NULL); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 365 "nico.y"
    {   Node* n1 = create_node((yylsp[(1) - (7)]).first_line, if_node, "if", NULL);
									                            Node* n2 = create_node((yylsp[(1) - (7)]).first_line, l_parenteses_node, "(", NULL);
                               									Node* n4 = create_node((yylsp[(1) - (7)]).first_line, r_parenteses_node, ")", NULL);
                               									Node* n5 = create_node((yylsp[(1) - (7)]).first_line, then_node, "then", NULL);
				                               					(yyval.no) = create_node((yylsp[(1) - (7)]).first_line, enunciado_node, NULL, n1, n2, (yyvsp[(3) - (7)].no), n4, n5, (yyvsp[(6) - (7)].no), (yyvsp[(7) - (7)].no), NULL); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 370 "nico.y"
    {	Node* n1 = create_node((yylsp[(1) - (7)]).first_line, while_node, "while", NULL);
									                            Node* n2 = create_node((yylsp[(1) - (7)]).first_line, l_parenteses_node, "(", NULL);
                               									Node* n4 = create_node((yylsp[(1) - (7)]).first_line, r_parenteses_node, ")", NULL);
                               									Node* n5 = create_node((yylsp[(1) - (7)]).first_line, l_chaves_node, "{", NULL);
                               									Node* n7 = create_node((yylsp[(1) - (7)]).first_line, r_chaves_node, "}", NULL);
                                 								(yyval.no) = create_node((yylsp[(1) - (7)]).first_line, enunciado_node, NULL, n1, n2, (yyvsp[(3) - (7)].no), n4, n5, (yyvsp[(6) - (7)].no), n7, NULL); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 379 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (1)]).first_line, end_node, "end", NULL);
					                (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, fiminstcontrole_node, NULL, n, NULL); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 381 "nico.y"
    {   Node* n1 = create_node((yylsp[(1) - (3)]).first_line, else_node, "else", NULL);
                       				Node* n3 = create_node((yylsp[(1) - (3)]).first_line, end_node, "end", NULL);
                       				(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, fiminstcontrole_node, NULL, n1, (yyvsp[(2) - (3)].no), n3, NULL); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 387 "nico.y"
    {  	Node* n = create_node((yylsp[(1) - (1)]).first_line, true_node, "true", NULL);
					                (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, expbool_node, NULL, n, NULL); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 389 "nico.y"
    {  	Node* n = create_node((yylsp[(1) - (1)]).first_line, false_node, "false", NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, expbool_node, NULL, n, NULL); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 391 "nico.y"
    {   Node* n1 = create_node((yylsp[(1) - (3)]).first_line, l_parenteses_node, "(", NULL);
                   					Node* n3 = create_node((yylsp[(1) - (3)]).first_line, r_parenteses_node, ")", NULL);
                   					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, NULL, n1, (yyvsp[(2) - (3)].no), n3, NULL); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 394 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (3)]).first_line, and_node, "and", NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 396 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (3)]).first_line, or_node, "or", NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 398 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (2)]).first_line, not_node, (yyvsp[(1) - (2)].cadeia), NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (2)]).first_line, expbool_node, NULL, n, (yyvsp[(2) - (2)].no), NULL); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 400 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (3)]).first_line, gt_node, ">", NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 402 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (3)]).first_line, lt_node, "<", NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 404 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (3)]).first_line, le_node, "<=", NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 406 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (3)]).first_line, ge_node, ">=", NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 408 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (3)]).first_line, eq_node, "==", NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 410 "nico.y"
    {   Node* n = create_node((yylsp[(1) - (3)]).first_line, ne_node, "<>", NULL);
       					            (yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, NULL, (yyvsp[(1) - (3)].no), n, (yyvsp[(3) - (3)].no), NULL); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2158 "nico.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 413 "nico.y"



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
#line 1 "analisador.y"

/*
 * =====================================================================================
 * Seção de Declarações em C
 *
 * Esta seção é copiada diretamente para o arquivo C gerado pelo Bison.
 * Contém todas as inclusões de bibliotecas, definições de estruturas de dados,
 * variáveis globais e protótipos de funções necessárias para o analisador.
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Protótipos das funções do analisador léxico e de erro.
void yyerror(char *s);
int yylex(void);
extern FILE *yyin; // Ponteiro para o arquivo de entrada, gerenciado pelo Flex/Lex.

// Enum para os tipos de dados suportados pela linguagem.
typedef enum {
    TIPO_INT,
    TIPO_FLOAT,
    TIPO_STRING,
    TIPO_VETOR,     // Um tipo especial para identificar vetores na tabela de símbolos.
    TIPO_NULO       // Representa um valor nulo ou não inicializado.
} Tipo;

// Union para armazenar diferentes tipos de valores em uma única variável.
typedef union {
    int i;
    float f;
    char *s;
    struct Valor *v; // Ponteiro para um array de 'Valor' (usado para vetores).
} ValorUnion;

// Estrutura principal para representar um valor na linguagem (seja int, float, etc.).
typedef struct Valor {
    Tipo tipo;              // O tipo do valor atualmente armazenado.
    ValorUnion val;         // O valor em si, usando a union.
    int tamanho_vetor;      // Se for um vetor, armazena seu tamanho.
} Valor;

// Estrutura para a Tabela de Símbolos (armazena variáveis e vetores).
typedef struct Simbolo {
    char *nome;             // Nome da variável/vetor.
    Tipo tipo_declarado;    // Tipo com o qual foi declarado (TIPO_INT, TIPO_VETOR, etc.).
    Valor valor;            // O valor atual do símbolo.
    struct Simbolo *prox;   // Ponteiro para o próximo símbolo na lista ligada.
} Simbolo;

// Estrutura para um nó da Árvore Sintática Abstrata (AST - Abstract Syntax Tree).
typedef struct AstNode {
    int nodetype;           // Tipo do nó (ex: '+', 'I' para IF, 'K' para constante).
    struct AstNode *l;      // Ponteiro para o filho esquerdo (ou único filho).
    struct AstNode *r;      // Ponteiro para o filho direito.
} AstNode;

// Variável Global: a cabeça da lista ligada que implementa a Tabela de Símbolos.
Simbolo *tabela_simbolos = NULL;

// Protótipos das Funções Auxiliares (implementadas na seção C mais abaixo).
Simbolo* busca_simbolo(char *nome);
Simbolo* insere_simbolo(char *nome, Tipo tipo_dec);
AstNode* novo_no_ast(int nodetype, AstNode *l, AstNode *r);
AstNode* novo_no_num_int(int ival);
AstNode* novo_no_num_float(float fval);
AstNode* novo_no_texto(char *sval);
AstNode* novo_no_id(char *id);
AstNode* novo_no_vetor_acesso(char *id, AstNode *indice);
AstNode* novo_no_atribuicao(char *id, AstNode *valor);
AstNode* novo_no_atribuicao_vetor(char *id, AstNode *indice, AstNode* valor);
AstNode* novo_no_controle(int nodetype, AstNode *cond, AstNode *corpo_verdade, AstNode *corpo_falso);
AstNode* novo_no_comparacao(int cmptype, AstNode *l, AstNode *r);
Valor eval(AstNode *a); // Função principal que interpreta a AST.
char* valor_para_string(Valor v);


#line 152 "analisador.tab.c"

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

#include "analisador.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_INTEIRO = 3,                  /* T_INTEIRO  */
  YYSYMBOL_T_REAL = 4,                     /* T_REAL  */
  YYSYMBOL_T_TEXTO = 5,                    /* T_TEXTO  */
  YYSYMBOL_NUM_INT = 6,                    /* NUM_INT  */
  YYSYMBOL_NUM_FLOAT = 7,                  /* NUM_FLOAT  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_TEXTO = 9,                      /* TEXTO  */
  YYSYMBOL_INICIO = 10,                    /* INICIO  */
  YYSYMBOL_SE = 11,                        /* SE  */
  YYSYMBOL_SENAO = 12,                     /* SENAO  */
  YYSYMBOL_ENQUANTO = 13,                  /* ENQUANTO  */
  YYSYMBOL_ESCREVA = 14,                   /* ESCREVA  */
  YYSYMBOL_LEIA = 15,                      /* LEIA  */
  YYSYMBOL_VAR = 16,                       /* VAR  */
  YYSYMBOL_FIM = 17,                       /* FIM  */
  YYSYMBOL_CMP = 18,                       /* CMP  */
  YYSYMBOL_19_ = 19,                       /* '='  */
  YYSYMBOL_20_ = 20,                       /* '+'  */
  YYSYMBOL_21_ = 21,                       /* '-'  */
  YYSYMBOL_22_ = 22,                       /* '*'  */
  YYSYMBOL_23_ = 23,                       /* '/'  */
  YYSYMBOL_UMINUS = 24,                    /* UMINUS  */
  YYSYMBOL_SENAO_PREC = 25,                /* SENAO_PREC  */
  YYSYMBOL_26_ = 26,                       /* ';'  */
  YYSYMBOL_27_ = 27,                       /* '['  */
  YYSYMBOL_28_ = 28,                       /* ']'  */
  YYSYMBOL_29_ = 29,                       /* '('  */
  YYSYMBOL_30_ = 30,                       /* ')'  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_programa = 34,                  /* programa  */
  YYSYMBOL_lista_comandos = 35,            /* lista_comandos  */
  YYSYMBOL_comando = 36,                   /* comando  */
  YYSYMBOL_tipo_var = 37,                  /* tipo_var  */
  YYSYMBOL_exp = 38                        /* exp  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   140

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  6
/* YYNRULES -- Number of rules.  */
#define YYNRULES  29
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  79

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   275


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,    30,    22,    20,     2,    21,     2,    23,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
       2,    19,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    27,     2,    28,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      15,    16,    17,    18,    24,    25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   129,   129,   130,   135,   136,   152,   158,   176,   179,
     182,   185,   188,   191,   194,   199,   200,   201,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_INTEIRO", "T_REAL",
  "T_TEXTO", "NUM_INT", "NUM_FLOAT", "ID", "TEXTO", "INICIO", "SE",
  "SENAO", "ENQUANTO", "ESCREVA", "LEIA", "VAR", "FIM", "CMP", "'='",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "SENAO_PREC", "';'", "'['", "']'",
  "'('", "')'", "'{'", "'}'", "$accept", "programa", "lista_comandos",
  "comando", "tipo_var", "exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-56)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      20,    22,    46,   -56,   106,   -56,    -3,    19,    25,    37,
      45,    29,   -56,   -56,     2,     2,     2,     2,     2,    56,
     -56,   -56,   -56,    74,   -56,   -56,    64,   -56,     2,     2,
     107,    72,    35,    49,    55,    53,   -22,     2,   -56,    66,
       2,     2,     2,     2,     2,   -56,    78,    67,    75,    79,
      89,   -56,     2,    81,   -56,    40,    58,    58,   -56,   -56,
       2,   -56,   -56,   -56,   -56,    90,   -56,   114,     4,    27,
      98,   -56,    95,   -56,   -56,    85,   -56,    36,   -56
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     4,     0,     3,     0,     1,     0,     0,     0,     0,
       0,     0,     2,     5,     0,     0,     0,     0,     0,     0,
      15,    16,    17,     0,    18,    19,    21,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,     0,
       0,     0,     0,     0,     0,     8,     0,     0,     0,     0,
       0,     6,     0,     0,    29,    27,    23,    24,    25,    26,
       0,     4,     4,    13,    14,     0,    22,     0,     0,     0,
       0,     9,    10,    12,     7,     0,     4,     0,    11
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -55,   -56,   -56,   -15
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     4,    13,    23,    30
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      31,    32,    33,    34,    51,    52,    68,    69,    24,    25,
      26,    27,     6,    38,    39,     7,    14,     8,     9,    10,
      11,    77,    53,    28,    15,    55,    56,    57,    58,    59,
       1,    29,    20,    21,    22,     6,    72,    65,     7,     3,
       8,     9,    10,    11,     6,    67,     5,     7,    16,     8,
       9,    10,    11,    40,    17,    41,    42,    43,    44,    73,
      41,    42,    43,    44,    35,    47,    18,    40,    78,    41,
      42,    43,    44,    40,    19,    41,    42,    43,    44,    48,
      43,    44,    36,    50,    40,    49,    41,    42,    43,    44,
      40,    37,    41,    42,    43,    44,    54,    60,    61,    40,
      46,    41,    42,    43,    44,    63,    62,    75,    40,    66,
      41,    42,    43,    44,     6,    64,    76,     7,    70,     8,
       9,    10,    11,    12,    74,    40,     0,    41,    42,    43,
      44,     0,    40,    45,    41,    42,    43,    44,     0,     0,
      71
};

static const yytype_int8 yycheck[] =
{
      15,    16,    17,    18,    26,    27,    61,    62,     6,     7,
       8,     9,     8,    28,    29,    11,    19,    13,    14,    15,
      16,    76,    37,    21,    27,    40,    41,    42,    43,    44,
      10,    29,     3,     4,     5,     8,    32,    52,    11,    17,
      13,    14,    15,    16,     8,    60,     0,    11,    29,    13,
      14,    15,    16,    18,    29,    20,    21,    22,    23,    32,
      20,    21,    22,    23,     8,    30,    29,    18,    32,    20,
      21,    22,    23,    18,    29,    20,    21,    22,    23,    30,
      22,    23,     8,    30,    18,    30,    20,    21,    22,    23,
      18,    27,    20,    21,    22,    23,    30,    19,    31,    18,
      28,    20,    21,    22,    23,    26,    31,    12,    18,    28,
      20,    21,    22,    23,     8,    26,    31,    11,    28,    13,
      14,    15,    16,    17,    26,    18,    -1,    20,    21,    22,
      23,    -1,    18,    26,    20,    21,    22,    23,    -1,    -1,
      26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    34,    17,    35,     0,     8,    11,    13,    14,
      15,    16,    17,    36,    19,    27,    29,    29,    29,    29,
       3,     4,     5,    37,     6,     7,     8,     9,    21,    29,
      38,    38,    38,    38,    38,     8,     8,    27,    38,    38,
      18,    20,    21,    22,    23,    26,    28,    30,    30,    30,
      30,    26,    27,    38,    30,    38,    38,    38,    38,    38,
      19,    31,    31,    26,    26,    38,    28,    38,    35,    35,
      28,    26,    32,    32,    26,    12,    31,    35,    32
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    34,    35,    35,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    37,    37,    37,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,     4,     7,     4,     7,
       7,    11,     7,     5,     5,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     3,     3,     3,     3,     2,     3
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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: INICIO lista_comandos FIM  */
#line 129 "analisador.y"
                                  { if((yyvsp[-1].a)) eval((yyvsp[-1].a)); /* Ao final, avalia a AST construída */ }
#line 1224 "analisador.tab.c"
    break;

  case 3: /* programa: INICIO FIM  */
#line 130 "analisador.y"
                                  { /* Programa vazio é válido */ }
#line 1230 "analisador.tab.c"
    break;

  case 4: /* lista_comandos: %empty  */
#line 135 "analisador.y"
      { (yyval.a) = NULL; }
#line 1236 "analisador.tab.c"
    break;

  case 5: /* lista_comandos: lista_comandos comando  */
#line 137 "analisador.y"
      {
          // Constrói uma lista de nós da AST.
          if ((yyvsp[-1].a) == NULL) {
              (yyval.a) = (yyvsp[0].a); // Se a lista estava vazia, o primeiro comando é o início da lista.
          } else if ((yyvsp[0].a) == NULL) {
              (yyval.a) = (yyvsp[-1].a); // Se o comando for uma declaração (que retorna NULL), mantém a lista existente.
          } else {
              // Cria um nó 'L' (Lista) para encadear os comandos.
              (yyval.a) = novo_no_ast('L', (yyvsp[-1].a), (yyvsp[0].a));
          }
      }
#line 1252 "analisador.tab.c"
    break;

  case 6: /* comando: VAR tipo_var ID ';'  */
#line 153 "analisador.y"
        { 
            insere_simbolo((yyvsp[-1].str), (Tipo)(yyvsp[-2].ival)); // Insere na tabela de símbolos.
            (yyval.a) = NULL; // Declarações não geram nós executáveis na AST, então retorna NULL.
        }
#line 1261 "analisador.tab.c"
    break;

  case 7: /* comando: VAR tipo_var ID '[' exp ']' ';'  */
#line 159 "analisador.y"
        {
            // Insere o símbolo como um TIPO_VETOR.
            Simbolo *s = insere_simbolo((yyvsp[-4].str), TIPO_VETOR);
            if (s) { // Se a inserção foi bem-sucedida (sem redeclaração).
                s->valor.tipo = (Tipo)(yyvsp[-5].ival); // Armazena o tipo dos *elementos* do vetor.
                Valor v_indice = eval((yyvsp[-2].a)); // Avalia a expressão do tamanho na hora.
                if (v_indice.tipo == TIPO_INT) {
                    s->valor.tamanho_vetor = v_indice.val.i;
                    // Aloca memória para o vetor.
                    s->valor.val.v = (Valor*)calloc(v_indice.val.i, sizeof(Valor));
                } else {
                    yyerror("Tamanho do vetor deve ser um inteiro.");
                }
            }
            (yyval.a) = NULL; // Também não gera nó executável.
        }
#line 1282 "analisador.tab.c"
    break;

  case 8: /* comando: ID '=' exp ';'  */
#line 177 "analisador.y"
        { (yyval.a) = novo_no_atribuicao((yyvsp[-3].str), (yyvsp[-1].a)); /* Cria um nó de atribuição. */ }
#line 1288 "analisador.tab.c"
    break;

  case 9: /* comando: ID '[' exp ']' '=' exp ';'  */
#line 180 "analisador.y"
        { (yyval.a) = novo_no_atribuicao_vetor((yyvsp[-6].str), (yyvsp[-4].a), (yyvsp[-1].a)); /* Cria um nó de atribuição a vetor. */ }
#line 1294 "analisador.tab.c"
    break;

  case 10: /* comando: SE '(' exp ')' '{' lista_comandos '}'  */
#line 183 "analisador.y"
        { (yyval.a) = novo_no_controle('I', (yyvsp[-4].a), (yyvsp[-1].a), NULL); /* Nó de controle 'I' (IF) sem ELSE. */ }
#line 1300 "analisador.tab.c"
    break;

  case 11: /* comando: SE '(' exp ')' '{' lista_comandos '}' SENAO '{' lista_comandos '}'  */
#line 186 "analisador.y"
        { (yyval.a) = novo_no_controle('I', (yyvsp[-8].a), (yyvsp[-5].a), (yyvsp[-1].a)); /* Nó de controle 'I' (IF) com ELSE. */ }
#line 1306 "analisador.tab.c"
    break;

  case 12: /* comando: ENQUANTO '(' exp ')' '{' lista_comandos '}'  */
#line 189 "analisador.y"
        { (yyval.a) = novo_no_controle('W', (yyvsp[-4].a), (yyvsp[-1].a), NULL); /* Nó de controle 'W' (WHILE). */ }
#line 1312 "analisador.tab.c"
    break;

  case 13: /* comando: ESCREVA '(' exp ')' ';'  */
#line 192 "analisador.y"
        { (yyval.a) = novo_no_ast('P', (yyvsp[-2].a), NULL); /* Nó 'P' (Print). */ }
#line 1318 "analisador.tab.c"
    break;

  case 14: /* comando: LEIA '(' ID ')' ';'  */
#line 195 "analisador.y"
        { (yyval.a) = novo_no_ast('R', novo_no_id((yyvsp[-2].str)), NULL); /* Nó 'R' (Read). */ }
#line 1324 "analisador.tab.c"
    break;

  case 15: /* tipo_var: T_INTEIRO  */
#line 199 "analisador.y"
                { (yyval.ival) = TIPO_INT; }
#line 1330 "analisador.tab.c"
    break;

  case 16: /* tipo_var: T_REAL  */
#line 200 "analisador.y"
                { (yyval.ival) = TIPO_FLOAT; }
#line 1336 "analisador.tab.c"
    break;

  case 17: /* tipo_var: T_TEXTO  */
#line 201 "analisador.y"
                { (yyval.ival) = TIPO_STRING; }
#line 1342 "analisador.tab.c"
    break;

  case 18: /* exp: NUM_INT  */
#line 206 "analisador.y"
                              { (yyval.a) = (AstNode*)novo_no_num_int((yyvsp[0].ival));    }
#line 1348 "analisador.tab.c"
    break;

  case 19: /* exp: NUM_FLOAT  */
#line 207 "analisador.y"
                              { (yyval.a) = (AstNode*)novo_no_num_float((yyvsp[0].fval));  }
#line 1354 "analisador.tab.c"
    break;

  case 20: /* exp: TEXTO  */
#line 208 "analisador.y"
                              { (yyval.a) = (AstNode*)novo_no_texto((yyvsp[0].str));      }
#line 1360 "analisador.tab.c"
    break;

  case 21: /* exp: ID  */
#line 209 "analisador.y"
                              { (yyval.a) = (AstNode*)novo_no_id((yyvsp[0].str));         }
#line 1366 "analisador.tab.c"
    break;

  case 22: /* exp: ID '[' exp ']'  */
#line 210 "analisador.y"
                              { (yyval.a) = novo_no_vetor_acesso((yyvsp[-3].str), (yyvsp[-1].a));     }
#line 1372 "analisador.tab.c"
    break;

  case 23: /* exp: exp '+' exp  */
#line 211 "analisador.y"
                              { (yyval.a) = novo_no_ast('+', (yyvsp[-2].a), (yyvsp[0].a));         }
#line 1378 "analisador.tab.c"
    break;

  case 24: /* exp: exp '-' exp  */
#line 212 "analisador.y"
                              { (yyval.a) = novo_no_ast('-', (yyvsp[-2].a), (yyvsp[0].a));         }
#line 1384 "analisador.tab.c"
    break;

  case 25: /* exp: exp '*' exp  */
#line 213 "analisador.y"
                              { (yyval.a) = novo_no_ast('*', (yyvsp[-2].a), (yyvsp[0].a));         }
#line 1390 "analisador.tab.c"
    break;

  case 26: /* exp: exp '/' exp  */
#line 214 "analisador.y"
                              { (yyval.a) = novo_no_ast('/', (yyvsp[-2].a), (yyvsp[0].a));         }
#line 1396 "analisador.tab.c"
    break;

  case 27: /* exp: exp CMP exp  */
#line 215 "analisador.y"
                              { (yyval.a) = novo_no_comparacao((yyvsp[-1].fn), (yyvsp[-2].a), (yyvsp[0].a));   }
#line 1402 "analisador.tab.c"
    break;

  case 28: /* exp: '-' exp  */
#line 216 "analisador.y"
                              { (yyval.a) = novo_no_ast('M', (yyvsp[0].a), NULL);        }
#line 1408 "analisador.tab.c"
    break;

  case 29: /* exp: '(' exp ')'  */
#line 217 "analisador.y"
                              { (yyval.a) = (yyvsp[-1].a); /* Parênteses apenas agrupam, não criam nós. */ }
#line 1414 "analisador.tab.c"
    break;


#line 1418 "analisador.tab.c"

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
      yyerror (YY_("syntax error"));
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 220 "analisador.y"


/* * =====================================================================================
 * Seção de Código C
 *
 * Implementação de todas as funções C declaradas na primeira seção.
 * Aqui é onde a "mágica" acontece: manipulação da tabela de símbolos,
 * criação dos nós da AST e, mais importante, a interpretação da AST (função eval).
 * =====================================================================================
 */

// Procura um símbolo (variável) na tabela de símbolos.
Simbolo* busca_simbolo(char *nome) {
    Simbolo *s;
    // Percorre a lista ligada.
    for (s = tabela_simbolos; s != NULL; s = s->prox) {
        if (strcmp(s->nome, nome) == 0) {
            return s; // Retorna o ponteiro para o símbolo se encontrado.
        }
    }
    return NULL; // Retorna NULL se não encontrar.
}

// Insere um novo símbolo na tabela de símbolos.
Simbolo* insere_simbolo(char *nome, Tipo tipo_dec) {
    if (busca_simbolo(nome) != NULL) {
        yyerror("Variavel ja declarada.");
        return NULL;
    }
    Simbolo *s = (Simbolo*) malloc(sizeof(Simbolo));
    s->nome = strdup(nome); // Duplica a string do nome para evitar problemas de ponteiro.
    s->tipo_declarado = tipo_dec;
    s->valor.tipo = TIPO_NULO; // Variáveis começam com valor nulo.
    s->prox = tabela_simbolos; // Insere no início da lista.
    tabela_simbolos = s;
    return s;
}

// Função genérica para criar um novo nó da AST.
AstNode* novo_no_ast(int nodetype, AstNode *l, AstNode *r) {
    AstNode *a = (AstNode*)malloc(sizeof(AstNode));
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

// Funções "fábrica" para criar nós de constantes, encapsulando o valor.
AstNode* novo_no_num_int(int ival) {
    Valor *v = (Valor*)malloc(sizeof(Valor));
    v->tipo = TIPO_INT;
    v->val.i = ival;
    return novo_no_ast('K', (AstNode*)v, NULL); // 'K' para constante.
}

AstNode* novo_no_num_float(float fval) {
    Valor *v = (Valor*)malloc(sizeof(Valor));
    v->tipo = TIPO_FLOAT;
    v->val.f = fval;
    return novo_no_ast('K', (AstNode*)v, NULL);
}

AstNode* novo_no_texto(char *sval) {
    Valor *v = (Valor*)malloc(sizeof(Valor));
    v->tipo = TIPO_STRING;
    v->val.s = strdup(sval);
    return novo_no_ast('K', (AstNode*)v, NULL);
}

// Cria um nó que referencia um Identificador (variável/vetor).
AstNode* novo_no_id(char *id) {
    Simbolo *s = busca_simbolo(id);
    if (s == NULL) {
        char err[100];
        sprintf(err, "Variavel '%s' nao declarada", id);
        yyerror(err);
        exit(1);
    }
    // O nó 'N' (Nome) armazena um ponteiro direto para a entrada na tabela de símbolos.
    return novo_no_ast('N', (AstNode*)s, NULL);
}

// Cria um nó para acesso a um elemento de vetor.
AstNode* novo_no_vetor_acesso(char *id, AstNode *indice) {
    Simbolo *s = busca_simbolo(id);
    if (s == NULL) {
        yyerror("Vetor nao declarado");
        exit(1);
    }
    // Nó 'A' (Acesso) guarda o símbolo e a AST do índice.
    return novo_no_ast('A', (AstNode*)s, indice);
}

// Cria um nó para atribuição a uma variável.
AstNode* novo_no_atribuicao(char *id, AstNode *valor) {
    Simbolo *s = busca_simbolo(id);
    if (s == NULL) {
        yyerror("Variavel nao declarada");
        exit(1);
    }
    // Nó '=' guarda o símbolo e a AST do valor a ser atribuído.
    return novo_no_ast('=', (AstNode*)s, valor);
}

// Cria um nó para atribuição a um elemento de vetor.
AstNode* novo_no_atribuicao_vetor(char *id, AstNode *indice, AstNode* valor) {
    Simbolo *s = busca_simbolo(id);
    if (s == NULL) {
        yyerror("Vetor nao declarado");
        exit(1);
    }
    // Nó 'a' (atribuição a arranjo) é mais complexo.
    // Reutilizamos o nó de atribuição e adicionamos a AST do índice.
    AstNode *temp = novo_no_ast('=', (AstNode*)s, valor);
    return novo_no_ast('a', temp, indice);
}

// Cria um nó para estruturas de controle (IF, WHILE).
AstNode* novo_no_controle(int nodetype, AstNode *cond, AstNode *corpo_v, AstNode *corpo_f) {
    AstNode *a = (AstNode*)malloc(sizeof(AstNode));
    a->nodetype = nodetype;
    a->l = cond; // Filho esquerdo é a condição.
    a->r = novo_no_ast(0, corpo_v, corpo_f); // Filho direito é um nó auxiliar que guarda os corpos.
    return a;
}

// Cria um nó de comparação.
AstNode* novo_no_comparacao(int cmptype, AstNode *l, AstNode *r) {
    AstNode *a = (AstNode*)malloc(sizeof(AstNode));
    a->nodetype = 'C'; // 'C' para comparação.
    a->l = novo_no_ast(cmptype, l, r); // Filho esquerdo é um nó auxiliar que guarda o tipo de comparação e os operandos.
    return a;
}

// Verifica se um valor é considerado "verdadeiro" na lógica da linguagem.
int eh_verdadeiro(Valor v) {
    switch (v.tipo) {
        case TIPO_INT:    return v.val.i != 0;
        case TIPO_FLOAT:  return v.val.f != 0.0;
        case TIPO_STRING: return v.val.s[0] != '\0'; // String vazia é falsa.
        default:          return 0; // Nulo e outros tipos são falsos.
    }
}

// Converte qualquer tipo de valor para uma string (para impressão ou concatenação).
char* valor_para_string(Valor v) {
    char buffer[50];
    switch (v.tipo) {
        case TIPO_INT:    sprintf(buffer, "%d", v.val.i); return strdup(buffer);
        case TIPO_FLOAT:  sprintf(buffer, "%g", v.val.f); return strdup(buffer);
        case TIPO_STRING: return strdup(v.val.s);
        case TIPO_NULO:   return strdup("(nulo)");
        default:          return strdup("(tipo desconhecido)");
    }
}

/**
 * @brief Função central do interpretador. Avalia (executa) uma AST recursivamente.
 * * @param a Ponteiro para o nó da AST a ser avaliado.
 * @return Valor O resultado da avaliação do nó.
 */
Valor eval(AstNode *a) {
    Valor v = { .tipo = TIPO_NULO }, v_esq, v_dir, v_indice;
    if (!a) {
        return v; // Se o nó for nulo (ex: comando de declaração), não faz nada.
    }

    Simbolo *s;
    switch (a->nodetype) {
        case 'K': // Constante: o valor já está pronto no nó.
            v = *(Valor*)(a->l);
            break;

        case 'N': // Nome (ID): busca o valor na tabela de símbolos.
            s = (Simbolo*)(a->l);
            v = s->valor;
            break;

        case 'A': // Acesso a Vetor: avalia o índice e pega o valor no vetor.
            s = (Simbolo*)(a->l);
            v_indice = eval(a->r);
            if (s->tipo_declarado != TIPO_VETOR) {
                yyerror("Variavel nao e um vetor");
            } else if (v_indice.tipo != TIPO_INT) {
                yyerror("Indice do vetor deve ser inteiro");
            } else {
                int idx = v_indice.val.i;
                if (idx < 0 || idx >= s->valor.tamanho_vetor) {
                    yyerror("Indice do vetor fora dos limites");
                } else {
                    v = s->valor.val.v[idx]; // Pega o valor na posição correta.
                }
            }
            break;

        case '=': // Atribuição a variável.
            s = (Simbolo*)(a->l);
            v_dir = eval(a->r); // Avalia o lado direito da atribuição.
            // Coerção de tipo: permite atribuir um inteiro a uma variável float.
            if (s->tipo_declarado == TIPO_FLOAT && v_dir.tipo == TIPO_INT) {
                v_dir.tipo = TIPO_FLOAT;
                v_dir.val.f = v_dir.val.i;
            }
            if (s->tipo_declarado != v_dir.tipo) {
                char erro[100];
                sprintf(erro, "Erro de tipo: atribuicao invalida para a variavel '%s'", s->nome);
                yyerror(erro);
            } else {
                s->valor = v_dir; // Atualiza o valor na tabela de símbolos.
            }
            v = s->valor; // O resultado de uma atribuição é o próprio valor atribuído.
            break;

        case 'a': // Atribuição a elemento de vetor.
            s = (Simbolo*)(a->l->l);
            v_dir = eval(a->l->r);
            v_indice = eval(a->r);
            // Validações de tipo e limites.
            if (s->tipo_declarado != TIPO_VETOR) { yyerror("Variavel nao e um vetor"); break; }
            if (v_indice.tipo != TIPO_INT) { yyerror("Indice do vetor deve ser inteiro"); break; }
            // Coerção de tipo.
            if (s->valor.tipo == TIPO_FLOAT && v_dir.tipo == TIPO_INT) {
                v_dir.tipo = TIPO_FLOAT;
                v_dir.val.f = v_dir.val.i;
            }
            if (s->valor.tipo != v_dir.tipo) {
                yyerror("Erro de tipo na atribuicao de valor ao vetor.");
            } else {
                int idx = v_indice.val.i;
                if (idx < 0 || idx >= s->valor.tamanho_vetor) {
                    yyerror("Indice do vetor fora dos limites");
                } else {
                    s->valor.val.v[idx] = v_dir; // Atribui o valor na posição correta.
                    v = v_dir;
                }
            }
            break;

        case '+': // Soma ou Concatenação.
            v_esq = eval(a->l);
            v_dir = eval(a->r);
            // Se um dos operandos for string, faz concatenação.
            if (v_esq.tipo == TIPO_STRING || v_dir.tipo == TIPO_STRING) {
                char *s_esq = valor_para_string(v_esq);
                char *s_dir = valor_para_string(v_dir);
                char *resultado = (char*) malloc(strlen(s_esq) + strlen(s_dir) + 1);
                strcpy(resultado, s_esq);
                strcat(resultado, s_dir);
                v.tipo = TIPO_STRING;
                v.val.s = resultado;
                free(s_esq); free(s_dir);
            // Senão, faz soma numérica.
            } else if ((v_esq.tipo == TIPO_INT || v_esq.tipo == TIPO_FLOAT) &&
                       (v_dir.tipo == TIPO_INT || v_dir.tipo == TIPO_FLOAT)) {
                // Promove para float se necessário.
                if (v_esq.tipo == TIPO_FLOAT || v_dir.tipo == TIPO_FLOAT) {
                    float f_esq = (v_esq.tipo == TIPO_INT) ? v_esq.val.i : v_esq.val.f;
                    float f_dir = (v_dir.tipo == TIPO_INT) ? v_dir.val.i : v_dir.val.f;
                    v.tipo = TIPO_FLOAT;
                    v.val.f = f_esq + f_dir;
                } else {
                    v.tipo = TIPO_INT;
                    v.val.i = v_esq.val.i + v_dir.val.i;
                }
            } else {
                yyerror("Operador '+' invalido para estes tipos.");
            }
            break;

        case '-': case '*': case '/': // Operações aritméticas.
            v_esq = eval(a->l);
            v_dir = eval(a->r);
            if (!((v_esq.tipo == TIPO_INT || v_esq.tipo == TIPO_FLOAT) &&
                  (v_dir.tipo == TIPO_INT || v_dir.tipo == TIPO_FLOAT))) {
                yyerror("Operadores '-', '*' e '/' so podem ser usados com numeros.");
                break;
            }
            // Promove para float se necessário.
            if (v_esq.tipo == TIPO_FLOAT || v_dir.tipo == TIPO_FLOAT) {
                float f_esq = (v_esq.tipo == TIPO_INT) ? v_esq.val.i : v_esq.val.f;
                float f_dir = (v_dir.tipo == TIPO_INT) ? v_dir.val.i : v_dir.val.f;
                v.tipo = TIPO_FLOAT;
                switch(a->nodetype) {
                    case '-': v.val.f = f_esq - f_dir; break;
                    case '*': v.val.f = f_esq * f_dir; break;
                    case '/': v.val.f = f_esq / f_dir; break; // Divisão de float.
                }
            } else {
                v.tipo = TIPO_INT;
                switch(a->nodetype) {
                    case '-': v.val.i = v_esq.val.i - v_dir.val.i; break;
                    case '*': v.val.i = v_esq.val.i * v_dir.val.i; break;
                    case '/': v.val.i = v_esq.val.i / v_dir.val.i; break; // Divisão inteira.
                }
            }
            break;
            
        case 'C': // Comparação.
            v_esq = eval(a->l->l);
            v_dir = eval(a->l->r);
            // Comparações são sempre feitas como floats para simplicidade.
            float f_esq = (v_esq.tipo == TIPO_INT) ? v_esq.val.i : v_esq.val.f;
            float f_dir = (v_dir.tipo == TIPO_INT) ? v_dir.val.i : v_dir.val.f;
            v.tipo = TIPO_INT; // Resultado da comparação é 1 (true) ou 0 (false).
            switch(a->l->nodetype) { // O tipo da comparação está no nó auxiliar.
                case 1: v.val.i = f_esq >  f_dir; break; // >
                case 2: v.val.i = f_esq <  f_dir; break; // <
                case 3: v.val.i = f_esq != f_dir; break; // !=
                case 4: v.val.i = f_esq == f_dir; break; // ==
                case 5: v.val.i = f_esq >= f_dir; break; // >=
                case 6: v.val.i = f_esq <= f_dir; break; // <=
            }
            break;

        case 'M': // Menos unário.
            v = eval(a->l);
            if (v.tipo == TIPO_INT) v.val.i = -v.val.i;
            else if (v.tipo == TIPO_FLOAT) v.val.f = -v.val.f;
            break;

        case 'I': // IF/ELSE.
            if (eh_verdadeiro(eval(a->l))) { // Avalia a condição.
                if(a->r->l) v = eval(a->r->l); // Se verdadeira, executa o corpo IF.
            } else {
                if(a->r->r) v = eval(a->r->r); // Se falsa, executa o corpo ELSE (se existir).
            }
            break;

        case 'W': // WHILE.
            while(eh_verdadeiro(eval(a->l))) { // Avalia a condição a cada iteração.
                v = eval(a->r->l); // Executa o corpo do laço.
            }
            break;

        case 'P': // ESCREVA (Print).
            v = eval(a->l);
            switch (v.tipo) {
                case TIPO_INT:    printf("%d\n", v.val.i);    break;
                case TIPO_FLOAT:  printf("%g\n", v.val.f);    break;
                case TIPO_STRING: printf("%s\n", v.val.s);    break;
                case TIPO_NULO:   printf("(nulo)\n");         break;
                default:          printf("Tipo nao imprimivel\n");
            }
            break;

        case 'R': // LEIA (Read).
            s = (Simbolo*)(a->l->l);
            char buffer[256];
            if(fgets(buffer, 255, stdin)) {
                buffer[strcspn(buffer, "\n")] = 0; // Remove a quebra de linha do final.
                // Converte a string lida para o tipo declarado da variável.
                if (s->tipo_declarado == TIPO_STRING) {
                    s->valor.tipo = TIPO_STRING;
                    s->valor.val.s = strdup(buffer);
                } else if (s->tipo_declarado == TIPO_INT) {
                    s->valor.tipo = TIPO_INT;
                    s->valor.val.i = atoi(buffer);
                } else if (s->tipo_declarado == TIPO_FLOAT) {
                    s->valor.tipo = TIPO_FLOAT;
                    s->valor.val.f = atof(buffer);
                } else {
                    yyerror("Nao e possivel ler valor para este tipo de variavel.");
                }
                v = s->valor;
            }
            break;

        case 'L': // Lista de comandos: executa um após o outro.
            if(a->l) eval(a->l);
            if(a->r) v = eval(a->r);
            break;

        default:
            printf("Erro interno: no desconhecido %c\n", a->nodetype);
    }
    return v;
}

// Função de erro padrão do Yacc/Bison.
void yyerror(char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}

// Função principal do programa.
int main(int argc, char **argv) {
    // Permite que o nome do arquivo de entrada seja passado como argumento.
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    } else {
        // Se nenhum arquivo for passado, tenta abrir um arquivo padrão "entradas.txt".
        yyin = fopen("entradas.txt", "r");
        if (!yyin) {
            perror("Nao foi possivel abrir 'entradas.txt'");
            return 1;
        }
    }
    
    yyparse(); // Inicia o processo de análise sintática.
    
    if (yyin != stdin) {
        fclose(yyin);
    }
    
    return 0;
}

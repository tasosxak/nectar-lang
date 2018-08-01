/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "nectar_syntax"

/*Author: Tasos Temperekidis*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MHNYMA 0

/* ----------------------------------------------------------- */
/* --------- Declarations for Syntax-Semantic Analysis ------- */
/* ----------------------------------------------------------- */


#include "nectar_defs.h"

HASH_TAB ht; /*Symbol Table for Methods,Classes and declarations*/
HASH_TAB arr_st[MAX_SYM_TABLES]; /*Method's Symbol Table*/

int topOfSt = 0; /*The current activated method's symbol table*/
int TopOfStack=-1;
int TopOfWhile=-1;
int TopOfRt = -1;
int numOfParams = 0;  /* For number of method's parameters*/
int numOfArguments =0; /* For "arguments and parameters matching"*/
int enableReturn = 1;

/*** FOR MIX CODE GENERATION ***/
int NUM_BYTES_VAR=0; /*Number of variables (for mix variable names)*/
int NUM_METH=0; /*Number of methods (for mix method names)*/
int NUM_PAR=0;
char NUM_VAR_ARR[7];
char TEMP_NUM_VAR_ARR[7];

char METHOD_NAME[50];
char METHOD_NAME_PARS[50];
char METHOD_NAME_TEMP[25];

char CLASS_NAME[50];

symbol *vs[30];
symbol *whiles[30];  /*For "break in while" checking*/
symbol *returns[30]; /* Check if return keyword exists for all cases in a method*/
symbol *cur_class;
int CUR_TYPE = 1000;
symbol *p,*p1,*p2,*p3,*p4,*p5,*p6,*p7,*p8,*p9;

AstNode *TreeRoot;


#line 56 "nectar_syntax"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union
{
    int   yint;
    char  ystr[81];
    struct AstNode_tag *stnode;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 87 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define FALSE 257
#define TRUE 258
#define INT 259
#define RETURN 260
#define IF 261
#define ELSE 262
#define WHILE 263
#define BREAK 264
#define TRY 265
#define READ 266
#define PRINTLN 267
#define TIMES 268
#define USE 269
#define UNLESS 270
#define NOT 271
#define AND 272
#define OR 273
#define REAL 274
#define PUTS 275
#define BOOL 276
#define FUNC 277
#define RIGHTARROW 278
#define CLASS 279
#define PRIVATE 280
#define PUBLIC 281
#define ABSTRACT 282
#define METH 283
#define VAR 284
#define STR 285
#define SELF 286
#define IN 287
#define FOR 288
#define DEC_CONST 289
#define LITERAL 290
#define REAL_DEC_CONST 291
#define IDIV 292
#define GE 293
#define LE 294
#define NE 295
#define EQ 296
#define ID 297
#define INC 298
#define DEC 299
#define ADDASSIGN 300
#define SUBASSIGN 301
#define LOWER_THAN_ELSE 302
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    1,    1,    2,    2,    9,   46,    3,
    8,    8,    8,    5,    5,    6,    6,    7,    7,    7,
    4,   47,   48,   10,   49,   50,   11,   12,   12,   14,
   14,   15,   15,   15,   15,   15,   13,   16,   16,   17,
   17,   51,   18,   52,   18,   53,   18,   54,   19,   55,
   19,   19,   20,   20,   23,   23,   23,   23,   23,   23,
   23,   56,   21,   21,   21,   21,   21,   21,   57,   21,
   21,   21,   58,   21,   59,   21,   60,   21,   21,   21,
   21,   21,   21,   21,   25,   24,   24,   22,   30,   31,
   32,   32,   36,   37,   37,   34,   33,   26,   26,   27,
   27,   28,   28,   29,   29,   35,   35,   35,   35,   35,
   35,   38,   38,   39,   39,   40,   40,   41,   41,   41,
   41,   42,   42,   42,   42,   42,   42,   42,   42,   42,
   42,   42,   42,   42,   42,   43,   43,   43,   43,   44,
   44,   45,   45,
};
static const YYINT yylen[] = {                            2,
    1,    2,    2,    2,    0,    2,    0,    1,    0,    5,
    0,    1,    1,    2,    0,    5,    7,    3,    5,    0,
    4,    0,    0,   10,    0,    0,   10,    4,    0,    5,
    0,    1,    1,    1,    1,    1,    4,    2,    0,    2,
    0,    0,    7,    0,   10,    0,    9,    0,    4,    0,
    6,    0,    2,    0,    1,    1,    1,    1,    2,    4,
    1,    0,    2,    2,    2,    2,    3,    6,    0,    9,
    4,    4,    0,    6,    0,    6,    0,    4,    2,    1,
    3,    5,    2,    1,    1,    3,    1,    3,    3,    3,
    3,    3,    5,    5,    3,    1,    1,    3,    1,    3,
    1,    2,    1,    3,    1,    1,    1,    1,    1,    1,
    1,    3,    1,    1,    1,    3,    1,    1,    1,    1,
    1,    1,    3,    1,    1,    1,    1,    1,    1,    4,
    6,    2,    2,    1,    4,    2,    2,    2,    2,    2,
    0,    3,    0,
};
static const YYINT yydefred[] = {                         0,
    0,   12,   13,    0,    0,    1,    0,    0,    0,    0,
   25,    0,    2,    0,    3,    4,    0,    0,    9,    0,
   32,   33,   34,   35,   36,    0,    0,    0,    0,    0,
    0,    0,    0,   10,    0,    0,  128,  127,    0,  129,
  125,  134,  126,    0,    0,    0,    0,    0,    0,    0,
  101,  103,    0,    0,    0,    0,  117,  122,    0,    0,
    0,    0,    0,    0,    0,    0,  102,    0,  132,  133,
    0,   97,  137,  139,    0,    0,    0,  136,  138,    0,
    0,  114,  115,  106,  107,  108,  109,  110,  111,    0,
    0,  118,  119,  120,  121,    0,   44,    0,   85,   43,
    0,    0,    0,    0,    8,   14,   26,    0,  123,   96,
    0,    0,    0,  100,    0,    0,    0,    0,    0,  116,
    0,    0,    0,    0,   21,   22,    6,    0,   30,    0,
   47,  135,  130,    0,    0,    0,   49,    0,    0,    0,
   27,    0,  142,   45,    0,    0,    0,   16,    0,   54,
    0,  131,   51,    0,    0,    0,    0,    0,   17,    0,
   18,    0,    0,   62,   73,    0,    0,    0,   75,   54,
   37,   53,   80,    0,   84,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   79,    0,    0,    0,
    0,    0,    0,    0,   77,   83,   64,   65,   63,    0,
    0,    0,    0,   66,   19,   23,   67,    0,    0,    0,
   81,    0,    0,   88,    0,    0,    0,    0,   92,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   86,    0,
   71,   72,   78,    0,    0,    0,   24,    0,    0,   82,
    0,    0,    0,    0,    0,   74,   76,    0,   69,    0,
    0,   70,
};
static const YYINT yydgoto[] = {                          5,
    6,  102,    7,   34,   63,   64,  148,    8,  104,  105,
    9,   28,  141,   29,   26,  150,  151,   10,   61,  157,
  172,  173,  174,  189,  175,  176,   50,   51,   52,  177,
  178,  179,   53,   54,   90,  181,  222,   55,   91,   56,
   96,   57,   58,  116,  117,   27,  139,  225,   17,  128,
   32,  121,   76,  123,  145,  185,  251,  186,  191,  217,
};
static const YYINT yysindex[] = {                      -121,
 -277,    0,    0, -264,    0,    0, -121, -235, -121, -121,
    0,   37,    0, -199,    0,    0,   61, -206,    0,    0,
    0,    0,    0,    0,    0,  -24,   12,   79, -159,  229,
 -142,  104,   86,    0, -127,   95,    0,    0,  677,    0,
    0,    0,    0,  229, -246,  116, -132, -132, -109, -105,
    0,    0,  -52,  126,   67,  -26,    0,    0,   75, -128,
  111, -122, -168,   86, -206, -206,    0,  -23,    0,    0,
 -120,    0,    0,    0,  229,  104,  229,    0,    0,  229,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  677,
  677,    0,    0,    0,    0,  677,    0,  118,    0,    0,
  122,   56, -114, -168,    0,    0,    0,  141,    0,    0,
  146, -105,  111,    0,  -81,  147,  229,   91,  -26,    0,
  104,  229,  104, -206,    0,    0,    0,   68,    0,    0,
    0,    0,    0,  -31,  111, -109,    0,  -15,  150,    0,
    0,  152,    0,    0,  104,  229, -103,    0,    0,    0,
  -89,    0,    0,  -30,    8,  155,  652,    0,    0,  229,
    0,  -80,  229,    0,    0,  111,  229,  229,    0,    0,
    0,    0,    0, -223,    0,  -57,  111,  111,  111,   -4,
  111,  -30, -206,  -33,  157,  159,    0,  -25,  111,   -3,
 -132,  720,  229,  229,    0,    0,    0,    0,    0,  229,
 -132,  229,  229,    0,    0,    0,    0,  229,  229, -132,
    0,  229,  -87,    0,  -33,  -33,  849, -109,    0,  -27,
   45,  158, -109, -109,   68,   -6,   -5,  111,    0,  229,
    0,    0,    0,  229, -132,  229,    0,  849,  849,    0,
  763, -109,  160, -109,  -61,    0,    0,  229,    0, -109,
  849,    0,
};
static const YYINT yyrindex[] = {                         1,
    0,    0,    0,    0,    0,    0,    1,    0,    1,    1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -32,
    0,    0,    0,    0,    0,    7,    0,    0,    0,    0,
    0,  144, -110,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -37,    0,    0,   48,  324,
    0,    0,   18,    0,  374,   59,    0,    0,    0,    0,
    0,    0, -108, -110,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  144,    0,    0,    0,    0,
  174,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   49,    0,    0,
    0,    0,    0, -108,    0,    0,    0,  164,    0,    0,
    0,  417,    0,    0,    0,    0,    0,  473,  114,    0,
  144,    0,  144,    0,    0,    0,    0,    0,    0,  174,
    0,    0,    0,  165,    0,   50,    0,   21,    0,  527,
    0,    0,    0,    0,  144,    0,    0,    0,  -32,    0,
    0,    0,    0,   21,   21,    0,    0,  571,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -165, -146, -145, -144,  911,
 -133,   21,    0,    0,    0,    0,    0,    0, -131,  -29,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   22,    0,  953,
    0,    0,   63,   73,    0,    0,    0, -130,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  166,    0,   74,  806,    0,    0,    0,    0,  168,
    0,    0,
};
static const YYINT yygindex[] = {                         0,
  135,  105,    0,    0,  149,    0, -106,  -21,    0,    0,
    0,   69,  -17,    0,  -34,    0,    0,   66,  -48,   52,
 -167,    0,    0,   13, 1108, 1070,  153,  161,  234,    0,
    0,   77,  840,  216,    0,    0,   58,  208,    0,  210,
    0,  209,    0,  191,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 1336
static const YYINT yytable[] = {                         97,
    5,   99,   96,   97,   97,   97,   97,   97,   29,   97,
   95,  132,  143,  147,   15,   92,    7,  109,  210,   11,
   93,   97,   97,   97,   97,   99,   97,  113,  147,   87,
  107,  108,   12,  200,  238,  239,   30,  193,   80,  201,
  212,  103,   69,   14,   70,  146,  194,  159,  161,  233,
   42,  147,   21,   97,  124,   97,  200,  124,  124,  124,
  124,  124,  124,   80,  124,   42,   31,   22,  160,   23,
  245,  246,  135,  247,  137,  205,  124,  124,   24,  124,
   91,  124,  103,  252,   20,   97,   80,   97,  235,  138,
   25,   46,   48,   50,   18,   61,  153,   19,  113,  113,
   20,  113,  113,  113,   61,  234,   46,   48,   50,   82,
  124,   83,    2,    3,   56,   57,   55,  113,  113,   35,
  113,   89,  113,   56,   57,   55,   87,   58,   85,   59,
   60,   90,   93,   82,   33,   83,   58,   36,   59,   60,
  124,   13,  124,   15,   16,   20,   59,   60,  206,   62,
   65,  113,   66,  112,  112,    1,  112,  112,  112,    2,
    3,   71,    4,   75,   72,   81,   77,   97,   98,   99,
   15,   15,  112,  112,  101,  112,  110,  112,  122,  124,
  125,  113,  126,  113,  129,  130,   15,  133,   11,  149,
  140,   75,  152,  155,    4,  162,  208,  183,  209,  230,
  249,  236,   52,  248,   28,  140,  112,  237,  127,   95,
  195,   94,  106,  143,  141,   75,  158,  156,  143,   97,
   97,  192,   97,   97,  229,   97,   97,  112,   97,   97,
   97,   87,   97,   97,   97,   97,  112,  114,  112,   75,
   87,   75,   75,   97,   97,   78,   79,   75,   97,   75,
   97,   97,   97,   97,   97,   97,   97,   97,   97,   97,
   97,   97,   97,   97,   31,   94,   75,   75,   44,   75,
   78,   79,   67,   45,  124,  124,  219,  124,  124,   11,
  124,  124,   91,  124,  124,  124,  111,  124,  124,  124,
  124,   91,  243,   78,   79,  202,  203,  118,  124,  124,
  119,   20,   20,  124,  120,  124,  124,  124,  124,  124,
  124,  124,  124,  124,  124,  113,  113,   20,  113,  113,
  142,  113,  113,   89,  113,  113,  113,    0,  113,  113,
  113,  113,   89,   90,   93,    0,    0,    0,    0,  113,
  113,    0,   90,   93,  113,    0,  113,  113,  113,  113,
    0,  113,  113,  113,  113,  113,  113,  113,    0,   84,
   86,   88,   89,   99,   99,    0,    0,   99,   99,    0,
  112,  112,    0,  112,  112,    0,  112,  112,    0,  112,
  112,  112,   99,  112,  112,  112,  112,   99,    0,    0,
    0,    0,    0,    0,  112,  112,    0,    0,    0,  112,
    0,  112,  112,  112,  112,    0,  112,  112,  112,  112,
  112,  112,  112,  105,  105,    0,   99,  105,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  143,  143,  105,    0,    0,    0,    0,  105,    0,    0,
    0,    0,    0,    0,  143,    0,   99,    0,   99,    0,
    0,    0,    0,    0,    0,    0,   98,   98,    0,  143,
   98,   98,  143,  143,  143,    0,  105,    0,    0,    0,
  143,  143,  143,    0,    0,   98,    0,    0,    0,    0,
   98,    0,    0,    0,    0,   37,   38,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  105,    0,  105,   39,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   98,
    0,    0,  104,  104,   40,    0,  104,   41,   42,   43,
    0,    0,    0,    0,    0,   46,   47,   48,    0,    0,
    0,  104,    0,    0,    0,    0,  104,    0,    0,   98,
    0,   98,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  104,   39,    0,    0,    0,
    0,   39,    0,    0,    0,    0,    0,    0,    0,    0,
   99,   99,    0,   99,   99,   39,   99,   99,    0,   99,
   99,   99,    0,   99,   99,  104,   99,  104,    0,    0,
    0,    0,    0,    0,   99,   99,    0,    0,    0,   99,
   38,   99,   99,   99,   99,   38,    0,    0,    0,    0,
   99,   99,   99,    0,    0,    0,    0,    0,    0,   38,
  105,  105,    0,  105,  105,    0,  105,  105,    0,  105,
  105,  105,    0,  105,  105,  105,  105,    0,    0,   39,
    0,   39,    0,    0,  105,  105,    0,    0,    0,  105,
    0,  105,  105,  105,  105,    0,    0,    0,    0,    0,
  105,  105,  105,   98,   98,    0,   98,   98,    0,   98,
   98,    0,   98,   98,   98,    0,   98,   98,    0,   98,
    0,   44,    0,   38,    0,   38,   45,   98,   98,    0,
    0,    0,   98,    0,   98,   98,   98,   98,    0,    0,
   99,    0,    0,   98,   98,   98,   44,    0,    0,    0,
    0,   45,    0,    0,    0,    0,    0,    0,    0,  104,
  104,    0,  104,  104,    0,  104,  104,    0,  104,  104,
  104,    0,  104,  104,  104,  104,    0,    0,    0,    0,
    0,    0,    0,  104,  104,    0,    0,    0,  104,   44,
  104,  104,  104,  104,   45,    0,    0,    0,    0,  104,
  104,  104,    0,    0,  170,    0,  171,    0,   99,    0,
    0,    0,    0,   39,   39,    0,   39,   39,    0,   39,
   39,    0,   39,   39,    0,    0,    0,   39,    0,    0,
    0,    0,   44,    0,    0,    0,    0,   45,    0,    0,
   41,    0,   39,    0,   39,   39,   39,   39,    0,    0,
    0,   99,    0,   39,   39,   39,    0,   38,   38,    0,
   38,   38,    0,   38,   38,    0,   38,   38,    0,    0,
    0,   38,  170,    0,  214,   68,    0,    0,    0,    0,
   68,    0,    0,    0,   40,    0,   38,    0,   38,   38,
   38,   38,    0,    0,   68,    0,    0,   38,   38,   38,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  170,   73,   74,   44,    0,
    0,    0,    0,   45,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   99,   37,   38,
    0,  163,  164,    0,  165,  166,    0,  167,  168,    0,
    0,    0,   39,    0,    0,    0,    0,    0,   68,    0,
   68,    0,    0,   37,   38,    0,    0,   40,    0,  169,
   41,   42,   43,    0,    0,    0,    0,  124,   46,   47,
   48,    0,  124,  124,    0,  124,    0,  124,    0,    0,
    0,    0,   40,    0,    0,   41,   42,   43,    0,  124,
  124,  170,  124,   46,   47,   48,   37,   38,    0,  163,
  164,    0,  165,  166,    0,  167,  168,    0,    0,  124,
   39,    0,    0,    0,  124,  124,  180,  124,    0,  124,
    0,    0,    0,    0,    0,   40,    0,  169,   41,   42,
   43,  124,  124,    0,  124,    0,   46,   47,   48,   37,
   38,    0,  163,  164,    0,  165,  166,    0,  167,  168,
  213,  180,    0,   39,    0,   75,    0,    0,    0,  220,
  221,    0,    0,    0,    0,    0,    0,    0,   40,  228,
  169,   41,   42,   43,    0,    0,  180,    0,    0,   46,
   47,   48,   68,   68,    0,   68,   68,    0,   68,   68,
    0,   68,   68,    0,  221,    0,   68,  180,  180,    0,
  180,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  180,   68,    0,   68,   68,   68,   68,    0,    0,   49,
    0,    0,   68,   68,   68,   37,   38,    0,  163,  164,
    0,  165,  166,   68,  167,  168,    0,    0,    0,   39,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   40,    0,  169,   41,   42,   43,
    0,    0,    0,    0,    0,   46,   47,   48,    0,  115,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  100,    0,
    0,  124,    0,    0,    0,    0,    0,    0,  124,    0,
  124,    0,  124,  124,    0,    0,  134,    0,    0,    0,
    0,  136,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  124,  124,  124,  124,  124,    0,    0,    0,
    0,    0,    0,  124,    0,  154,    0,    0,    0,    0,
  131,    0,  124,    0,  124,  124,    0,    0,    0,  182,
    0,    0,  184,    0,    0,    0,  188,  190,    0,    0,
    0,    0,  144,    0,  124,  124,  124,  124,  124,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  215,  216,    0,    0,    0,    0,    0,  218,
    0,  223,  224,  187,    0,    0,    0,  226,  227,    0,
    0,  190,    0,  196,  197,  198,  199,    0,  204,    0,
    0,  207,    0,    0,    0,    0,  211,    0,    0,  241,
    0,    0,    0,  242,    0,  244,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  250,    0,    0,
    0,    0,  231,  232,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  240,
};
static const YYINT yycheck[] = {                         37,
    0,   59,   40,   41,   42,   43,   44,   45,   41,   47,
   37,   93,   44,   44,  125,   42,  125,   41,   44,  297,
   47,   59,   60,   61,   62,   59,   64,   76,   44,   59,
   65,   66,  297,   61,   41,   41,   61,  261,   91,   44,
   44,   63,  289,  279,  291,   61,  270,  154,  155,  217,
   44,   44,  259,   91,   37,   93,   61,   40,   41,   42,
   43,   44,   45,   91,   47,   59,   91,  274,   61,  276,
  238,  239,  121,  241,  123,  182,   59,   60,  285,   62,
   59,   64,  104,  251,   64,  123,   91,  125,   44,  124,
  297,   44,   44,   44,   58,  261,  145,  297,   40,   41,
   40,   43,   44,   45,  270,   61,   59,   59,   59,   43,
   93,   45,  281,  282,  261,  261,  261,   59,   60,   41,
   62,   59,   64,  270,  270,  270,   60,  261,   62,  261,
  261,   59,   59,   43,  123,   45,  270,  297,  270,  270,
  123,    7,  125,    9,   10,  125,  289,   44,  183,   64,
  278,   93,   58,   40,   41,  277,   43,   44,   45,  281,
  282,   46,  284,  273,  297,   40,  272,   93,  297,   59,
  281,  282,   59,   60,  297,   62,  297,   64,   61,   58,
  125,  123,  297,  125,   44,   40,  297,   41,  297,   40,
  123,  273,   41,  297,  284,   41,   40,  278,   40,  287,
  262,   44,   59,   44,   41,   41,   93,  225,  104,   44,
  268,   44,   64,   40,   41,  273,  151,  149,   45,  257,
  258,  170,  260,  261,  212,  263,  264,   75,  266,  267,
  268,  261,  270,  271,  272,  273,  123,   77,  125,  273,
  270,  273,  273,  281,  282,  298,  299,  273,  286,  273,
  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,  300,  301,  297,  292,  273,  273,   40,  273,
  298,  299,   39,   45,  257,  258,  200,  260,  261,  279,
  263,  264,  261,  266,  267,  268,   71,  270,  271,  272,
  273,  270,  235,  298,  299,  300,  301,   90,  281,  282,
   91,  281,  282,  286,   96,  288,  289,  290,  291,  292,
  293,  294,  295,  296,  297,  257,  258,  297,  260,  261,
  130,  263,  264,  261,  266,  267,  268,   -1,  270,  271,
  272,  273,  270,  261,  261,   -1,   -1,   -1,   -1,  281,
  282,   -1,  270,  270,  286,   -1,  288,  289,  290,  291,
   -1,  293,  294,  295,  296,  297,  298,  299,   -1,  293,
  294,  295,  296,   40,   41,   -1,   -1,   44,   45,   -1,
  257,  258,   -1,  260,  261,   -1,  263,  264,   -1,  266,
  267,  268,   59,  270,  271,  272,  273,   64,   -1,   -1,
   -1,   -1,   -1,   -1,  281,  282,   -1,   -1,   -1,  286,
   -1,  288,  289,  290,  291,   -1,  293,  294,  295,  296,
  297,  298,  299,   40,   41,   -1,   93,   44,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  257,  258,   59,   -1,   -1,   -1,   -1,   64,   -1,   -1,
   -1,   -1,   -1,   -1,  271,   -1,  123,   -1,  125,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   40,   41,   -1,  286,
   44,   45,  289,  290,  291,   -1,   93,   -1,   -1,   -1,
  297,  298,  299,   -1,   -1,   59,   -1,   -1,   -1,   -1,
   64,   -1,   -1,   -1,   -1,  257,  258,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,  125,  271,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,
   -1,   -1,   40,   41,  286,   -1,   44,  289,  290,  291,
   -1,   -1,   -1,   -1,   -1,  297,  298,  299,   -1,   -1,
   -1,   59,   -1,   -1,   -1,   -1,   64,   -1,   -1,  123,
   -1,  125,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   40,   -1,   -1,   -1,
   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  257,  258,   -1,  260,  261,   59,  263,  264,   -1,  266,
  267,  268,   -1,  270,  271,  123,  273,  125,   -1,   -1,
   -1,   -1,   -1,   -1,  281,  282,   -1,   -1,   -1,  286,
   40,  288,  289,  290,  291,   45,   -1,   -1,   -1,   -1,
  297,  298,  299,   -1,   -1,   -1,   -1,   -1,   -1,   59,
  257,  258,   -1,  260,  261,   -1,  263,  264,   -1,  266,
  267,  268,   -1,  270,  271,  272,  273,   -1,   -1,  123,
   -1,  125,   -1,   -1,  281,  282,   -1,   -1,   -1,  286,
   -1,  288,  289,  290,  291,   -1,   -1,   -1,   -1,   -1,
  297,  298,  299,  257,  258,   -1,  260,  261,   -1,  263,
  264,   -1,  266,  267,  268,   -1,  270,  271,   -1,  273,
   -1,   40,   -1,  123,   -1,  125,   45,  281,  282,   -1,
   -1,   -1,  286,   -1,  288,  289,  290,  291,   -1,   -1,
   59,   -1,   -1,  297,  298,  299,   40,   -1,   -1,   -1,
   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,   -1,  260,  261,   -1,  263,  264,   -1,  266,  267,
  268,   -1,  270,  271,  272,  273,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  281,  282,   -1,   -1,   -1,  286,   40,
  288,  289,  290,  291,   45,   -1,   -1,   -1,   -1,  297,
  298,  299,   -1,   -1,  123,   -1,  125,   -1,   59,   -1,
   -1,   -1,   -1,  257,  258,   -1,  260,  261,   -1,  263,
  264,   -1,  266,  267,   -1,   -1,   -1,  271,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   -1,   -1,   45,   -1,   -1,
  284,   -1,  286,   -1,  288,  289,  290,  291,   -1,   -1,
   -1,   59,   -1,  297,  298,  299,   -1,  257,  258,   -1,
  260,  261,   -1,  263,  264,   -1,  266,  267,   -1,   -1,
   -1,  271,  123,   -1,  125,   40,   -1,   -1,   -1,   -1,
   45,   -1,   -1,   -1,  284,   -1,  286,   -1,  288,  289,
  290,  291,   -1,   -1,   59,   -1,   -1,  297,  298,  299,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  123,   47,   48,   40,   -1,
   -1,   -1,   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,  257,  258,
   -1,  260,  261,   -1,  263,  264,   -1,  266,  267,   -1,
   -1,   -1,  271,   -1,   -1,   -1,   -1,   -1,  123,   -1,
  125,   -1,   -1,  257,  258,   -1,   -1,  286,   -1,  288,
  289,  290,  291,   -1,   -1,   -1,   -1,   37,  297,  298,
  299,   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
   -1,   -1,  286,   -1,   -1,  289,  290,  291,   -1,   59,
   60,  123,   62,  297,  298,  299,  257,  258,   -1,  260,
  261,   -1,  263,  264,   -1,  266,  267,   -1,   -1,   37,
  271,   -1,   -1,   -1,   42,   43,  157,   45,   -1,   47,
   -1,   -1,   -1,   -1,   -1,  286,   -1,  288,  289,  290,
  291,   59,   60,   -1,   62,   -1,  297,  298,  299,  257,
  258,   -1,  260,  261,   -1,  263,  264,   -1,  266,  267,
  191,  192,   -1,  271,   -1,  273,   -1,   -1,   -1,  200,
  201,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  286,  210,
  288,  289,  290,  291,   -1,   -1,  217,   -1,   -1,  297,
  298,  299,  257,  258,   -1,  260,  261,   -1,  263,  264,
   -1,  266,  267,   -1,  235,   -1,  271,  238,  239,   -1,
  241,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  251,  286,   -1,  288,  289,  290,  291,   -1,   -1,   30,
   -1,   -1,  297,  298,  299,  257,  258,   -1,  260,  261,
   -1,  263,  264,   44,  266,  267,   -1,   -1,   -1,  271,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  286,   -1,  288,  289,  290,  291,
   -1,   -1,   -1,   -1,   -1,  297,  298,  299,   -1,   80,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   61,   -1,
   -1,  261,   -1,   -1,   -1,   -1,   -1,   -1,  268,   -1,
  270,   -1,  272,  273,   -1,   -1,  117,   -1,   -1,   -1,
   -1,  122,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  292,  293,  294,  295,  296,   -1,   -1,   -1,
   -1,   -1,   -1,  261,   -1,  146,   -1,   -1,   -1,   -1,
  113,   -1,  270,   -1,  272,  273,   -1,   -1,   -1,  160,
   -1,   -1,  163,   -1,   -1,   -1,  167,  168,   -1,   -1,
   -1,   -1,  135,   -1,  292,  293,  294,  295,  296,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  193,  194,   -1,   -1,   -1,   -1,   -1,  200,
   -1,  202,  203,  166,   -1,   -1,   -1,  208,  209,   -1,
   -1,  212,   -1,  176,  177,  178,  179,   -1,  181,   -1,
   -1,  184,   -1,   -1,   -1,   -1,  189,   -1,   -1,  230,
   -1,   -1,   -1,  234,   -1,  236,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  248,   -1,   -1,
   -1,   -1,  215,  216,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  228,
};
#define YYFINAL 5
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 302
#define YYUNDFTOKEN 365
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,0,0,0,
0,0,"':'","';'","'<'","'='","'>'",0,"'@'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"FALSE","TRUE","INT","RETURN","IF",
"ELSE","WHILE","BREAK","TRY","READ","PRINTLN","TIMES","USE","UNLESS","NOT",
"AND","OR","REAL","PUTS","BOOL","FUNC","RIGHTARROW","CLASS","PRIVATE","PUBLIC",
"ABSTRACT","METH","VAR","STR","SELF","IN","FOR","DEC_CONST","LITERAL",
"REAL_DEC_CONST","IDIV","GE","LE","NE","EQ","ID","INC","DEC","ADDASSIGN",
"SUBASSIGN","LOWER_THAN_ELSE",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : definitions",
"definitions : class definitions",
"definitions : func definitions",
"definitions : decl definitions",
"definitions :",
"meth_list : methodef meth_list",
"meth_list :",
"methodef : meth",
"$$1 :",
"class : modifier CLASS ID $$1 bodyclass",
"modifier :",
"modifier : PUBLIC",
"modifier : ABSTRACT",
"fields : field fields",
"fields :",
"field : '@' ID ':' type attrs",
"field : '@' ID ':' type '=' expr attrs",
"attrs : ',' ID attrs",
"attrs : ',' ID '=' expr attrs",
"attrs :",
"bodyclass : '{' fields meth_list '}'",
"$$2 :",
"$$3 :",
"meth : modifier ID $$2 '(' params ')' RIGHTARROW type $$3 body",
"$$4 :",
"$$5 :",
"func : FUNC ID $$4 '(' params ')' RIGHTARROW type $$5 body",
"params : formals ID ':' type",
"params :",
"formals : formals ID ':' type ','",
"formals :",
"type : INT",
"type : REAL",
"type : BOOL",
"type : STR",
"type : ID",
"body : '{' decls stmts '}'",
"decls : decl_list decl",
"decls :",
"decl_list : decl_list decl",
"decl_list :",
"$$6 :",
"decl : VAR ID ':' type $$6 vars separator",
"$$7 :",
"decl : VAR ID ':' type '[' DEC_CONST ']' $$7 vars separator",
"$$8 :",
"decl : VAR ID ':' type '=' expr $$8 vars separator",
"$$9 :",
"vars : ',' ID $$9 vars",
"$$10 :",
"vars : ',' ID '=' expr $$10 vars",
"vars :",
"stmts : stmts stmt",
"stmts :",
"singlestmt : assign",
"singlestmt : addassign",
"singlestmt : subassign",
"singlestmt : listedassign",
"singlestmt : PRINTLN inline",
"singlestmt : READ expr ',' location",
"singlestmt : expr",
"code :",
"stmt : assign separator",
"stmt : addassign separator",
"stmt : subassign separator",
"stmt : listedassign separator",
"stmt : RETURN expr separator",
"stmt : IF code '(' expr ')' stmt",
"$$11 :",
"stmt : IF code '(' expr ')' stmt ELSE $$11 stmt",
"stmt : singlestmt IF expr separator",
"stmt : singlestmt UNLESS expr separator",
"$$12 :",
"stmt : WHILE $$12 '(' expr ')' stmt",
"$$13 :",
"stmt : FOR $$13 location IN expr stmt",
"$$14 :",
"stmt : expr TIMES $$14 stmt",
"stmt : BREAK separator",
"stmt : block",
"stmt : PRINTLN inline separator",
"stmt : READ expr ',' location separator",
"stmt : expr separator",
"stmt : separator",
"separator : ';'",
"inline : expr ',' inline",
"inline : expr",
"block : '{' stmts '}'",
"addassign : location ADDASSIGN expr",
"subassign : location SUBASSIGN expr",
"assign : location '=' expr",
"assign : location '=' assign",
"listedassign : location ',' nestedassign ',' expr",
"nestedassign : location ',' nestedassign ',' expr",
"nestedassign : location '=' expr",
"method : ID",
"location : ID",
"expr : expr OR logAnd_expr",
"expr : logAnd_expr",
"logAnd_expr : logAnd_expr AND not_expr",
"logAnd_expr : not_expr",
"not_expr : NOT comp_expr",
"not_expr : comp_expr",
"comp_expr : add_expr relop add_expr",
"comp_expr : add_expr",
"relop : GE",
"relop : '>'",
"relop : LE",
"relop : '<'",
"relop : NE",
"relop : EQ",
"add_expr : add_expr addop term",
"add_expr : term",
"addop : '+'",
"addop : '-'",
"term : term mulop factor",
"term : factor",
"mulop : '*'",
"mulop : '/'",
"mulop : IDIV",
"mulop : '%'",
"factor : incdec",
"factor : '(' expr ')'",
"factor : location",
"factor : DEC_CONST",
"factor : REAL_DEC_CONST",
"factor : TRUE",
"factor : FALSE",
"factor : SELF",
"factor : method '(' actuals ')'",
"factor : ID '.' method '(' actuals ')'",
"factor : '-' DEC_CONST",
"factor : '-' REAL_DEC_CONST",
"factor : LITERAL",
"factor : location '[' expr ']'",
"incdec : location INC",
"incdec : INC location",
"incdec : location DEC",
"incdec : DEC location",
"actuals : args expr",
"actuals :",
"args : args expr ','",
"args :",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 2114 "nectar_syntax"



void Init_Hash_Table(void)
{  int i;

   for(i=0; i<SYM_TABLE_SIZE; i++)
      ht.table[i]=NULL;
}


void Init_Array_Hash_Table(void)
{  int i,j;

   for(i=0; i<MAX_SYM_TABLES; i++){
        for(j=0; j<SYM_TABLE_SIZE; j++){
            arr_st[i].table[j]=NULL;
          }
     }
}


void push_wh(symbol *p)
{
   whiles[++TopOfWhile]=p;

}

void push_rt(symbol *p)
{
   returns[++TopOfRt]=p;
}

symbol *pop_rt(void)
{

   return(returns[TopOfRt--]);
}



void push_vs(symbol *p)
{
   vs[++TopOfStack]=p;
}

symbol* see_wh()
{
   return whiles[TopOfWhile];
}

symbol *pop_wh(void)
{
	if(TopOfWhile<0) return(NULL);
	symbol * temp;
	temp = whiles[TopOfWhile--];
	whiles[TopOfWhile+1] = NULL;

   return(temp);
}


symbol *pop_vs(void)
{

   return(vs[TopOfStack--]);
}

symbol *new_symbol(char *name){

   symbol *symbp;
   symbp=(symbol *)malloc(sizeof(symbol));
   memset(symbp,0,sizeof(symbol));
   strncpy(symbp->name,name,(strlen(name)>NAME_MAX)?NAME_MAX:strlen(name));


   symbp->timi=0;
   symbp->lvalue=1;
   symbp->arg = 0;
   symbp->mht = NULL;
   symbp->has_timi = 0;
   symbp->dcl_ptr = NULL;
   symbp->NextSymbol=NULL;
   symbp->PrevSymbol=NULL;
   return(symbp);
}

void add_method_dcl(symbol *symbp)
{  dcl *p,*q;

   q=(dcl *)malloc(sizeof(dcl));
   q->dcl_type=METHOD;
   q->num_params=numOfParams;
   p=symbp->dcl_ptr;
   if(!p)
      symbp->dcl_ptr=q;


}

void add_array_dcl(symbol *symbp, int size)
{  dcl *p,*q;

   q=(dcl *)malloc(sizeof(dcl));
   q->dcl_type=ARRAY;
   q->num_params=size;
   p=symbp->dcl_ptr;
   if(!p)
      symbp->dcl_ptr=q;


}

int is_integral(symbol *s){

	if(s){
		if(s->typos == INT)
			return(1);


	}

	return(0);

}

int set_class_types(symbol *symbp, int class_tipos)
{
   switch(class_tipos){

    case INT:
         if(symbp->typos) return(1);
         symbp->typos=class_tipos;
    break;
	  case REAL:
         if(symbp->typos) return(1);
         symbp->typos=class_tipos;
    break;
	  case BOOL:
         if(symbp->typos) return(1);
         symbp->typos=class_tipos;
    break;
    case METHOD:
		     add_method_dcl(symbp);
    break;
    case STR:
          if(symbp->typos) return(1);
          symbp->typos=class_tipos;
    break;
    default:
          if(symbp->typos) return(1);
          symbp->typos=class_tipos;
    break;
   }
   return(0);
}


void Init_while_stack(){
	int i =0;
	for(;i<30; i++)
		whiles[i] = NULL;

}



void copy_attributes(symbol *dst, symbol *src){

   symbol *p;
   int ret_v;

   if(src){

     p=dst;

     if(src->typos){

            ret_v=set_class_types(p,src->typos);
            if(ret_v){
               printf("One type permitted\n");
               exit(1);
            }
         }
      }

}



int mkkey(char *s)
{  char *p;
   int athr=0;

   for(p=s; *p; p++) athr=athr+(*p);
   return (athr % SYM_TABLE_SIZE);
}

void addsymb(symbol *symbp, int gl)
{  int i;
   symbol *p;

    if(topOfSt == MAX_SYM_TABLES) {
			printf("Out of memory :( , the number of methods must be less than %d",MAX_SYM_TABLES); //if the number of methods is greater than MAX_SYM_TABLES constant
			exit(1);
			}

 if(gl ==1) {
   i=mkkey(symbp->name);
   p=ht.table[i];
   symbp->NextSymbol=p;
   symbp->PrevSymbol=NULL;
   symbp->mht= &arr_st[topOfSt];
   if(p) p->PrevSymbol=symbp;
   ht.table[i]=symbp;
   ht.numbsymbols++;
 }else {

   i=mkkey(symbp->name);
   p=arr_st[topOfSt].table[i];
   symbp->NextSymbol=p;
   symbp->PrevSymbol=NULL;
   if(p) p->PrevSymbol=symbp;
   arr_st[topOfSt].table[i]=symbp;
   arr_st[topOfSt].numbsymbols++;

}

}

symbol *findsymb(char *onoma, int gl)
{  int i;
   symbol *p;

   if(gl == 1){
   i=mkkey(onoma);
   p=ht.table[i];

   while(p && (strcmp(p->name,onoma) !=0)){
      p=p->NextSymbol;
}
}else {
    i=mkkey(onoma);
	 if(topOfSt == MAX_SYM_TABLES) {
			printf("Out of memory :( , the number of methods must be less than %d",MAX_SYM_TABLES); //if the number of methods is greater than MAX_SYM_TABLES constant
			exit(1);
			}
    p=arr_st[topOfSt].table[i];
    while(p && (strcmp(p->name,onoma) !=0))
       p=p->NextSymbol;


   }
 return(p);
}

void add_symbols_to_table(symbol *symbp, int gl)
{
      symbol *exists;
      exists=findsymb(symbp->name,gl);

      if( !exists )
      {
         addsymb(symbp,gl);

      }
           /* -- exists -- */
      else
      {
         printf("Error: '%s' redeclaration\n",symbp->name);
         exit(1);
      }

}

void discard_symbol(symbol *symbp)
{
   if(symbp)
   {


      symbp->PrevSymbol->NextSymbol = symbp->NextSymbol;
      symbp->NextSymbol->PrevSymbol = symbp->PrevSymbol;
	  symbp->PrevSymbol = NULL;
	  symbp->NextSymbol = NULL;

   }
}

void check_assignment(symbol *opnd1, symbol *opnd2)
{  symbol *p;

   if( !(opnd1->lvalue))
   {
      printf("Error: The left operand must be an lvalue (modifiable)\n");
      exit(1);
   }

   return;
}


void copy_value(symbol *dst, symbol *src)
{
   if(src->has_timi){

      if(src->has_timi == CONST_VAL){

		 switch (dst->typos){
			 case INT:

				dst->timi = src->timi;
				dst->has_timi=src->has_timi;

			 break;
			 case REAL:

				dst->dtimi = src->dtimi;
				dst->has_timi=src->has_timi;

			 break;
			 case BOOL:

				dst->timi = src->timi;
				dst->has_timi=src->has_timi;

			 break;

		 }

       }
   }
}

void copy_symbol(symbol *dst, symbol *src)
{
   if( src && dst){
		dst->typos=src->typos;
		copy_value(dst,src);
   }

}

AstNode *MkNode(int tipos,symbol *sn,
              AstNode *z0,AstNode *z1,AstNode *z2,AstNode *z3)
{  AstNode *p;

   p=(AstNode *)malloc(sizeof(AstNode));
   if(!p)
   {
      printf("Out of memory\n");
      exit(1);
   }
   else
   {
      p->NodeType=tipos;
      p->SymbolNode=sn;
      p->pAstNode[0]=z0;
      p->pAstNode[1]=z1;
      p->pAstNode[2]=z2;
      p->pAstNode[3]=z3;
      return(p);
   }
}

void check_while(symbol *pexp, symbol *pst)
{
   if(pexp->typos != INT)
   {
      printf("Error: The expression must have scalar type\n");
      exit(1);
   }

}



void check_ifelse(symbol *pexp, symbol *pst1, symbol *pst2)
{

   if( !is_integral(pexp))
   {
      printf("Error: The expression must have scalar type\n");
      exit(1);
   }
  // discard_symbol(pexp);
  // discard_symbol(pst1);
   //discard_symbol(pst2);
}

void preOrder(AstNode* p, int indent){
    if(p != NULL) {

		if (indent) {
			int i;
            for (i=0; i<=indent; i++){
				printf(" ");
			}
        }
        printf("%s\n", p->NodeType);
        if(p->pAstNode[0]) preOrder(p->pAstNode[0], indent+8);
        if(p->pAstNode[1]) preOrder(p->pAstNode[1], indent+8);
        if(p->pAstNode[2]) preOrder(p->pAstNode[2], indent+8);

    }
}



void Show_Hash_Table(void)
{
	int i,j;

	printf("\n------------- METHODS ---------\n");
	for(i=0; i<SYM_TABLE_SIZE; i++){

		printf("%s ",ht.table[i]) ;
	}
	printf("\n------------- VARIABLES ---------\n");

	for (i=0; i<MAX_SYM_TABLES ;i++){
		for (j=0; j<SYM_TABLE_SIZE; j++){
			printf("%s ",arr_st[i].table[j]) ;
		}
		printf("\n");
	}


}





symbol *check_logic_op(symbol *opnd1, symbol *opnd2)
{  symbol *p;

   if(( !is_integral(opnd1) ) || ( !is_integral(opnd2) ))
   {
      printf("Error: Both operands must be integers\n");

      exit(1);
   }
   p=new_symbol("");
   p->typos=INT;
   p->lvalue=0;
   p->has_timi=0;

   if((opnd1->has_timi==CONST_VAL) && (opnd1->has_timi==CONST_VAL))
         p->has_timi=CONST_VAL;

   if((opnd1->sclass==CONSTANT) && (opnd2->sclass==CONSTANT))
      p->sclass=CONSTANT;

   return(p);
}


symbol *check_muldiv_arithm_op(symbol *opnd1, symbol *opnd2)
{  symbol *p;

   if(( !is_integral(opnd1) ) || ( !is_integral(opnd2) ))
   {
      printf("Error: Both operands must be integers\n");
      exit(1);
   }
   p=new_symbol("");
   p->typos=INT;
   p->lvalue=0;
   p->has_timi=0;
   if((opnd1->has_timi==CONST_VAL) && (opnd1->has_timi==CONST_VAL))
         p->has_timi=CONST_VAL;

   if((opnd1->sclass==CONSTANT) && (opnd2->sclass==CONSTANT))
      p->sclass=CONSTANT;

   return(p);
}

int isSuperType(int type1, int type2){

	switch(type1){

		case INT:
			switch(type2){

				case INT:
					 return(1);
				break;
				case REAL:
					 return(0);
				break;
				case BOOL:
					 return(0);
				break;
			}
		break;
		case REAL:
			switch(type2){

				case INT:
					 return(1);
				break;
				case REAL:
					 return(1);
				break;
				case BOOL:
					 return(0);
				break;

			}
		break;
		case BOOL:
			switch(type2){

					case INT:
						 return(0);
					break;
					case REAL:
						 return(0);
					break;
					case BOOL:
						 return(1);
					break;

				}
		break;
    default:
         return type1 == type2;


	}


}


symbol *check_addsub_arithm_op(symbol *opnd1, symbol *opnd2)
{  symbol *p;
   dcl *d1, *d2;

   p=new_symbol("");

   if(is_integral(opnd1) && is_integral(opnd2))
   {
      p->typos=opnd1->typos;
	 /* if(opnd1->has_timi)
		{
			if(opnd1->has_timi == CONST_VAL)
				p->timi = opnd1->timi;
			p->has_timi=opnd1->has_timi;
		}*/
	   if((opnd1->has_timi==CONST_VAL) && (opnd1->has_timi==CONST_VAL))
         p->has_timi=CONST_VAL;

      if((opnd1->sclass==CONSTANT) && (opnd2->sclass==CONSTANT))
         p->sclass=CONSTANT;
   }
   else
   {
      printf("Error: Both operands must be integers\n");
      exit(1);
   }

   p->lvalue=0;


   return(p);
}


int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}


void yyerror(char *s)
{
   fputs(s,stderr); putc('\n',stderr);
}
#line 1369 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 87 "nectar_syntax"
	{

      		     p1 = findsymb("main",1);/*Every program in coral language must has a main function*/
      		     if(!p1) {
      					printf("Error : 'main' not found in program");
      					exit(1);
      				}

			        TreeRoot=MkNode(astProgram,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);


        }
break;
case 2:
#line 104 "nectar_syntax"
	{ yyval.stnode=MkNode(astClassDef,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL); }
break;
case 3:
#line 105 "nectar_syntax"
	{ yyval.stnode=MkNode(astFuncDef,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL); }
break;
case 4:
#line 106 "nectar_syntax"
	{ yyval.stnode=MkNode(astDeclDef,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL); }
break;
case 5:
#line 107 "nectar_syntax"
	{ yyval.stnode=MkNode(astEmptyDef,NULL,NULL,NULL,NULL,NULL); }
break;
case 6:
#line 112 "nectar_syntax"
	{yyval.stnode=MkNode(astMethSeq,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL); }
break;
case 7:
#line 114 "nectar_syntax"
	{ yyval.stnode=MkNode(astEmptyMethList,NULL,NULL,NULL,NULL,NULL); }
break;
case 8:
#line 117 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 9:
#line 121 "nectar_syntax"
	{

         strcpy(CLASS_NAME,yystack.l_mark[0].ystr);
         p1 = pop_vs();

         p2 = new_symbol(CLASS_NAME);
         p2->accessor = p1->accessor;
         p2->lvalue = 0;
         p2->typos = CUR_TYPE++;
         /*Check if main method have parameters*/
         if((strcmp(p2->name,"Object") == 0)){

           printf("Error: Object class already exists\n");
           exit(1);
         }

         add_symbols_to_table(p2,1);

         if(topOfSt == MAX_SYM_TABLES) {
  				printf("Out of memory :( , the number of classes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
  				exit(1);
  			 }

         cur_class = p2;

       }
break;
case 10:
#line 146 "nectar_syntax"
	{


         yyval.stnode=MkNode(astClass,cur_class,yystack.l_mark[0].stnode,NULL,NULL,NULL);

         cur_class = NULL;
         strcpy(CLASS_NAME,"");
       }
break;
case 11:
#line 157 "nectar_syntax"
	{

             yyval.stnode=MkNode(astPrivateClassMod,NULL,NULL,NULL,NULL,NULL);
             p1 = new_symbol(""); /*create symbol*/
   	         p1->accessor = PRIVATE_ACC;
   	         push_vs(p1);
          }
break;
case 12:
#line 164 "nectar_syntax"
	{

             yyval.stnode=MkNode(astPublicClassMod,NULL,NULL,NULL,NULL,NULL);
             p1 = new_symbol(""); /*create symbol*/
             p1->accessor = PUBLIC_ACC;
             push_vs(p1);
         }
break;
case 13:
#line 171 "nectar_syntax"
	{

             yyval.stnode=MkNode(astAbstractClassMod,NULL,NULL,NULL,NULL,NULL);
             p1 = new_symbol(""); /*create symbol*/
   	         p1->accessor = ABSTRACT_ACC;
   	         push_vs(p1);
         }
break;
case 14:
#line 182 "nectar_syntax"
	{yyval.stnode=MkNode(astFields,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL);}
break;
case 15:
#line 183 "nectar_syntax"
	{yyval.stnode=MkNode(astEmptyFields,NULL,NULL,NULL,NULL,NULL);}
break;
case 16:
#line 186 "nectar_syntax"
	{

               p1 = pop_vs();
               p3 = new_symbol(yystack.l_mark[-3].ystr);
               p3->sclass = MEMORY;
               p3->typos = p1->typos;
               p3->accessor = PRIVATE_ACC;
               p3->lvalue = 0;
               add_symbols_to_table(p3,1);

               if(topOfSt == MAX_SYM_TABLES) {
                printf("Out of memory :( , the number of attributes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
                exit(1);
               }

              yyval.stnode=MkNode(astField,p3,yystack.l_mark[0].stnode,NULL,NULL,NULL);


         }
break;
case 17:
#line 205 "nectar_syntax"
	{


           p1 = pop_vs();
           p2 = pop_vs();

           p4 = new_symbol(yystack.l_mark[-5].ystr);
           p4->sclass = MEMORY;
           p4->typos = p2->typos;
           p4->accessor = PRIVATE_ACC;
           p4->lvalue = 0;

           add_symbols_to_table(p4,0);

          if(topOfSt == MAX_SYM_TABLES) {
            printf("Out of memory :( , the number of attributes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
            exit(1);
          }

           yyval.stnode=MkNode(astFieldAssign,p4,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL);


         }
break;
case 18:
#line 231 "nectar_syntax"
	{

           p1 = pop_vs();
           /*p2 = pop_vs();*/

           p3 = new_symbol(yystack.l_mark[0].stnode);
           p3->sclass = MEMORY;
           p3->typos = p1->typos;
           p3->accessor = PRIVATE_ACC;
           p3->lvalue = 0;

           add_symbols_to_table(p3,1);

           if(topOfSt == MAX_SYM_TABLES) {
              printf("Out of memory :( , the number of attributes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
              exit(1);
           }

          yyval.stnode=MkNode(astAttrs,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);

          push_vs(p1);

        }
break;
case 19:
#line 255 "nectar_syntax"
	{

          p1 = pop_vs();
          p2 = pop_vs();
          /*p3 = pop_vs();*/

          p4 = new_symbol(yystack.l_mark[-2].ystr);
          p4->sclass = MEMORY;
          p4->typos = p2->typos;
          p4->accessor = PRIVATE_ACC;
          p4->lvalue = 0;

          add_symbols_to_table(p4,0);

          if(topOfSt == MAX_SYM_TABLES) {
           printf("Out of memory :( , the number of attributes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
           exit(1);
          }

          yyval.stnode=MkNode(astAttrsAssign,p4,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL);

          push_vs(p2);

        }
break;
case 20:
#line 279 "nectar_syntax"
	{ yyval.stnode=MkNode(astEmptyAttrs,NULL,NULL,NULL,NULL,NULL); }
break;
case 21:
#line 285 "nectar_syntax"
	{yyval.stnode=MkNode(astBodyClass,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,NULL,NULL);
       	 }
break;
case 22:
#line 290 "nectar_syntax"
	{

          strcat(METHOD_NAME,yystack.l_mark[0].ystr);
          char snum[6];
          nitoa(CUR_TYPE -1,snum);
          strcat(METHOD_NAME,snum);
          numOfParams = 1;
		      push_rt(new_symbol("method"));

        }
break;
case 23:
#line 299 "nectar_syntax"
	{

    			 p1 = pop_vs();
           p3 = pop_vs();
    			 p2 = new_symbol(METHOD_NAME);
    			 p2->lvalue = 0;

    			 set_class_types(p2,METHOD);
    			 /*copy_attributes(p2,p1);*/
           p2->typos = p1->typos;
           p2->accessor = p3->accessor;

    			 /*Check if main method have parameters*/
    			 if((strcmp(p2->name,"main") == 0) && (numOfParams>0)){

    				 printf("Error: The main method must have no parameters\n");
    				 exit(1);

    			  }

    			 /*Create a pseudonym for this method, which is important for code generation*/
    			 if(strcmp(p2->name,"main") !=0){
    				 strcpy(NUM_VAR_ARR, "@METH_");
    				 sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_METH);
    				 strcpy(p2->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));
    				 NUM_METH++;
    			 }else{
    				strcpy(p2->pseudonym,"_main");
    			 }


    			 add_symbols_to_table(p2,0);

    			 if(topOfSt == MAX_SYM_TABLES) {
    				printf("Out of memory :( , the number of methods must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
    				exit(1);
    			 }



    			 strcpy(METHOD_NAME,"");
           /*push_vs(p1);*/
    			 push_vs(p2);
		 }
break;
case 24:
#line 344 "nectar_syntax"
	{

		/*Checking for return statement*/

		if( TopOfRt <= 0 || !returns[0] || !returns[1] || strcmp(returns[0]->name,"method") != 0 || strcmp(returns[1]->name,"return" )!=0) {
			printf("Error: Method '%s' has not return statement\n",yystack.l_mark[-7].stnode);
			exit(1);
		}

		pop_rt();
		pop_rt();


		p2 = pop_vs();


	 	yyval.stnode=MkNode(astMethLast,p2,yystack.l_mark[-5].stnode,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL);

		if(topOfSt < MAX_SYM_TABLES)
				topOfSt++;

		numOfParams =0; /*reset the number of parameters for the next method*/
		enableReturn=1;
		NUM_PAR =0;
		NUM_BYTES_VAR = 0;
	}
break;
case 25:
#line 374 "nectar_syntax"
	{

      		 strcat(METHOD_NAME,yystack.l_mark[0].ystr);
      		 push_rt(new_symbol("method"));

      		 }
break;
case 26:
#line 379 "nectar_syntax"
	{

      			 p1 = pop_vs();

      			 p2 = new_symbol(METHOD_NAME);
      			 p2->lvalue = 0;

      			 set_class_types(p2,METHOD);
      			 /*copy_attributes(p2,p1);*/
            p2->typos = p1->typos;

      			 /*Check if main method have parameters*/
      			 if((strcmp(p2->name,"main") == 0) && (numOfParams>0)){

      				 printf("Error: The main method must have no parameters\n");
      				 exit(1);

      			  }

      			 /*Create a pseudonym for this method, which is important for code generation*/
      			 if(strcmp(p2->name,"main") !=0){
      				 strcpy(NUM_VAR_ARR, "@METH_");
      				 sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_METH);
      				 strcpy(p2->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));
      				 NUM_METH++;
      			 }else{
      				strcpy(p2->pseudonym,"_main");
      			 }


      			 add_symbols_to_table(p2,1);

      			 if(topOfSt == MAX_SYM_TABLES) {
      				printf("Out of memory :( , the number of methods must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
      				exit(1);
      			 }



      			 strcpy(METHOD_NAME,"");
            /* push_vs(p1);*/
             push_vs(p2);
      		 }
break;
case 27:
#line 423 "nectar_syntax"
	{

      		/*Checking for return statement*/

      		if( TopOfRt <= 0 || !returns[0] || !returns[1] || strcmp(returns[0]->name,"method") != 0 || strcmp(returns[1]->name,"return" )!=0) {
      			printf("Error: Method '%s' has not return statement\n",yystack.l_mark[-8].ystr);
      			exit(1);
      		}

      		pop_rt();
      		pop_rt();


      		p2 = pop_vs();



      	 	yyval.stnode=MkNode(astFuncLast,p2,yystack.l_mark[-2].stnode,yystack.l_mark[-5].stnode,yystack.l_mark[0].stnode,NULL);

      		if(topOfSt < MAX_SYM_TABLES)
      				topOfSt++;

      		numOfParams =0; /*reset the number of parameters for the next method*/
      		enableReturn=1;
      		NUM_PAR =0;
      		NUM_BYTES_VAR = 0;
      	}
break;
case 28:
#line 454 "nectar_syntax"
	{


         p2 = pop_vs();
	       p3 = new_symbol(yystack.l_mark[-2].ystr);
         p3->arg = 1;
	       copy_attributes(p3,p2);

		     sprintf(METHOD_NAME_TEMP,"%d",p2->typos);
		     strcat(METHOD_NAME,METHOD_NAME_TEMP);

		     /*Create a pseudonym for this parameter, which is important for code generation*/

		     strcpy(NUM_VAR_ARR, "ebp + ");
		     sprintf(TEMP_NUM_VAR_ARR, "%d", 4 * (NUM_PAR + 2));
		     strcpy(p3->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));
		     NUM_PAR ++;

	       add_symbols_to_table(p3,0);
	       yyval.stnode=MkNode(astParamSeq,p3,yystack.l_mark[0].stnode,yystack.l_mark[-2].ystr,NULL,NULL);
		     numOfParams++;
         p3->index = numOfParams;
          }
break;
case 29:
#line 477 "nectar_syntax"
	{ yyval.stnode=MkNode(astParamEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
case 30:
#line 482 "nectar_syntax"
	{

	     p2 = pop_vs();
	     p3 = new_symbol(yystack.l_mark[-3].ystr);
	     p3->arg = 1;
	     copy_attributes(p3,p2);

		   sprintf(METHOD_NAME_TEMP,"%d",p2->typos);
		   strcat(METHOD_NAME,METHOD_NAME_TEMP);

		   strcpy(NUM_VAR_ARR, "ebp + ");
		   sprintf(TEMP_NUM_VAR_ARR, "%d", 4 *(NUM_PAR+2));
		   strcpy(p3->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));
		   NUM_PAR++;

	     add_symbols_to_table(p3,0);
	     yyval.stnode=MkNode(astFormalsSeq,p3,yystack.l_mark[-1].stnode,yystack.l_mark[-3].ystr,NULL,NULL);
		   numOfParams++;
       p3->index = numOfParams;
		 }
break;
case 31:
#line 502 "nectar_syntax"
	{ yyval.stnode=MkNode(astFormalsEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
case 32:
#line 507 "nectar_syntax"
	{

          yyval.stnode=MkNode(astInt,NULL,NULL,NULL,NULL,NULL);
 	        p1 = new_symbol(""); /*create symbol*/
	        set_class_types(p1,yystack.l_mark[0].yint); /*the type of symbol is integer*/
	        push_vs(p1);

        }
break;
case 33:
#line 515 "nectar_syntax"
	{

          yyval.stnode=MkNode(astReal,NULL,NULL,NULL,NULL,NULL);
 	        p1 = new_symbol(""); /*create symbol*/
	        set_class_types(p1,yystack.l_mark[0].yint); /*the type of symbol is real*/
	        push_vs(p1);

         }
break;
case 34:
#line 523 "nectar_syntax"
	{

          yyval.stnode=MkNode(astBool,NULL,NULL,NULL,NULL,NULL);
 	        p1 = new_symbol(""); /*create symbol*/
	        set_class_types(p1,yystack.l_mark[0].yint); /*the type of symbol is integer*/
	        push_vs(p1);

        }
break;
case 35:
#line 532 "nectar_syntax"
	{

              yyval.stnode=MkNode(astStr,NULL,NULL,NULL,NULL,NULL);
     	        p1 = new_symbol(""); /*create symbol*/
    	        set_class_types(p1,yystack.l_mark[0].yint); /*the type of symbol is string*/
    	        push_vs(p1);

            }
break;
case 36:
#line 540 "nectar_syntax"
	{

          yyval.stnode=MkNode(astPointer,NULL,NULL,NULL,NULL,NULL);
 	        p1 = new_symbol(yystack.l_mark[0].ystr); /*create symbol*/
          p = findsymb(yystack.l_mark[0].ystr,1);
	        p1->typos = p->typos;
	        push_vs(p1);

        }
break;
case 37:
#line 552 "nectar_syntax"
	{
	 yyval.stnode=MkNode(astBody,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,NULL,NULL);}
break;
case 38:
#line 558 "nectar_syntax"
	{ yyval.stnode=MkNode(astDeclsSeq,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL);}
break;
case 39:
#line 559 "nectar_syntax"
	{ yyval.stnode=MkNode(astDeclsEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
case 40:
#line 564 "nectar_syntax"
	{ yyval.stnode=MkNode(astDeclListSeq,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL);}
break;
case 41:
#line 565 "nectar_syntax"
	{ yyval.stnode=MkNode(astDeclListEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
case 42:
#line 570 "nectar_syntax"
	{

        		p1 = pop_vs();
        		p2 = new_symbol(yystack.l_mark[-2].ystr);
        	  copy_attributes(p2, p1);

            /*Create a pseudonym for this variable, which is important for code generation*/
        		strcpy(NUM_VAR_ARR, "ebp - ");
            NUM_BYTES_VAR-=1;
            p2->index = NUM_BYTES_VAR;

            switch(p1->typos){

        			case INT:

        				sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR );

        			break;
        			case REAL:
        				sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR);

        			break;
        			case BOOL:

        				sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR );

        			break;
              case STR:

              break;
              default:

                p =  findsymb(p1->name,1);
                if(p == NULL){
                    printf("Error: Undeclared class '%s\n",p1->name);
                    exit(0);
                }
                strcpy(p2->nameclass ,p->name);

              break;
        		}

            strcpy(p2->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));

        		p2->sclass = MEMORY;
        		add_symbols_to_table(p2,0);

        		push_vs(p1);


  }
break;
case 43:
#line 620 "nectar_syntax"
	{

    		pop_vs();
    		yyval.stnode=MkNode(astDecl,NULL,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

    }
break;
case 44:
#line 626 "nectar_syntax"
	{

    		p1 = pop_vs();
        p2 = pop_vs();
    		p3 = new_symbol(yystack.l_mark[-5].ystr);
    	  copy_attributes(p3, p2);

		    add_array_dcl(p3,atoi(yystack.l_mark[-1].ystr));
        /*Create a pseudonym for this variable, which is important for code generation*/
    		strcpy(NUM_VAR_ARR, "ebp - ");

    		switch(p1->typos){
    			case INT:

    			    NUM_BYTES_VAR+=4*(atoi(yystack.l_mark[-1].ystr));
    				  sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR );

    			break;
    			case REAL:

    				  NUM_BYTES_VAR+=8*(atoi(yystack.l_mark[-1].ystr));
    				  sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR);

    			break;
    			case BOOL:

    			    NUM_BYTES_VAR+=4*(atoi(yystack.l_mark[-1].ystr));
    				  sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR );

    			break;
    		}

		    strcpy(p2->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));

		    p3->sclass = MEMORY;
		    add_symbols_to_table(p3,0);

		    push_vs(p2);


		}
break;
case 45:
#line 666 "nectar_syntax"
	{

		    pop_vs();
		    yyval.stnode=MkNode(astDecl,NULL,yystack.l_mark[-6].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

    }
break;
case 46:
#line 672 "nectar_syntax"
	{

    		   p3 = pop_vs();
    	     p1 = pop_vs();
    	     p2 = new_symbol(yystack.l_mark[-4].ystr);
    	     copy_attributes(p2, p1);

           strcpy(NUM_VAR_ARR, "ebp - ");
           NUM_BYTES_VAR -=1;
           p2->index = NUM_BYTES_VAR;

           switch(p1->typos){

               case INT:

                 sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR);

               break;
               case REAL:

                 sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR);

               break;
               case BOOL:

                 sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR);

               break;
          }

          strcpy(p2->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));

          if(!isSuperType(p1->typos, p3->typos)) {
    			     printf("Warning: The type of '%s' is not '%d'\n",p1->name,p3->typos);
    		   }

    	     copy_value(p2,p3);
    		   p2->sclass = MEMORY;
    	     add_symbols_to_table(p2,0);

    		   push_vs(p1);

	  }
break;
case 47:
#line 714 "nectar_syntax"
	{

    	     pop_vs();
    	     yyval.stnode=MkNode(astDeclAssign,NULL,yystack.l_mark[-5].stnode,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL);
	  }
break;
case 48:
#line 722 "nectar_syntax"
	{

        p1 = pop_vs();
		    p2 = new_symbol(yystack.l_mark[0].ystr);
	      copy_attributes(p2, p1);

        strcpy(NUM_VAR_ARR, "ebp - ");
        NUM_BYTES_VAR-=1;
        p2->index = NUM_BYTES_VAR;

		    switch(p1->typos){

      			case INT:
      				sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR );

      			break;
      			case REAL:
      				sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR);

      			break;
      			case BOOL:
      				sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR );

      			break;
  		  }

        strcpy(p2->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));


		    add_symbols_to_table(p2,0);

		    p2->sclass = MEMORY;
		    push_vs(p1);

	   }
break;
case 49:
#line 756 "nectar_syntax"
	{

    		p = pop_vs();
    		yyval.stnode=MkNode(astVarsSeq,p,yystack.l_mark[0].stnode,NULL,NULL,NULL);
    		push_vs(p);

    }
break;
case 50:
#line 763 "nectar_syntax"
	{

		   p3 = pop_vs();
	     p1 = pop_vs();
	     p2 = new_symbol(yystack.l_mark[-2].ystr);
	     copy_attributes(p2, p1);
       strcpy(NUM_VAR_ARR, "ebp - ");
       NUM_BYTES_VAR-=1;
       p2->index = NUM_BYTES_VAR;

		   switch(p1->typos){
      			case INT:
      				sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR );
      			break;
      			case REAL:
      				sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR);
      			break;
      			case BOOL:
      				sprintf(TEMP_NUM_VAR_ARR, "%d", NUM_BYTES_VAR );
			      break;
		  }

      strcpy(p2->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));
  		if(!isSuperType(p1->typos, p3->typos)) {
  			 printf("Warning: The type of '%s' is not '%d'\n",p1->name,p3->typos);
  		 }

	     copy_value(p2,p3);
	     add_symbols_to_table(p2,0);

		   p2->sclass = MEMORY;
	     push_vs(p1);

	  }
break;
case 51:
#line 796 "nectar_syntax"
	{

         p=pop_vs();
	       yyval.stnode=MkNode(astVarAssign,p,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
	       push_vs(p);
    }
break;
case 52:
#line 802 "nectar_syntax"
	{ yyval.stnode=MkNode(astVarEmpty,NULL,NULL,NULL,NULL,NULL); }
break;
case 53:
#line 807 "nectar_syntax"
	{ yyval.stnode=MkNode(astStmtSeq,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL); pop_vs();  }
break;
case 54:
#line 808 "nectar_syntax"
	{ yyval.stnode=MkNode(astStmtEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
case 55:
#line 812 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[0].stnode;
			pop_vs();
			push_vs(NULL);
	    }
break;
case 56:
#line 817 "nectar_syntax"
	{

			yyval.stnode=yystack.l_mark[0].stnode;
			push_vs(NULL);
        }
break;
case 57:
#line 822 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[0].stnode;
			push_vs(NULL);
        }
break;
case 58:
#line 826 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[0].stnode;
			push_vs(NULL);
        }
break;
case 59:
#line 831 "nectar_syntax"
	{

		  yyval.stnode=MkNode(astPrintLnStmt,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);
		  push_vs(NULL);

	    }
break;
case 60:
#line 838 "nectar_syntax"
	{



		  yyval.stnode=MkNode(astReadStmt,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
		  pop_vs();
      p = pop_vs();
      if( p->typos != STR){

          printf("Error: The type of print message in read statement must be string\n");
          exit(1);
      }

		  push_vs(NULL);

	    }
break;
case 61:
#line 854 "nectar_syntax"
	{

			pop_vs();
			yyval.stnode=MkNode(astExprStmt,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);
			push_vs(NULL);
		}
break;
case 62:
#line 863 "nectar_syntax"
	{ if(enableReturn==1)
		         push_rt(new_symbol("if"));
			 }
break;
case 63:
#line 869 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[-1].stnode;
			pop_vs();
			push_vs(NULL);
      }
break;
case 64:
#line 874 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[-1].stnode;
			push_vs(NULL);
      }
break;
case 65:
#line 878 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[-1].stnode;
			push_vs(NULL);
      }
break;
case 66:
#line 882 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[-1].stnode;
			push_vs(NULL);
      }
break;
case 67:
#line 886 "nectar_syntax"
	{

      if(enableReturn == 1){

				if(strcmp(returns[TopOfRt]->name,"method") == 0){
					enableReturn =0;
					push_rt(new_symbol("return"));

				}else{

					if(strcmp(returns[TopOfRt]->name,"word") ==0 || strcmp(returns[TopOfRt]->name,"return") ==0 )
					 {
						 pop_rt();
						 push_rt(new_symbol("return"));
					 }else{
				        push_rt(new_symbol("return"));
					 }
				  }
			}
			yyval.stnode=MkNode(astReturnStmt,NULL,yystack.l_mark[-1].stnode,NULL,NULL,NULL);
			p = pop_vs();


			if( !isSuperType(vs[0]->typos, p->typos)){
				printf("Error: The returned type of method '%s' is not '%d'\n", vs[0]->name,p->typos);
				exit(1);
			}
      push_vs(NULL);

      }
break;
case 68:
#line 916 "nectar_syntax"
	{


			p6 = pop_vs();
			p4 = pop_vs();

			/*check_ifelse(p4,p6,p9);*/

			if(enableReturn == 1){

				if (strcmp(returns[TopOfRt]->name, "return") ==0 || strcmp(returns[TopOfRt]->name, "word") ==0){
								pop_rt();
					}

			   pop_rt();

			}

			yyval.stnode=MkNode(astIfStmt,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);

			push_vs(NULL);



	  }
break;
case 69:
#line 941 "nectar_syntax"
	{
				 if (enableReturn == 1){

							if (strcmp(returns[TopOfRt]->name, "return") !=0 && strcmp(returns[TopOfRt]->name, "word") !=0){
								push_rt(new_symbol("word"));
							}

								push_rt(new_symbol("else"));
					}
			   }
break;
case 70:
#line 950 "nectar_syntax"
	{

			p9 = pop_vs();
			p6 = pop_vs();
			p4 = pop_vs();

			/*check_ifelse(p4,p6,p9);*/

			if(enableReturn == 1){

				if (strcmp(returns[TopOfRt]->name, "return") !=0 && strcmp(returns[TopOfRt]->name, "word") !=0){
								push_rt(new_symbol("word"));
					}

				p7 = pop_rt();
				p5 = pop_rt();
				p3 = pop_rt();
				p2 = pop_rt();

				if(strcmp(p3->name,"return") ==0  && strcmp(p7->name,"return") == 0)
					push_rt(new_symbol("return"));
				else if(strcmp(returns[TopOfRt]->name, "word") !=0)
					  push_rt(new_symbol("word"));



			}

			yyval.stnode=MkNode(astIfElseStmt,NULL,yystack.l_mark[-5].stnode,yystack.l_mark[-3].stnode,yystack.l_mark[0].stnode,NULL);

			push_vs(NULL);

      }
break;
case 71:
#line 983 "nectar_syntax"
	{

		  p3 = pop_vs();
		  p1 = pop_vs();

		  yyval.stnode = MkNode(astSingleIfStmt,NULL,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

		  push_vs(NULL);

	  }
break;
case 72:
#line 993 "nectar_syntax"
	{

		  p3 = pop_vs();
		  p1 = pop_vs();

		  yyval.stnode = MkNode(astSingleUnlessStmt,NULL,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

		  push_vs(NULL);

	  }
break;
case 73:
#line 1003 "nectar_syntax"
	{ p = new_symbol("");
				push_wh(p);
				enableReturn =0;
				}
break;
case 74:
#line 1006 "nectar_syntax"
	{

			yyval.stnode=MkNode(astWhileStmt,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
			p6=pop_vs();
			p4=pop_vs();
			/*check_while(p4,p6);*/
			pop_wh();
		    if(TopOfWhile <0) enableReturn=1;
			push_vs(NULL);

     }
break;
case 75:
#line 1018 "nectar_syntax"
	{

          p = new_symbol("");
          push_wh(p);
          enableReturn =0;

    }
break;
case 76:
#line 1024 "nectar_syntax"
	{

         yyval.stnode=MkNode(astForStmt,NULL,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL);
         p6=pop_vs();
         p4=pop_vs();
         pop_wh();
         if(TopOfWhile <0) enableReturn=1;
         push_vs(NULL);

    }
break;
case 77:
#line 1034 "nectar_syntax"
	{ p = new_symbol("");
				push_wh(p);
				enableReturn =0;
				}
break;
case 78:
#line 1037 "nectar_syntax"
	{


			p5=pop_vs();
			p1=pop_vs();
			/*check_while(p4,p6);*/

			if( p1->typos != INT) {

				printf("Error: The number of loop in 'times' statement must be integer\n");
				exit(1);
			}

			yyval.stnode=MkNode(astTimesStmt,NULL,yystack.l_mark[-3].stnode,yystack.l_mark[0].stnode,NULL,NULL);
			pop_wh();
		    if(TopOfWhile <0) enableReturn=1;
			push_vs(NULL);
		}
break;
case 79:
#line 1055 "nectar_syntax"
	{
			 p = pop_wh();
			 if(!p) {
				 printf("Error: break statement not within loop ");
				 exit(1);

			 }else{

				 push_wh(p);
			 }

			 yyval.stnode=MkNode(astBreakStmt,NULL,NULL,NULL,NULL,NULL);
			 push_vs(NULL);
        }
break;
case 80:
#line 1069 "nectar_syntax"
	{
			        yyval.stnode=yystack.l_mark[0].stnode;
			        push_vs(NULL);
      }
break;
case 81:
#line 1074 "nectar_syntax"
	{


		  yyval.stnode=MkNode(astPrintLnStmt,NULL,yystack.l_mark[-1].stnode,NULL,NULL,NULL);
		  push_vs(NULL);

	  }
break;
case 82:
#line 1081 "nectar_syntax"
	{


		  yyval.stnode=MkNode(astReadStmt,NULL,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);
		  pop_vs();
      pop_vs();
		  push_vs(NULL);

	  }
break;
case 83:
#line 1090 "nectar_syntax"
	{

			pop_vs();
			yyval.stnode=MkNode(astExprStmt,NULL,yystack.l_mark[-1].stnode,NULL,NULL,NULL);
			push_vs(NULL);
		}
break;
case 84:
#line 1097 "nectar_syntax"
	{

			yyval.stnode=MkNode(astNullStmt,NULL,NULL,NULL,NULL,NULL);
			/*push_vs(NULL);*/
		  }
break;
case 85:
#line 1105 "nectar_syntax"
	{yyval.stnode = yystack.l_mark[0].ystr;}
break;
case 86:
#line 1108 "nectar_syntax"
	{

		  p1 = pop_vs();

		  yyval.stnode=MkNode(astExprInline,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);


	  }
break;
case 87:
#line 1117 "nectar_syntax"
	{

		  p1 = pop_vs();

		  yyval.stnode=MkNode(astSingleExprInline,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);


	  }
break;
case 88:
#line 1127 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[-1].stnode;}
break;
case 89:
#line 1132 "nectar_syntax"
	{

		   yyval.stnode=MkNode(astAddAssign,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
		   p3 = pop_vs();
		   p1 = pop_vs();
		   check_assignment(p1,p3);

		   if(!isSuperType(p1->typos, p3->typos)) {
			 printf("Warning: The type of '%s' is not '%d'\n",p1->name,p3->typos);


		     }

		   /*push_vs(p3);*/
	  }
break;
case 90:
#line 1149 "nectar_syntax"
	{

		   yyval.stnode=MkNode(astSubAssign,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
		   p3 = pop_vs();
		   p1 = pop_vs();
		   check_assignment(p1,p3);

		   if(!isSuperType(p1->typos, p3->typos)) {
			 printf("Warning: The type of '%s' is not '%d'\n",p1->name,p3->typos);


		    }
		   /*push_vs(p3);*/
	  }
break;
case 91:
#line 1167 "nectar_syntax"
	{

		 yyval.stnode=MkNode(astAssign,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
	     p3 = pop_vs();
	     p1 = pop_vs();

		 check_assignment(p1,p3);


		  if(!isSuperType(p1->typos, p3->typos)) {
			 printf("Warning: The type of '%s' is not '%d'\n",p1->name,p3->typos);


		 }


		 push_vs(p3);

        }
break;
case 92:
#line 1187 "nectar_syntax"
	{

		 yyval.stnode=MkNode(astAssignSeq,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
	     p3 = pop_vs();
	     p1 = pop_vs();
		 check_assignment(p1,p3);

		 if(!isSuperType(p1->typos, p3->typos)) {
			 printf("Warning: The type of '%s' is not '%d'\n",p1->name,p3->typos);


		 }


		 push_vs(p3);

	   }
break;
case 93:
#line 1208 "nectar_syntax"
	{


	     p3 = pop_vs();
	     p1 = pop_vs();
		 check_assignment(p1,p3);
		 yyval.stnode=MkNode(astListedAssign,NULL,yystack.l_mark[-4].stnode,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL);

		}
break;
case 94:
#line 1219 "nectar_syntax"
	{

	     p3 = pop_vs();
	     p1 = pop_vs();
		 check_assignment(p1,p3);

		 yyval.stnode=MkNode(astNestedAssign,NULL,yystack.l_mark[-4].stnode,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL);

        }
break;
case 95:
#line 1228 "nectar_syntax"
	{

		 p3 = pop_vs();
	     p1 = pop_vs();
		 check_assignment(p1,p3);

		 yyval.stnode=MkNode(astEmbedAssign,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);

		 }
break;
case 96:
#line 1241 "nectar_syntax"
	{


    			/*strcat(METHOD_NAME,$1);*/
    			p1 = new_symbol(yystack.l_mark[0].ystr);

    			/*
    			if(strcmp(p1->name,"main") == 0) {
    				printf("ERROR: You can't call the main method");
    				exit(1);
    			}*/


    			push_vs(p1);
    			yyval.stnode=MkNode(astMethodName,p1,NULL,NULL,NULL,NULL);

             }
break;
case 97:
#line 1261 "nectar_syntax"
	{
			p1 = findsymb(yystack.l_mark[0].ystr,0);

			if(p1!=NULL){
				/*copy_symbol(p2,p1);*/
				push_vs(p1);
			}
			else{

				/*printf("Error: '%s' undeclared variable",$1);*/
				/*exit(1);*/
			 }
			/*copy_symbol(p2,p1);*/
			yyval.stnode=MkNode(astLocation,p1,NULL,NULL,NULL,NULL);
}
break;
case 98:
#line 1282 "nectar_syntax"
	{

			p3 = pop_vs();
			p1 = pop_vs();

			p = new_symbol("");

			if (p1->sclass == CONSTANT && p3->sclass == CONSTANT)
				p->sclass = CONSTANT;

			switch(p1->typos){

				 case INT:
						switch(p3->typos){
							case REAL:
								 printf("Error: bad operand types for binary operator \n");
								 exit(1);
							break;
							case INT:
								 printf("Error: bad operand types for binary operator \n");
								 exit(1);
							break;

						}

				 break;
				 case REAL:

						switch(p3->typos){
							case REAL:

								 printf("Error: bad operand types for binary operator \n");
								 exit(1);

							break;
							case INT:

								 printf("Error: bad operand types for binary operator \n");
								 exit(1);

							break;

						}
				 break;
				 case BOOL:

						 switch(p3->typos){

								case REAL:

									printf("Error: bad operand types for binary operator \n");
									exit(1);

								break;
								case INT:

									printf("Error: bad operand types for binary operator \n");
									exit(1);

								break;
								case BOOL:
									 p->typos = BOOL;
								break;

						  }

				 break;



			 }

			yyval.stnode=MkNode(astOrExpr,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
			/*p = check_logic_op(p1,p3);*/
			push_vs(p);

		}
break;
case 99:
#line 1359 "nectar_syntax"
	{ yyval.stnode= yystack.l_mark[0].stnode;}
break;
case 100:
#line 1364 "nectar_syntax"
	{

			p3 = pop_vs();
			p1 = pop_vs();

			p = new_symbol("");

			if (p1->sclass == CONSTANT && p3->sclass == CONSTANT)
				p->sclass = CONSTANT;

			switch(p1->typos){

				 case INT:
						switch(p3->typos){
							case REAL:
								 printf("Error: bad operand types for binary operator \n");
								 exit(1);
							break;
							case INT:
								 printf("Error: bad operand types for binary operator \n");
								 exit(1);
							break;

						}

				 break;
				 case REAL:

						switch(p3->typos){
							case REAL:

								 printf("Error: bad operand types for binary operator \n");
								 exit(1);

							break;
							case INT:

								 printf("Error: bad operand types for binary operator \n");
								 exit(1);

							break;

						}
				 break;
				 case BOOL:

						 switch(p3->typos){
								case REAL:

									printf("Error: bad operand types for binary operator \n");
									exit(1);

								break;
								case INT:

									printf("Error: bad operand types for binary operator \n");
									exit(1);

								break;
								case BOOL:
									 p->typos = BOOL;
								break;

						  }

				 break;



			 }

			yyval.stnode=MkNode(astAndExpr,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
			/*p = check_logic_op(p1,p3);*/
			push_vs(p);

		}
break;
case 101:
#line 1440 "nectar_syntax"
	{ yyval.stnode = yystack.l_mark[0].stnode;}
break;
case 102:
#line 1444 "nectar_syntax"
	{

			p2 = pop_vs();

			if( p2->typos != BOOL){

				 printf("Error: bad operand types for binary operator \n");
				 exit(1);

			}

			yyval.stnode=MkNode(astNotExpr,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);

			push_vs(p2);


	  }
break;
case 103:
#line 1461 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 104:
#line 1465 "nectar_syntax"
	{

		p3 = pop_vs();
		p1 = pop_vs();

		p = new_symbol("");

		if (p1->sclass == CONSTANT && p3->sclass == CONSTANT)
				p->sclass = CONSTANT;

		switch(p1->typos){

			 case INT:
					switch(p3->typos){
						case REAL:
							p->typos = INT;
						break;
						case INT:
							p->typos = INT;
						break;
						case BOOL:
						    printf("Error: bad operand types for binary operator \n");
							exit(1);
						break;

					}

			 break;
			 case REAL:

					switch(p3->typos){
						case REAL:
							p->typos = INT;
						break;
						case INT:
							p->typos = INT;
						break;
						case BOOL:
						    printf("Error: bad operand types for binary operator \n");
							exit(1);
						break;

					}
			 break;
			 case BOOL:

					if( yystack.l_mark[-1].stnode->NodeType == astEOp || yystack.l_mark[-1].stnode->NodeType == astNeOp){

							switch(p3->typos){
								case REAL:
									printf("Error: bad operand types for binary operator \n");
								break;
								case INT:
									printf("Error: bad operand types for binary operator \n");
								break;
								case BOOL:
									p->typos = BOOL;
								break;

							}
					}
					else {
						printf("Error: bad operand types for binary operator \n");
						exit(1);
					}

			 break;


		 }

		yyval.stnode=MkNode(astCompExpr,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL);
		/*p = check_logic_op(p1,p3);*/
	    push_vs(p);
}
break;
case 105:
#line 1540 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 106:
#line 1544 "nectar_syntax"
	{ yyval.stnode=MkNode(astGeOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 107:
#line 1545 "nectar_syntax"
	{ yyval.stnode=MkNode(astGOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 108:
#line 1546 "nectar_syntax"
	{ yyval.stnode=MkNode(astLeOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 109:
#line 1547 "nectar_syntax"
	{ yyval.stnode=MkNode(astLOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 110:
#line 1548 "nectar_syntax"
	{ yyval.stnode=MkNode(astNeOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 111:
#line 1549 "nectar_syntax"
	{ yyval.stnode=MkNode(astEOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 112:
#line 1554 "nectar_syntax"
	{


	     p3 = pop_vs();
		 p1 = pop_vs();

		 p = new_symbol("");

		 if (p1->sclass == CONSTANT && p3->sclass == CONSTANT)
				p->sclass = CONSTANT;

		switch(p1->typos){

			 case INT:
					switch(p3->typos){
						case REAL:
							p->typos = REAL;
						break;
						case INT:
							p->typos = INT;
						break;
						case BOOL:
						  printf("Error: bad operand types for binary operator \n");
							exit(1);
						break;
            case STR:
              printf("Error: bad operand types for binary operator \n");
              exit(1);
            break;

					}

			 break;
			 case REAL:

					switch(p3->typos){
						case REAL:
							p->typos = REAL;
						break;
						case INT:
							p->typos = REAL;
						break;
						case BOOL:
						    printf("Error: bad operand types for binary operator \n");
							  exit(1);
						break;
            case STR:
              printf("Error: bad operand types for binary operator \n");
              exit(1);
            break;

					}
			 break;
			 case BOOL:

					printf("Error: bad operand types for binary operator \n");
				    exit(1);

			 break;
       case STR:
             switch(p3->typos){
               case REAL:
                   printf("Error: bad operand types for binary operator \n");
                   exit(1);
               break;
               case INT:
                   printf("Error: bad operand types for binary operator \n");
                   exit(1);
               break;
               case BOOL:
                   printf("Error: bad operand types for binary operator \n");
                   exit(1);
               break;
               case STR:
                  p->typos = STR;
               break;

             }
       break;


		 }

         yyval.stnode=MkNode(astAddExpr,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL);
	     push_vs(p);
        }
break;
case 113:
#line 1640 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 114:
#line 1644 "nectar_syntax"
	{ yyval.stnode=MkNode(astAddOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 115:
#line 1645 "nectar_syntax"
	{ yyval.stnode=MkNode(astSubOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 116:
#line 1649 "nectar_syntax"
	{


	     p3 = pop_vs();
	     p1 = pop_vs();

		 p = new_symbol("");

		 /*p = check_muldiv_arithm_op(p1,p3);*/

		 if (p1->sclass == CONSTANT && p3->sclass == CONSTANT)
				p->sclass = CONSTANT;

		 switch(p1->typos){

			 case INT:
					switch(p3->typos){
						case REAL:
							p->typos = REAL;
						break;
						case INT:
							p->typos = INT;
						break;
						case BOOL:
						   printf("Error: bad operand types for binary operator \n");
							 exit(1);
						break;
            case STR:
                p->typos = STR;
            break;

					}

			 break;
			 case REAL:

					switch(p3->typos){
						case REAL:
							p->typos = REAL;
						break;
						case INT:
							p->typos = REAL;
						break;
						case BOOL:
						    printf("Error: bad operand types for binary operator \n");
							  exit(1);
						break;
            case STR:
                printf("Error: bad operand types for binary operator \n");
                exit(1);
            break;

					}
			 break;
			 case BOOL:

					  printf("Error: bad operand types for binary operator \n");
				    exit(1);

			 break;
       case STR:

					switch(p3->typos){
						case REAL:
                printf("Error: bad operand types for binary operator \n");
                exit(1);
						break;
						case INT:
							  p->typos = STR;
						break;
						case BOOL:
						    printf("Error: bad operand types for binary operator \n");
							  exit(1);
						break;

					}
			 break;


		 }


	     yyval.stnode=MkNode(astMulExpr,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL);
       p->lvalue = 0;
	     push_vs(p);
}
break;
case 117:
#line 1735 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 118:
#line 1739 "nectar_syntax"
	{  yyval.stnode=MkNode(astMulOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 119:
#line 1740 "nectar_syntax"
	{  yyval.stnode=MkNode(astDivOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 120:
#line 1741 "nectar_syntax"
	{  yyval.stnode=MkNode(astIdivOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 121:
#line 1742 "nectar_syntax"
	{  yyval.stnode=MkNode(astModOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 122:
#line 1746 "nectar_syntax"
	{ yyval.stnode= yystack.l_mark[0].stnode; }
break;
case 123:
#line 1747 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[-1].stnode;}
break;
case 124:
#line 1748 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 125:
#line 1749 "nectar_syntax"
	{
          p1=new_symbol("");
          p1->typos=INT;
          p1->sclass=CONSTANT;
          p1->lvalue=0;
          p1->timi=atoi(yystack.l_mark[0].ystr);
          p1->has_timi=CONST_VAL;
          push_vs(p1);
	      yyval.stnode = MkNode(astDeConst,p1,NULL,NULL,NULL,NULL);
         }
break;
case 126:
#line 1760 "nectar_syntax"
	{
          p1=new_symbol("");
          p1->typos=REAL;
          p1->sclass=CONSTANT;
          p1->lvalue=0;
          p1->dtimi=atof(yystack.l_mark[0].ystr);
          p1->has_timi=CONST_VAL;
          push_vs(p1);
	      yyval.stnode = MkNode(astRealDeConst,p1,NULL,NULL,NULL,NULL);
         }
break;
case 127:
#line 1770 "nectar_syntax"
	{
	       p1 = new_symbol("");
         p1->sclass=CONSTANT;
		      p1->typos = BOOL;
          p1->lvalue=0;
          p1->timi=1;
          p1->has_timi=CONST_VAL;
	      push_vs(p1);
	      yyval.stnode = MkNode(astTrue,p1,NULL,NULL,NULL,NULL);
       }
break;
case 128:
#line 1780 "nectar_syntax"
	{
	      p1 = new_symbol("");
          p1->sclass=CONSTANT;
		  p1->typos = BOOL;
          p1->lvalue=0;
          p1->timi=0;
          p1->has_timi=CONST_VAL;
	      push_vs(p1);
          yyval.stnode = MkNode(astFalse,p1,NULL,NULL,NULL,NULL);
       }
break;
case 129:
#line 1790 "nectar_syntax"
	{
          p1 = new_symbol("");
          p1->sclass=CONSTANT;
          p = findsymb(CLASS_NAME,1);
          p1->typos = p->typos;
          p1->lvalue=0;
          p1->timi=1;
          p1->has_timi=CONST_VAL;
          push_vs(p1);
         yyval.stnode = MkNode(astSelf,p1,NULL,NULL,NULL,NULL);
         }
break;
case 130:
#line 1801 "nectar_syntax"
	{

		  p2 = pop_vs();
		  p1 = pop_vs();
      push_rt(new_symbol("*"));

		  strcpy(METHOD_NAME_TEMP,"");

	      while(strcmp(p1->name,"259") == 0 || strcmp(p1->name,"274") == 0 || strcmp(p1->name,"276") == 0 || strcmp(p1->name,"285") == 0 ){
          push_rt(p1);
			    p1 = pop_vs();
		  }

      push_vs(p1);

      p1 = pop_rt();

      while(strcmp(p1->name,"259") == 0 || strcmp(p1->name,"274") == 0 || strcmp(p1->name,"276") == 0 || strcmp(p1->name,"285") == 0 ){
        strcat(METHOD_NAME_TEMP,p1->name);
        p1 = pop_rt();
    }

      p1 = pop_vs();


		  strcpy(METHOD_NAME,p1->name);
		  strcat(METHOD_NAME,METHOD_NAME_TEMP);
		  p3 = new_symbol(METHOD_NAME);

		  strcpy(METHOD_NAME,"");
		  strcpy(METHOD_NAME_TEMP,"");

		  p = findsymb(p3->name,1);

		  if(p == NULL){
             printf("Error: '%s' undeclared method",p3->name);
			       exit(1);
		    }
		  /*printf("%s\n",p->name);*/
		 /* printf("%d\n",numOfArguments);*/

		 /* if(p->dcl_ptr->num_params != numOfArguments){

			  printf("Error: The number of arguments must match");
			  exit(1);
		  }
		  */

        yyval.stnode = MkNode(astFunctionCall,p,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);
 	      push_vs(p);

		  /*numOfArguments =0;*/
	}
break;
case 131:
#line 1855 "nectar_syntax"
	{

               p2 = pop_vs();
               p1 = pop_vs();

               push_rt(new_symbol("*"));
               strcpy(METHOD_NAME_TEMP,"");

               while(isNumeric(p1->name) != 0 ){
                   push_rt(p1);
                   p1 = pop_vs();
               }

               push_vs(p1);
               p1 = pop_rt();

               while(isNumeric(p1->name) != 0 ){
                 strcat(METHOD_NAME_TEMP,p1->name);
                 p1 = pop_rt();
               }

               p1 = pop_vs();


               strcpy(METHOD_NAME,p1->name);


               p6 = findsymb(yystack.l_mark[-5].ystr,1);
               int i;
               if(p6 != NULL){
                    char snum[6];
                    nitoa(p6->typos,snum);
                    strcat(METHOD_NAME,snum);
                    strcat(METHOD_NAME,METHOD_NAME_TEMP);
                    p3 = new_symbol(METHOD_NAME);
                    i=mkkey(p3->name);
                    p7=p6->mht->table[i];

                    while(p7 && (strcmp(p7->name,p3->name) !=0)){
                            p7=p7->NextSymbol;
                    }

                    if(p7 == NULL){
                      printf("Undeclared method!\n");
                      exit(1);
                   }

                    p = p6;

                    yyval.stnode = MkNode(astStaticMethodCall,p,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

               }
               else {

                  p = findsymb(yystack.l_mark[-5].ystr,0);
                  if(p == NULL){
                         printf("Error: '%s' undeclared variable",yystack.l_mark[-5].ystr);
                         exit(1);
                    }

                  char snum[6];
                  nitoa(p->typos,snum);
                  strcat(METHOD_NAME,snum);
                  strcat(METHOD_NAME,METHOD_NAME_TEMP);
                  p3 = new_symbol(METHOD_NAME);

                  p6 = findsymb(p->nameclass,1);
                  if(p6 != NULL){

                      i=mkkey(p3->name);
                      p7=p6->mht->table[i];

                      while(p7 && (strcmp(p7->name,p3->name) !=0)){
                               p7=p7->NextSymbol;
                       }

                      if(p6 == NULL){
                        printf("Undeclared method!\n");
                        exit(1);
                      }

                      /*p = p6;*/
                      yyval.stnode = MkNode(astMethodCall,p,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);
                  }

               }


               strcpy(METHOD_NAME,"");
               strcpy(METHOD_NAME_TEMP,"");


               /*printf("%s\n",p->name);*/
              /* printf("%d\n",numOfArguments);*/

              /* if(p->dcl_ptr->num_params != numOfArguments){

                 printf("Error: The number of arguments must match");
                 exit(1);
               }
               */


                 push_vs(p);

               /*numOfArguments =0;*/
    }
break;
case 132:
#line 1963 "nectar_syntax"
	{
          p1=new_symbol("");
          p1->typos=INT;
          p1->sclass=CONSTANT;
          p1->lvalue=0;
          p1->timi=-atoi(yystack.l_mark[0].ystr);
          p1->has_timi=CONST_VAL;
          push_vs(p1);
	      yyval.stnode = MkNode(astDeConst,p1,NULL,NULL,NULL,NULL);
        }
break;
case 133:
#line 1973 "nectar_syntax"
	{
          p1=new_symbol("");
          p1->typos=REAL;
          p1->sclass=CONSTANT;
          p1->lvalue=0;
          p1->dtimi= -atof(yystack.l_mark[-1].ystr);
          p1->has_timi=CONST_VAL;
          push_vs(p1);
	      yyval.stnode = MkNode(astRealDeConst,p1,NULL,NULL,NULL,NULL);
         }
break;
case 134:
#line 1984 "nectar_syntax"
	{

     		  p2 = new_symbol("");
          strncpy(p2->stimi,yystack.l_mark[0].ystr + 1, strlen(yystack.l_mark[0].ystr) - 2);
          p2->sclass = CONSTANT;
     		  p2->typos = STR;
          push_vs(p2);
     		  yyval.stnode=MkNode(astString,p2,NULL,NULL,NULL,NULL);

     	  }
break;
case 135:
#line 1994 "nectar_syntax"
	{

          pop_vs();
          p1=pop_vs();
          p = new_symbol("");
          p->sclass = MEMORY;
          p->typos = p1->typos;
          push_vs(p);
          yyval.stnode=MkNode(astArrayIndex,p,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

     }
break;
case 136:
#line 2008 "nectar_syntax"
	{

		  p1 = pop_vs();

		 if(p1->typos != INT) {

			  printf("Error: Only integers you can increase by one\n");
			  exit(1);
		  }

		 push_vs(p1);

		 /*here you should check if location is integer*/
		 yyval.stnode = MkNode(astIncreaseAfter,NULL,yystack.l_mark[-1].stnode,NULL,NULL,NULL);

	 }
break;
case 137:
#line 2024 "nectar_syntax"
	{

		 p2 = pop_vs();

		 if(p2->typos != INT) {

			  printf("Error: Only integers you can increase by one\n");
			  exit(1);
		  }

		 push_vs(p2);

		 /*here you should check if location is integer*/
		 yyval.stnode = MkNode(astIncreaseBefore,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);

	 }
break;
case 138:
#line 2040 "nectar_syntax"
	{

		 p1 = pop_vs();

		 if(p1->typos != INT) {

			  printf("Error: Only integers you can decrease by one\n");
			  exit(1);
		  }

		 push_vs(p1);

		  /*here you should check if location is integer*/
		 yyval.stnode = MkNode(astDecreaseAfter,NULL,yystack.l_mark[-1].stnode,NULL,NULL,NULL);

	 }
break;
case 139:
#line 2056 "nectar_syntax"
	{

		  p2 = pop_vs();

		  if(p2->typos != INT) {

			  printf("Error: Only integers you can decrease by one\n");
			  exit(1);
		  }

		  push_vs(p2);

		  /*here you should check if location is integer*/
		 yyval.stnode = MkNode(astDecreaseBefore,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);

	 }
break;
case 140:
#line 2075 "nectar_syntax"
	{

      p2 = pop_vs();

  	  /*numOfArguments++;*/

	    sprintf(METHOD_NAME_PARS,"%d",p2->typos);
	    p1 = new_symbol(METHOD_NAME_PARS);
	    p1->typos = p2->typos;

	    push_vs(p1);
      push_vs(NULL);

	    yyval.stnode=MkNode(astActuals,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL);

      }
break;
case 141:
#line 2091 "nectar_syntax"
	{ yyval.stnode=MkNode(astActualsEmpty,NULL,NULL,NULL,NULL,NULL); push_vs(NULL);}
break;
case 142:
#line 2095 "nectar_syntax"
	{

		   p2 = pop_vs();
		   /*numOfArguments++;*/

		   sprintf(METHOD_NAME_PARS,"%d",p2->typos);
		   p1 = new_symbol(METHOD_NAME_PARS);
	     p1->typos = p2->typos;

	     push_vs(p1);

		   yyval.stnode=MkNode(astArgsSeq,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

       }
break;
case 143:
#line 2109 "nectar_syntax"
	{ yyval.stnode=MkNode(astArgsEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
#line 3864 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}

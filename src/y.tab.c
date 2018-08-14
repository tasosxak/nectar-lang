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

int topOfSt = 0; /*The current activated method's symbol table*/
int TopOfStack=-1;
int TopOfWhile=-1;
int TopOfRt = -1;
int numOfParams = 0;  /* For number of method's parameters*/
int numOfArguments =0; /* For "arguments and parameters matching"*/
int enableReturn = 1;
int shared = 0;
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
symbol *cur_method;
symbol *cur_func;
int CUR_TYPE = 1000;
symbol *p,*p1,*p2,*p3,*p4,*p5,*p6,*p7,*p8,*p9;

AstNode *TreeRoot;


#line 57 "nectar_syntax"
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
#line 88 "y.tab.c"

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
#define FINAL 289
#define EXTENDS 290
#define SHARED 291
#define DEC_CONST 292
#define LITERAL 293
#define REAL_DEC_CONST 294
#define THREE_DOTS 295
#define IDIV 296
#define GE 297
#define LE 298
#define NE 299
#define EQ 300
#define ID 301
#define NOTATION 302
#define INC 303
#define DEC 304
#define ADDASSIGN 305
#define SUBASSIGN 306
#define LOWER_THAN_ELSE 307
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    1,    2,    2,    9,   49,   50,    3,
   10,   10,    8,    8,   19,   19,    5,    5,    6,    6,
    7,    7,    7,    4,   51,   52,   11,   53,   54,   12,
   13,   13,   15,   15,   15,   16,   16,   16,   16,   16,
   14,   55,   17,   56,   17,   57,   17,   58,   18,   59,
   18,   18,   20,   20,   23,   23,   23,   23,   23,   23,
   23,   60,   21,   21,   21,   21,   21,   21,   61,   21,
   21,   21,   21,   62,   21,   63,   64,   21,   65,   21,
   21,   21,   21,   21,   21,   21,   25,   24,   24,   22,
   30,   31,   32,   32,   36,   37,   37,   34,   33,   26,
   26,   27,   27,   28,   28,   29,   29,   35,   35,   35,
   35,   35,   35,   38,   38,   39,   39,   40,   40,   41,
   41,   41,   41,   42,   42,   42,   42,   42,   42,   42,
   42,   42,   42,   42,   42,   42,   42,   42,   45,   46,
   46,   44,   44,   43,   43,   43,   43,   47,   47,   48,
   48,
};
static const YYINT yylen[] = {                            2,
    1,    2,    2,    0,    2,    0,    2,    0,    0,    7,
    2,    0,    0,    1,    1,    0,    2,    0,    5,    7,
    3,    5,    0,    4,    0,    0,   10,    0,    0,   10,
    4,    0,    5,    0,    1,    1,    1,    1,    1,    1,
    3,    0,    6,    0,    9,    0,    8,    0,    4,    0,
    6,    0,    2,    0,    1,    1,    1,    1,    2,    4,
    1,    0,    2,    2,    2,    2,    3,    6,    0,    9,
    4,    2,    4,    0,    6,    0,    0,    7,    0,    4,
    2,    1,    3,    5,    2,    1,    1,    3,    1,    3,
    3,    3,    3,    3,    5,    5,    3,    1,    1,    3,
    1,    3,    1,    2,    1,    3,    1,    1,    1,    1,
    1,    1,    1,    3,    1,    1,    1,    3,    1,    1,
    1,    1,    1,    1,    3,    1,    1,    1,    1,    1,
    1,    4,    6,    2,    2,    1,    4,    1,    3,    2,
    0,    3,    0,    2,    2,    2,    2,    2,    0,    3,
    0,
};
static const YYINT yydefred[] = {                         0,
    0,   14,    0,    1,    0,    0,    0,   28,    2,    0,
    3,    0,    8,    0,    0,   35,    0,    0,    0,    9,
    0,    0,   11,    0,    0,    0,    0,   10,   36,   37,
   38,   39,   40,   29,    0,    0,    0,    0,    0,   33,
    0,   15,    0,    0,    0,   17,   54,   30,    0,   24,
    5,    0,    7,    0,    0,    0,    0,   25,  130,  129,
    0,   62,   74,    0,    0,    0,    0,    0,  131,   76,
  127,  136,  128,    0,   54,   41,    0,   87,    0,    0,
    0,    0,    0,   53,   82,    0,   86,    0,    0,  103,
  105,    0,    0,    0,    0,    0,    0,    0,    0,  119,
  124,  138,    0,    0,    0,   19,    0,    0,    0,    0,
   81,    0,    0,    0,  104,    0,    0,    0,    0,  134,
  135,    0,   99,  145,  147,    0,    0,   72,    0,    0,
   79,    0,   85,    0,   64,   65,   63,    0,    0,  144,
  146,    0,    0,    0,    0,   66,  116,  117,  108,  109,
  110,  111,  112,  113,    0,    0,  120,  121,  122,  123,
    0,    0,    0,   21,    0,   67,    0,    0,    0,   83,
    0,    0,    0,  125,   90,   98,    0,    0,  139,    0,
    0,    0,    0,  102,    0,   94,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  118,   20,    0,    0,
    0,    0,    0,   88,    0,    0,    0,  142,   71,   73,
   80,    0,    0,    0,  137,  132,    0,   22,    0,    0,
    0,   84,    0,    0,    0,    0,    0,    0,    0,    0,
  150,    0,    0,   75,    0,    0,    0,   43,    0,  133,
    0,   26,   69,    0,   44,    0,   78,    0,    0,    0,
   47,    0,    0,    0,   27,   70,   45,    0,   49,    0,
   51,
};
static const YYINT yydgoto[] = {                          3,
    4,   43,    5,   28,   37,   38,   57,    6,   44,   20,
   53,    7,   17,   48,   18,   34,   83,  238,   45,   54,
   84,   85,   86,  113,   87,   88,   89,   90,   91,   92,
   93,   94,  104,   96,  155,   97,  189,   98,  156,   99,
  161,  100,  101,  126,  102,  127,  193,  194,   15,   24,
  107,  249,   12,   39,  225,  252,  244,  254,  260,  109,
  250,  110,  117,  239,  182,
};
static const YYINT yysindex[] = {                      -242,
 -280,    0,    0,    0, -242, -229, -242,    0,    0, -264,
    0,   11,    0, -224, -215,    0,   48, -225, -202,    0,
 -165,   47,    0,   -6, -228, -228, -181,    0,    0,    0,
    0,    0,    0,    0,   85,   77, -163, -181,   19,    0,
 -228,    0,   20, -163, -138,    0,    0,    0,  -17,    0,
    0, -157,    0,  506,  822, -155,   88,    0,    0,    0,
  822,    0,    0,   88,  822,  822,  843, -153,    0,    0,
    0,    0,    0,  822,    0,    0, -164,    0,  103, -150,
 -150,    0,   88,    0,    0, -173,    0,   32, -122,    0,
    0,   88,   88,   88,   -8,  113,   88,   71,   -9,    0,
    0,    0,  -35,    4,    3,    0,  115,  -45,  119,  123,
    0,  -31,   88,  -15,    0,   94, -137,  -25,  560,    0,
    0, -135,    0,    0,    0,  822,   74,    0,  822,  822,
    0,  822,    0,  822,    0,    0,    0,  822, -150,    0,
    0,  822,  822,  822,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  843,  843,    0,    0,    0,    0,
  843,   88,  822,    0, -224,    0,  822,  822, -150,    0,
  822, -228, -119,    0,    0,    0,  129,   -3,    0,  -45,
  -45,  693, -122,    0, -103,    0,  -59,    5,  128, -103,
 -103,  -81,  134,  822,   89,   -9,    0,    0,  -35,  137,
  -23,  -21,   88,    0,  -46,  822,    0,    0,    0,    0,
    0,  822, -150,  822,    0,    0,   -1,    0, -104,  693,
  693,    0,  822, -112,  139, -103,  140, -103,  141, -103,
    0, -228,  -78,    0, -103,   95, -114,    0,  693,    0,
  822,    0,    0,  139,    0,  130,    0, -103,   19,  693,
    0,  139,  822,  139,    0,    0,    0, -103,    0,  139,
    0,
};
static const YYINT yyrindex[] = {                         1,
    0,    0,    0,    0,    1,    0,    1,    0,    0,    0,
    0,    0,    0,  -30,   66,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -108,    0,    0,    0,
    0,    0,    0,    0,  149,    0,  -99, -108,    0,    0,
    0,    0,    0,  -99, -264,    0,    0,    0,  138,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -37,    0,
    0,  201,    0,    0,    0,    0,    0, -169,  300,    0,
    0, -168, -161, -151,  882,    0, -149,  354,   63,    0,
    0,    0,  138,   18,  138,    0,    0,    0,    0,    0,
    0,    0, -146,   13,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  795,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -30,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  100,    0,    0,
    0,    0,  408,    0,   67,    0,  929,    0,    0,   78,
  112,    0,    0,    0,  456,  117,    0,    0,  138,    0,
    0,    0, -143,    0,    8,    0,  795,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  155,    0,    0,    0,
    0,    0,    0,    0,  142,  742,    0,  154,    0,  136,
    0,    0,  614,    0,   26,    0,    0,    0,    0,    0,
    0,    0,    0,  142,    0,   35,    0,  156,    0,    0,
    0,  142,    0,  142,    0,    0,    0,   37,    0,  142,
    0,
};
static const YYINT yygindex[] = {                         0,
  133,  159,    0,    0,  161,    0,  -63,  160,    0,    0,
    0,    0,   39,  -43,    0,   -7,    0, -170,    0,  132,
 -152,    0,    0,   38,  372, 1067,   79,   80,  145,    0,
    0,   75,  936,   93,    0,    0,    6,   61,    0,   62,
    0,   56,    0,    0,    0,    0,   15,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 1320
static const YYINT yytable[] = {                         99,
    4,  138,   98,   99,   99,   99,   99,   99,   56,   99,
   32,  215,  169,   78,  223,  174,   18,  220,   35,  221,
    8,   99,   99,   99,   99,    6,   56,  160,  171,  211,
   29,  144,  157,   49,    1,  139,   13,  158,    2,  162,
  208,  164,  231,   55,  224,   30,   56,   31,  213,   10,
   14,   42,  138,   99,  126,   99,   32,  126,  126,  126,
  126,  126,  126,  163,  126,  212,   42,  233,  234,   46,
   16,   89,   33,  251,   19,   22,  126,  126,   48,  126,
   50,  257,  144,  259,   46,   99,  247,  129,   21,  261,
   78,   61,   56,   48,  144,   50,  130,  256,   23,   57,
   61,   56,  115,  115,   26,  115,  115,  115,   57,   55,
  126,   58,   25,  147,   59,  148,   27,   60,   55,   36,
   58,  115,  115,   59,  115,   93,   60,  120,   40,  121,
  152,  147,  150,  148,   41,  218,   91,    9,   42,   11,
  126,   47,    2,   58,   50,  105,   78,  116,  122,  134,
  123,  172,  145,  115,  165,  115,  114,  114,  167,  114,
  114,  114,  168,  173,  205,  176,  179,  206,  207,  132,
   92,  214,   18,  232,  216,  114,  114,  219,  114,  236,
  240,   16,  237,  243,  241,  115,  246,  245,   12,   31,
  253,  132,  140,   18,   95,  148,   23,   97,   46,   96,
   52,   16,   51,  200,   52,  255,  119,  114,  204,  114,
  183,  115,  186,  184,  177,  195,  197,  196,  229,   99,
   99,  227,   99,   99,  242,   99,   99,  132,   99,   99,
   99,    0,   99,   99,   99,   99,    0,  132,    0,  114,
  143,  132,    0,  140,  141,  143,   99,  132,   99,  132,
   99,  132,    0,    0,   99,   99,   99,  132,   99,   99,
   99,   99,   99,   99,    0,   99,   99,   99,   99,  132,
   34,  132,    0,   89,  126,  126,    0,  126,  126,   13,
  126,  126,   89,  126,  126,  126,  159,  126,  126,  126,
  126,  143,    0,  141,  140,  141,  142,  143,    0,  131,
    0,  126,    0,  126,  132,  126,  140,  141,    0,  126,
  126,  126,    0,  126,  126,  126,  126,  126,  126,  115,
  115,    0,  115,  115,    0,  115,  115,   93,  115,  115,
  115,    0,  115,  115,  115,  115,   93,    0,   91,  101,
  101,    0,    0,  101,  101,    0,  115,   91,  115,    0,
  115,    0,    0,    0,  115,  115,  115,    0,  101,  115,
  115,  115,  115,  115,    0,  115,  115,  149,  151,  153,
  154,    0,   92,  114,  114,    0,  114,  114,    0,  114,
  114,   92,  114,  114,  114,    0,  114,  114,  114,  114,
  101,    0,  101,  107,  107,    0,   95,  107,    0,    0,
  114,    0,  114,    0,  114,   95,    0,    0,  114,  114,
  114,    0,  107,  114,  114,  114,  114,  114,    0,  114,
  114,    0,  101,    0,    0,    0,    0,    0,  106,    0,
    0,    0,    0,    0,    0,  111,    0,    0,    0,    0,
    0,    0,    0,    0,  107,    0,  107,  100,  100,    0,
    0,  100,  100,    0,  128,    0,    0,  143,  143,  133,
    0,    0,    0,  135,  136,  137,  100,    0,  146,    0,
    0,  143,    0,    0,    0,    0,  107,    0,    0,  166,
    0,    0,    0,    0,  170,    0,  143,    0,    0,    0,
    0,    0,  143,  143,  143,  106,  106,    0,  100,  106,
  100,  143,    0,  143,  143,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  106,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  100,    0,    0,  198,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   74,  106,    0,  106,    0,
   77,  209,  210,    0,    0,    0,  101,  101,    0,  101,
  101,    0,  101,  101,   78,  101,  101,  101,    0,  101,
  101,    0,  101,    0,  222,    0,    0,    0,  106,    0,
    0,    0,    0,  101,    0,  101,    0,  101,    0,    0,
    0,  101,  101,  101,    0,    0,   82,    0,    0,   74,
  101,    0,  101,  101,   77,    0,    0,    0,    0,    0,
  107,  107,    0,  107,  107,    0,  107,  107,   78,  107,
  107,  107,    0,  107,  107,  107,  107,    0,   75,    0,
   76,    0,    0,    0,    0,    0,    0,  107,    0,  107,
    0,  107,    0,    0,    0,  107,  107,  107,    0,    0,
   82,    0,    0,   68,  107,    0,  107,  107,   68,    0,
    0,    0,    0,    0,  100,  100,    0,  100,  100,    0,
  100,  100,   68,  100,  100,  100,    0,  100,  100,    0,
  100,    0,   75,    0,  175,    0,    0,    0,    0,    0,
    0,  100,    0,  100,    0,  100,    0,    0,    0,  100,
  100,  100,    0,    0,   68,    0,    0,    0,  100,    0,
  100,  100,  106,  106,    0,  106,  106,    0,  106,  106,
    0,  106,  106,  106,    0,  106,  106,  106,  106,    0,
    0,    0,   74,    0,    0,    0,   68,   77,   68,  106,
    0,  106,    0,  106,    0,    0,    0,  106,  106,  106,
    0,   78,    0,    0,    0,    0,  106,    0,  106,  106,
    0,    0,   59,   60,    0,   61,   62,    0,   63,   64,
    0,   65,   66,    0,    0,    0,   67,    0,    0,    0,
    0,   77,    0,   82,    0,    0,   77,    0,    0,   68,
    0,   69,    0,   70,    0,    0,    0,   71,   72,   73,
   77,    0,    0,    0,    0,    0,   79,    0,   80,   81,
    0,    0,    0,    0,    0,   75,   59,   60,    0,   61,
   62,    0,   63,   64,    0,   65,   66,    0,    0,    0,
   67,    0,   77,    0,  151,  149,    0,    0,    0,  151,
    0,    0,    0,   68,    0,   69,    0,   70,    0,    0,
    0,   71,   72,   73,    0,    0,    0,    0,    0,    0,
   79,   74,   80,   81,   77,    0,   77,    0,    0,    0,
   68,   68,    0,   68,   68,    0,   68,   68,    0,   68,
   68,    0,   74,    0,   68,  151,    0,   77,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   68,    0,   68,
    0,   68,    0,    0,    0,   68,   68,   68,    0,    0,
    0,    0,   82,    0,   68,    0,   68,   68,  126,    0,
    0,    0,    0,  126,  126,    0,  126,    0,  126,    0,
    0,    0,    0,   82,    0,    0,    0,    0,    0,    0,
  126,  126,    0,  126,    0,    0,    0,    0,    0,   59,
   60,    0,   61,   62,    0,   63,   64,    0,   65,   66,
    0,    0,    0,   67,    0,  126,    0,    0,    0,    0,
  126,  126,    0,  126,    0,  126,   68,    0,   69,    0,
   70,    0,    0,    0,   71,   72,   73,  126,  126,   95,
  126,    0,    0,   79,    0,   80,   81,    0,   77,   77,
    0,   77,   77,    0,   77,   77,    0,   77,   77,    0,
    0,    0,   77,    0,    0,  124,  125,    0,    0,    0,
    0,    0,    0,    0,    0,   77,    0,   77,    0,   77,
    0,    0,    0,   77,   77,   77,    0,    0,    0,    0,
    0,    0,   77,    0,   77,   77,    0,    0,    0,    0,
    0,  151,  151,    0,   95,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  151,    0,    0,    0,    0,
    0,    0,    0,  187,  188,    0,    0,    0,   59,   60,
  151,    0,    0,    0,    0,    0,  151,  151,  151,    0,
    0,    0,   67,    0,    0,  151,    0,  151,  151,   59,
   60,    0,    0,    0,  203,    0,    0,   69,    0,    0,
    0,    0,    0,   71,   72,   73,    0,   95,    0,    0,
    0,  103,   79,    0,   80,   81,    0,  108,   69,    0,
    0,  112,  114,    0,   71,   72,   73,    0,    0,    0,
  118,    0,  126,   79,    0,   80,   81,    0,  188,  126,
    0,  126,    0,  126,  126,   95,   95,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   95,    0,    0,  126,  126,  126,
  126,  126,    0,    0,    0,   95,    0,    0,    0,  126,
    0,    0,  178,    0,    0,  180,  181,    0,  126,    0,
  126,  126,    0,    0,  185,    0,    0,    0,  190,  191,
  192,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  126,  126,  126,  126,  126,  199,
    0,    0,    0,  201,  202,    0,    0,  114,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  217,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  226,    0,    0,    0,    0,    0,  228,    0,
  230,    0,    0,    0,    0,    0,    0,    0,    0,  235,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  248,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  258,
};
static const YYINT yycheck[] = {                         37,
    0,   61,   40,   41,   42,   43,   44,   45,   44,   47,
   41,   93,   44,   59,   61,   41,  125,   41,   26,   41,
  301,   59,   60,   61,   62,  125,   44,   37,   44,  182,
  259,   91,   42,   41,  277,   44,  301,   47,  281,  103,
   44,  105,   44,   61,   91,  274,   44,  276,   44,  279,
   40,   44,   61,   91,   37,   93,  285,   40,   41,   42,
   43,   44,   45,   61,   47,   61,   59,  220,  221,   44,
  295,   59,  301,  244,  290,  301,   59,   60,   44,   62,
   44,  252,   91,  254,   59,  123,  239,  261,   41,  260,
   59,  261,  261,   59,   91,   59,  270,  250,  301,  261,
  270,  270,   40,   41,   58,   43,   44,   45,  270,  261,
   93,  261,  278,   43,  261,   45,  123,  261,  270,  301,
  270,   59,   60,  270,   62,   59,  270,  292,   44,  294,
   60,   43,   62,   45,   58,  199,   59,    5,  302,    7,
  123,  123,  281,  301,  125,  301,   59,  301,   46,  272,
  301,   58,   40,   91,   40,   93,   40,   41,   40,   43,
   44,   45,   40,  301,  172,  301,   93,  287,   40,  273,
   59,   44,  281,  278,   41,   59,   60,   41,   62,  292,
   41,  281,   44,  262,   44,  123,  301,   93,  123,   41,
   61,  273,   93,  302,   59,   41,   59,   44,   38,   44,
   59,  301,   44,  165,   45,  249,   75,   91,  171,   93,
  132,   67,  138,  134,  122,  155,  161,  156,  213,  257,
  258,  207,  260,  261,  232,  263,  264,  273,  266,  267,
  268,   -1,  270,  271,  272,  273,   -1,  273,   -1,  123,
   40,  273,   -1,  303,  304,   45,  284,  273,  286,  273,
  288,  273,   -1,   -1,  292,  293,  294,  273,  296,  297,
  298,  299,  300,  301,   -1,  303,  304,  305,  306,  273,
  301,  273,   -1,  261,  257,  258,   -1,  260,  261,  279,
  263,  264,  270,  266,  267,  268,  296,  270,  271,  272,
  273,   91,   -1,   93,  303,  304,  305,  306,   -1,  268,
   -1,  284,   -1,  286,  273,  288,  303,  304,   -1,  292,
  293,  294,   -1,  296,  297,  298,  299,  300,  301,  257,
  258,   -1,  260,  261,   -1,  263,  264,  261,  266,  267,
  268,   -1,  270,  271,  272,  273,  270,   -1,  261,   40,
   41,   -1,   -1,   44,   45,   -1,  284,  270,  286,   -1,
  288,   -1,   -1,   -1,  292,  293,  294,   -1,   59,  297,
  298,  299,  300,  301,   -1,  303,  304,  297,  298,  299,
  300,   -1,  261,  257,  258,   -1,  260,  261,   -1,  263,
  264,  270,  266,  267,  268,   -1,  270,  271,  272,  273,
   91,   -1,   93,   40,   41,   -1,  261,   44,   -1,   -1,
  284,   -1,  286,   -1,  288,  270,   -1,   -1,  292,  293,
  294,   -1,   59,  297,  298,  299,  300,  301,   -1,  303,
  304,   -1,  123,   -1,   -1,   -1,   -1,   -1,   57,   -1,
   -1,   -1,   -1,   -1,   -1,   64,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   91,   -1,   93,   40,   41,   -1,
   -1,   44,   45,   -1,   83,   -1,   -1,  257,  258,   88,
   -1,   -1,   -1,   92,   93,   94,   59,   -1,   97,   -1,
   -1,  271,   -1,   -1,   -1,   -1,  123,   -1,   -1,  108,
   -1,   -1,   -1,   -1,  113,   -1,  286,   -1,   -1,   -1,
   -1,   -1,  292,  293,  294,   40,   41,   -1,   91,   44,
   93,  301,   -1,  303,  304,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  123,   -1,   -1,  162,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   40,   91,   -1,   93,   -1,
   45,  180,  181,   -1,   -1,   -1,  257,  258,   -1,  260,
  261,   -1,  263,  264,   59,  266,  267,  268,   -1,  270,
  271,   -1,  273,   -1,  203,   -1,   -1,   -1,  123,   -1,
   -1,   -1,   -1,  284,   -1,  286,   -1,  288,   -1,   -1,
   -1,  292,  293,  294,   -1,   -1,   91,   -1,   -1,   40,
  301,   -1,  303,  304,   45,   -1,   -1,   -1,   -1,   -1,
  257,  258,   -1,  260,  261,   -1,  263,  264,   59,  266,
  267,  268,   -1,  270,  271,  272,  273,   -1,  123,   -1,
  125,   -1,   -1,   -1,   -1,   -1,   -1,  284,   -1,  286,
   -1,  288,   -1,   -1,   -1,  292,  293,  294,   -1,   -1,
   91,   -1,   -1,   40,  301,   -1,  303,  304,   45,   -1,
   -1,   -1,   -1,   -1,  257,  258,   -1,  260,  261,   -1,
  263,  264,   59,  266,  267,  268,   -1,  270,  271,   -1,
  273,   -1,  123,   -1,  125,   -1,   -1,   -1,   -1,   -1,
   -1,  284,   -1,  286,   -1,  288,   -1,   -1,   -1,  292,
  293,  294,   -1,   -1,   91,   -1,   -1,   -1,  301,   -1,
  303,  304,  257,  258,   -1,  260,  261,   -1,  263,  264,
   -1,  266,  267,  268,   -1,  270,  271,  272,  273,   -1,
   -1,   -1,   40,   -1,   -1,   -1,  123,   45,  125,  284,
   -1,  286,   -1,  288,   -1,   -1,   -1,  292,  293,  294,
   -1,   59,   -1,   -1,   -1,   -1,  301,   -1,  303,  304,
   -1,   -1,  257,  258,   -1,  260,  261,   -1,  263,  264,
   -1,  266,  267,   -1,   -1,   -1,  271,   -1,   -1,   -1,
   -1,   40,   -1,   91,   -1,   -1,   45,   -1,   -1,  284,
   -1,  286,   -1,  288,   -1,   -1,   -1,  292,  293,  294,
   59,   -1,   -1,   -1,   -1,   -1,  301,   -1,  303,  304,
   -1,   -1,   -1,   -1,   -1,  123,  257,  258,   -1,  260,
  261,   -1,  263,  264,   -1,  266,  267,   -1,   -1,   -1,
  271,   -1,   91,   -1,   40,   41,   -1,   -1,   -1,   45,
   -1,   -1,   -1,  284,   -1,  286,   -1,  288,   -1,   -1,
   -1,  292,  293,  294,   -1,   -1,   -1,   -1,   -1,   -1,
  301,   40,  303,  304,  123,   -1,   45,   -1,   -1,   -1,
  257,  258,   -1,  260,  261,   -1,  263,  264,   -1,  266,
  267,   -1,   40,   -1,  271,   91,   -1,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  284,   -1,  286,
   -1,  288,   -1,   -1,   -1,  292,  293,  294,   -1,   -1,
   -1,   -1,   91,   -1,  301,   -1,  303,  304,   37,   -1,
   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,   -1,
   -1,   -1,   -1,   91,   -1,   -1,   -1,   -1,   -1,   -1,
   59,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,  257,
  258,   -1,  260,  261,   -1,  263,  264,   -1,  266,  267,
   -1,   -1,   -1,  271,   -1,   37,   -1,   -1,   -1,   -1,
   42,   43,   -1,   45,   -1,   47,  284,   -1,  286,   -1,
  288,   -1,   -1,   -1,  292,  293,  294,   59,   60,   54,
   62,   -1,   -1,  301,   -1,  303,  304,   -1,  257,  258,
   -1,  260,  261,   -1,  263,  264,   -1,  266,  267,   -1,
   -1,   -1,  271,   -1,   -1,   80,   81,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  284,   -1,  286,   -1,  288,
   -1,   -1,   -1,  292,  293,  294,   -1,   -1,   -1,   -1,
   -1,   -1,  301,   -1,  303,  304,   -1,   -1,   -1,   -1,
   -1,  257,  258,   -1,  119,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  271,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  138,  139,   -1,   -1,   -1,  257,  258,
  286,   -1,   -1,   -1,   -1,   -1,  292,  293,  294,   -1,
   -1,   -1,  271,   -1,   -1,  301,   -1,  303,  304,  257,
  258,   -1,   -1,   -1,  169,   -1,   -1,  286,   -1,   -1,
   -1,   -1,   -1,  292,  293,  294,   -1,  182,   -1,   -1,
   -1,   55,  301,   -1,  303,  304,   -1,   61,  286,   -1,
   -1,   65,   66,   -1,  292,  293,  294,   -1,   -1,   -1,
   74,   -1,  261,  301,   -1,  303,  304,   -1,  213,  268,
   -1,  270,   -1,  272,  273,  220,  221,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  239,   -1,   -1,  296,  297,  298,
  299,  300,   -1,   -1,   -1,  250,   -1,   -1,   -1,  261,
   -1,   -1,  126,   -1,   -1,  129,  130,   -1,  270,   -1,
  272,  273,   -1,   -1,  138,   -1,   -1,   -1,  142,  143,
  144,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  296,  297,  298,  299,  300,  163,
   -1,   -1,   -1,  167,  168,   -1,   -1,  171,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  194,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  206,   -1,   -1,   -1,   -1,   -1,  212,   -1,
  214,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  223,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  241,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  253,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 307
#define YYUNDFTOKEN 375
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,0,0,0,
0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"FALSE","TRUE","INT","RETURN","IF","ELSE",
"WHILE","BREAK","TRY","READ","PRINTLN","TIMES","USE","UNLESS","NOT","AND","OR",
"REAL","PUTS","BOOL","FUNC","RIGHTARROW","CLASS","PRIVATE","PUBLIC","ABSTRACT",
"METH","VAR","STR","SELF","IN","FOR","FINAL","EXTENDS","SHARED","DEC_CONST",
"LITERAL","REAL_DEC_CONST","THREE_DOTS","IDIV","GE","LE","NE","EQ","ID",
"NOTATION","INC","DEC","ADDASSIGN","SUBASSIGN","LOWER_THAN_ELSE",0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : definitions",
"definitions : class definitions",
"definitions : func definitions",
"definitions :",
"meth_list : methodef meth_list",
"meth_list :",
"methodef : note meth",
"$$1 :",
"$$2 :",
"class : modifier CLASS ID $$1 extension $$2 bodyclass",
"extension : EXTENDS ID",
"extension :",
"modifier :",
"modifier : PUBLIC",
"note : NOTATION",
"note :",
"fields : field fields",
"fields :",
"field : ID ':' type attrs separator",
"field : ID ':' type '=' expr attrs separator",
"attrs : ',' ID attrs",
"attrs : ',' ID '=' expr attrs",
"attrs :",
"bodyclass : '{' fields meth_list '}'",
"$$3 :",
"$$4 :",
"meth : modifier ID $$3 '(' params ')' RIGHTARROW type $$4 body",
"$$5 :",
"$$6 :",
"func : FUNC ID $$5 '(' params ')' RIGHTARROW type $$6 body",
"params : formals ID ':' type",
"params :",
"formals : formals ID ':' type ','",
"formals :",
"formals : THREE_DOTS",
"type : INT",
"type : REAL",
"type : BOOL",
"type : STR",
"type : ID",
"body : '{' stmts '}'",
"$$7 :",
"decl : VAR ID ':' type $$7 vars",
"$$8 :",
"decl : VAR ID ':' type '[' DEC_CONST ']' $$8 vars",
"$$9 :",
"decl : VAR ID ':' type '=' expr $$9 vars",
"$$10 :",
"vars : ',' ID $$10 vars",
"$$11 :",
"vars : ',' ID '=' expr $$11 vars",
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
"$$12 :",
"stmt : IF code '(' expr ')' stmt ELSE $$12 stmt",
"stmt : singlestmt IF expr separator",
"stmt : decl separator",
"stmt : singlestmt UNLESS expr separator",
"$$13 :",
"stmt : WHILE $$13 '(' expr ')' stmt",
"$$14 :",
"$$15 :",
"stmt : FOR $$14 ID IN expr $$15 stmt",
"$$16 :",
"stmt : expr TIMES $$16 stmt",
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
"factor : elements",
"elements : '[' sequence ']'",
"sequence : other_elements expr",
"sequence :",
"other_elements : other_elements expr ','",
"other_elements :",
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
#line 2308 "nectar_syntax"



void Init_Hash_Table(void)
{  int i;

   for(i=0; i<SYM_TABLE_SIZE; i++)
      ht.table[i]=NULL;
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
   symbp->iterable = 0;
   symbp->field = 0;
   return(symbp);
}

void mk_iterable(symbol *symbp){

  symbp->iterable = 1;
  return;
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

void addsymb(symbol *symbp, int gl){

    int i;
    symbol *p;

    i=mkkey(symbp->name);

   if(gl ==0) {

     //printf("GLOBAL SYMBOL:: %s\n",symbp->name);

     p=ht.table[i];
     symbp->NextSymbol=p;
     symbp->PrevSymbol=NULL;
     if(p) p->PrevSymbol=symbp;
     ht.table[i]=symbp;
     ht.numbsymbols++;

     //printf("Global HashTable: %s\n",symbp->name);

   }
   else if(gl ==1 || gl == 2) {

     //printf("LOCAL SYMBOL:: %s\n",symbp->name);

     p= cur_class->mht->table[i];
     symbp->NextSymbol=p;
     symbp->PrevSymbol=NULL;
     if(p) p->PrevSymbol=symbp;
     cur_class->mht->table[i] = symbp;
     cur_class->mht->numbsymbols++;

     //printf("Class %s HashTable: %s\n",cur_class->name,symbp->name);
  }
  else if(gl ==3) {

    //printf("LOCAL SYMBOL:: %s\n",symbp->name);

    if(cur_func != NULL){
      p= cur_func->mht->table[i];
      symbp->NextSymbol=p;
      symbp->PrevSymbol=NULL;
      if(p) p->PrevSymbol=symbp;
      cur_func->mht->table[i] = symbp;
      cur_func->mht->numbsymbols++;

      //printf("Function %s HashTable: %s\n",cur_func->name,symbp->name);
   }
   else if(cur_method != NULL){
     p= cur_method->mht->table[i];
     symbp->NextSymbol=p;
     symbp->PrevSymbol=NULL;
     if(p) p->PrevSymbol=symbp;
     cur_method->mht->table[i] = symbp;
     cur_method->mht->numbsymbols++;

     //printf("Method %s HashTable: %s\n",cur_method->name,symbp->name);
   }
 }

}

symbol* findsymb(char *onoma, int gl){

    int i;
    symbol *p;
    i=mkkey(onoma);

    //printf("Try to find %s in %d hashtable\n",onoma,gl);

    if(gl == 0){

        p=ht.table[i];
        while(p && (strcmp(p->name,onoma) !=0))
              p=p->NextSymbol;

    }
    else if(gl == 1) {

      p= cur_class->mht->table[i];
      while(p && (strcmp(p->name,onoma) !=0))
            p=p->NextSymbol;
   }
   else if(gl == 2){
       p= cur_class->mht->table[i];
       while(p && (strcmp(p->name,onoma) !=0))
             p=p->NextSymbol;
   }
   else if(gl == 3){

       if(cur_func != NULL){
           p= cur_func->mht->table[i];
           while(p && (strcmp(p->name,onoma) !=0))
                 p=p->NextSymbol;
       }
       else if(cur_method != NULL){
           p= cur_method->mht->table[i];
           while(p && (strcmp(p->name,onoma) !=0))
                 p=p->NextSymbol;
       }

   }

   //if(p == NULL) printf("not found!\n");
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

void discard_symbol(symbol *symbp){

   if(symbp){

      symbp->PrevSymbol->NextSymbol = symbp->NextSymbol;
      symbp->NextSymbol->PrevSymbol = symbp->PrevSymbol;
	    symbp->PrevSymbol = NULL;
	    symbp->NextSymbol = NULL;
   }

}

void check_assignment(symbol *opnd1, symbol *opnd2){

   symbol *p;

   if( !(opnd1->lvalue)){
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
			//printf("%s ",arr_st[i].table[j]) ;
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

int startswith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

void yyerror(char *s)
{
   fputs(s,stderr); putc('\n',stderr);
}
#line 1436 "y.tab.c"

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
#line 88 "nectar_syntax"
	{

      		     p1 = findsymb("main",0);/*Every program in coral language must has a main function*/
      		     if(!p1) {
      					printf("Error : 'main' not found in program");
      					exit(1);
      				}

			        TreeRoot=MkNode(astProgram,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);


        }
break;
case 2:
#line 105 "nectar_syntax"
	{ yyval.stnode=MkNode(astClassDef,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL); }
break;
case 3:
#line 106 "nectar_syntax"
	{ yyval.stnode=MkNode(astFuncDef,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL); }
break;
case 4:
#line 108 "nectar_syntax"
	{ yyval.stnode=MkNode(astEmptyDef,NULL,NULL,NULL,NULL,NULL); }
break;
case 5:
#line 113 "nectar_syntax"
	{yyval.stnode=MkNode(astMethSeq,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL); }
break;
case 6:
#line 115 "nectar_syntax"
	{ yyval.stnode=MkNode(astEmptyMethList,NULL,NULL,NULL,NULL,NULL); }
break;
case 7:
#line 118 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 8:
#line 122 "nectar_syntax"
	{

         strcpy(CLASS_NAME,yystack.l_mark[0].ystr);
         p1 = pop_vs();

         p2 = new_symbol(CLASS_NAME);
         p2->accessor = p1->accessor;
         p2->lvalue = 0;

         p2->typos = CUR_TYPE++;

         add_symbols_to_table(p2,0);

         if(topOfSt == MAX_SYM_TABLES) {
  				printf("Out of memory :( , the number of classes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
  				exit(1);
  			 }

         p2->mht= malloc(sizeof(HASH_TAB));
         cur_class = p2;


       }
break;
case 9:
#line 144 "nectar_syntax"
	{

         if((strcmp(cur_class->name,"Object") == 0)){

           strcpy(cur_class->base_class_name,"NULL");
         }
       }
break;
case 10:
#line 150 "nectar_syntax"
	{


         yyval.stnode=MkNode(astClass,cur_class,yystack.l_mark[0].stnode,NULL,NULL,NULL);

         cur_class = NULL;
         strcpy(CLASS_NAME,"");
       }
break;
case 11:
#line 161 "nectar_syntax"
	{

               p1 = findsymb(yystack.l_mark[0].ystr,0);

         			 if(p1!=NULL){
         				    strcpy(cur_class->base_class_name,p1->name);
         			 }
         			 else{

         				printf("Error: '%s' undeclared class",yystack.l_mark[-1].yint);
         				exit(1);
         			 }

         			 /*$$=MkNode(astExtension,p1,NULL,NULL,NULL,NULL);*/
         }
break;
case 12:
#line 176 "nectar_syntax"
	{

           strcpy(cur_class->base_class_name,"Object");
           /*$$=MkNode(astNoExtension,NULL,NULL,NULL,NULL,NULL);*/
         }
break;
case 13:
#line 183 "nectar_syntax"
	{

             yyval.stnode=MkNode(astPrivateClassMod,NULL,NULL,NULL,NULL,NULL);
             p1 = new_symbol(""); /*create symbol*/
   	         p1->accessor = PRIVATE_ACC;
   	         push_vs(p1);
          }
break;
case 14:
#line 190 "nectar_syntax"
	{

             yyval.stnode=MkNode(astPublicClassMod,NULL,NULL,NULL,NULL,NULL);
             p1 = new_symbol(""); /*create symbol*/
             p1->accessor = PUBLIC_ACC;
             push_vs(p1);
         }
break;
case 15:
#line 199 "nectar_syntax"
	{

             if(strcmp(yystack.l_mark[0].ystr,"$shared")==0){

                shared= 1;

             }
             else if (strcmp(yystack.l_mark[0].ystr,"$final")==0){

             }
             else if (strcmp(yystack.l_mark[0].ystr,"$abstract")==0){

             }
         }
break;
case 16:
#line 213 "nectar_syntax"
	{}
break;
case 17:
#line 218 "nectar_syntax"
	{yyval.stnode=MkNode(astFields,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL);}
break;
case 18:
#line 219 "nectar_syntax"
	{yyval.stnode=MkNode(astEmptyFields,NULL,NULL,NULL,NULL,NULL);}
break;
case 19:
#line 222 "nectar_syntax"
	{

               if(startswith("@",yystack.l_mark[-4].ystr)==0) {

                 printf("Error: The fields of class should start with '@'.\n");
                 exit(1);
               }
               p1 = pop_vs();
               p3 = new_symbol(yystack.l_mark[-4].ystr);
               p3->sclass = MEMORY;
               p3->typos = p1->typos;
               p3->accessor = PRIVATE_ACC;
               p3->lvalue = 1;
               p3->field = 1;
               strcpy(p3->nameclass ,p1->name);
               add_symbols_to_table(p3,1);

               if(topOfSt == MAX_SYM_TABLES) {
                printf("Out of memory :( , the number of attributes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
                exit(1);
               }

              yyval.stnode=MkNode(astField,p3,yystack.l_mark[-1].stnode,NULL,NULL,NULL);


         }
break;
case 20:
#line 248 "nectar_syntax"
	{

           if(startswith("@",yystack.l_mark[-6].ystr)==0) {

             printf("Error: The fields of class should start with '@'.\n");
             exit(1);
           }

           p1 = pop_vs();
           p2 = pop_vs();

           p4 = new_symbol(yystack.l_mark[-6].ystr);
           p4->sclass = MEMORY;
           p4->typos = p2->typos;
           p4->accessor = PRIVATE_ACC;
           p4->lvalue = 1;
           p4->field = 1;
           add_symbols_to_table(p4,1);

          if(topOfSt == MAX_SYM_TABLES) {
            printf("Out of memory :( , the number of attributes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
            exit(1);
          }

           yyval.stnode=MkNode(astFieldAssign,p4,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,NULL,NULL);


         }
break;
case 21:
#line 279 "nectar_syntax"
	{

          if(startswith("@",yystack.l_mark[-1].ystr)==0) {

            printf("Error: The fields of class should start with '@'.\n");
            exit(1);
          }

           p1 = pop_vs();
           /*p2 = pop_vs();*/

           p3 = new_symbol(yystack.l_mark[0].stnode);
           p3->sclass = MEMORY;
           p3->typos = p1->typos;
           p3->accessor = PRIVATE_ACC;
           p3->lvalue = 1;
           p3->field = 1;
           strcpy(p3->nameclass ,p1->name);
           add_symbols_to_table(p3,1);

           if(topOfSt == MAX_SYM_TABLES) {
              printf("Out of memory :( , the number of attributes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
              exit(1);
           }

          yyval.stnode=MkNode(astAttrs,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);

          push_vs(p1);

        }
break;
case 22:
#line 310 "nectar_syntax"
	{

          if(startswith("@",yystack.l_mark[-3].ystr)==0) {

            printf("Error: The fields of class should start with '@'.\n");
            exit(1);
          }

          p1 = pop_vs();
          p2 = pop_vs();
          /*p3 = pop_vs();*/

          p4 = new_symbol(yystack.l_mark[-2].ystr);
          p4->sclass = MEMORY;
          p4->typos = p2->typos;
          p4->accessor = PRIVATE_ACC;
          p4->lvalue = 1;
          strcpy(p4->nameclass ,p2->name);
          add_symbols_to_table(p4,1);

          if(topOfSt == MAX_SYM_TABLES) {
           printf("Out of memory :( , the number of attributes must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
           exit(1);
          }

          yyval.stnode=MkNode(astAttrsAssign,p4,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL);

          push_vs(p2);

        }
break;
case 23:
#line 340 "nectar_syntax"
	{ yyval.stnode=MkNode(astEmptyAttrs,NULL,NULL,NULL,NULL,NULL); }
break;
case 24:
#line 346 "nectar_syntax"
	{yyval.stnode=MkNode(astBodyClass,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,NULL,NULL);
       	 }
break;
case 25:
#line 351 "nectar_syntax"
	{

          strcat(METHOD_NAME,yystack.l_mark[0].ystr);
          char snum[6];
          nitoa(CUR_TYPE -1,snum);
          strcat(METHOD_NAME,snum);

		      push_rt(new_symbol("method"));
          p2 = new_symbol("");
          set_class_types(p2,METHOD);
          p2->lvalue = 0;
          p2->mht= malloc(sizeof(HASH_TAB));
          if((strcmp(yystack.l_mark[0].ystr,"new") == 0)){
            p2->modifier = SHARED_MOD;
            numOfParams = 1;
          }
          else {

              if(shared == 1) {
                p2->modifier = SHARED_MOD;
              }
              else{
                numOfParams = 1;
              }
        }

          cur_method = p2;
          push_vs(p2);

        }
break;
case 26:
#line 380 "nectar_syntax"
	{

    			 p1 = pop_vs();
           p2 = pop_vs();
           p3 = pop_vs();

           strcpy(p2->name,METHOD_NAME);

    			 /*copy_attributes(p2,p1);*/
           p2->typos = p1->typos;
           p2->accessor = p3->accessor;


    			 if(topOfSt == MAX_SYM_TABLES) {
    				printf("Out of memory :( , the number of methods must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
    				exit(1);
    			 }

           add_symbols_to_table(p2,2);

    			 strcpy(METHOD_NAME,"");
           /*push_vs(p1);*/
    			 push_vs(p2);

		 }
break;
case 27:
#line 406 "nectar_syntax"
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

		numOfParams =0; /*reset the number of parameters for the next method*/
		enableReturn=1;
		NUM_PAR =0;
		NUM_BYTES_VAR = 0;
    cur_method =  NULL;
    shared = 0;
	}
break;
case 28:
#line 435 "nectar_syntax"
	{

      		 strcat(METHOD_NAME,yystack.l_mark[0].ystr);
      		 push_rt(new_symbol("method"));
           p2 = new_symbol("");
           p2->lvalue = 0;
           set_class_types(p2,METHOD);
           p2->mht= malloc(sizeof(HASH_TAB));
           cur_func = p2;
           push_vs(p2);

      		 }
break;
case 29:
#line 446 "nectar_syntax"
	{

      			 p1 = pop_vs();
             p2 = pop_vs();
             strcpy(p2->name,METHOD_NAME);
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


      			 if(topOfSt == MAX_SYM_TABLES) {
      				printf("Out of memory :( , the number of methods must be less than %d",MAX_SYM_TABLES); /*if the number of methods is greater than MAX_SYM_TABLES constant*/
      				exit(1);
      			 }

             add_symbols_to_table(p2,0);
      			 strcpy(METHOD_NAME,"");
            /* push_vs(p1);*/
             push_vs(p2);

      		 }
break;
case 30:
#line 485 "nectar_syntax"
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
          cur_func = NULL;
      	}
break;
case 31:
#line 517 "nectar_syntax"
	{


         p2 = pop_vs();
	       p3 = new_symbol(yystack.l_mark[-2].ystr);
         p3->arg = 1;
	       copy_attributes(p3,p2);
         strcpy(p3->nameclass,p2->name);
		     sprintf(METHOD_NAME_TEMP,"%d",p2->typos);
		     strcat(METHOD_NAME,METHOD_NAME_TEMP);

		     /*Create a pseudonym for this parameter, which is important for code generation*/

		     strcpy(NUM_VAR_ARR, "ebp + ");
		     sprintf(TEMP_NUM_VAR_ARR, "%d", 4 * (NUM_PAR + 2));
		     strcpy(p3->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));
		     NUM_PAR ++;

	       add_symbols_to_table(p3,3);
	       yyval.stnode=MkNode(astParamSeq,p3,yystack.l_mark[0].stnode,yystack.l_mark[-2].ystr,NULL,NULL);
		     numOfParams++;
         p3->index = numOfParams;
          }
break;
case 32:
#line 540 "nectar_syntax"
	{ yyval.stnode=MkNode(astParamEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
case 33:
#line 545 "nectar_syntax"
	{

	     p2 = pop_vs();
	     p3 = new_symbol(yystack.l_mark[-3].ystr);
	     p3->arg = 1;
	     copy_attributes(p3,p2);
       strcpy(p3->nameclass,p2->name);
		   sprintf(METHOD_NAME_TEMP,"%d",p2->typos);
		   strcat(METHOD_NAME,METHOD_NAME_TEMP);

		   strcpy(NUM_VAR_ARR, "ebp + ");
		   sprintf(TEMP_NUM_VAR_ARR, "%d", 4 *(NUM_PAR+2));
		   strcpy(p3->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));
		   NUM_PAR++;

	     add_symbols_to_table(p3,3);
	     yyval.stnode=MkNode(astFormalsSeq,p3,yystack.l_mark[-1].stnode,yystack.l_mark[-3].ystr,NULL,NULL);
		   numOfParams++;
       p3->index = numOfParams;
		 }
break;
case 34:
#line 565 "nectar_syntax"
	{ yyval.stnode=MkNode(astFormalsEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
case 35:
#line 566 "nectar_syntax"
	{

           p2 = pop_vs();
           p3 = new_symbol("...");
           p3->arg = 1;
           p3->typos = ARRAY;

           sprintf(METHOD_NAME_TEMP,"%d",p2->typos);
           strcat(METHOD_NAME,METHOD_NAME_TEMP);
           NUM_PAR++;
           add_symbols_to_table(p3,0);
           numOfParams++;
           p3->index = numOfParams;

           yyval.stnode=MkNode(astFormalsDots,p3,NULL,NULL,NULL,NULL);


      }
break;
case 36:
#line 587 "nectar_syntax"
	{

          yyval.stnode=MkNode(astInt,NULL,NULL,NULL,NULL,NULL);
 	        p1 = new_symbol("int"); /*create symbol*/
	        set_class_types(p1,yystack.l_mark[0].yint); /*the type of symbol is integer*/
	        push_vs(p1);

        }
break;
case 37:
#line 595 "nectar_syntax"
	{

          yyval.stnode=MkNode(astReal,NULL,NULL,NULL,NULL,NULL);
 	        p1 = new_symbol("real"); /*create symbol*/
	        set_class_types(p1,yystack.l_mark[0].yint); /*the type of symbol is real*/
	        push_vs(p1);

         }
break;
case 38:
#line 603 "nectar_syntax"
	{

          yyval.stnode=MkNode(astBool,NULL,NULL,NULL,NULL,NULL);
 	        p1 = new_symbol("bool"); /*create symbol*/
	        set_class_types(p1,yystack.l_mark[0].yint); /*the type of symbol is integer*/
	        push_vs(p1);

        }
break;
case 39:
#line 612 "nectar_syntax"
	{

              yyval.stnode=MkNode(astStr,NULL,NULL,NULL,NULL,NULL);
     	        p1 = new_symbol("str"); /*create symbol*/
    	        set_class_types(p1,yystack.l_mark[0].yint); /*the type of symbol is string*/
    	        push_vs(p1);

            }
break;
case 40:
#line 620 "nectar_syntax"
	{

          yyval.stnode=MkNode(astPointer,NULL,NULL,NULL,NULL,NULL);
 	        p1 = new_symbol(yystack.l_mark[0].ystr); /*create symbol*/
          p = findsymb(yystack.l_mark[0].ystr,0);
	        p1->typos = p->typos;
	        push_vs(p1);

        }
break;
case 41:
#line 632 "nectar_syntax"
	{
	 yyval.stnode=MkNode(astBody,NULL,yystack.l_mark[-1].stnode,NULL,NULL,NULL);}
break;
case 42:
#line 637 "nectar_syntax"
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
                  mk_iterable(p2);
              break;
              default:

                p =  findsymb(p1->name,0);
                if(p == NULL){
                    printf("Error: Undeclared class '%s\n",p1->name);
                    exit(0);
                }
                strcpy(p2->nameclass ,p->name);

              break;
        		}

            strcpy(p2->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));

        		p2->sclass = MEMORY;
        		add_symbols_to_table(p2,3);

        		push_vs(p1);


  }
break;
case 43:
#line 687 "nectar_syntax"
	{

    		pop_vs();
    		yyval.stnode=MkNode(astDecl,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);

    }
break;
case 44:
#line 693 "nectar_syntax"
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
		    add_symbols_to_table(p3,3);

		    push_vs(p2);


		}
break;
case 45:
#line 733 "nectar_syntax"
	{

		    pop_vs();
		    yyval.stnode=MkNode(astDecl,NULL,yystack.l_mark[-5].stnode,yystack.l_mark[0].stnode,NULL,NULL);

    }
break;
case 46:
#line 739 "nectar_syntax"
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
               case STR:
                   mk_iterable(p2);
               break;
          }

          strcpy(p2->pseudonym, strcat(NUM_VAR_ARR, TEMP_NUM_VAR_ARR));

          if(!isSuperType(p1->typos, p3->typos)) {
    			     printf("Warning: The type of '%s' is not '%d'\n",p1->name,p3->typos);
    		   }

    	     copy_value(p2,p3);
    		   p2->sclass = MEMORY;
    	     add_symbols_to_table(p2,3);

    		   push_vs(p1);

	  }
break;
case 47:
#line 784 "nectar_syntax"
	{

    	     pop_vs();
    	     yyval.stnode=MkNode(astDeclAssign,NULL,yystack.l_mark[-4].stnode,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL);
	  }
break;
case 48:
#line 792 "nectar_syntax"
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


		    add_symbols_to_table(p2,3);

		    p2->sclass = MEMORY;
		    push_vs(p1);

	   }
break;
case 49:
#line 826 "nectar_syntax"
	{

    		p = pop_vs();
    		yyval.stnode=MkNode(astVarsSeq,p,yystack.l_mark[0].stnode,NULL,NULL,NULL);
    		push_vs(p);

    }
break;
case 50:
#line 833 "nectar_syntax"
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
	     add_symbols_to_table(p2,3);

		   p2->sclass = MEMORY;
	     push_vs(p1);

	  }
break;
case 51:
#line 866 "nectar_syntax"
	{

         p=pop_vs();
	       yyval.stnode=MkNode(astVarAssign,p,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);
	       push_vs(p);
    }
break;
case 52:
#line 872 "nectar_syntax"
	{ yyval.stnode=MkNode(astVarEmpty,NULL,NULL,NULL,NULL,NULL); }
break;
case 53:
#line 877 "nectar_syntax"
	{ yyval.stnode=MkNode(astStmtSeq,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL); pop_vs();  }
break;
case 54:
#line 878 "nectar_syntax"
	{ yyval.stnode=MkNode(astStmtEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
case 55:
#line 882 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[0].stnode;
			pop_vs();
			push_vs(NULL);
	    }
break;
case 56:
#line 887 "nectar_syntax"
	{

			yyval.stnode=yystack.l_mark[0].stnode;
			push_vs(NULL);
        }
break;
case 57:
#line 892 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[0].stnode;
			push_vs(NULL);
        }
break;
case 58:
#line 896 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[0].stnode;
			push_vs(NULL);
        }
break;
case 59:
#line 901 "nectar_syntax"
	{

		  yyval.stnode=MkNode(astPrintLnStmt,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);
		  push_vs(NULL);

	    }
break;
case 60:
#line 908 "nectar_syntax"
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
#line 924 "nectar_syntax"
	{

			pop_vs();
			yyval.stnode=MkNode(astExprStmt,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);
			push_vs(NULL);
		}
break;
case 62:
#line 933 "nectar_syntax"
	{ if(enableReturn==1)
		         push_rt(new_symbol("if"));
			 }
break;
case 63:
#line 939 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[-1].stnode;
			pop_vs();
			push_vs(NULL);
      }
break;
case 64:
#line 944 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[-1].stnode;
			push_vs(NULL);
      }
break;
case 65:
#line 948 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[-1].stnode;
			push_vs(NULL);
      }
break;
case 66:
#line 952 "nectar_syntax"
	{
			yyval.stnode=yystack.l_mark[-1].stnode;
			push_vs(NULL);
      }
break;
case 67:
#line 956 "nectar_syntax"
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
#line 986 "nectar_syntax"
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
#line 1011 "nectar_syntax"
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
#line 1020 "nectar_syntax"
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
#line 1053 "nectar_syntax"
	{

		  p3 = pop_vs();
		  p1 = pop_vs();

		  yyval.stnode = MkNode(astSingleIfStmt,NULL,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

		  push_vs(NULL);

	  }
break;
case 72:
#line 1063 "nectar_syntax"
	{

		  yyval.stnode = yystack.l_mark[-1].stnode;
		  push_vs(NULL);

	  }
break;
case 73:
#line 1069 "nectar_syntax"
	{

		  p3 = pop_vs();
		  p1 = pop_vs();

		  yyval.stnode = MkNode(astSingleUnlessStmt,NULL,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

		  push_vs(NULL);

	  }
break;
case 74:
#line 1079 "nectar_syntax"
	{ p = new_symbol("");
				push_wh(p);
				enableReturn =0;
				}
break;
case 75:
#line 1082 "nectar_syntax"
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
case 76:
#line 1094 "nectar_syntax"
	{

          p = new_symbol("");
          push_wh(p);
          enableReturn =0;

    }
break;
case 77:
#line 1100 "nectar_syntax"
	{

      p4=pop_vs();

      if(p4->iterable == 0){

           printf("NotIterableError: The expression in for loop must be iterable.\n");
           exit(0);
      }

      NUM_BYTES_VAR-=1;
      p = new_symbol(yystack.l_mark[-2].ystr);
      p->index = NUM_BYTES_VAR;
      p->sclass = MEMORY;
      p->typos = p4->typos;
      add_symbols_to_table(p,3);
      push_vs(p);

    }
break;
case 78:
#line 1118 "nectar_syntax"
	{


         p6=pop_vs();
         p = pop_vs();
         pop_wh();
         if(TopOfWhile <0) enableReturn=1;
         push_vs(NULL);

         yyval.stnode=MkNode(astForStmt,p,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);

    }
break;
case 79:
#line 1130 "nectar_syntax"
	{ p = new_symbol("");
				push_wh(p);
				enableReturn =0;
				}
break;
case 80:
#line 1133 "nectar_syntax"
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
case 81:
#line 1151 "nectar_syntax"
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
case 82:
#line 1165 "nectar_syntax"
	{
			        yyval.stnode=yystack.l_mark[0].stnode;
			        push_vs(NULL);
      }
break;
case 83:
#line 1170 "nectar_syntax"
	{


		  yyval.stnode=MkNode(astPrintLnStmt,NULL,yystack.l_mark[-1].stnode,NULL,NULL,NULL);
		  push_vs(NULL);

	  }
break;
case 84:
#line 1177 "nectar_syntax"
	{


		  yyval.stnode=MkNode(astReadStmt,NULL,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);
		  pop_vs();
      pop_vs();
		  push_vs(NULL);

	  }
break;
case 85:
#line 1186 "nectar_syntax"
	{

			pop_vs();
			yyval.stnode=MkNode(astExprStmt,NULL,yystack.l_mark[-1].stnode,NULL,NULL,NULL);
			push_vs(NULL);
		}
break;
case 86:
#line 1193 "nectar_syntax"
	{

			yyval.stnode=MkNode(astNullStmt,NULL,NULL,NULL,NULL,NULL);
			/*push_vs(NULL);*/
		  }
break;
case 87:
#line 1201 "nectar_syntax"
	{yyval.stnode = yystack.l_mark[0].ystr;}
break;
case 88:
#line 1204 "nectar_syntax"
	{

		  p1 = pop_vs();

		  yyval.stnode=MkNode(astExprInline,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);


	  }
break;
case 89:
#line 1213 "nectar_syntax"
	{

		  p1 = pop_vs();

		  yyval.stnode=MkNode(astSingleExprInline,NULL,yystack.l_mark[0].stnode,NULL,NULL,NULL);


	  }
break;
case 90:
#line 1223 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[-1].stnode;}
break;
case 91:
#line 1228 "nectar_syntax"
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
case 92:
#line 1245 "nectar_syntax"
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
case 93:
#line 1263 "nectar_syntax"
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
case 94:
#line 1283 "nectar_syntax"
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
case 95:
#line 1304 "nectar_syntax"
	{


	     p3 = pop_vs();
	     p1 = pop_vs();
		 check_assignment(p1,p3);
		 yyval.stnode=MkNode(astListedAssign,NULL,yystack.l_mark[-4].stnode,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL);

		}
break;
case 96:
#line 1315 "nectar_syntax"
	{

	     p3 = pop_vs();
	     p1 = pop_vs();
		 check_assignment(p1,p3);

		 yyval.stnode=MkNode(astNestedAssign,NULL,yystack.l_mark[-4].stnode,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL);

        }
break;
case 97:
#line 1324 "nectar_syntax"
	{

		 p3 = pop_vs();
	     p1 = pop_vs();
		 check_assignment(p1,p3);

		 yyval.stnode=MkNode(astEmbedAssign,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[0].stnode,NULL,NULL);

		 }
break;
case 98:
#line 1337 "nectar_syntax"
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
case 99:
#line 1357 "nectar_syntax"
	{

        if(startswith("@",yystack.l_mark[0].ystr) == 1){
            if(shared == 1){

              printf("Error: You cannot use field in shared method.\n");
              exit(1);
            }
			       p1 = findsymb(yystack.l_mark[0].ystr,1);
        }
        else {

             p1 = findsymb(yystack.l_mark[0].ystr,3);
        }
      /*printf("%s\n",p1->name);*/
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
case 100:
#line 1390 "nectar_syntax"
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
case 101:
#line 1467 "nectar_syntax"
	{ yyval.stnode= yystack.l_mark[0].stnode;}
break;
case 102:
#line 1472 "nectar_syntax"
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
case 103:
#line 1548 "nectar_syntax"
	{ yyval.stnode = yystack.l_mark[0].stnode;}
break;
case 104:
#line 1552 "nectar_syntax"
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
case 105:
#line 1569 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 106:
#line 1573 "nectar_syntax"
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
case 107:
#line 1648 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 108:
#line 1652 "nectar_syntax"
	{ yyval.stnode=MkNode(astGeOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 109:
#line 1653 "nectar_syntax"
	{ yyval.stnode=MkNode(astGOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 110:
#line 1654 "nectar_syntax"
	{ yyval.stnode=MkNode(astLeOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 111:
#line 1655 "nectar_syntax"
	{ yyval.stnode=MkNode(astLOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 112:
#line 1656 "nectar_syntax"
	{ yyval.stnode=MkNode(astNeOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 113:
#line 1657 "nectar_syntax"
	{ yyval.stnode=MkNode(astEOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 114:
#line 1662 "nectar_syntax"
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
                  mk_iterable(p);
               break;

             }
       break;


		 }

         yyval.stnode=MkNode(astAddExpr,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL);
	     push_vs(p);
        }
break;
case 115:
#line 1749 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 116:
#line 1753 "nectar_syntax"
	{ yyval.stnode=MkNode(astAddOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 117:
#line 1754 "nectar_syntax"
	{ yyval.stnode=MkNode(astSubOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 118:
#line 1758 "nectar_syntax"
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
              if(yystack.l_mark[-1].stnode->NodeType == astDivOp )
                p->typos = REAL;
              else
							  p->typos = INT;
						break;
						case BOOL:
						   printf("Error: bad operand types for binary operator \n");
							 exit(1);
						break;
            case STR:
                p->typos = STR;
                mk_iterable(p);
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
                mk_iterable(p);

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
case 119:
#line 1850 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 120:
#line 1854 "nectar_syntax"
	{  yyval.stnode=MkNode(astMulOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 121:
#line 1855 "nectar_syntax"
	{  yyval.stnode=MkNode(astDivOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 122:
#line 1856 "nectar_syntax"
	{  yyval.stnode=MkNode(astIdivOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 123:
#line 1857 "nectar_syntax"
	{  yyval.stnode=MkNode(astModOp,NULL,NULL,NULL,NULL,NULL);}
break;
case 124:
#line 1861 "nectar_syntax"
	{ yyval.stnode= yystack.l_mark[0].stnode; }
break;
case 125:
#line 1862 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[-1].stnode;}
break;
case 126:
#line 1863 "nectar_syntax"
	{ yyval.stnode=yystack.l_mark[0].stnode;}
break;
case 127:
#line 1864 "nectar_syntax"
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
case 128:
#line 1875 "nectar_syntax"
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
case 129:
#line 1885 "nectar_syntax"
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
case 130:
#line 1895 "nectar_syntax"
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
case 131:
#line 1905 "nectar_syntax"
	{

          if(shared == 1){

            printf("Error: You cannot use 'self' in shared method.\n");
            exit(1);
          }
          p1 = new_symbol("");
          p1->sclass=CONSTANT;
          p = findsymb(CLASS_NAME,0);
          p1->typos = p->typos;
          p1->lvalue=0;
          p1->timi=1;
          p1->has_timi=CONST_VAL;
          push_vs(p1);
         yyval.stnode = MkNode(astSelf,p1,NULL,NULL,NULL,NULL);
         }
break;
case 132:
#line 1922 "nectar_syntax"
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

		  p = findsymb(p3->name,0);

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
case 133:
#line 1976 "nectar_syntax"
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

               p6 = findsymb(yystack.l_mark[-5].ystr,0);
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
                      printf("Error: Method %s is undeclared.\n",p7->name);
                      exit(1);
                   }
                   else if(p7->modifier != SHARED_MOD){
                     printf("Error: Method %s is not shared.\n",p7->name);
                     exit(1);
                   }
                    p = p6;
                    yyval.stnode = MkNode(astStaticMethodCall,p,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

               }
               else {

                  p = findsymb(yystack.l_mark[-5].ystr,3);
                  if(p == NULL){

                         p = findsymb(yystack.l_mark[-5].ystr,1);
                         if(p == NULL){
                           printf("Error: '%s' undeclared variable",yystack.l_mark[-5].ystr);
                           exit(1);
                        }
                    }

                  char snum[6];
                  nitoa(p->typos,snum);
                  strcat(METHOD_NAME,snum);
                  strcat(METHOD_NAME,METHOD_NAME_TEMP);
                  p3 = new_symbol(METHOD_NAME);
                  p6 = findsymb(p->nameclass,0);
                  if(p6 != NULL){

                      i=mkkey(p3->name);
                      /*printf(p3->name);*/
                      p7=p6->mht->table[i];
                      while(p7 && (strcmp(p7->name,p3->name) !=0)){
                              p7=p7->NextSymbol;
                      }

                      if(p7 == NULL){
                        printf("Undeclared method!\n");
                        exit(1);
                      }
                      p2 = new_symbol(p7->name);

                      p2->index = p->index;
                      p2->typos = p->typos;
                      strcpy(p2->nameclass, p->nameclass);
                      p2->instance_method_type_call = p7->typos;
                      p2->field = p->field;
                      strcpy(p2->ax_name,p->name);

                      yyval.stnode = MkNode(astMethodCall,p2,yystack.l_mark[-3].stnode,yystack.l_mark[-1].stnode,NULL,NULL);
                  }else{
                    printf("Error: '%s' is not class.",p->nameclass);
                    exit(1);
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
case 134:
#line 2098 "nectar_syntax"
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
case 135:
#line 2108 "nectar_syntax"
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
case 136:
#line 2119 "nectar_syntax"
	{

     		  p2 = new_symbol("");
          strncpy(p2->stimi,yystack.l_mark[0].ystr + 1, strlen(yystack.l_mark[0].ystr) - 2);
          p2->sclass = CONSTANT;
     		  p2->typos = STR;
          mk_iterable(p2);
          push_vs(p2);
     		  yyval.stnode=MkNode(astString,p2,NULL,NULL,NULL,NULL);

     	  }
break;
case 137:
#line 2130 "nectar_syntax"
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
case 138:
#line 2141 "nectar_syntax"
	{


     }
break;
case 139:
#line 2148 "nectar_syntax"
	{

      pop_vs();

      p = new_symbol("");
      yyval.stnode=MkNode(astElements,NULL,yystack.l_mark[-1].stnode,NULL,NULL,NULL);
      push_vs(p);

    }
break;
case 140:
#line 2160 "nectar_syntax"
	{

        pop_vs();
        pop_vs();

        p = new_symbol("");

        yyval.stnode=MkNode(astElementSeq,NULL,yystack.l_mark[-1].stnode,yystack.l_mark[0].stnode,NULL,NULL);

        push_vs(p);
    }
break;
case 141:
#line 2171 "nectar_syntax"
	{

        p = new_symbol("");

        yyval.stnode=MkNode(astEmptyElementSeq,NULL,NULL,NULL,NULL,NULL);

        push_vs(p);

    }
break;
case 142:
#line 2183 "nectar_syntax"
	{

      pop_vs();
      pop_vs();

      p = new_symbol("");

      yyval.stnode=MkNode(astOtherElementSeq,NULL,yystack.l_mark[-2].stnode,yystack.l_mark[-1].stnode,NULL,NULL);

      push_vs(p);
    }
break;
case 143:
#line 2194 "nectar_syntax"
	{

        p = new_symbol("");
        push_vs(p);

        yyval.stnode=MkNode(astEmptyOtherElementSeq,NULL,NULL,NULL,NULL,NULL);
    }
break;
case 144:
#line 2204 "nectar_syntax"
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
case 145:
#line 2220 "nectar_syntax"
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
case 146:
#line 2236 "nectar_syntax"
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
case 147:
#line 2252 "nectar_syntax"
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
case 148:
#line 2271 "nectar_syntax"
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
case 149:
#line 2286 "nectar_syntax"
	{ yyval.stnode=MkNode(astActualsEmpty,NULL,NULL,NULL,NULL,NULL); push_vs(NULL);}
break;
case 150:
#line 2290 "nectar_syntax"
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
case 151:
#line 2303 "nectar_syntax"
	{ yyval.stnode=MkNode(astArgsEmpty,NULL,NULL,NULL,NULL,NULL);}
break;
#line 4146 "y.tab.c"
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

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
extern YYSTYPE yylval;

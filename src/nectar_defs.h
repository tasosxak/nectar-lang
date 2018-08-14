#define SYM_TABLE_SIZE 41
#define NAME_MAX  32
#define MAX_SYM_TABLES 31

#define METHOD  		2
#define CONSTANT        3
#define MEMORY          4
#define REGISTER        5
#define INTCONST        7
#define IDENTIFIER      8
#define STACK			9
#define ARITHEXPR      10
#define LOGICEXPR      11
#define ASSIGNMENT     12
#define CONST_VAL      13
#define ARRAY          14
#define PRIVATE_ACC    15
#define PUBLIC_ACC     16
#define ABSTRACT_MOD     17
#define FINAL_MOD     18
#define SHARED_MOD  19

#define astEmptyProgram     399
#define astProgram          400
#define astMethSeq		      401
#define astMethLast 	      402
#define astParamSeq     403
#define astParamEmpty	404
#define astFormalsSeq	405
#define astFormalsEmpty	406
#define astInt		 	407
#define astIfElseStmt	408
#define astBody         409
#define astDeclsSeq		410
#define astDeclsEmpty	411
#define astDeclListSeq	412
#define astDeclListEmpty	413
#define astDecl 	    414
#define astDeclAssign	415
#define astVarsSeq	    416
#define astVarAssign	417
#define astVarEmpty		418
#define astStmtSeq      419
#define astStmtEmpty	420
#define astLocation 	421
#define astReturnStmt	422
#define astMethodName	423
#define astWhileStmt	424
#define astBreakStmt	425
#define astCompExpr		427
#define astAssign		429
#define astAddExpr      431
#define astAddExprLast  432
#define astNullStmt     435
#define astGeOp			437
#define astGOp			438
#define astLeOp			439
#define astLOp			440
#define astNeOp			441
#define astEOp			442
#define astAddOp		443
#define astSubOp		444
#define astMulExpr		445
#define astMulOp		446
#define astDivOp		447
#define astDeConst 		448
#define astTrue			449
#define astFalse		450
#define astMethodCall	451
#define astActuals		452
#define astActualsEmpty 453
#define astArgsSeq		454
#define astArgsEmpty    455
#define astPrintStmt	456
#define astReadStmt		457
#define astPrintLtStmt	458
#define astPrintLnLtStmt 459
#define astPrintLnStmt	460
#define astAssignSeq	461
#define astEmbedAssign	462
#define astNestedAssign	463
#define astListedAssign	465
#define astTimesStmt	466
#define astLibList   	467
#define astLib			468
#define astEmptyLib		469
#define astSingleIfStmt 470
#define astSingleUnlessStmt 471
#define astExprStmt		472
#define astIfStmt		473
#define astModOp		474
#define astIncreaseAfter 475
#define astIncreaseBefore 476
#define astDecreaseAfter   477
#define astDecreaseBefore  478
#define astAndExpr		 479
#define astOrExpr		 480
#define	astNotExpr		 481
#define astAddAssign	 482
#define astSubAssign	 483
#define astReal	   	 	 484
#define astRealDeConst   485
#define astPutsStmt  	 486
#define astExprInline    487
#define astLiteralInline 488
#define astSingleExprInline 489
#define astSingleLiteralInline 490
#define astBool  	 	 491
#define astClassDef 492
#define astMethDef 493
#define astDeclDef 494
#define astClass  495
#define astPrivateClassMod 496
#define astPublicClassMod 498
#define astAbstractClassMod 499
#define astBodyClass 500
#define astFields 501
#define astEmptyFields 502
#define astField 503
#define astFieldAssign 504
#define astAttrs 505
#define astAttrsAssign 506
#define astEmptyAttrs 507
#define astPrivateMod 508
#define astPublicMod  509
#define astEmptyDef 510
#define astEmptyMethList 511
#define astFuncLast 512
#define astFuncDef 513
#define astPointer 514
#define astIdivOp    515
#define astStr   516
#define astString 517
#define astFunctionCall 518
#define astStaticMethodCall 519
#define astSelf 520
#define astArrayIndex 521
#define astForStmt 522
#define astElements 523
#define astElementSeq 524
#define astEmptyElementSeq 525
#define astOtherElementSeq 526
#define astEmptyOtherElementSeq 527
#define astForStmt 528
#define astFormalsDots 529
#define astFinalClassMod 530
#define astSharedMethodMod 531
/* ----------------------------------------------------------- */
/* ----- THE STRUCTURE FOR THE ABSTRACT SYNTAX TREE NODES ---- */
/* ----------------------------------------------------------- */

typedef struct dcl_tag {
   int dcl_type;                    /* -- METHOD -------------- */
   int num_params;                         /* -- Number of parameters ---- */
   struct dcl_tag *next_dcl_type;
} dcl;


typedef struct AstNode_tag {
    int NodeType;
    struct symbol_tag *SymbolNode;
    struct AstNode_tag *pAstNode[4];
} AstNode;

typedef struct symbol_tag {
   int accessor;
   unsigned char name[NAME_MAX+1];  /* -- Variable name .------------------ */
   unsigned char ax_name[NAME_MAX+1];  /* -- Variable name .------------------ */
   unsigned char base_class_name[NAME_MAX+1];
   unsigned char nameclass[NAME_MAX+1];  /* -- Variable class's name .------------------ */
   int typos;                       /* -- INT REAL BOOL---------------------------- */
   int sclass;			     /* -- REGISTER, CONSTANT, MEMORY,STACK ----- */
   int timi;                        /* -- Value assigned . ---------------- */
   float dtimi;
   int stype;					/* -- LOGICEXPR , ARITHEXPR */
   int lvalue;                      /* -- TRUE or FALSE .------------------ */
   int arg;
   int field;
   int has_timi;
   int index;
   int modifier;
   dcl* dcl_ptr;
   int iterable;
   int instance_method_type_call;
   unsigned char pseudonym[NAME_MAX+1];
   unsigned char stimi[NAME_MAX+1];
   struct symbol_tag *NextSymbol;
   struct symbol_tag *PrevSymbol;
   struct hash_tab *mht;

} symbol;



typedef struct hash_tab {
   int numbsymbols;
   symbol *table[SYM_TABLE_SIZE];
} HASH_TAB;


AstNode *MkNode(int tipos,symbol *sn,
              AstNode *z0,AstNode *z1,AstNode *z2,AstNode *z3);

void traverse(AstNode *p,int n);
void kena(int n);
void ProcessDecimConst(AstNode *p);
void CodeGeneration(AstNode *p, int lev, int lvalue, int leftChild);
void ProcessAddExpr(AstNode *p, int lev, int lvalue, int leftChild);
void add_method_dcl(symbol *symbp);
void main(int argc, char **argv);
symbol* see_wh();
void yyerror(char *s);
symbol *check_addsub_arithm_op(symbol *opnd1, symbol *opnd2);
symbol *check_muldiv_arithm_op(symbol *opnd1, symbol *opnd2);
symbol *check_logic_op(symbol *opnd1, symbol *opnd2);
void Show_Hash_Table(void);
void preOrder(AstNode* p, int indent);
void check_ifelse(symbol *pexp, symbol *pst1, symbol *pst2);
void check_while(symbol *pexp, symbol *pst);
void copy_symbol(symbol *dst, symbol *src);
void copy_value(symbol *dst, symbol *src);
void check_assignment(symbol *opnd1, symbol *opnd2);
void discard_symbol(symbol *symbp);
void add_symbols_to_table(symbol *symbp, int gl);
symbol *findsymb(char *onoma, int gl);
void addsymb(symbol *symbp, int gl);
int mkkey(char *s);
int startswith(const char *pre, const char *str);
int isNumeric (const char * s);
void copy_attributes(symbol *dst, symbol *src);
void Init_while_stack();
int set_class_types(symbol *symbp, int class_tipos);
int is_integral(symbol *s);
void add_method_dcl(symbol *symbp);
symbol *new_symbol(char *name);
symbol *pop_vs(void);
symbol *pop_wh(void);
void push_vs(symbol *p);
symbol *pop_rt(void);
void push_rt(symbol *p);
void push_wh(symbol *p);
void Init_Hash_Table(void);
int yylex();
int yyparse();

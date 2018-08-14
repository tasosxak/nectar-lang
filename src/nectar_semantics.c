#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "nectar_defs.h"
#include "y.tab.h"
#include <time.h>

char* filename;

extern AstNode *TreeRoot;
extern FILE* yyin;

int TAG_IFS = -1; //Number of if-else statements
int TAG_WHILES =-1; //Number of while-loop statements
int REG_A_IN_USE = 0; //True if register-AX is in use or not
int BYTES_OF_PARAMETERS = 0;
int NUM_OF_LITERALS = 0;
int LOC_ASSIGN_COUNTER =0;
int R_TYPES_COUNTER = 0;
int NUM_COMP = 0;
int IS_METHOD = 0;
char PARAMETERS_CALL[31];

int NUM_OF_INT_CONST = 0;
int NUM_OF_REAL_CONST = 0;

symbol* assigns[50];
int r_types[50];
char CUR_METHOD_NAME[31];
FILE *data, *text;



char *nitoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}


void kena(int n)
{  int i;

   for(i=0; i<n; i++) printf(" ");
}

float xfmod(float a, float b){
  return a/b;
}
void traverse(AstNode *p,int n)
{  int i;

   n=n+3;
   if(p)
   {
      switch (p->NodeType)
      {
         case astEmptyProgram:
            kena(n); printf("astEmptyProgram\n");
         break;
         case astProgram:
            kena(n); printf("astProgram\n");
         break;
         case astMethSeq:
            kena(n); printf("astMethSeq\n");
         break;
         case astMethLast:
            kena(n); printf("astMethLast: %s\n",p->SymbolNode->name);
         break;
         case astParamSeq:
            kena(n); printf("astParamSeq\n");
         break;
         case astParamEmpty:
            kena(n); printf("astParamEmpty\n");
         break;
         case astFormalsSeq:
            kena(n); printf("astFormalsSeq\n");
         break;
         case astFormalsEmpty:
            kena(n); printf("astFormalsEmpty\n");
         break;
         case astInt:
            kena(n); printf("astInt\n");
         break;
         case astIfElseStmt:
            kena(n); printf("astIfElseStmt\n");
         break;
         case astBody:
            kena(n); printf("astBody\n");
         break;
         case astDeclsSeq:
            kena(n); printf("astDeclsSeq\n");
         break;
         case astDeclsEmpty:
            kena(n); printf("astDeclsEmpty\n");
         break;
         case astDeclListSeq:
            kena(n); printf("astDeclListSeq\n");
         break;
         case astDeclListEmpty:
            kena(n); printf("astDeclListEmpty\n");
         break;
         case astDecl:
            kena(n); printf("astDecl\n");
         break;
         case astDeclAssign:
            kena(n); printf("astDeclAssign\n");
         break;
         case astVarsSeq:
            kena(n); printf("astVarsSeq\n");
         break;
         case astVarAssign:
            kena(n); printf("astVarAssign\n");
         break;
         case astVarEmpty:
            kena(n); printf("astVarEmpty\n");
         break;
         case astStmtSeq:
            kena(n); printf("astStmtSeq\n");
         break;
         case astStmtEmpty:
            kena(n); printf("astStmtEmpty\n");
         break;
         case astLocation:
            kena(n); printf("astLocation: %s\n",p->SymbolNode->name);
         break;
         case astReturnStmt:
            kena(n); printf("astReturnStmt\n");
         break;
         case astMethodName:
            kena(n); printf("astMethodName: %s\n",p->SymbolNode->name);
         break;
         case astWhileStmt:
            kena(n); printf("astWhileStmt\n");
         break;
         case astBreakStmt:
            kena(n); printf("astBreakStmt\n");
         break;
         case astCompExpr:
            kena(n); printf("astCompExpr\n");
         break;
         case astAssign:
            kena(n); printf("astAssign\n");
         break;
         case astAddExpr:
            kena(n); printf("astAddExpr\n");
         break;
         case astAddExprLast:
            kena(n); printf("astAddExprLast\n");
         break;
         case astNullStmt:
            kena(n); printf("astNullStmt\n");
         break;
         case astMethodCall:
            kena(n); printf("astMethodCall: %s\n",p->SymbolNode->name);
         break;
         case astGeOp:
            kena(n); printf("astGeOp\n");
         break;
         case astGOp:
            kena(n); printf("astGOp\n");
         break;
         case astLeOp:
            kena(n); printf("astLeOp\n");
         break;
		 case astLOp:
            kena(n); printf("astLOp\n");
         break;
		 case astNeOp:
            kena(n); printf("astNeOp\n");
         break;
		 case astEOp:
            kena(n); printf("astEOp\n");
         break;
		 case astAddOp:
            kena(n); printf("astAddOp\n");
         break;
		 case astSubOp:
            kena(n); printf("astSubOp\n");
         break;
		 case astMulExpr:
            kena(n); printf("astMulExpr\n");
         break;
		 case astMulOp:
            kena(n); printf("astMulOp\n");
         break;
		 case astDivOp:
            kena(n); printf("astDivOp\n");
         break;
		 case astDeConst:
            kena(n); printf("astDeConst\n");
         break;
		 case astTrue:
            kena(n); printf("astTrue\n");
         break;
		 case astActualsEmpty:
            kena(n); printf("astActualsEmpty\n");
         break;
		 case astFalse:
            kena(n); printf("astFalse\n");
         break;
		 case astActuals:
            kena(n); printf("astActuals\n");
         break;
		 case astArgsSeq:
            kena(n); printf("astArgsSeq\n");
         break;
		 case astArgsEmpty:
            kena(n); printf("astArgsEmpty\n");
         break;
         default:
            printf("Unknown=%d\n",p->NodeType);
      }
      for(i=0; i<4; i++) traverse(p->pAstNode[i],n);
   }
}

//-------------Processes for Code Generation ---------------//


//Program
void ProcessProgram(AstNode*p, int lev){
   CodeGeneration(p->pAstNode[0],lev+1,0,0);

}

void ProcessClassDef(AstNode *p,int lev) {
    CodeGeneration(p->pAstNode[0],lev+1,0,0);
    CodeGeneration(p->pAstNode[1],lev+1,0,0);
}

void ProcessFuncDef(AstNode *p,int lev){
    CodeGeneration(p->pAstNode[0],lev+1,0,0);
    CodeGeneration(p->pAstNode[1],lev+1,0,0);
}

void ProcessDeclDef(AstNode *p,int lev){
    CodeGeneration(p->pAstNode[0],lev+1,0,0);
    CodeGeneration(p->pAstNode[1],lev+1,0,0);
}

void ProcessClass(AstNode *p,int lev){

  switch(p->SymbolNode->accessor){

    case PRIVATE_ACC:
    fprintf(text,"private class %s.%s extends %s:\n",filename,p->SymbolNode->name,p->SymbolNode->base_class_name);
    break;
    case PUBLIC_ACC:
    fprintf(text,"public class %s.%s extends %s:\n",filename,p->SymbolNode->name,p->SymbolNode->base_class_name);
    break;
    //case ABSTRACT_ACC:
    //fprintf(text,"abstract class %s.%s extends %s:\n",filename,p->SymbolNode->name,p->SymbolNode->base_class_name);
    //break;
    //case FINAL_ACC:
    //fprintf(text,"final class %s.%s extends %s:\n",filename,p->SymbolNode->name,p->SymbolNode->base_class_name);
    //break;

  }

  CodeGeneration(p->pAstNode[0],lev+1,0,0);

  fprintf(text,"endclass\n\n");
}

void ProcessBodyClass(AstNode *p,int lev){

  CodeGeneration(p->pAstNode[0],lev+1,0,0);
  CodeGeneration(p->pAstNode[1],lev+1,0,0);
}

void ProcessFields(AstNode *p,int lev){

  CodeGeneration(p->pAstNode[0],lev+1,0,0);
  CodeGeneration(p->pAstNode[1],lev+1,0,0);
}

void ProcessEmptyFields(AstNode *p,int lev){
}

void ProcessField(AstNode *p,int lev){

  switch(p->SymbolNode->accessor){

    case PRIVATE_ACC:
      fprintf(text,"private");
    break;
    case PUBLIC_ACC:
      fprintf(text,"public");
    break;
  }

  switch(p->SymbolNode->typos){

    case INT:
      fprintf(text," I %s;\n",p->SymbolNode->name);
    break;
    case REAL:
      fprintf(text," D %s;\n",p->SymbolNode->name);
    break;
    case BOOL:
      fprintf(text," I %s;\n",p->SymbolNode->name);
    break;
    case STR:
      fprintf(text," S %s;\n",p->SymbolNode->name);
    break;
    default:
      fprintf(text," %s %s;\n",p->SymbolNode->nameclass,p->SymbolNode->name);
  }

  CodeGeneration(p->pAstNode[0],lev+1,0,0);
}

void ProcessFieldAssign(AstNode *p,int lev){


}

void ProcessAttrs(AstNode *p,int lev){

  switch(p->SymbolNode->accessor){

    case PRIVATE_ACC:
      fprintf(text,"private");
    break;
    case PUBLIC_ACC:
      fprintf(text,"public");
    break;
  }

  switch(p->SymbolNode->typos){

    case INT:
      fprintf(text," I %s;\n",p->SymbolNode->name);
    break;
    case REAL:
      fprintf(text," D %s;\n",p->SymbolNode->name);
    break;
    case BOOL:
      fprintf(text," I %s;\n",p->SymbolNode->name);
    break;
    case STR:
      fprintf(text," S %s;\n",p->SymbolNode->name);
    break;
    default:
      fprintf(text," %s %s;\n",p->SymbolNode->nameclass,p->SymbolNode->name);
  }

}

void ProcessAttrsAssign(AstNode *p,int lev){
}

void ProcessEmptyAttrs(AstNode *p,int lev){
}

void ProcessEmptyDef(AstNode *p,int lev){

}

void ProcessEmptyMethList(AstNode *p,int lev){

}

void ProcessMethList(AstNode *p,int lev){

  CodeGeneration(p->pAstNode[0],lev+1,0,0);
  CodeGeneration(p->pAstNode[1],lev+1,0,0);

}

void ProcessFuncLast(AstNode *p,int lev){

  BYTES_OF_PARAMETERS = 0;

  //Code Generation for parameters
	CodeGeneration(p->pAstNode[1],lev+1,0,0);

	//Method definition
	fprintf(data,"virtual V %s.%s();\n",filename,p->SymbolNode->name);
	//fprintf(text,"push ebp\n");
	//fprintf(text,"mov ebp,esp\n");
	//if(strcmp(p->SymbolNode->name,"main") == 0)
		//fprintf(text,"fldcw [cw]\n");


	//BYTES_OF_PARAMETERS = 4 * p->SymbolNode->dcl_ptr->num_params;

	//Code Generation for statements
	CodeGeneration(p->pAstNode[2],lev+1,0,1);

	fprintf(data,"\n\n");

}

//Methods
void ProcessMethSeq(AstNode*p, int lev){
   CodeGeneration(p->pAstNode[0],lev+1,0,0);
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
}

//Method
void ProcessMethLast(AstNode*p, int lev){

	BYTES_OF_PARAMETERS = 1;
  strcpy(CUR_METHOD_NAME,p->SymbolNode->name);
  IS_METHOD = 1;
  //Code Generation for parameters
	CodeGeneration(p->pAstNode[1],lev+1,0,0);

  switch(p->SymbolNode->accessor){

    case PRIVATE_ACC:
      fprintf(text,"private");
    break;
    case PUBLIC_ACC:
      fprintf(text,"public");
    break;
  }
  //Method definition
	fprintf(data," virtual V %s(R);\n",p->SymbolNode->name);


	//Code Generation for statements
	CodeGeneration(p->pAstNode[2],lev+1,0,1);

	fprintf(data,"\n\n");
  strcpy(CUR_METHOD_NAME, "");
  IS_METHOD = 0;
}

//Body
void ProcessBody(AstNode*p, int lev){
   CodeGeneration(p->pAstNode[0],lev+1,0,1);
}

//Statements
void ProcessStmtSeq(AstNode*p, int lev){
   CodeGeneration(p->pAstNode[0],lev+1,1,1);
   CodeGeneration(p->pAstNode[1],lev+1,1,1);
}
/*
//Library List
void ProcessLibList(AstNode *p, int lev, int leftChild){

	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	CodeGeneration(p->pAstNode[1],lev+1,0,0);



}*/
/*
//Library
void ProcessLib(AstNode *p, int lev, int leftChild){

	system("copy data.asm + text.asm program.asm");
	system("del data.asm");
	system("del text.asm");
	fprintf(text,"%%include \"%s\"\n",p->SymbolNode->name);
}
*/


void ProcessArrayIndex(AstNode *p, int lev){

  symbol *lhs;
  symbol *rhs;
  symbol *sn;

  CodeGeneration(p->pAstNode[0],lev+1,1,0);
  lhs = pop_vs();
  CodeGeneration(p->pAstNode[1],lev+1,0,0);
  rhs = pop_vs();

  sn = new_symbol("");
  sn->typos = lhs->typos;
  sn->sclass = MEMORY;

  push_vs(sn);
}

// Expr Statement
void ProcessExprStmt(AstNode *p, int lev, int lvalue,int leftChild){

	symbol *lhs;

	CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
	pop_vs();


}


// While Statement
void ProcessForStmt(AstNode *p, int lev, int lvalue,int leftChild)
{
   symbol *lhs, *rhs, *wh;
   int TEMP_TAG_WHILE;
   TAG_WHILES++;
   TEMP_TAG_WHILE= TAG_WHILES;


   //Code Generation for the iterable expression
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
   rhs=pop_vs();

   switch(rhs->typos){

     case STR:
        fprintf(text,"v_sconst \"\"\n");
     break;
   }


   /*Push a symbol to whiles stack, this helps
    'break' statements to recognize in which while-statement
   they belong to */
   if( rhs->sclass == MEMORY ){

       wh = new_symbol("");
       wh->timi = TEMP_TAG_WHILE;
       push_wh(wh);

       if(rhs->field == 0){
           fprintf(text,"sload_ %d\n", rhs->index);
         }
       else{
           fprintf(text,"rload_ 1\n");
           fprintf(text,"getfield %s\n",rhs->name);
         }

       //While definition
       fprintf(text,"label NAME=for%d:\n",TEMP_TAG_WHILE);

       fprintf(text,"try %d :\n",TEMP_TAG_WHILE);
       fprintf(text,"snext\n");
       fprintf(text,"sstore_ %d\n",p->SymbolNode->index);

    	 //Code Generation statements in while-loop
       CodeGeneration(p->pAstNode[1],lev+1,0,0);
    	 fprintf(text,"jmp for%d\n",TEMP_TAG_WHILE);
    	 fprintf(text,"except StopIterationException %d :\n", TEMP_TAG_WHILE);

    	 pop_wh();
     }

    else if( rhs->sclass == STACK ){

        wh = new_symbol("");
        wh->timi = TEMP_TAG_WHILE;
        push_wh(wh);

        //While definition
        fprintf(text,"label NAME=for%d:\n",TEMP_TAG_WHILE);

        fprintf(text,"try %d :\n",TEMP_TAG_WHILE);
        fprintf(text,"snext\n");
        fprintf(text,"sstore_ %d\n",p->SymbolNode->index);

        //Code Generation statements in while-loop
        CodeGeneration(p->pAstNode[1],lev+1,0,0);
        fprintf(text,"jmp for%d\n",TEMP_TAG_WHILE);
        fprintf(text,"except StopIterationException %d :\n", TEMP_TAG_WHILE);

      	 pop_wh();
       }
  else /* --- CONSTANT --- */
  {
     if( strlen(rhs->stimi) > 0 )
     {
           wh = new_symbol("");
           wh->timi = TEMP_TAG_WHILE;
           push_wh(wh);

          fprintf(text,"sconst \"%s\"\n", rhs->stimi);
           //While definition
           fprintf(text,"label NAME=for%d:\n",TEMP_TAG_WHILE);

           fprintf(text,"try %d :\n",TEMP_TAG_WHILE);
           fprintf(text,"snext\n");
           fprintf(text,"sstore_ %d\n",p->SymbolNode->index);

          //Code Generation statements in while-loop
           CodeGeneration(p->pAstNode[1],lev+1,0,0);
          fprintf(text,"jmp for%d\n",TEMP_TAG_WHILE);
          fprintf(text,"except StopIterationException %d :\n", TEMP_TAG_WHILE);

          pop_wh();
     }

   }

}

// While Statement
void ProcessWhileStmt(AstNode *p, int lev, int lvalue,int leftChild)
{
   symbol *rhs, *wh;
   int TEMP_TAG_WHILE;
   TAG_WHILES++;
   TEMP_TAG_WHILE= TAG_WHILES;

   //While definition
   fprintf(text,"label NAME=while%d:\n",TEMP_TAG_WHILE);

   //Code Generation for the logical expression
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
   rhs=pop_vs();

   if(rhs->typos != BOOL){

	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",rhs->typos);
	   exit(1);

   }

   /*Push a symbol to whiles stack, this helps
    'break' statements to recognize in which while-statement
   they belong to */
   if( rhs->sclass == MEMORY ){

       wh = new_symbol("");
       wh->timi = TEMP_TAG_WHILE;
       push_wh(wh);
       if(rhs->field == 0){
           fprintf(text,"iload_ %d\n", rhs->index);
         }
       else{
           fprintf(text,"rload_ 1\n");
           fprintf(text,"getfield %s\n",rhs->name);
        }

       fprintf(text,"ifzero endwhile%d\n",TEMP_TAG_WHILE);

    	 //Code Generation statements in while-loop
       CodeGeneration(p->pAstNode[1],lev+1,0,0);
    	 fprintf(text,"jmp while%d\n",TEMP_TAG_WHILE);
    	 fprintf(text,"label NAME=endwhile%d:\n", TEMP_TAG_WHILE);

    	 pop_wh();
     }

    else if( rhs->sclass == STACK ){

         wh = new_symbol("");
         wh->timi = TEMP_TAG_WHILE;
         push_wh(wh);

         fprintf(text,"ifzero endwhile%d\n",TEMP_TAG_WHILE);

      	 //Code Generation statements in while-loop
         CodeGeneration(p->pAstNode[1],lev+1,0,0);
      	 fprintf(text,"jmp while%d\n",TEMP_TAG_WHILE);
      	 fprintf(text,"label NAME=endwhile%d:\n", TEMP_TAG_WHILE);

      	 pop_wh();
       }
  else /* --- CONSTANT --- */
  {
     if( rhs->timi != 0 )
     {
          wh = new_symbol("");
          wh->timi = TEMP_TAG_WHILE;
          push_wh(wh);

          CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);

          fprintf(text,"jmp while%d\n",TEMP_TAG_WHILE);
          fprintf(text,"label NAME=endwhile%d:\n", TEMP_TAG_WHILE);

          pop_wh();
     }

   }

}

//Dec Constant (Integer)
void ProcessDeConst(AstNode *p)
{
   push_vs(p->SymbolNode);
}

//Real Dec Constant (Real)
void ProcessRealDeConst(AstNode *p)
{

   push_vs(p->SymbolNode);
}

//String
void ProcessString(AstNode *p)
{

   push_vs(p->SymbolNode);
}


// Times Statement
void ProcessTimesStmt(AstNode *p, int lev, int lvalue,int leftChild)
{
   symbol *lhs, *rhs, *wh;
   int TEMP_TAG_WHILE;
   TAG_WHILES++;
   TEMP_TAG_WHILE= TAG_WHILES;

   CodeGeneration(p->pAstNode[0],lev+1,0,0);
   lhs = pop_vs();

   if(lhs->typos != INT){

	   printf("Incompatible_Types_Error: The counter of times statement must be integer",lhs->typos);
	   exit(1);

   }

   if( lhs->sclass == MEMORY ){

	   /*Push a symbol to whiles stack, this helps
	    'break' statements to recognize in which while-statement
		they belong to */

	   wh = new_symbol("");
	   wh->timi = TEMP_TAG_WHILE;
	   push_wh(wh);

	   //fprintf(data,"COUNTER_%d dd  %d\n",TEMP_TAG_WHILE,lhs->timi);
		 //fprintf(text,"mov ecx,[COUNTER_%d]\n",TEMP_TAG_WHILE);
		// fprintf(text,"mov ecx, [%s]\n",lhs->pseudonym);
    if(lhs->field == 0){
        fprintf(text,"iload_ %d\n", lhs->index);
      }
    else{
        fprintf(text,"rload_ 1\n");
        fprintf(text,"getfield %s\n",lhs->name);
      }

		 //While definition
		 fprintf(text,"label NAME=while%d:\n",TEMP_TAG_WHILE);

		 //Code Generation for the logical expression
     fprintf(text,"dup 2\n");
		 fprintf(text,"ifzero endwhile%d\n",TEMP_TAG_WHILE);
		// fprintf(text,"push ecx\n");

         CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);

		 //fprintf(text,"pop ecx\n");
		 fprintf(text,"dec\n");

		 fprintf(text,"jmp while%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"label NAME=endwhile%d:\n", TEMP_TAG_WHILE);
     fprintf(text,"pop\n");
		 pop_wh();
   }
   else if( lhs->sclass == STACK ){

	   /*Push a symbol to whiles stack, this helps
	    'break' statements to recognize in which while-statement
		they belong to */

	   wh = new_symbol("");
	   wh->timi = TEMP_TAG_WHILE;
	   push_wh(wh);

	   //fprintf(data,"COUNTER_%d dd  %d\n",TEMP_TAG_WHILE,lhs->timi);
		 //fprintf(text,"mov ecx,[COUNTER_%d]\n",TEMP_TAG_WHILE);
		// fprintf(text,"mov ecx, [%s]\n",lhs->pseudonym);

		 //While definition
		 fprintf(text,"label NAME=while%d:\n",TEMP_TAG_WHILE);

		 //Code Generation for the logical expression
     fprintf(text,"dup 2\n");
		 fprintf(text,"ifzero endwhile%d\n",TEMP_TAG_WHILE);
		// fprintf(text,"push ecx\n");

         CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);

		 //fprintf(text,"pop ecx\n");
		 fprintf(text,"dec\n");

		 fprintf(text,"jmp while%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"label NAME=endwhile%d:\n", TEMP_TAG_WHILE);
     fprintf(text,"pop\n");
		 pop_wh();
   }
   else if( lhs->timi != 0 ){

		 wh = new_symbol("");
	   wh->timi = TEMP_TAG_WHILE;
	   push_wh(wh);

		 //fprintf(data,"COUNTER_%d dd  %d\n",TEMP_TAG_WHILE,lhs->timi);
		 //fprintf(text,"mov ecx,[COUNTER_%d]\n",TEMP_TAG_WHILE);
		 //fprintf(text,"mov ecx, %d\n",lhs->timi);
     fprintf(text,"iconst %d\n", lhs->timi);
		 //While definition
		 fprintf(text,"label NAME=while%d:\n",TEMP_TAG_WHILE);

		 //Code Generation for the logical expression
     fprintf(text,"dup 2\n");
		 fprintf(text,"ifzero endwhile%d\n",TEMP_TAG_WHILE);
		 //fprintf(text,"push ecx\n");

     CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);

		 //fprintf(text,"pop ecx\n");
		 fprintf(text,"dec\n");

		 fprintf(text,"jmp while%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"label NAME=endwhile%d:\n", TEMP_TAG_WHILE);
     fprintf(text,"pop\n");
		 pop_wh();
   }


}

// If Statement
 void ProcessIfStmt(AstNode*p,int lev, int lvalue,int leftChild){

	 symbol *lhs;
	 int TEMP_TAG_IF;
	 CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
	 lhs = pop_vs();

	 if(lhs->typos != BOOL){

	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",lhs->typos);
	   exit(1);

    }


   if( lhs->sclass == MEMORY ){

     TAG_IFS++;
		 TEMP_TAG_IF = TAG_IFS;

     if(lhs->field == 0){
          fprintf(text,"iload_ %d\n", lhs->index);
       }
     else{
         fprintf(text,"rload_ 1\n");
         fprintf(text,"getfield %s\n",lhs->name);
       }

		 fprintf(text,"ifzero endif%d\n",TEMP_TAG_IF);

		 //Code Generation for true
		 CodeGeneration(p->pAstNode[1],lev+1,lvalue,1);

		 //End
		 fprintf(text,"label NAME=endif%d:\n",TEMP_TAG_IF);

   }
   else if( lhs->sclass == STACK ){

      TAG_IFS++;
 		 TEMP_TAG_IF = TAG_IFS;


 		 fprintf(text,"ifzero endif%d\n",TEMP_TAG_IF);

 		 //Code Generation for true
 		 CodeGeneration(p->pAstNode[1],lev+1,lvalue,1);

 		 //End
 		 fprintf(text,"label NAME=endif%d:\n",TEMP_TAG_IF);

    }
   else { /*-- CONSTANT --*/

		  if( lhs->timi != 0 ){

				CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
			  }


		 }

 }


// If-else Statement
 void ProcessIfElseStmt(AstNode*p,int lev, int lvalue,int leftChild){

	 symbol *lhs;
	 int TEMP_TAG_IF;
	 CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
	 lhs = pop_vs();

     if(lhs->typos != BOOL){

	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",lhs->typos);
	   exit(1);

    }

  if( lhs->sclass == MEMORY ){

		  TAG_IFS++;
		  TEMP_TAG_IF = TAG_IFS;

      if(lhs->field == 0){
           fprintf(text,"iload_ %d\n", lhs->index);
        }
      else{
          fprintf(text,"rload_ 1\n");
          fprintf(text,"getfield %s\n",lhs->name);
        }


		 // fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
		  fprintf(text,"ifzero else%d\n",TEMP_TAG_IF);

		  //Code Generation for true
		  CodeGeneration(p->pAstNode[1],lev+1,lvalue,1);
		  fprintf(text,"jmp endif%d\n",TEMP_TAG_IF);
		  fprintf(text,"label NAME=else%d:\n", TEMP_TAG_IF);

		  //Code Generation for false
		  CodeGeneration(p->pAstNode[2],lev+1,lvalue,1);

		   //End
		  fprintf(text,"label NAME=endif%d:\n",TEMP_TAG_IF);

		  }
  else if( lhs->sclass == STACK ){

    		  TAG_IFS++;
    		  TEMP_TAG_IF = TAG_IFS;

    		 // fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
    		  fprintf(text,"ifzero else%d\n",TEMP_TAG_IF);

    		  //Code Generation for true
    		  CodeGeneration(p->pAstNode[1],lev+1,lvalue,1);
    		  fprintf(text,"jmp endif%d\n",TEMP_TAG_IF);
    		  fprintf(text,"label NAME=else%d:\n", TEMP_TAG_IF);

    		  //Code Generation for false
    		  CodeGeneration(p->pAstNode[2],lev+1,lvalue,1);

    		   //End
    		  fprintf(text,"label NAME=endif%d:\n",TEMP_TAG_IF);

    		  }
	else {

		  if( lhs->timi != 0 ){

				CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
			  }
		  else{

				CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);

			  }

		 }

 }

 // Single If Statement
 void ProcessSingleIfStmt(AstNode*p,int lev, int lvalue,int leftChild){

	 symbol *lhs;
	 int TEMP_TAG_IF;
	 CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
	 lhs = pop_vs();

	  if(lhs->typos != BOOL){

	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",lhs->typos);
	   exit(1);

    }

	 if( lhs->sclass == MEMORY ){

		  TAG_IFS++;
		  TEMP_TAG_IF = TAG_IFS;

      if(lhs->field == 0){
           fprintf(text,"iload_ %d\n", lhs->index);
        }
      else{
          fprintf(text,"rload_ 1\n");
          fprintf(text,"getfield %s\n",lhs->name);
        }

		  //fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
		  fprintf(text,"ifzero endif%d\n",TEMP_TAG_IF);

		  //Code Generation for true
		  CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);

		   //End
		  fprintf(text,"label NAME=endif%d:\n",TEMP_TAG_IF);

		  }
    else if( lhs->sclass == STACK ){

         TAG_IFS++;
         TEMP_TAG_IF = TAG_IFS;

         //fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
         fprintf(text,"ifzero endif%d\n",TEMP_TAG_IF);

         //Code Generation for true
         CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);

          //End
         fprintf(text,"label NAME=endif%d:\n",TEMP_TAG_IF);

         }
	else {

		  if( lhs->timi != 0 ){

				CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
			  }


	 }

 }

 // Single Unless Statement
 void ProcessSingleUnlessStmt(AstNode*p,int lev, int lvalue,int leftChild){

	 symbol *lhs;
	 int TEMP_TAG_IF;
	 CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
	 lhs = pop_vs();

	 if(lhs->typos != BOOL){

	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",lhs->typos);
	   exit(1);

   }

	if( lhs->sclass == MEMORY ){

		  TAG_IFS++;
		  TEMP_TAG_IF = TAG_IFS;

      if(lhs->field == 0){
           fprintf(text,"iload_ %d\n", lhs->index);
        }
      else{
          fprintf(text,"rload_ 1\n");
          fprintf(text,"getfield %s\n",lhs->name);
      }

		  //fprintf(text,"cmp ecx,0\n");
		  fprintf(text,"ifnotzero endif%d\n",TEMP_TAG_IF);

		  //Code Generation for true
		  CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);

		   //End
		  fprintf(text,"label NAME=endif%d:\n",TEMP_TAG_IF);

		  }
  else if( lhs->sclass == STACK ){

		  TAG_IFS++;
		  TEMP_TAG_IF = TAG_IFS;

		  //fprintf(text,"cmp ecx,0\n");
		  fprintf(text,"ifnotzero endif%d\n",TEMP_TAG_IF);

		  //Code Generation for true
		  CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);

		   //End
		  fprintf(text,"label NAME=endif%d:\n",TEMP_TAG_IF);

		  }
	else {

		  if( lhs->timi == 0 ){

				CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
			  }


	 }

 }



 //Assign Statement
void ProcessAssign(AstNode*p, int lev,int leftChild){

   symbol *rhs,*lhs;

   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);

   lhs = pop_vs();
   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
   rhs = pop_vs();

   switch(lhs->sclass)
	   {
		  case MEMORY:

			  switch(lhs->typos){

					case INT:

							 switch(rhs->typos){

									case INT:

											   if(rhs->sclass == MEMORY){

      													if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {


                                  if(lhs->field == 0){
                                      if(rhs->field == 0){
                                        fprintf(text,"iload_ %d\n",rhs->index);
                                      }
                                      else {
                                        fprintf(text,"rload_ 1\n");
                                        fprintf(text,"getfield %s\n",rhs->name);
                                      }

      														    fprintf(text,"istore_ %d\n",lhs->index);
                                    }
                                  else{
                                      if(rhs->field == 0){
                                        fprintf(text,"iload_ %d\n",rhs->index);
                                      }
                                      else {
                                        fprintf(text,"rload_ 1\n");
                                        fprintf(text,"getfield %s\n",rhs->name);
                                      }

                                      fprintf(text,"rload_ 1\n");
                                      fprintf(text,"putfield %s\n",lhs->name);
                                    }


      													}

												 }
                         else if(rhs->sclass == STACK){

                              if(lhs->field == 0){
                                  fprintf(text,"istore_ %d\n",lhs->index);
                                }
                              else{
                                  fprintf(text,"rload_ 1\n");
                                  fprintf(text,"putfield %s\n",lhs->name);
                                }

  												 }
											   else if(rhs->sclass == CONSTANT) {

                           if(lhs->field == 0){
                                  fprintf(text,"iconst %d\n",rhs->timi);
                                  fprintf(text,"istore_ %d\n",lhs->index);
                             }
                           else{
                               fprintf(text,"iconst %d\n",rhs->timi);
                               fprintf(text,"rload_ 1\n");
                               fprintf(text,"putfield %s\n",lhs->name);
                             }



												 }
									break;
									case REAL:
													 if(rhs->sclass == MEMORY){

                             if(lhs->field == 0){
                                 if(rhs->field == 0){
                                   fprintf(text,"dload_ %d\n",rhs->index);
                                 }
                                 else {
                                   fprintf(text,"rload_ 1\n");
                                   fprintf(text,"getfield %s\n",rhs->name);
                                 }
                                 fprintf(text,"d2i\n");
                                 fprintf(text,"istore_ %d\n",lhs->index);
                               }
                             else{
                                 if(rhs->field == 0){
                                   fprintf(text,"dload_ %d\n",rhs->index);
                                 }
                                 else {
                                   fprintf(text,"rload_ 1\n");
                                   fprintf(text,"getfield %s\n",rhs->name);
                                 }

                                 fprintf(text,"d2i\n");
                                 fprintf(text,"rload_ 1\n");
                                 fprintf(text,"putfield %s\n",lhs->name);
                               }

														 }
                           else if(rhs->sclass == STACK){

                               fprintf(text,"d2i\n");
                               fprintf(text,"istore_ %d\n",lhs->index);

                              }
													 else if(rhs->sclass == CONSTANT) {

														  fprintf(data,"iconst %d\n",NUM_OF_REAL_CONST,rhs->dtimi);
															fprintf(text,"istore_ %d\n",lhs->index);

														 }
									break;
									case BOOL:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;
							 }
					break;
					case REAL:

							switch(rhs->typos){

											case INT:

                          if(rhs->sclass == MEMORY){

                            if(lhs->field == 0){
                                if(rhs->field == 0){
                                  fprintf(text,"iload_ %d\n",rhs->index);
                                }
                                else {
                                  fprintf(text,"rload_ 1\n");
                                  fprintf(text,"getfield %s\n",rhs->name);
                                }
                                fprintf(text,"i2d\n");
                                fprintf(text,"dstore_ %d\n",lhs->index);
                              }
                            else{
                                if(rhs->field == 0){
                                  fprintf(text,"iload_ %d\n",rhs->index);
                                }
                                else {
                                  fprintf(text,"rload_ 1\n");
                                  fprintf(text,"getfield %s\n",rhs->name);
                                }

                                fprintf(text,"i2d\n");
                                fprintf(text,"rload_ 1\n");
                                fprintf(text,"putfield %s\n",lhs->name);
                              }

                            }
                          else if(rhs->sclass == STACK){

                                 fprintf(text,"i2d\n");
                                 fprintf(text,"dstore_ %d\n",lhs->index);

                              }
                          else if(rhs->sclass == CONSTANT) {

                             fprintf(text,"dconst %f\n",rhs->timi);
                             fprintf(text,"dstore_ %d\n",lhs->index);


                            }
											break;
											case REAL:

                          if(rhs->sclass == MEMORY){

                             if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {


                                 if(lhs->field == 0){
                                     if(rhs->field == 0){
                                       fprintf(text,"dload_ %d\n",rhs->index);
                                     }
                                     else {
                                       fprintf(text,"rload_ 1\n");
                                       fprintf(text,"getfield %s\n",rhs->name);
                                     }

                                     fprintf(text,"dstore_ %d\n",lhs->index);
                                   }
                                 else{
                                     if(rhs->field == 0){
                                       fprintf(text,"dload_ %d\n",rhs->index);
                                     }
                                     else {
                                       fprintf(text,"rload_ 1\n");
                                       fprintf(text,"getfield %s\n",rhs->name);
                                     }

                                     fprintf(text,"rload_ 1\n");
                                     fprintf(text,"putfield %s\n",lhs->name);
                                   }



                             }

                            }
                          else if(rhs->sclass == STACK){

                               fprintf(text,"dstore_ %d\n",lhs->index);

                            }
                          else if(rhs->sclass == CONSTANT) {

                             fprintf(text,"dconst %lf\n",rhs->dtimi);
                             fprintf(text,"dstore_ %d\n",lhs->index);


                            }
											break;
											case BOOL:
  												printf("Error: bad operand types for binary operator \n");
  												exit(1);
											break;
									 }
					break;
					case BOOL:

					   switch(rhs->typos){
								case INT:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
								case REAL:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
								case BOOL:

                    if(rhs->sclass == MEMORY){

                       if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {

                         if(lhs->field == 0){
                             if(rhs->field == 0){
                               fprintf(text,"iload_ %d\n",rhs->index);
                             }
                             else {
                               fprintf(text,"rload_ 1\n");
                               fprintf(text,"getfield %s\n",rhs->name);
                             }

                             fprintf(text,"istore_ %d\n",lhs->index);
                           }
                         else{
                             if(rhs->field == 0){
                               fprintf(text,"iload_ %d\n",rhs->index);
                             }
                             else {
                               fprintf(text,"rload_ 1\n");
                               fprintf(text,"getfield %s\n",rhs->name);
                             }

                             fprintf(text,"rload_ 1\n");
                             fprintf(text,"putfield %s\n",lhs->name);
                           }

                       }

                      }
                    else if(rhs->sclass == STACK){

                         fprintf(text,"istore_ %d\n",lhs->index);

                      }
                    else if(rhs->sclass == CONSTANT) {

                       fprintf(text,"iconst %d\n",rhs->timi);
                       fprintf(text,"istore_ %d\n",lhs->index);


                      }

								break;
					   }

					break;
          case STR:

               switch(rhs->typos){

                  case STR:

                         if(rhs->sclass == MEMORY){

                                if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {

                                  if(lhs->field == 0){
                                      if(rhs->field == 0){
                                        fprintf(text,"sload_ %d\n",rhs->index);
                                      }
                                      else {
                                        fprintf(text,"rload_ 1\n");
                                        fprintf(text,"getfield %s\n",rhs->name);
                                      }

      														    fprintf(text,"sstore_ %d\n",lhs->index);
                                    }
                                  else{
                                      if(rhs->field == 0){
                                        fprintf(text,"sload_ %d\n",rhs->index);
                                      }
                                      else {
                                        fprintf(text,"rload_ 1\n");
                                        fprintf(text,"getfield %s\n",rhs->name);
                                      }

                                      fprintf(text,"rload_ 1\n");
                                      fprintf(text,"putfield %s\n",lhs->name);
                                    }

                                }

                         }
                         else if(rhs->sclass == STACK){

                              fprintf(text,"sstore_ %d\n",lhs->index);

                           }
                         else if(rhs->sclass == CONSTANT) {

                          fprintf(text,"sconst \"%s\"\n",rhs->stimi);
                          fprintf(text,"sstore_ %d\n",lhs->index);


                         }
                  break;
                  case INT:
                      printf("Error: bad operand types for binary operator \n");
                      exit(1);
                  break;
                  case REAL:
                      printf("Error: bad operand types for binary operator \n");
                      exit(1);
                  break;
                  case BOOL:
                      printf("Error: bad operand types for binary operator \n");
                      exit(1);
                  break;
               }
          break;
          default:

               switch(rhs->typos){

                  case INT:
                      printf("Error: bad operand types for binary operator \n");
                      exit(1);
                  break;
                  case REAL:
                      printf("Error: bad operand types for binary operator \n");
                      exit(1);
                  break;
                  case BOOL:
                      printf("Error: bad operand types for binary operator \n");
                      exit(1);
                  break;
                  case STR:
                      printf("Error: bad operand types for binary operator \n");
                      exit(1);
                  break;
                  default:

                         if(rhs->sclass == MEMORY){

                                if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {

                                  if(lhs->field == 0){
                                      if(rhs->field == 0){
                                        fprintf(text,"rload_ %d\n",rhs->index);
                                      }
                                      else {
                                        fprintf(text,"rload_ 1\n");
                                        fprintf(text,"getfield %s\n",rhs->name);
                                      }

      														    fprintf(text,"rstore_ %d\n",lhs->index);
                                    }
                                  else{
                                      if(rhs->field == 0){
                                        fprintf(text,"rload_ %d\n",rhs->index);
                                      }
                                      else {
                                        fprintf(text,"rload_ 1\n");
                                        fprintf(text,"getfield %s\n",rhs->name);
                                      }

                                      fprintf(text,"rload_ 1\n");
                                      fprintf(text,"putfield %s\n",lhs->name);
                                    }

                                }

                         }
                         else if(rhs->sclass == STACK){

                           if(lhs->field == 0){

                               fprintf(text,"rstore_ %d\n",lhs->index);
                             }
                           else{

                               fprintf(text,"rload_ 1\n");
                               fprintf(text,"putfield %s\n",lhs->name);
                             }

                           }
                         else if(rhs->sclass == CONSTANT) {

                           if(lhs->field == 0){

                               fprintf(text,"rstore_ %d\n",lhs->index);
                             }
                           else{

                               fprintf(text,"rload_ 1\n");
                               fprintf(text,"putfield %s\n",lhs->name);
                             }


                         }
                break;
               }
          break;
			    }
      break;
		  case CONSTANT:
			 fprintf(text,"ERROR ASSIGN[CONSTANT-]");
		  break;
		  case REGISTER:
			 fprintf(text,"ERROR ASSIGN[REGISTER-]");
		  break;
		  case STACK:
			 fprintf(text,"ERROR ASSIGN[STACK-]");
		  break;
	   }

	push_vs(lhs);
	push_vs(rhs);

}

void ProcessUniqueAssign(AstNode*p, int lev,int leftChild){

	symbol *lhs , *rhs;

	ProcessAssign(p,lev,leftChild);
	rhs = pop_vs();
	lhs = pop_vs();

	switch(rhs->typos){

		case INT:
				switch(lhs->typos){

					case INT:
						//Nothing to pop
					break;
					case REAL:
						//fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}

		break;
		case REAL:
			switch(lhs->typos){

					case INT:
						//fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case REAL:
						//fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}

		break;
		case BOOL:
				switch(lhs->typos){

					case INT:
						//Nothing to pop
					break;
					case REAL:
						//Nothing to pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}

		break;


	}


}



//Add Assign Statement
void ProcessAddAssign(AstNode*p, int lev,int leftChild){

   symbol *rhs,*lhs;

   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();

   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
   rhs = pop_vs();


   switch(lhs->sclass)
	   {
		  case MEMORY:
				switch(lhs->typos) {

					case INT:
							switch(rhs->typos){

								case INT:
										 if(rhs->sclass == MEMORY){


													fprintf(text,"iload_ %d\n",lhs->index);
													fprintf(text,"iload_ %d\n",rhs->index);
                          fprintf(text,"iadd\n");
													fprintf(text,"istore_ %d\n",lhs->index);


											 }
										 else if(rhs->sclass == CONSTANT) {

                       fprintf(text,"iload_ %d\n",lhs->index);
                       fprintf(text,"iconst %d\n",rhs->timi);
                       fprintf(text,"iadd\n");
                       fprintf(text,"istore_ %d\n",lhs->index);

											 }
										 else if(rhs->sclass == STACK)
											 {
                         fprintf(text,"iload_ %d\n",lhs->index);
                         fprintf(text,"iadd\n");
                         fprintf(text,"istore_ %d\n",lhs->index);

											 }
								break;
								case REAL:

                        if(rhs->sclass == MEMORY){


                              fprintf(text,"iload_ %d\n",lhs->index);
                              fprintf(text,"i2d\n");
                              fprintf(text,"dload_ %d\n",rhs->index);
                              fprintf(text,"dadd\n");
                              fprintf(text,"d2i\n");
                              fprintf(text,"istore_ %d\n",lhs->index);


                           }
                         else if(rhs->sclass == CONSTANT) {

                               fprintf(text,"iload_ %d\n",lhs->index);
                               fprintf(text,"i2d\n");
                               fprintf(text,"dconst %lf\n",rhs->dtimi);
                               fprintf(text,"dadd\n");
                               fprintf(text,"d2i\n");
                               fprintf(text,"istore_ %d\n",lhs->index);

                           }
                         else if(rhs->sclass == STACK)
                           {

                              printf(text,"ERROR ADDASSIGN [RIGHT-STACK]\n");


                           }
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

						switch(rhs->typos){

									case INT:

                      if(rhs->sclass == MEMORY){


                            fprintf(text,"dload_ %d\n",lhs->index);
                            fprintf(text,"iload_ %d\n",rhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"dadd\n");
                            fprintf(text,"dstore_ %d\n",lhs->index);


                         }
                       else if(rhs->sclass == CONSTANT) {

                          fprintf(text,"dload_ %d\n",lhs->index);
                          fprintf(text,"dconst %d\n",rhs->timi);
                          fprintf(text,"dadd\n");
                          fprintf(text,"dstore_ %d\n",lhs->index);

                         }
                       else if(rhs->sclass == STACK)
                         {
                            printf(text,"ERROR ADDASSIGN [RIGHT-STACK]\n");

                         }
									break;
									case REAL:

                        if(rhs->sclass == MEMORY){


                              fprintf(text,"dload_ %d\n",lhs->index);
                              fprintf(text,"dload_ %d\n",rhs->index);
                              fprintf(text,"dadd\n");
                              fprintf(text,"dstore_ %d\n",lhs->index);


                           }
                         else if(rhs->sclass == CONSTANT) {

                               fprintf(text,"dload_ %d\n",lhs->index);
                               fprintf(text,"dconst %lf\n",rhs->dtimi);
                               fprintf(text,"dadd\n");
                               fprintf(text,"dstore_ %d\n",lhs->index);

                           }
                         else if(rhs->sclass == STACK)
                           {
                              fprintf(text,"dload_ %d\n",lhs->index);
                              fprintf(text,"dadd\n");
                              fprintf(text,"dstore_ %d\n",lhs->index);

                           }
									break;
                  case STR:
                    printf("Error: bad operand types for binary operator \n");
                    exit(1);
									break;
									case BOOL:
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

						switch(rhs->typos){

									case INT:
                      printf("Error: bad operand types for binary operator \n");
                      exit(1);
									break;
									case REAL:
                      printf("Error: bad operand types for binary operator \n");
                      exit(1);
									break;
                  case STR:

                      if(rhs->sclass == MEMORY){


                            fprintf(text,"sload_ %d\n",lhs->index);
                            fprintf(text,"sload_ %d\n",rhs->index);
                            fprintf(text,"sadd\n");
                            fprintf(text,"sstore_ %d\n",lhs->index);


                         }
                       else if(rhs->sclass == CONSTANT) {

                          fprintf(text,"sload_ %d\n",lhs->index);
                          fprintf(text,"sconst \"%s\"\n",rhs->stimi);
                          fprintf(text,"sadd\n");
                          fprintf(text,"sstore_ %d\n",lhs->index);

                         }
                       else if(rhs->sclass == STACK)
                         {
                            printf(text,"ERROR ADDASSIGN [RIGHT-STACK]\n");

                         }
									break;
									case BOOL:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;
								}
					break;
				}
		  break;
		  case CONSTANT:
			 fprintf(text,"ERROR ADDASSIGN[CONSTANT-]");
		  break;
		  case REGISTER:
			 fprintf(text,"ERROR ADDASSIGN[REGISTER-]");
		  break;
		  case STACK:
			 fprintf(text,"ERROR ADDASSIGN[STACK-]");
		  break;
	   }



}

//Sub Assign Statement
void ProcessSubAssign(AstNode*p, int lev,int leftChild){

   symbol *rhs,*lhs;

   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();

   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
   rhs = pop_vs();


   switch(lhs->sclass)
	   {
		  case MEMORY:
				switch(lhs->typos) {

					case INT:
							switch(rhs->typos){

								case INT:
										 if(rhs->sclass == MEMORY){


													fprintf(text,"iload_ %d\n",lhs->index);
													fprintf(text,"iload_ %d\n",rhs->index);
                          fprintf(text,"isub\n");
													fprintf(text,"istore_ %d\n",lhs->index);


											 }
										 else if(rhs->sclass == CONSTANT) {

                       fprintf(text,"iload_ %d\n",lhs->index);
                       fprintf(text,"iconst %d\n",rhs->timi);
                       fprintf(text,"isub\n");
                       fprintf(text,"istore_ %d\n",lhs->index);

											 }
										 else if(rhs->sclass == STACK)
											 {
                         //fprintf(text,"iload_ %d\n",lhs->index);
                         //fprintf(text,"isub\n");
                         //fprintf(text,"istore_ %d\n",lhs->index);
                         printf("MEMORY-STACK ERROR");
                         exit(1);
											 }
								break;
								case REAL:

                        if(rhs->sclass == MEMORY){


                              fprintf(text,"iload_ %d\n",lhs->index);
                              fprintf(text,"i2d\n");
                              fprintf(text,"dload_ %d\n",rhs->index);
                              fprintf(text,"dsub\n");
                              fprintf(text,"d2i\n");
                              fprintf(text,"istore_ %d\n",lhs->index);


                           }
                         else if(rhs->sclass == CONSTANT) {

                               fprintf(text,"iload_ %d\n",lhs->index);
                               fprintf(text,"i2d\n");
                               fprintf(text,"dconst %lf\n",rhs->dtimi);
                               fprintf(text,"dsub\n");
                               fprintf(text,"d2i\n");
                               fprintf(text,"istore_ %d\n",lhs->index);

                           }
                         else if(rhs->sclass == STACK)
                           {
                              //fprintf(text,"iload_ %d\n",lhs->index);
                              //fprintf(text,"dsub\n");
                              //fprintf(text,"d2i\n");
                              //fprintf(text,"istore_ %d\n",lhs->index);
                              printf("MEMORY-STACK ERROR");
                              exit(1);
                           }
								break;
								case BOOL:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
							}
					break;
					case REAL:

						switch(rhs->typos){

									case INT:

                      if(rhs->sclass == MEMORY){


                            fprintf(text,"dload_ %d\n",lhs->index);
                            fprintf(text,"iload_ %d\n",rhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"dsub\n");
                            fprintf(text,"dstore_ %d\n",lhs->index);


                         }
                       else if(rhs->sclass == CONSTANT) {

                          fprintf(text,"dload_ %d\n",lhs->index);
                          fprintf(text,"dconst %d\n",rhs->timi);
                          fprintf(text,"dsub\n");
                          fprintf(text,"dstore_ %d\n",lhs->index);

                         }
                       else if(rhs->sclass == STACK)
                         {
                            //fprintf(text,"dload_ %d\n",lhs->index);
                            //fprintf(text,"dsub\n");
                            //fprintf(text,"dstore_ %d\n",lhs->index);
                            printf("MEMORY-STACK ERROR");
                            exit(1);

                         }
									break;
									case REAL:

                        if(rhs->sclass == MEMORY){


                              fprintf(text,"dload_ %d\n",lhs->index);
                              fprintf(text,"dload_ %d\n",rhs->index);
                              fprintf(text,"dsub\n");
                              fprintf(text,"dstore_ %d\n",lhs->index);


                           }
                         else if(rhs->sclass == CONSTANT) {

                               fprintf(text,"dload_ %d\n",lhs->index);
                               fprintf(text,"dconst %lf\n",rhs->dtimi);
                               fprintf(text,"dsub\n");
                               fprintf(text,"dstore_ %d\n",lhs->index);

                           }
                         else if(rhs->sclass == STACK)
                           {
                              //fprintf(text,"dload_ %d\n",lhs->index);
                              //fprintf(text,"dsub\n");
                              //fprintf(text,"dstore_ %d\n",lhs->index);
                              printf("MEMORY-STACK ERROR");
                              exit(1);
                           }
									break;
									case BOOL:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;
								}
					break;
					case BOOL:
							printf("Error: bad operand types for binary operator \n");
							exit(1);
					break;
				}
		  break;
		  case CONSTANT:
			 fprintf(text,"ERROR ADDASSIGN[CONSTANT-]");
		  break;
		  case REGISTER:
			 fprintf(text,"ERROR ADDASSIGN[REGISTER-]");
		  break;
		  case STACK:
			 fprintf(text,"ERROR ADDASSIGN[STACK-]");
		  break;
	   }



}

//Increase after
void ProcessIncreaseAfter(AstNode* p, int lev, int lvalue,int leftChild){

	symbol *lhs;

	CodeGeneration(p->pAstNode[0],lev+1,0,0); // Location
	lhs = pop_vs();


	if (lhs->sclass == MEMORY){

		lhs->sclass = STACK;

		fprintf(text,"iload_ %d\n", lhs->index);
    fprintf(text,"iload_ %d\n", lhs->index);
    //fprintf(text,"dup 2\n");
    fprintf(text,"inc\n");
		fprintf(text,"istore_ %d\n", lhs->index);

	}

  if(lvalue){
    fprintf(text,"pop\n");
  }

	push_vs(lhs);

}

//Increase Before
void ProcessIncreaseBefore(AstNode* p, int lev,int lvalue, int leftChild){

	symbol *lhs;

	CodeGeneration(p->pAstNode[0],lev+1,0,0); // Location
	lhs = pop_vs();


  	if (lhs->sclass == MEMORY){

  		lhs->sclass = STACK;

  		fprintf(text, "iload_ %d\n", lhs->index);
      fprintf(text,"inc\n");
      fprintf(text, "dup 2\n");
  		fprintf(text, "istore_ %d\n", lhs->index);

  	}

    if(lvalue){
      fprintf(text,"pop\n");
    }

	push_vs(lhs);

}

//Decrease after
void ProcessDecreaseAfter(AstNode* p, int lev,int lvalue, int leftChild){

	symbol *lhs;

	CodeGeneration(p->pAstNode[0],lev+1,0,0); // Location
	lhs = pop_vs();


  if (lhs->sclass == MEMORY){

		lhs->sclass = STACK;

		fprintf(text,"iload_ %d\n", lhs->index);
    fprintf(text,"dup 2\n");
    fprintf(text,"dec\n");
		fprintf(text,"istore_ %d\n", lhs->index);

	}

  if(lvalue){
    fprintf(text,"pop\n");
  }
	push_vs(lhs);

}


//Decrease Before
void ProcessDecreaseBefore(AstNode* p, int lev,int lvalue, int leftChild){

	symbol *lhs;

	CodeGeneration(p->pAstNode[0],lev+1,0,0); // Location
	lhs = pop_vs();


  if (lhs->sclass == MEMORY){

    lhs->sclass = STACK;

    fprintf(text,"iload_ %d\n", lhs->index);
    fprintf(text,"dec\n");
    fprintf(text,"dup 2\n");
    fprintf(text,"istore_ %d\n", lhs->index);

  }

  if(lvalue){
    fprintf(text,"pop\n");
  }

	push_vs(lhs);

}


//Assign Sequence Statement
void ProcessAssignSeq(AstNode*p, int lev,int leftChild){

   symbol *rhs,*lhs;

   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();

   //Code Generation for assign-expression(right)
   if(p->pAstNode[1] ->NodeType == astAssign)
		ProcessAssign(p->pAstNode[1],lev+1,0);
   else if(p->pAstNode[1]->NodeType == astAssignSeq)
		ProcessAssignSeq(p->pAstNode[1],lev+1,0);

   rhs = pop_vs();

   pop_vs(); // pop the lhs of assign

   switch(lhs->sclass)
	   {
		  case MEMORY:

				switch(lhs->typos){

					case INT:

						switch(rhs->typos){

							case INT:
									 if(rhs->sclass == MEMORY){

											if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {

												fprintf(text,"iload_ %d\n",rhs->index);
												fprintf(text,"istore_ %d\n",lhs->index);

											}

										 }
									 else if(rhs->sclass == CONSTANT) {

                        fprintf(text,"iconst %d\n",rhs->timi);
                        fprintf(text,"istore_ %d\n",lhs->index);

										 }
									else {  /*---- STACK ---*/

										 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									 }
							break;
							case REAL:

									if(rhs->sclass == MEMORY){

											if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {

                            fprintf(text,"dload_ %d\n",rhs->index);
                            fprintf(text,"d2i");
                            fprintf(text,"istore_ %d\n",lhs->index);

											}

									 }
									else if(rhs->sclass == CONSTANT) {

                    fprintf(text,"iconst %d\n",(int) rhs->dtimi);
                    fprintf(text,"istore_ %d\n",lhs->index);

									}
									else {  /*---- STACK ---*/

											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");

									}
							break;
							case BOOL:
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							break;
						}
					break;
					case REAL:

                switch(rhs->typos){

                  case INT:
                       if(rhs->sclass == MEMORY){

                          if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {

                            fprintf(text,"iload_ %d\n",rhs->index);
                            fprintf(text,"i2d");
                            fprintf(text,"dstore_ %d\n",lhs->index);

                          }

                         }
                       else if(rhs->sclass == CONSTANT) {

                            fprintf(text,"dconst %d\n",rhs->timi);
                            fprintf(text,"dstore_ %d\n",lhs->index);

                         }
                      else {  /*---- STACK ---*/

                         fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
                       }
                  break;
                  case REAL:

                      if(rhs->sclass == MEMORY){

                          if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {

                                fprintf(text,"dload_ %d\n",rhs->index);
                                fprintf(text,"dstore_ %d\n",lhs->index);

                          }

                       }
                      else if(rhs->sclass == CONSTANT) {

                        fprintf(text,"dconst %d\n",(int) rhs->dtimi);
                        fprintf(text,"dstore_ %d\n",lhs->index);

                      }
                      else {  /*---- STACK ---*/

                          fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");

                      }
                      break;
                    }
					break;
					case BOOL:

						switch(rhs->typos){

							case BOOL:
                    if(rhs->sclass == MEMORY){

                       if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {

                         fprintf(text,"iload_ %d\n",rhs->index);
                         fprintf(text,"istore_ %d\n",lhs->index);

                       }

                      }
                    else if(rhs->sclass == CONSTANT) {

                         fprintf(text,"iconst %d\n",rhs->timi);
                         fprintf(text,"istore_ %d\n",lhs->index);

                      }
                   else {  /*---- STACK ---*/

                      fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
                    }
							break;
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
				}
		  break;
		  case CONSTANT:
			 fprintf(text,"ERROR ASSIGN[CONSTANT-]");
		  break;
		  case REGISTER:
			 fprintf(text,"ERROR ASSIGN[REGISTER-]");
		  break;
		  case STACK:
			 fprintf(text,"ERROR ASSIGN[STACK-]");
		  break;
	   }

    push_vs(lhs);
    push_vs(rhs);

}

void ProcessAboveMultiAssignSeq(AstNode*p, int lev,int leftChild){

	symbol *lhs , *rhs;

	ProcessAssignSeq(p,lev,leftChild);
	rhs = pop_vs();
	lhs = pop_vs();

	switch(rhs->typos){

		case INT:
				switch(lhs->typos){

					case INT:
						//Nothing to pop
					break;
					case REAL:
						fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}

		break;
		case REAL:
			switch(lhs->typos){

					case INT:
						fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case REAL:
						fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}

		break;
		case BOOL:
				switch(lhs->typos){

					case INT:
						//Nothing to pop
					break;
					case REAL:
						//Nothing to pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}

		break;


	}


}

//Listed Assign Statement
void ProcessListedAssign(AstNode*p, int lev,int leftChild){

   symbol *rhs,*lhs;

   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();
   assigns[LOC_ASSIGN_COUNTER++] = lhs;

   //Code Generation for nested
   CodeGeneration(p->pAstNode[1],lev+1,0,0);


   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[2],lev+1,0,0);
   rhs = pop_vs();



   switch(lhs->sclass)
	   {
		  case MEMORY:

					 switch(rhs->typos){

							case INT:
									r_types[R_TYPES_COUNTER++] = INT;

									if(rhs->sclass == MEMORY){

										fprintf(text,"iload_ %d\n",rhs->index);

										}

									else if(rhs->sclass == CONSTANT) {

										fprintf(text,"iconst %d\n",rhs->timi);

										}
							break;
							case REAL:

									r_types[R_TYPES_COUNTER++] = REAL;


									if(rhs->sclass == MEMORY){

										fprintf(text,"dload_ %d\n",rhs->index);

										}

									else if(rhs->sclass == CONSTANT) {

										fprintf(text,"dconst %lf\n",rhs->dtimi);


									}
							break;
							case BOOL:
									r_types[R_TYPES_COUNTER++] = BOOL;

                  if(rhs->sclass == MEMORY){

										fprintf(text,"iload_ %d\n",rhs->index);

										}

									else if(rhs->sclass == CONSTANT) {

										fprintf(text,"iconst %d\n",rhs->timi);

										}

							break;
              case STR:
									r_types[R_TYPES_COUNTER++] = STR;

                  if(rhs->sclass == MEMORY){

										fprintf(text,"sload_ %d\n",rhs->index);

										}

									else if(rhs->sclass == CONSTANT) {

										fprintf(text,"sconst %s\n",rhs->stimi);

										}

							break;
					 }

				  break;
				  case CONSTANT:
					 fprintf(text,"ERROR ASSIGN[CONSTANT-]");
				  break;
				  case REGISTER:
					 fprintf(text,"ERROR ASSIGN[REGISTER-]");
				  break;
				  case STACK:
					 fprintf(text,"ERROR ASSIGN[STACK-]");
				  break;

	   }

	   int i;
	   R_TYPES_COUNTER--;

	   for (i = LOC_ASSIGN_COUNTER-1; i >= 0; i--){


			switch(assigns[i]->typos){


				case INT:

						switch(r_types[R_TYPES_COUNTER--]){

							case INT:
								fprintf(text, "istore_ %d\n",  assigns[i]->index);
							break;
							case REAL:
                fprintf(text,"d2i\n");
								fprintf(text, "istore_ %d\n",  assigns[i]->index);
							break;
							case BOOL:
              case STR:
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							break;

						}

				break;
				case REAL:

					switch(r_types[R_TYPES_COUNTER--]){

								case INT:
                    fprintf(text,"i2d\n");
									  fprintf(text, "dstore_ %d\n",  assigns[i]->index);
								break;
								case REAL:
									fprintf(text, "dstore_ %d\n",  assigns[i]->index);
								break;
								case BOOL:
                case STR:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;

							}
				break;
				case BOOL:

						switch(r_types[R_TYPES_COUNTER--]){

							case BOOL:
								fprintf(text, "istore_ %d\n",  assigns[i]->index);
							break;
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
        case STR:

						switch(r_types[R_TYPES_COUNTER--]){

              case STR:
                fprintf(text, "sstore_ %d\n",  assigns[i]->index);
              break;
							case BOOL:
							case REAL:
							case INT:
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							break;

						}
				break;


			}



		}

	   R_TYPES_COUNTER = 0; // Already is zero
	   LOC_ASSIGN_COUNTER =0;



 }





//Nested Assign Statement
void ProcessNestedAssign(AstNode*p, int lev,int leftChild){

   symbol *rhs,*lhs;

   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();
   assigns[LOC_ASSIGN_COUNTER++] = lhs;

   //Code Generation for nested
   CodeGeneration(p->pAstNode[1],lev+1,0,0);


   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[2],lev+1,0,0);
   rhs = pop_vs();




   switch(lhs->sclass)
    {
     case MEMORY:

          switch(rhs->typos){

             case INT:
                 r_types[R_TYPES_COUNTER++] = INT;

                 if(rhs->sclass == MEMORY){

                   fprintf(text,"iload_ %d\n",rhs->index);

                   }

                 else if(rhs->sclass == CONSTANT) {

                   fprintf(text,"iconst %d\n",rhs->timi);

                   }
             break;
             case REAL:

                 r_types[R_TYPES_COUNTER++] = REAL;


                 if(rhs->sclass == MEMORY){

                   fprintf(text,"dload_ %d\n",rhs->index);

                   }

                 else if(rhs->sclass == CONSTANT) {

                   fprintf(text,"dconst %lf\n",rhs->dtimi);


                 }
             break;
             case BOOL:
                 r_types[R_TYPES_COUNTER++] = BOOL;

                  if(rhs->sclass == MEMORY){

                   fprintf(text,"iload_ %d\n",rhs->index);

                   }

                 else if(rhs->sclass == CONSTANT) {

                   fprintf(text,"iconst %d\n",rhs->timi);

                   }

             break;
              case STR:
                 r_types[R_TYPES_COUNTER++] = STR;

                  if(rhs->sclass == MEMORY){

                   fprintf(text,"sload_ %d\n",rhs->index);

                   }

                 else if(rhs->sclass == CONSTANT) {

                   fprintf(text,"sconst %s\n",rhs->stimi);

                   }

             break;
          }

         break;
         case CONSTANT:
          fprintf(text,"ERROR ASSIGN[CONSTANT-]");
         break;
         case REGISTER:
          fprintf(text,"ERROR ASSIGN[REGISTER-]");
         break;
         case STACK:
          fprintf(text,"ERROR ASSIGN[STACK-]");
         break;

    }


}


 //Embed Assign Statement
void ProcessEmbedAssign(AstNode*p, int lev,int leftChild){

   symbol *rhs,*lhs;

   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();
   assigns[LOC_ASSIGN_COUNTER++] = lhs;

   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
   rhs = pop_vs();

   switch(lhs->sclass)
    {
     case MEMORY:

          switch(rhs->typos){

             case INT:
                 r_types[R_TYPES_COUNTER++] = INT;

                 if(rhs->sclass == MEMORY){

                   fprintf(text,"iload_ %d\n",rhs->index);

                   }

                 else if(rhs->sclass == CONSTANT) {

                   fprintf(text,"iconst %d\n",rhs->timi);

                   }
             break;
             case REAL:

                 r_types[R_TYPES_COUNTER++] = REAL;


                 if(rhs->sclass == MEMORY){

                   fprintf(text,"dload_ %d\n",rhs->index);

                   }

                 else if(rhs->sclass == CONSTANT) {

                   fprintf(text,"dconst %lf\n",rhs->dtimi);


                 }
             break;
             case BOOL:
                 r_types[R_TYPES_COUNTER++] = BOOL;

                  if(rhs->sclass == MEMORY){

                   fprintf(text,"iload_ %d\n",rhs->index);

                   }

                 else if(rhs->sclass == CONSTANT) {

                   fprintf(text,"iconst %d\n",rhs->timi);

                   }

             break;
              case STR:
                 r_types[R_TYPES_COUNTER++] = STR;

                  if(rhs->sclass == MEMORY){

                   fprintf(text,"sload_ %d\n",rhs->index);

                   }

                 else if(rhs->sclass == CONSTANT) {

                   fprintf(text,"sconst %s\n",rhs->stimi);

                   }

             break;
          }

         break;
         case CONSTANT:
          fprintf(text,"ERROR ASSIGN[CONSTANT-]");
         break;
         case REGISTER:
          fprintf(text,"ERROR ASSIGN[REGISTER-]");
         break;
         case STACK:
          fprintf(text,"ERROR ASSIGN[STACK-]");
         break;

    }


}


void ProcessMethodName(AstNode* p){

	push_vs(p->SymbolNode);

}

void ProcessSelf(AstNode* p){

	push_vs(p->SymbolNode);

}

//Location
void ProcessLocation(AstNode* p){

	/*symbol *sn;

	sn = new_symbol(p->SymbolNode->name);
    strcpy(sn->pseudonym,p->SymbolNode->pseudonym);
	sn->lvalue = 0;
	sn->sclass = MEMORY;*/
  p->SymbolNode->sclass = MEMORY;
	push_vs(p->SymbolNode);

}

//Not Expression
void ProcessNotExpr(AstNode *p, int lev, int lvalue, int leftChild)
{

   symbol *lhs;

   //Code Generation for right operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,leftChild);
   lhs=pop_vs();

   if(lhs->typos != BOOL){

	   printf("Logical_Error: Bad operand type for unary operator 'not'");
	   exit(1);

   }


   switch(lhs->sclass)
   {
      case MEMORY:

			fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
			fprintf(text,"mov  eax, 1\n");
			fprintf(text,"jcxz $ + 8\n");
			fprintf(text,"mov  eax, 0\n");

			if (leftChild == 1){
				fprintf(text, "push eax\n");
				lhs->sclass = STACK;
			} else {
				fprintf(text, "mov [rgs], eax\n");
				lhs->sclass = REGISTER;
			}

      break;
      case REGISTER:
            fprintf(text,"mov ecx,[rgs]\n");
			fprintf(text,"mov  eax, 1\n");
			fprintf(text,"jcxz $ + 8\n");
			fprintf(text,"mov  eax, 0\n");
			fprintf(text,"mov [rgs],eax\n");

      break;
      case CONSTANT:

			 lhs->timi = !lhs->timi;
      break;
      case STACK:

				// -- POP -- //
				fprintf(text,"pop ecx\n");
				fprintf(text,"mov  eax, 1\n");
				fprintf(text,"jcxz $ + 8\n");
				fprintf(text,"mov  eax, 0\n");
				fprintf(text,"push eax\n");


      break;
   }


	push_vs(lhs);
}

//And Expression
void ProcessAndExpr(AstNode *p, int lev, int lvalue, int leftChild)
{

   symbol *sn,*rhs,*lhs;

   //Code Generation for left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();

   //Code Generation for right operand
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
   rhs=pop_vs();

   if(lhs->typos != BOOL || rhs->typos != BOOL){

	   printf("Logical_Error: Bad operand types for binary operator 'and'");
	   exit(1);

   }

   sn=new_symbol("");
   sn->lvalue = 0;
   sn->typos=BOOL;
   sn->sclass=MEMORY;


   switch(lhs->sclass)
   {
      case MEMORY:

			fprintf(text, "mov eax, 0\n");
			fprintf(text, "mov ecx, [%s]\n", lhs->pseudonym);

			 if(rhs->sclass == MEMORY) {

				fprintf(text, "jcxz $ + 14\n");
				fprintf(text,"mov ecx,[%s]\n", rhs->pseudonym);

			 }
			 else if(rhs->sclass == CONSTANT){

				fprintf(text,"jcxz $ + 16\n"); // jump 3 statements later (2+5+3=10)
				fprintf(text,"mov ecx,%d\n", rhs->timi);

			 }
			 else if (rhs->sclass == REGISTER){

				fprintf(text, "jcxz $ + 17\n"); // jump 3 statements later (2+6+3=11)
				fprintf(text, "mov ecx,[rgs]\n");

			 }
			 else{ /* -- STACK -- */
			    fprintf(text,"ERROR LOGEXPR(MEMORY-STACK)\n");
			}
      break;
      case REGISTER:
         fprintf(text,"ERROR LOGEXPR[REGISTER-]");
      break;
      case CONSTANT:

			 if(rhs->sclass == REGISTER){

				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "mov ecx, %d\n", lhs->pseudonym);

				 fprintf(text,"jcxz $ + 17\n");
				 fprintf(text, "mov ecx,[rgs]\n");

			 }
			 else if(rhs->sclass == CONSTANT)
			 {

					sn->timi = (lhs->timi && rhs->timi);

				    sn->sclass = CONSTANT;

			 }
			 else if(rhs->sclass == MEMORY){

				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "mov ecx, %d\n", lhs->pseudonym);

				 fprintf(text,"jcxz $ + 14\n");
				 fprintf(text, "mov ecx,[%s]\n",rhs->pseudonym);

			 }
			 else{ /* -- STACK -- */

				  fprintf(text,"ERROR LOGEXPR[CONSTANT-STACK]\n");
			}
      break;
      case STACK:

				// -- POP -- //
				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "pop ecx\n");



				if(rhs->sclass == MEMORY){

					 fprintf(text,"jcxz $ + 14\n");
					 fprintf(text,"mov ecx,[%s]\n",rhs->pseudonym);

				 }
				else if (rhs->sclass == REGISTER) {

					 fprintf(text,"jcxz $ + 17\n");
					 fprintf(text,"mov ecx,[rgs]\n");

				 }
				else if(rhs->sclass == CONSTANT)  {

					 fprintf(text,"jcxz $ + 16\n"); // jump 3 statements later (2+5+3=10)
					 fprintf(text,"mov ecx,%d\n", rhs->timi);

			     }
				else { /* -- STACK -- */
				   fprintf(text,"ERROR LOGEXPR[STACK-STACK]\n");
			     }

      break;
   }


	if(sn->sclass == REGISTER )
		 {
			 fprintf(text, "jcxz $ + 8\n"); // jump 2 statements later
		     fprintf(text,"mov eax, 1\n");

			if (leftChild == 1){

				         // -- PUSH -- //
						 fprintf(text,"push eax\n");


						  sn->sclass=STACK;
			}else {

				fprintf(text,"mov [rgs],eax\n");

			}
	}

	push_vs(sn);
}



//Or Expression
void ProcessOrExpr(AstNode *p, int lev, int lvalue, int leftChild)
{

   symbol *sn,*rhs,*lhs;

   //Code Generation for left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();

   //Code Generation for right operand
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
   rhs=pop_vs();

    if(lhs->typos != BOOL || rhs->typos != BOOL){

	   printf("Logical_Error: Bad operand types for binary operator 'or'");
	   exit(1);

   }

   sn=new_symbol("");
   sn->lvalue = 0;
   sn->typos=BOOL;
   sn->sclass=REGISTER;


   switch(lhs->sclass)
   {
      case MEMORY:

			fprintf(text, "mov eax, 0\n");
			fprintf(text, "mov ecx, [%s]\n", lhs->pseudonym);
			fprintf(text, "cmp ecx, 0\n");

			 if(rhs->sclass == MEMORY) {

				fprintf(text,"jne $ + 8\n");
				fprintf(text,"mov ecx, [%s]\n", rhs->pseudonym);

			 }
			 else if(rhs->sclass == CONSTANT){

				fprintf(text, "jne $ + 10\n"); // jump 3 statements later (2+5+3=10)
				fprintf(text,"mov ecx,%d\n", rhs->timi);

			 }
			 else if (rhs->sclass == REGISTER){

				fprintf(text, "jne $ + 11\n"); // jump 3 statements later (2+6+3=11)
				fprintf(text, "mov ecx,[rgs]\n");

			 }
			 else{ /* -- STACK -- */
			    fprintf(text,"ERROR LOGEXPR(MEMORY-STACK)\n");
			}
      break;
      case REGISTER:
         fprintf(text,"ERROR LOGEXPR[REGISTER-]");
      break;
      case CONSTANT:

			 if(rhs->sclass == REGISTER){

				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "mov ecx, %d\n", lhs->pseudonym);
		         fprintf(text, "cmp ecx, 0\n");

				 fprintf(text,"jne $ + 11\n");
				 fprintf(text, "mov ecx,[rgs]\n");

			 }
			 else if(rhs->sclass == CONSTANT)
			 {

					sn->timi = (lhs->timi || rhs->timi);

				    sn->sclass = CONSTANT;

			 }
			 else if(rhs->sclass == MEMORY){

				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "mov ecx, %d\n", lhs->pseudonym);
		         fprintf(text, "cmp ecx, 0\n");

				 fprintf(text,"jne $ + 8\n");
				 fprintf(text, "mov ecx,[%s]\n",rhs->pseudonym);

			 }
			 else{ /* -- STACK -- */

				  fprintf(text,"ERROR LOGEXPR[CONSTANT-STACK]\n");
			}
      break;
      case STACK:

				// -- POP -- //
				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "pop ecx\n");
		         fprintf(text, "cmp ecx, 0\n");


				if(rhs->sclass == MEMORY){

					 fprintf(text,"jne $ + 8\n");
					 fprintf(text,"mov ecx,[%s]\n",rhs->pseudonym);

				 }
				else if (rhs->sclass == REGISTER) {

					 fprintf(text,"jne $ + 11\n");
					 fprintf(text,"mov ecx,[rgs]\n");

				 }
				else if(rhs->sclass == CONSTANT)  {

					 fprintf(text, "jne $ + 10\n"); // jump 3 statements later (2+5+3=10)
					 fprintf(text,"mov ecx,%d\n", rhs->timi);

			     }
				else { /* -- STACK -- */
				   fprintf(text,"ERROR LOGEXPR[STACK-STACK]\n");
			     }

      break;
   }


	if(sn->sclass == REGISTER )
		 {
			 fprintf(text, "jcxz $ + 8\n"); // jump 2 statements later
		     fprintf(text,"mov eax, 1\n");

			if (leftChild == 1){

				         // -- PUSH -- //
						 fprintf(text,"push eax\n");


						  sn->sclass=STACK;
			}else {

				fprintf(text,"mov [rgs],eax\n");

			}
	}

	push_vs(sn);
}


//Compare Expression
void ProcessCompExpr(AstNode *p, int lev, int lvalue, int leftChild)
{

   symbol *sn,*rhs,*lhs;

   //Code Generation for left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();

   //Code Generation for right operand
   CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);
   rhs=pop_vs();

   sn=new_symbol("");
   sn->lvalue = 0;
   sn->typos= BOOL;
   sn->sclass=STACK;


   switch(lhs->sclass)
   {
      case MEMORY:

				switch(lhs->typos){

							case INT:
								 switch(rhs->typos){


									 case INT:
												 if(rhs->sclass == MEMORY) {

													fprintf(text,"iload_ %d\n",lhs->index);
													fprintf(text,"iload_ %d\n",rhs->index);
                          fprintf(text,"icmp\n");

												 }
												 else if(rhs->sclass == CONSTANT){

                           fprintf(text,"iload_ %d\n",lhs->index);
 													 fprintf(text,"iconst %d\n",rhs->timi);
                           fprintf(text,"icmp\n");

												 }
												 else{ /* -- STACK -- */
													fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
												}


									 break;
									 case REAL:

                          if(rhs->sclass == MEMORY) {

                             fprintf(text,"iload_ %d\n",lhs->index);
                             fprintf(text,"dload_ %d\n",rhs->index);
                             fprintf(text,"dcmp\n");

                          }
                          else if(rhs->sclass == CONSTANT){

                             fprintf(text,"iload_ %d\n",lhs->index);
                             fprintf(text,"dconst %lf\n",rhs->dtimi);
                             fprintf(text,"dcmp\n");

                          }
                          else{ /* -- STACK -- */
                           fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
                         }

									 break;
									 case BOOL:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									 break;

								 }

							break;
							case REAL:

										switch(rhs->typos){


												 case INT:
															  if(rhs->sclass == MEMORY) {

																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fild dword [%s]\n",rhs->pseudonym);

																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");

															 }
															 else if(rhs->sclass == CONSTANT){

																fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);

																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");

															 }
															 else if (rhs->sclass == REGISTER){

																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fild dword [rgs]\n");

																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");

															 }
															 else{ /* -- STACK -- */
																fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
															}


												 break;
												 case REAL:

															 if(rhs->sclass == MEMORY) {

																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fld qword [%s]\n",rhs->pseudonym);

																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");

															 }
															 else if(rhs->sclass == CONSTANT){

																fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);

																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");

															 }
															 else if (rhs->sclass == REGISTER){

																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fld qword [frgs]\n");

																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");

															 }
															 else{ /* -- STACK -- */
																fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
															}

												 break;
												 case BOOL:
													printf("Error: bad operand types for binary operator \n");
													exit(1);
												 break;

											 }

							break;
							case BOOL:

								 switch(rhs->typos){


									 case BOOL:
												 //check for == and !=


												 if(rhs->sclass == MEMORY) {

													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);

												 }
												 else if(rhs->sclass == CONSTANT){

													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"cmp eax,%d\n",rhs->timi);

												 }
												 else if (rhs->sclass == REGISTER){

													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"cmp eax,[rgs]\n");

												 }
												 else{ /* -- STACK -- */
													fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
												}


									 break;
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

						}


      break;
      case REGISTER:
         fprintf(text,"ERROR COMPEXPR[REGISTER-]");
      break;
      case CONSTANT:

				switch(lhs->typos){

							case INT:

								 switch(rhs->typos){


									 case INT:

											 if(rhs->sclass == REGISTER){

												  fprintf(text,"mov eax,%d\n",lhs->timi);
												  fprintf(text,"cmp eax,[rgs]\n");

											 }
											 else if(rhs->sclass == CONSTANT)
											 {

												 switch (p->pAstNode[1]->NodeType){

														case astLeOp:
															sn->timi = (lhs->timi <= rhs->timi);

														break;
														case astLOp:
															sn->timi  = (lhs->timi < rhs->timi);
														break;
														case astGOp:
															sn->timi  = (lhs->timi > rhs->timi);
														break;
														case astGeOp:
															sn->timi = (lhs->timi >= rhs->timi);
														break;
														case astEOp:
															sn->timi = (lhs->timi == rhs->timi);
														break;
														case astNeOp:
															sn->timi = (lhs->timi != rhs->timi);
														break;
													}

												sn->sclass = CONSTANT;
											 }
											 else if(rhs->sclass == MEMORY){

												  fprintf(text,"mov eax,%d\n",lhs->timi);
												  fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);

											 }
											 else{ /* -- STACK -- */

												  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");
											}
									 break;
									 case REAL:

										         if(rhs->sclass == REGISTER){

													  fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													  fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);
													  fprintf(text,"fld qword [frgs]\n");

													  fprintf(text,"fcomip\n");
													  fprintf(text,"ffreep\n");

												 }
												 else if(rhs->sclass == CONSTANT)
												 {

													 switch (p->pAstNode[1]->NodeType){

															case astLeOp:

																sn->timi = (lhs->timi <= rhs->dtimi);

															break;
															case astLOp:

																sn->timi  = (lhs->timi < rhs->dtimi);

															break;
															case astGOp:

																sn->timi  = (lhs->timi > rhs->dtimi);

															break;
															case astGeOp:

																sn->timi = (lhs->timi >= rhs->dtimi);

															break;
															case astEOp:

																sn->timi = (lhs->timi == rhs->dtimi);

															break;
															case astNeOp:

																sn->timi = (lhs->timi != rhs->dtimi);

															break;
														}

													sn->sclass = CONSTANT;
												 }
												 else if(rhs->sclass == MEMORY){

													  fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													  fprintf(text,"fild dword [INT_%d]\n",NUM_OF_REAL_CONST++);
													  fprintf(text,"fld qword [%s]\n",rhs->pseudonym);

													  fprintf(text,"fcomip\n");
													  fprintf(text,"ffreep\n");

												 }
												 else{ /* -- STACK -- */

													  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");
												}
									 break;
									 case BOOL:
											printf("Error: bad operand types for binary operator \n");
											exit(1);
									 break;
								 }

							break;
							case REAL:

								 switch(rhs->typos){


										 case INT:

												 if(rhs->sclass == REGISTER){

													  fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													  fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													  fprintf(text,"fild dword [rgs]\n");

													  fprintf(text,"fcomip\n");
													  fprintf(text,"ffreep\n");

												 }
												 else if(rhs->sclass == CONSTANT)
												 {

													 switch (p->pAstNode[1]->NodeType){

															case astLeOp:
																sn->timi = (lhs->dtimi <= rhs->timi);

															break;
															case astLOp:
																sn->timi  = (lhs->dtimi < rhs->timi);
															break;
															case astGOp:
																sn->timi  = (lhs->dtimi > rhs->timi);
															break;
															case astGeOp:
																sn->timi = (lhs->dtimi >= rhs->timi);
															break;
															case astEOp:
																sn->timi = (lhs->dtimi == rhs->timi);
															break;
															case astNeOp:
																sn->timi = (lhs->dtimi != rhs->timi);
															break;
														}

													sn->sclass = CONSTANT;
												 }
												 else if(rhs->sclass == MEMORY){

													  fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													  fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													  fprintf(text,"fild dword [%s]\n",rhs->pseudonym);

													  fprintf(text,"fcomip\n");
													  fprintf(text,"ffreep\n");

												 }
												 else{ /* -- STACK -- */

													  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");
												}
										 break;
										 case REAL:

													 if(rhs->sclass == REGISTER){

														  fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
														  fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
														  fprintf(text,"fld qword [frgs]\n");

														  fprintf(text,"fcomip\n");
														  fprintf(text,"ffreep\n");

													 }
													 else if(rhs->sclass == CONSTANT)
													 {

														 switch (p->pAstNode[1]->NodeType){

																case astLeOp:

																	sn->timi = (lhs->dtimi <= rhs->dtimi);

																break;
																case astLOp:

																	sn->timi  = (lhs->dtimi < rhs->dtimi);

																break;
																case astGOp:

																	sn->timi  = (lhs->dtimi > rhs->dtimi);

																break;
																case astGeOp:

																	sn->timi = (lhs->dtimi >= rhs->dtimi);

																break;
																case astEOp:

																	sn->timi = (lhs->dtimi == rhs->dtimi);

																break;
																case astNeOp:

																	sn->timi = (lhs->dtimi != rhs->dtimi);

																break;
															}

														sn->sclass = CONSTANT;
													 }
													 else if(rhs->sclass == MEMORY){

														  fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
														  fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
														  fprintf(text,"fld qword [%s]\n",rhs->pseudonym);

														  fprintf(text,"fcomip\n");
														  fprintf(text,"ffreep\n");

													 }
													 else{ /* -- STACK -- */

														  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");
													}
										 break;
										 case BOOL:
											printf("Error: bad operand types for binary operator \n");
											exit(1);
										 break;
									 }

								break;
								case BOOL:

								 switch(rhs->typos){


									 case BOOL:

											//same check

											 if(rhs->sclass == REGISTER){

												  fprintf(text,"mov eax,%d\n",lhs->timi);
												  fprintf(text,"cmp eax,[rgs]\n");

											 }
											 else if(rhs->sclass == CONSTANT)
											 {

												 switch (p->pAstNode[1]->NodeType){

														case astLeOp:
															sn->timi = (lhs->timi <= rhs->timi);

														break;
														case astLOp:
															sn->timi  = (lhs->timi < rhs->timi);
														break;
														case astGOp:
															sn->timi  = (lhs->timi > rhs->timi);
														break;
														case astGeOp:
															sn->timi = (lhs->timi >= rhs->timi);
														break;
														case astEOp:
															sn->timi = (lhs->timi == rhs->timi);
														break;
														case astNeOp:
															sn->timi = (lhs->timi != rhs->timi);
														break;
													}

												sn->sclass = CONSTANT;
											 }
											 else if(rhs->sclass == MEMORY){

												  fprintf(text,"mov eax,%d\n",lhs->timi);
												  fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);

											 }
											 else{ /* -- STACK -- */

												  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");
											}
									 break;
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

							}



      break;
      case STACK:

				switch(lhs->typos){

							case INT:

								 switch(rhs->typos){

									 case INT:

												// -- POP -- //
												fprintf(text,"pop eax\n");


												if(rhs->sclass == MEMORY){

													fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);

												 }
												else if (rhs->sclass == REGISTER) {

													fprintf(text,"cmp eax,[rgs]\n");

												 }
												else if(rhs->sclass == CONSTANT)  {

													fprintf(text,"cmp eax,%d\n",rhs->timi);

												 }
												else { /* -- STACK -- */
												   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");
												 }

									 break;
									 case REAL:

												// -- POP -- //
												fprintf(text,"fild dword [esp]\n");
												fprintf(text,"add esp,4\n");


												if(rhs->sclass == MEMORY){

													 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);

													 fprintf(text,"fcomip\n");
													 fprintf(text,"ffreep\n");

												 }
												else if (rhs->sclass == REGISTER) {

													 fprintf(text,"fld qword [frgs]\n");

													 fprintf(text,"fcomip\n");
													 fprintf(text,"ffreep\n");

												 }
												else if(rhs->sclass == CONSTANT)  {

													fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
												    fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);

													fprintf(text,"fcomip\n");
													fprintf(text,"ffreep\n");

												 }
												else { /* -- STACK -- */
												   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");
												 }
									 break;
									 case BOOL:

											printf("Error: bad operand types for binary operator \n");
											exit(1);
									 break;

								 }

							break;
							case REAL:

									 switch(rhs->typos){

											 case INT:

														// -- POP -- //
														fprintf(text,"fld qword [esp]\n");
														fprintf(text,"add esp,8\n");


														 if(rhs->sclass == MEMORY){

															 fprintf(text,"fild dword [%s]\n",rhs->pseudonym);

															 fprintf(text,"fcomip\n");
															 fprintf(text,"ffreep\n");

														 }
														else if (rhs->sclass == REGISTER) {

															 fprintf(text,"fild dword [rgs]\n");

															 fprintf(text,"fcomip\n");
															 fprintf(text,"ffreep\n");

														 }
														else if(rhs->sclass == CONSTANT)  {

															fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->dtimi);
															fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);

															fprintf(text,"fcomip\n");
															fprintf(text,"ffreep\n");

														 }
														else { /* -- STACK -- */
														   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");
														 }

											 break;
											 case REAL:

														// -- POP -- //
														fprintf(text,"fld qword [esp]\n");
														fprintf(text,"add esp,8\n");


														if(rhs->sclass == MEMORY){

															 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);

															 fprintf(text,"fcomip\n");
															 fprintf(text,"ffreep\n");

														 }
														else if (rhs->sclass == REGISTER) {

															 fprintf(text,"fld qword [frgs]\n");

															 fprintf(text,"fcomip\n");
															 fprintf(text,"ffreep\n");

														 }
														else if(rhs->sclass == CONSTANT)  {

															fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);

															fprintf(text,"fcomip\n");
															fprintf(text,"ffreep\n");

														 }
														else { /* -- STACK -- */
														   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");
														 }
											 break;
											 case BOOL:

													printf("Error: bad operand types for binary operator \n");
													exit(1);
											 break;

								 }
						break;
						case BOOL:

								 switch(rhs->typos){

									 case BOOL:
												// same check
												// -- POP -- //
												fprintf(text,"pop eax\n");


												if(rhs->sclass == MEMORY){

													fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);

												 }
												else if (rhs->sclass == REGISTER) {

													fprintf(text,"cmp eax,[rgs]\n");

												 }
												else if(rhs->sclass == CONSTANT)  {

													fprintf(text,"cmp eax,%d\n",rhs->timi);

												 }
												else { /* -- STACK -- */
												   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");
												 }

									 break;
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
						}


      break;
   }


	if(sn->sclass == STACK )
		 {


			//Set 1 in register A if the entire logical expression is true else set 0 (ENTA 0)
      switch (p->pAstNode[1]->NodeType){
					case astLeOp:

							 fprintf(text,"ifle success%d fail%d\n",NUM_COMP,NUM_COMP);

						break;
					case astLOp:

                fprintf(text,"ifl success%d fail%d\n",NUM_COMP,NUM_COMP);

					break;
					case astGOp:

                fprintf(text,"ifg success%d fail%d\n",NUM_COMP,NUM_COMP);

					break;
					case astGeOp:

                fprintf(text,"ifge success%d fail%d\n",NUM_COMP,NUM_COMP);

					break;
					case astEOp:

                fprintf(text,"ifeq success%d fail%d\n",NUM_COMP,NUM_COMP);

					break;
					case astNeOp:

                fprintf(text,"ifl success%d fail%d\n",NUM_COMP,NUM_COMP);


					break;
			}


      fprintf(text,"label NAME=fail%d:\n",NUM_COMP);
      fprintf(text,"iconst 0\n");
      fprintf(text,"jmp endblock%d\n",NUM_COMP);
      fprintf(text,"label NAME=success%d:\n",NUM_COMP);
      fprintf(text,"iconst 1\n");
      fprintf(text,"label NAME=endblock%d:\n",NUM_COMP);
      NUM_COMP++;

			if (leftChild == 1){

						 sn->sclass=STACK;

			}


	}

	push_vs(sn);
}


//Add Expression
void ProcessAddExpr(AstNode *p, int lev, int lvalue, int leftChild){

   symbol *lhs, *rhs, *sn;

   //Code Generation for left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();

   //Code Generation for right operand
   CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);
   rhs=pop_vs();

   sn=new_symbol("");
   sn->lvalue =0;
   sn->sclass=STACK;

   if(p->pAstNode[1]->NodeType == astAddOp) {


	    switch(lhs->sclass)
		   {
			  case MEMORY:

					switch(lhs->typos){

						case INT:

								switch(rhs->typos){

									case INT:

											 sn->typos=INT;

											 if(rhs->sclass == MEMORY)
											 {

													fprintf(text,"iload_ %d\n",lhs->index);
                          fprintf(text,"iload_ %d\n",rhs->index);
													fprintf(text,"iadd\n");

											 }
											 else if(rhs->sclass == CONSTANT)
											 {

                         fprintf(text,"iload_ %d\n",lhs->index);
                         fprintf(text,"iconst %d\n",rhs->timi);
                         fprintf(text,"iadd\n");


											 }
									break;

									case REAL:
													sn->typos=REAL;

											     if(rhs->sclass == CONSTANT)
													 {

                             fprintf(text,"iload_ %d\n",lhs->index);
                             fprintf(text,"i2d\n");
                             fprintf(text,"dconst %lf\n",rhs->dtimi);
                             fprintf(text,"dadd\n");

													 }else if(rhs->sclass == MEMORY){


                             fprintf(text,"iload_ %d\n",lhs->index);
                             fprintf(text,"i2d\n");
                             fprintf(text,"dload_ %d\n",rhs->index);
                             fprintf(text,"dadd\n");

													 }

									break;
								}
					    break;
						case REAL:

								switch(rhs->typos){

											case INT:
													 sn->typos=REAL;

                           if(rhs->sclass == CONSTANT)
													 {

                             fprintf(text,"dload_ %d\n",lhs->index);
                             fprintf(text,"dconst %d\n",rhs->timi);
                             fprintf(text,"dadd\n");

													 }else if(rhs->sclass == MEMORY){


                             fprintf(text,"dload_ %d\n",lhs->index);
                             fprintf(text,"iload_ %d\n",rhs->index);
                             fprintf(text,"i2d\n");
                             fprintf(text,"dadd\n");

													 }
											break;

											case REAL:

															sn->typos=REAL;

                              if(rhs->sclass == CONSTANT) {

                                fprintf(text,"dload_ %d\n",lhs->index);
                                fprintf(text,"dconst %lf\n",rhs->dtimi);
                                fprintf(text,"dadd\n");

   													 }else if(rhs->sclass == MEMORY){


                                fprintf(text,"dload_ %d\n",lhs->index);
                                fprintf(text,"dload_ %d\n",rhs->index);
                                fprintf(text,"dadd\n");

   													 }
											break;
										}
						break;
            case STR:
                  switch(rhs->typos){

                    case STR:

                         sn->typos= STR;

                         if(rhs->sclass == MEMORY)
                         {

                            fprintf(text,"sload_ %d\n",lhs->index);
                            fprintf(text,"sload_ %d\n",rhs->index);
                            fprintf(text,"sadd\n");

                         }
                         else if(rhs->sclass == CONSTANT)
                         {

                           fprintf(text,"sload_ %d\n",lhs->index);
                           fprintf(text,"sconst \"%s\"\n",rhs->stimi);
                           fprintf(text,"sadd\n");


                         }
                    break;
                  }
            break;
					}
			  break;
        case STACK:

					switch(lhs->typos){

						case INT:

								switch(rhs->typos){

									case INT:

											 sn->typos=INT;

											 if(rhs->sclass == MEMORY)
											 {

                          fprintf(text,"iload_ %d\n",rhs->index);
													fprintf(text,"iadd\n");

											 }
											 else if(rhs->sclass == CONSTANT)
											 {


                         fprintf(text,"iconst %d\n",rhs->timi);
                         fprintf(text,"iadd\n");


											 }
									break;

									case REAL:
													sn->typos=REAL;

											     if(rhs->sclass == CONSTANT)
													 {


                             fprintf(text,"dconst %lf\n",rhs->dtimi);
                             fprintf(text,"dadd\n");

													 }else if(rhs->sclass == MEMORY){



                             fprintf(text,"dload_ %d\n",rhs->index);
                             fprintf(text,"dadd\n");

													 }

									break;
								}
					    break;
						case REAL:

								switch(rhs->typos){

											case INT:
													 sn->typos=REAL;

                           if(rhs->sclass == CONSTANT)
													 {


                             fprintf(text,"dconst %d\n",rhs->timi);
                             fprintf(text,"dadd\n");

													 }else if(rhs->sclass == MEMORY){



                             fprintf(text,"iload_ %d\n",rhs->index);
                             fprintf(text,"i2d\n");
                             fprintf(text,"dadd\n");

													 }
											break;

											case REAL:

															sn->typos=REAL;

                              if(rhs->sclass == CONSTANT) {


                                fprintf(text,"dconst %lf\n",rhs->dtimi);
                                fprintf(text,"dadd\n");

   													 }else if(rhs->sclass == MEMORY){



                                fprintf(text,"dload_ %d\n",rhs->index);
                                fprintf(text,"dadd\n");

   													 }
											break;
										}
						break;

            case STR:

								switch(rhs->typos){

									case STR:

											 sn->typos=STR;

											 if(rhs->sclass == MEMORY)
											 {

                          fprintf(text,"sload_ %d\n",rhs->index);
													fprintf(text,"sadd\n");

											 }
											 else if(rhs->sclass == CONSTANT)
											 {


                         fprintf(text,"sconst \"%s\"\n",rhs->stimi);
                         fprintf(text,"sadd\n");


											 }
									break;
                }
            break;
          }
			  break;
			  case CONSTANT:

					switch(lhs->typos){

							case INT:

								 switch(rhs->typos){

									 case INT:
												sn->typos= INT;

												if(rhs->sclass == MEMORY){

                          fprintf(text,"iconst %d\n",lhs->timi);
                          fprintf(text,"iload_ %d\n",rhs->index);
                          fprintf(text,"iadd\n");

												 }
												 else if(rhs->sclass == CONSTANT){

													sn->timi = lhs->timi + rhs->timi;
													sn->sclass=CONSTANT;

												 }
									 break;
									 case REAL:
												 sn->typos=REAL;

												 if(rhs->sclass == MEMORY){

                           fprintf(text,"dconst %d\n",lhs->timi);
                           fprintf(text,"dload_ %d\n",rhs->index);
                           fprintf(text,"dadd\n");

												 }
												 else if(rhs->sclass == CONSTANT){

													sn->dtimi = lhs->timi + rhs->dtimi;
													sn->sclass=CONSTANT;

												 }
									 break;

								 }

							break;
							case REAL:

									  switch(rhs->typos){

											 case INT:
														sn->typos= REAL;

														if(rhs->sclass == MEMORY){

                              fprintf(text,"dconst %lf\n",lhs->dtimi);
                              fprintf(text,"iload_ %d\n",rhs->index);
                              fprintf(text,"i2d\n");
                              fprintf(text,"dadd\n");

														 }
														 else if(rhs->sclass == CONSTANT){

															sn->dtimi = lhs->dtimi + rhs->timi;
															sn->sclass=CONSTANT;

														 }
											 break;
											 case REAL:
														sn->typos= REAL;

														if(rhs->sclass == MEMORY){

                              fprintf(text,"dconst %lf\n",lhs->dtimi);
                              fprintf(text,"dload_ %d\n",rhs->index);
                              fprintf(text,"dadd\n");

														 }
														 else if(rhs->sclass == CONSTANT){

															sn->dtimi = lhs->dtimi + rhs->dtimi;
															sn->sclass=CONSTANT;

														 }
											 break;

										 }

							break;
              case STR:

								 switch(rhs->typos){

									 case STR:
												sn->typos= STR;

												if(rhs->sclass == MEMORY){

                          fprintf(text,"sconst \"%s\"\n",lhs->stimi);
                          fprintf(text,"sload_ %d\n",rhs->index);
                          fprintf(text,"sadd\n");

												 }
												 else if(rhs->sclass == CONSTANT){
                          char * str[80];
                          strcpy(str,lhs->stimi);
                          strcat(str,rhs->stimi);

                          strcpy(sn->stimi, str);

													sn->sclass=CONSTANT;

												 }
									 break;
                 }
              break;
						}

			  break;
		   }
   }
   else if(p->pAstNode[1]->NodeType == astSubOp)
   {

     switch(lhs->sclass)
      {
       case MEMORY:

         switch(lhs->typos){

           case INT:

               switch(rhs->typos){

                 case INT:

                      sn->typos=INT;

                      if(rhs->sclass == MEMORY)
                      {

                         fprintf(text,"iload_ %d\n",lhs->index);
                         fprintf(text,"iload_ %d\n",rhs->index);
                         fprintf(text,"isub\n");

                      }
                      else if(rhs->sclass == CONSTANT)
                      {

                        fprintf(text,"iload_ %d\n",lhs->index);
                        fprintf(text,"iconst %d\n",rhs->timi);
                        fprintf(text,"isub\n");


                      }
                 break;

                 case REAL:
                         sn->typos=REAL;

                          if(rhs->sclass == CONSTANT)
                          {

                            fprintf(text,"iload_ %d\n",lhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"dconst %lf\n",rhs->dtimi);
                            fprintf(text,"dsub\n");

                          }else if(rhs->sclass == MEMORY){


                            fprintf(text,"iload_ %d\n",lhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"dload_ %d\n",rhs->index);
                            fprintf(text,"dsub\n");

                          }

                 break;
               }
             break;
           case REAL:

               switch(rhs->typos){

                     case INT:
                          sn->typos=REAL;

                          if(rhs->sclass == CONSTANT)
                          {

                            fprintf(text,"dload_ %d\n",lhs->index);
                            fprintf(text,"dconst %d\n",rhs->timi);
                            fprintf(text,"dsub\n");

                          }else if(rhs->sclass == MEMORY){


                            fprintf(text,"dload_ %d\n",lhs->index);
                            fprintf(text,"iload_ %d\n",rhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"dsub\n");

                          }
                     break;

                     case REAL:

                             sn->typos=REAL;

                             if(rhs->sclass == CONSTANT) {

                               fprintf(text,"dload_ %d\n",lhs->index);
                               fprintf(text,"dconst %lf\n",rhs->dtimi);
                               fprintf(text,"dsub\n");

                            }else if(rhs->sclass == MEMORY){


                               fprintf(text,"dload_ %d\n",lhs->index);
                               fprintf(text,"dload_ %d\n",rhs->index);
                               fprintf(text,"dsub\n");

                            }
                     break;
                   }
           break;
         }
       break;
       case STACK:

         switch(lhs->typos){

           case INT:

               switch(rhs->typos){

                 case INT:

                      sn->typos=INT;

                      if(rhs->sclass == MEMORY)
                      {

                         fprintf(text,"iload_ %d\n",rhs->index);
                         fprintf(text,"isub\n");

                      }
                      else if(rhs->sclass == CONSTANT)
                      {


                        fprintf(text,"iconst %d\n",rhs->timi);
                        fprintf(text,"isub\n");


                      }
                 break;

                 case REAL:
                         sn->typos=REAL;

                          if(rhs->sclass == CONSTANT)
                          {


                            fprintf(text,"dconst %lf\n",rhs->dtimi);
                            fprintf(text,"dsub\n");

                          }else if(rhs->sclass == MEMORY){



                            fprintf(text,"dload_ %d\n",rhs->index);
                            fprintf(text,"dsub\n");

                          }

                 break;
               }
             break;
           case REAL:

               switch(rhs->typos){

                     case INT:
                          sn->typos=REAL;

                          if(rhs->sclass == CONSTANT)
                          {


                            fprintf(text,"dconst %d\n",rhs->timi);
                            fprintf(text,"dsub\n");

                          }else if(rhs->sclass == MEMORY){



                            fprintf(text,"iload_ %d\n",rhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"dsub\n");

                          }
                     break;

                     case REAL:

                             sn->typos=REAL;

                             if(rhs->sclass == CONSTANT) {


                               fprintf(text,"dconst %lf\n",rhs->dtimi);
                               fprintf(text,"dsub\n");

                            }else if(rhs->sclass == MEMORY){



                               fprintf(text,"dload_ %d\n",rhs->index);
                               fprintf(text,"dsub\n");

                            }
                     break;
                   }
           break;
         }
       break;
       case CONSTANT:

         switch(lhs->typos){

             case INT:

                switch(rhs->typos){

                  case INT:
                       sn->typos= INT;

                       if(rhs->sclass == MEMORY){

                         fprintf(text,"iconst %d\n",lhs->index);
                         fprintf(text,"iload_ %d\n",rhs->index);
                         fprintf(text,"isub\n");

                        }
                        else if(rhs->sclass == CONSTANT){

                         sn->timi = lhs->timi - rhs->timi;
                         sn->sclass=CONSTANT;

                        }
                  break;
                  case REAL:
                        sn->typos=REAL;

                        if(rhs->sclass == MEMORY){

                          fprintf(text,"dconst %d\n",lhs->index);
                          fprintf(text,"dload_ %d\n",rhs->index);
                          fprintf(text,"dsub\n");

                        }
                        else if(rhs->sclass == CONSTANT){

                         sn->dtimi = lhs->timi - rhs->dtimi;
                         sn->sclass=CONSTANT;

                        }
                  break;

                }

             break;
             case REAL:

                   switch(rhs->typos){

                      case INT:
                           sn->typos= REAL;

                           if(rhs->sclass == MEMORY){

                             fprintf(text,"dconst %lf\n",lhs->dtimi);
                             fprintf(text,"iload_ %d\n",rhs->index);
                             fprintf(text,"i2d\n");
                             fprintf(text,"dsub\n");

                            }
                            else if(rhs->sclass == CONSTANT){

                             sn->dtimi = lhs->dtimi - rhs->timi;
                             sn->sclass=CONSTANT;

                            }
                      break;
                      case REAL:
                           sn->typos= REAL;

                           if(rhs->sclass == MEMORY){

                             fprintf(text,"dconst %lf\n",lhs->dtimi);
                             fprintf(text,"dload_ %d\n",rhs->index);
                             fprintf(text,"dsub\n");

                            }
                            else if(rhs->sclass == CONSTANT){

                             sn->dtimi = lhs->dtimi - rhs->dtimi;
                             sn->sclass=CONSTANT;

                            }
                      break;

                    }

             break;

           }

       break;
      }


   }

   push_vs(sn);

}

//True
void ProcessTrue(AstNode* p){
	push_vs(p->SymbolNode);

}

//False
void ProcessFalse(AstNode* p){
	push_vs(p->SymbolNode);

}


//Function Call
void ProcessFunctionCall(AstNode *p, int lev, int lvalue, int leftChild){

	symbol *sn;
	sn = new_symbol("");
	sn->sclass= STACK;

	sn->typos = p->SymbolNode->typos;

	//Code Generation for actual parameters
	CodeGeneration(p->pAstNode[1],lev+1,0,0);



	//Jump to method
	fprintf(text,"invoke_static %s\n",p->SymbolNode->name);
  if(lvalue){
    fprintf(text,"pop\n");
  }
	push_vs(sn);


}


void ProcessMethodCall(AstNode *p, int lev, int lvalue, int leftChild){

  symbol *sn, *lhs;
  sn = new_symbol("");
  sn->sclass= STACK;

  //Code Generation for method name
  CodeGeneration(p->pAstNode[0],lev+1,0,0);
  lhs = pop_vs();

  //Code Generation for actual parameters
  CodeGeneration(p->pAstNode[1],lev+1,0,0);

  if(p->SymbolNode->field == 0){
      fprintf(text,"rload_ %d\n",p->SymbolNode->index);
    }
  else{
      fprintf(text,"rload_ 1\n");
      fprintf(text,"getfield %s\n",p->SymbolNode->ax_name);
    }


  //Jump to method
  fprintf(text,"invoke_virtual %s %s\n",p->SymbolNode->nameclass, p->SymbolNode->name);
  sn->typos = p->SymbolNode->instance_method_type_call;

  if(lvalue){
    fprintf(text,"pop\n");

  }
  strcpy(PARAMETERS_CALL,"");

  push_vs(sn);

}

//Static Method Call
void ProcessStaticMethodCall(AstNode *p, int lev, int lvalue, int leftChild){

	symbol *sn, *lhs;
	sn = new_symbol("");
	sn->sclass= STACK;

 //Code Generation for static method name
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
  lhs = pop_vs();

	sn->typos = lhs->typos;

	//Code Generation for actual parameters
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
  if (strcmp(lhs->name,"new") == 0){

    fprintf(text,"new %s\n", p->SymbolNode->name);
  }

  char snum[6];
  nitoa(p->SymbolNode->typos,snum);

	//Jump to method
	fprintf(text,"invoke_virtual %s %s%s%s\n",p->SymbolNode->name, lhs->name,snum,PARAMETERS_CALL);

  if(lvalue){
    fprintf(text,"pop\n");
  }
  strcpy(PARAMETERS_CALL,"");

	 push_vs(sn);


}


//Break Statement
void ProcessBreakStmt(){

	fprintf(text,"jmp endwhile%d\n",see_wh()->timi);
}

//Mul Expression
void ProcessMulExpr(AstNode *p, int lev, int lvalue, int leftChild)
{  symbol *sn,*rhs,*lhs;

	//Code Generation for the left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();

   //Code Generation for the right operand
   CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);
   rhs=pop_vs();

   sn = new_symbol("");
   sn->lvalue = 0;
   sn->sclass = STACK;


  if(p->pAstNode[1]->NodeType == astMulOp){

    switch(lhs->sclass)
     {
      case MEMORY:

            switch(lhs->typos){

                  case INT:

                        switch(rhs->typos){

                          case INT:

                               sn->typos=INT;

                               if(rhs->sclass == MEMORY)
                               {

                                  fprintf(text,"iload_ %d\n",lhs->index);
                                  fprintf(text,"iload_ %d\n",rhs->index);
                                  fprintf(text,"imul\n");

                               }
                               else if(rhs->sclass == CONSTANT)
                               {

                                 fprintf(text,"iload_ %d\n",lhs->index);
                                 fprintf(text,"iconst %d\n",rhs->timi);
                                 fprintf(text,"imul\n");


                               }
                          break;
                          case REAL:
                                  sn->typos=REAL;

                                   if(rhs->sclass == CONSTANT)
                                   {

                                     fprintf(text,"iload_ %d\n",lhs->index);
                                     fprintf(text,"i2d\n");
                                     fprintf(text,"dconst %lf\n",rhs->dtimi);
                                     fprintf(text,"dmul\n");

                                   }else if(rhs->sclass == MEMORY){


                                     fprintf(text,"iload_ %d\n",lhs->index);
                                     fprintf(text,"i2d\n");
                                     fprintf(text,"dload_ %d\n",rhs->index);
                                     fprintf(text,"dmul\n");

                                   }


                          break;
                          case STR:
                                  sn->typos= STR;

                                   if(rhs->sclass == CONSTANT)
                                   {

                                     fprintf(text,"iload_ %d\n",lhs->index);
                                     fprintf(text,"sconst \"%s\"\n",rhs->stimi);
                                     fprintf(text,"smul\n");

                                   }else if(rhs->sclass == MEMORY){


                                     fprintf(text,"iload_ %d\n",lhs->index);
                                     fprintf(text,"sload_ %d\n",rhs->index);
                                     fprintf(text,"smul\n");

                                   }
                          break;
                       }

          break;
          case REAL:

              switch(rhs->typos){

                    case INT:
                         sn->typos=REAL;

                         if(rhs->sclass == CONSTANT)
                         {

                           fprintf(text,"dload_ %d\n",lhs->index);
                           fprintf(text,"dconst %d\n",rhs->timi);
                           fprintf(text,"dmul\n");

                         }else if(rhs->sclass == MEMORY){


                           fprintf(text,"dload_ %d\n",lhs->index);
                           fprintf(text,"iload_ %d\n",rhs->index);
                           fprintf(text,"i2d\n");
                           fprintf(text,"dmul\n");

                         }
                    break;

                    case REAL:

                            sn->typos=REAL;

                            if(rhs->sclass == CONSTANT) {

                              fprintf(text,"dload_ %d\n",lhs->index);
                              fprintf(text,"dconst %lf\n",rhs->dtimi);
                              fprintf(text,"dmul\n");

                           }else if(rhs->sclass == MEMORY){


                              fprintf(text,"dload_ %d\n",lhs->index);
                              fprintf(text,"dload_ %d\n",rhs->index);
                              fprintf(text,"dmul\n");

                           }
                    break;
                  }
              break;
            }
      break;
      case STACK:

        switch(lhs->typos){

          case INT:

              switch(rhs->typos){

                case INT:

                     sn->typos=INT;

                     if(rhs->sclass == MEMORY)
                     {

                        fprintf(text,"iload_ %d\n",rhs->index);
                        fprintf(text,"imul\n");

                     }
                     else if(rhs->sclass == CONSTANT)
                     {


                       fprintf(text,"iconst %d\n",rhs->timi);
                       fprintf(text,"imul\n");


                     }
                break;

                case REAL:
                        sn->typos=REAL;

                         if(rhs->sclass == CONSTANT)
                         {


                           fprintf(text,"dconst %lf\n",rhs->dtimi);
                           fprintf(text,"dmul\n");

                         }else if(rhs->sclass == MEMORY){



                           fprintf(text,"dload_ %d\n",rhs->index);
                           fprintf(text,"dmul\n");

                         }

                break;
                case STR:
                        sn->typos=STR;

                         if(rhs->sclass == CONSTANT)
                         {


                           fprintf(text,"sconst \"%s\"\n",rhs->stimi);
                           fprintf(text,"smul\n");

                         }else if(rhs->sclass == MEMORY){

                           fprintf(text,"sload_ %d\n",rhs->index);
                           fprintf(text,"smul\n");

                         }

                break;
              }
          break;
          case REAL:

              switch(rhs->typos){

                    case INT:
                         sn->typos=REAL;

                         if(rhs->sclass == CONSTANT)
                         {


                           fprintf(text,"dconst %d\n",rhs->timi);
                           fprintf(text,"dmul\n");

                         }else if(rhs->sclass == MEMORY){



                           fprintf(text,"iload_ %d\n",rhs->index);
                           fprintf(text,"i2d\n");
                           fprintf(text,"dmul\n");

                         }
                    break;

                    case REAL:

                            sn->typos=REAL;

                            if(rhs->sclass == CONSTANT) {


                              fprintf(text,"dconst %lf\n",rhs->dtimi);
                              fprintf(text,"dmul\n");

                           }else if(rhs->sclass == MEMORY){



                              fprintf(text,"dload_ %d\n",rhs->index);
                              fprintf(text,"dmul\n");

                           }
                    break;
                  }
              break;
            }
      break;
      case CONSTANT:

        switch(lhs->typos){

            case INT:

               switch(rhs->typos){

                 case INT:
                      sn->typos= INT;

                      if(rhs->sclass == MEMORY){

                        fprintf(text,"iconst %d\n",lhs->timi);
                        fprintf(text,"iload_ %d\n",rhs->index);
                        fprintf(text,"imul\n");

                       }
                       else if(rhs->sclass == CONSTANT){

                        sn->timi = lhs->timi * rhs->timi;
                        sn->sclass=CONSTANT;

                       }
                 break;
                 case REAL:
                       sn->typos=REAL;

                       if(rhs->sclass == MEMORY){

                         fprintf(text,"dconst %d\n",lhs->timi);
                         fprintf(text,"dload_ %d\n",rhs->index);
                         fprintf(text,"dmul\n");

                       }
                       else if(rhs->sclass == CONSTANT){

                        sn->dtimi = lhs->timi * rhs->dtimi;
                        sn->sclass=CONSTANT;

                       }
                 break;
                 case STR:
                       sn->typos=STR;

                       if(rhs->sclass == MEMORY){

                         fprintf(text,"iconst %d\n",lhs->timi);
                         fprintf(text,"sload_ %d\n",rhs->index);
                         fprintf(text,"smul\n");

                       }
                       else if(rhs->sclass == CONSTANT){
                        char* str;
                        if(lhs->timi !=0){
                          str = (char *) malloc(sizeof(char)* lhs->timi * strlen(rhs->stimi));
                          strcpy(str,rhs->stimi);
                          int i;
                          for(i=0; i < lhs->timi - 1 ; i++)
                              strcat(str, rhs->stimi);
                        }
                        else {
                          strcpy(str,"");
                        }

                        strcpy(sn->stimi, str);

                        sn->sclass=CONSTANT;

                       }
                 break;

               }

            break;
            case REAL:

                  switch(rhs->typos){

                     case INT:
                          sn->typos= REAL;

                          if(rhs->sclass == MEMORY){

                            fprintf(text,"dconst %lf\n",lhs->dtimi);
                            fprintf(text,"iload_ %d\n",rhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"dmul\n");

                           }
                           else if(rhs->sclass == CONSTANT){

                            sn->dtimi = lhs->dtimi * rhs->timi;
                            sn->sclass=CONSTANT;

                           }
                     break;
                     case REAL:
                          sn->typos= REAL;

                          if(rhs->sclass == MEMORY){

                            fprintf(text,"dconst %lf\n",lhs->dtimi);
                            fprintf(text,"dload_ %d\n",rhs->index);
                            fprintf(text,"dmul\n");

                           }
                           else if(rhs->sclass == CONSTANT){

                            sn->dtimi = lhs->dtimi * rhs->dtimi;
                            sn->sclass=CONSTANT;

                           }
                     break;

                   }

            break;

          }
      break;
    }
  }
   else if (p->pAstNode[1]->NodeType == astDivOp || p->pAstNode[1]->NodeType == astIdivOp ) {

     switch(lhs->sclass)
      {
       case MEMORY:

         switch(lhs->typos){

           case INT:

               switch(rhs->typos){

                 case INT:

                      if(rhs->sclass == MEMORY)
                      {

                         fprintf(text,"iload_ %d\n",lhs->index);
                         if(p->pAstNode[1]->NodeType == astDivOp)
                            fprintf(text,"i2d\n");

                         fprintf(text,"iload_ %d\n",rhs->index);
                         if(p->pAstNode[1]->NodeType == astDivOp)
                            fprintf(text,"i2d\n");

                         if(p->pAstNode[1]->NodeType == astDivOp){
                               fprintf(text,"ddiv\n");
                               sn->typos= REAL;
                        }
                         else{
                               fprintf(text,"idiv\n");
                               sn->typos= INT;
                        }

                      }
                      else if(rhs->sclass == CONSTANT)
                      {

                        fprintf(text,"iload_ %d\n",lhs->index);
                        if(p->pAstNode[1]->NodeType == astDivOp){
                           fprintf(text,"i2d\n");
                           fprintf(text,"dconst %d\n",rhs->timi);
                           fprintf(text,"ddiv\n");
                           sn->typos= REAL;
                        }
                        else {
                           fprintf(text,"iconst %d\n",rhs->timi);
                           fprintf(text,"idiv\n");
                           sn->typos= INT;
                        }



                      }
                 break;

                 case REAL:

                          if(rhs->sclass == CONSTANT)
                          {

                            fprintf(text,"iload_ %d\n",lhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"dconst %lf\n",rhs->dtimi);
                            fprintf(text,"ddiv\n");

                            if(p->pAstNode[1]->NodeType == astIdivOp){
                                fprintf(text,"d2i\n");
                                sn->typos=INT;
                            }
                            else
                               sn->typos=REAL;

                          }else if(rhs->sclass == MEMORY){


                            fprintf(text,"iload_ %d\n",lhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"dload_ %d\n",rhs->index);
                            fprintf(text,"ddiv\n");

                            if(p->pAstNode[1]->NodeType == astIdivOp){
                              fprintf(text,"d2i\n");
                              sn->typos=INT;
                            }
                            else
                              sn->typos=REAL;


                          }

                 break;
               }
             break;
           case REAL:

               switch(rhs->typos){

                     case INT:

                          if(rhs->sclass == CONSTANT)
                          {
                            fprintf(text,"dload_ %d\n",lhs->index);
                            fprintf(text,"dconst %d\n",rhs->timi);
                            fprintf(text,"ddiv\n");

                            if(p->pAstNode[1]->NodeType == astIdivOp){
                              fprintf(text,"d2i\n");
                              sn->typos=INT;
                            }
                            else
                              sn->typos=REAL;

                          }else if(rhs->sclass == MEMORY){


                            fprintf(text,"dload_ %d\n",lhs->index);
                            fprintf(text,"iload_ %d\n",rhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"ddiv\n");

                            if(p->pAstNode[1]->NodeType == astIdivOp){
                              fprintf(text,"d2i\n");
                              sn->typos=INT;
                            }
                            else
                              sn->typos=REAL;
                          }
                     break;

                     case REAL:

                             if(rhs->sclass == CONSTANT) {

                               fprintf(text,"dload_ %d\n",lhs->index);
                               fprintf(text,"dconst %lf\n",rhs->dtimi);
                               fprintf(text,"ddiv\n");

                               if(p->pAstNode[1]->NodeType == astIdivOp){
                                 fprintf(text,"d2i\n");
                                 sn->typos=INT;
                               }
                               else
                                  sn->typos=REAL;

                            }else if(rhs->sclass == MEMORY){


                               fprintf(text,"dload_ %d\n",lhs->index);
                               fprintf(text,"dload_ %d\n",rhs->index);
                               fprintf(text,"ddiv\n");

                               if(p->pAstNode[1]->NodeType == astIdivOp){
                                 fprintf(text,"d2i\n");
                                 sn->typos=INT;
                               }
                               else
                                  sn->typos=REAL;

                            }
                     break;
                   }
           break;
         }
       break;
       case STACK:

         switch(lhs->typos){

           case INT:

               switch(rhs->typos){

                 case INT:

                      if(rhs->sclass == MEMORY)
                      {
                         if(p->pAstNode[1]->NodeType == astDivOp)
                            fprintf(text,"i2d\n");

                         fprintf(text,"iload_ %d\n",rhs->index);

                         if(p->pAstNode[1]->NodeType == astDivOp)
                            fprintf(text,"i2d\n");

                         if(p->pAstNode[1]->NodeType == astDivOp){
                               fprintf(text,"ddiv\n");
                               sn->typos= REAL;
                          }
                         else{
                            fprintf(text,"idiv\n");
                            sn->typos= INT;
                          }

                      }
                      else if(rhs->sclass == CONSTANT)
                      {

                        if(p->pAstNode[1]->NodeType == astDivOp)
                           fprintf(text,"i2d\n");

                        if(p->pAstNode[1]->NodeType == astDivOp)
                          fprintf(text,"dconst %d\n",rhs->timi);
                        else
                          fprintf(text,"iconst %d\n",rhs->timi);

                        if(p->pAstNode[1]->NodeType == astDivOp){
                          fprintf(text,"ddiv\n");
                          sn->typos= REAL;
                        }
                        else{
                          fprintf(text,"idiv\n");
                          sn->typos= INT;
                        }



                      }
                 break;

                 case REAL:

                          if(rhs->sclass == CONSTANT)
                          {

                            fprintf(text,"i2d\n");
                            fprintf(text,"dconst %lf\n",rhs->dtimi);
                            fprintf(text,"ddiv\n");

                            if(p->pAstNode[1]->NodeType == astIdivOp){
                              fprintf(text,"d2i\n");
                              sn->typos=INT;
                            }
                            else
                              sn->typos=REAL;

                          }else if(rhs->sclass == MEMORY){

                            fprintf(text,"i2d\n");
                            fprintf(text,"dload_ %d\n",rhs->index);
                            fprintf(text,"ddiv\n");

                            if(p->pAstNode[1]->NodeType == astIdivOp){
                              fprintf(text,"d2i\n");
                              sn->typos=INT;
                            }
                            else
                              sn->typos=REAL;

                          }

                 break;
               }
             break;
           case REAL:

               switch(rhs->typos){

                     case INT:

                          if(rhs->sclass == CONSTANT)
                          {

                            fprintf(text,"dconst %d\n",rhs->timi);
                            fprintf(text,"ddiv\n");

                            if(p->pAstNode[1]->NodeType == astIdivOp){
                              fprintf(text,"d2i\n");
                              sn->typos=INT;
                            }
                            else
                              sn->typos=REAL;

                          }else if(rhs->sclass == MEMORY){

                            fprintf(text,"iload_ %d\n",rhs->index);
                            fprintf(text,"i2d\n");
                            fprintf(text,"ddiv\n");

                            if(p->pAstNode[1]->NodeType == astIdivOp){
                              fprintf(text,"d2i\n");
                              sn->typos=INT;
                            }
                            else
                              sn->typos=REAL;

                          }
                     break;

                     case REAL:

                             if(rhs->sclass == CONSTANT) {


                               fprintf(text,"dconst %lf\n",rhs->dtimi);
                               fprintf(text,"ddiv\n");

                               if(p->pAstNode[1]->NodeType == astIdivOp){
                                 fprintf(text,"d2i\n");
                                 sn->typos=INT;
                               }
                               else
                                  sn->typos=REAL;

                            }else if(rhs->sclass == MEMORY){

                               fprintf(text,"dload_ %d\n",rhs->index);
                               fprintf(text,"ddiv\n");

                               if(p->pAstNode[1]->NodeType == astIdivOp){
                                 fprintf(text,"d2i\n");
                                 sn->typos=INT;
                               }
                               else
                                  sn->typos=REAL;

                            }
                     break;
                   }
           break;
         }
       break;
       case CONSTANT:

         switch(lhs->typos){

             case INT:

                switch(rhs->typos){

                  case INT:

                       if(rhs->sclass == MEMORY){

                         if(p->pAstNode[1]->NodeType == astDivOp)
                            fprintf(text,"dconst %d\n",lhs->index);
                         else
                            fprintf(text,"iconst %d\n",lhs->index);

                         fprintf(text,"iload_ %d\n",rhs->index);

                         if(p->pAstNode[1]->NodeType == astDivOp)
                            fprintf(text,"i2d\n");

                        if(p->pAstNode[1]->NodeType == astDivOp){
                            fprintf(text,"ddiv\n");
                            sn->typos= REAL;
                          }
                        else{
                           fprintf(text,"idiv\n");
                           sn->typos= INT;
                         }



                        }
                        else if(rhs->sclass == CONSTANT){

                          if(rhs->timi !=0){
                             if(p->pAstNode[1]->NodeType == astDivOp){
                                sn->dtimi = (float)lhs->timi / rhs->timi;
                                sn->typos= REAL;
                              }
                             else{
                                sn->timi = lhs->timi / rhs->timi;
                                sn->typos= INT;
                              }

                             sn->sclass=CONSTANT;
                          }else{

                            printf("You cannot divide by zero\n");
                            exit(1);
                          }

                        }
                  break;
                  case REAL:

                        if(rhs->sclass == MEMORY){

                          fprintf(text,"dconst %d\n",lhs->index);
                          fprintf(text,"dload_ %d\n",rhs->index);
                          fprintf(text,"ddiv\n");

                          if(p->pAstNode[1]->NodeType == astIdivOp){
                            fprintf(text,"d2i\n");
                            sn->typos=INT;
                          }
                          else
                            sn->typos=REAL;

                        }
                        else if(rhs->sclass == CONSTANT){

                          if(rhs->dtimi !=0){
                            if(p->pAstNode[1]->NodeType == astIdivOp){
                              sn->timi = (int)(lhs->timi / rhs->dtimi);
                              sn->typos=INT;
                            }
                            else {
                              sn->dtimi = (lhs->timi / rhs->dtimi);
                              sn->typos=REAL;
                            }
                             sn->sclass=CONSTANT;
                          }else{

                            printf("You cannot divide by zero\n");
                            exit(1);
                          }

                        }
                  break;

                }

             break;
             case REAL:

                   switch(rhs->typos){

                      case INT:


                           if(rhs->sclass == MEMORY){

                             fprintf(text,"dconst %lf\n",lhs->dtimi);
                             fprintf(text,"iload_ %d\n",rhs->index);
                             fprintf(text,"i2d\n");
                             fprintf(text,"ddiv\n");

                             if(p->pAstNode[1]->NodeType == astIdivOp){
                               fprintf(text,"d2i\n");
                               sn->typos=INT;
                             }
                             else
                                sn->typos=REAL;

                            }
                            else if(rhs->sclass == CONSTANT){


                              if(rhs->dtimi !=0){
                                if(p->pAstNode[1]->NodeType == astIdivOp){
                                  sn->timi = (int)(lhs->dtimi / rhs->timi);
                                  sn->typos=INT;
                                }
                                else {
                                  sn->dtimi = (lhs->dtimi / rhs->timi);
                                  sn->typos=REAL;
                                }
                                 sn->sclass=CONSTANT;
                              }else{

                                printf("You cannot divide by zero\n");
                                exit(1);
                              }

                            }
                      break;
                      case REAL:


                           if(rhs->sclass == MEMORY){

                             fprintf(text,"dconst %lf\n",lhs->dtimi);
                             fprintf(text,"dload_ %d\n",rhs->index);
                             fprintf(text,"ddiv\n");

                             if(p->pAstNode[1]->NodeType == astIdivOp){
                               fprintf(text,"d2i\n");
                               sn->typos=INT;
                             }
                             else
                                sn->typos=REAL;

                            }
                            else if(rhs->sclass == CONSTANT){

                              if(rhs->dtimi !=0){
                                if(p->pAstNode[1]->NodeType == astIdivOp){
                                  sn->timi = (int)(lhs->dtimi / rhs->dtimi);
                                  sn->typos=INT;
                                }
                                else {
                                  sn->dtimi = (lhs->dtimi / rhs->dtimi);
                                  sn->typos=REAL;
                                }
                                 sn->sclass=CONSTANT;
                              }else{

                                printf("You cannot divide by zero\n");
                                exit(1);
                              }

                            }
                      break;

                    }

             break;

           }

       break;
      }
   }



   push_vs(sn);


}


//Declarations
void ProcessDeclsSeq(AstNode *p,int lev,int lvalue,int leftChild){
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
}

//Declaration List
void ProcessDeclListSeq(AstNode *p,int lev,int lvalue,int leftChild){
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	CodeGeneration(p->pAstNode[1],lev+1,0,0);

}

//Declaration
void ProcessDecl(AstNode *p,int lev,int lvalue,int leftChild){




	int lhs;

	lhs  = p->pAstNode[0] -> NodeType;

	switch(lhs){

		case astInt:
				//Variable Declaration
				fprintf(text,"v_iconst 0\n");
		break;
		case astReal:

				fprintf(text,"v_dconst 0.0\n");

		break;
		case astBool:
				//Variable Declaration
				fprintf(text,"v_iconst 0\n");
		break;
    case astStr:
				//Variable Declaration
				fprintf(text,"v_sconst \"\"\n");
		break;
    case astPointer:
				//Variable Declaration
				fprintf(text,"v_rconst Null\n");
		break;

	}


	//Code Generation for next variables
	CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
}


//Declaration Assign
void ProcessDeclAssign(AstNode *p,int lev,int lvalue,int leftChild){

	symbol  *rhs;
	int lhs;

	lhs = p->pAstNode[0]->NodeType;

	//Code Generation for expression
	CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
	rhs = pop_vs();

	switch(rhs->sclass){

		case CONSTANT:

			switch(rhs->typos){

				case INT:

					switch(lhs){

						case astInt:

							 fprintf(text,"v_iconst %d\n",rhs->timi);

					    break;
						case astReal:

							 fprintf(text,"v_dconst %d\n", rhs->timi);

						break;
						case astBool:

						    printf("Error: bad operand types for binary operator \n");
							exit(1);

					    break;

					}

				break;
				case REAL:

					switch(lhs){

							case astInt:

								 fprintf(text,"v_iconst %d\n",(int) rhs->dtimi);

							break;
							case astReal:

								 fprintf(text,"v_dconst %lf\n", rhs->dtimi);

							break;
							case astBool:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
							break;

						}


				break;
				case BOOL:

					switch(lhs){

						case astInt:

							 printf("Error: bad operand types for binary operator \n");
							 exit(1);

					    break;
						case astReal:

							 printf("Error: bad operand types for binary operator \n");
							 exit(1);

						break;
						case astBool:

						     fprintf(text,"v_iconst %d\n",rhs->timi);

					    break;

					}

				break;
        case STR:

					switch(lhs){

						case astInt:

                printf("Error: bad operand types for binary operator \n");
                exit(1);

					  break;
						case astReal:

                printf("Error: bad operand types for binary operator \n");
                exit(1);

						break;
						case astBool:

						    printf("Error: bad operand types for binary operator \n");
							  exit(1);

					  break;
            case astStr:

						    fprintf(text,"v_sconst \"%s\"\n",rhs->stimi);

					  break;

					}

				break;


			}
		break;
		case MEMORY:

				switch(rhs->typos){

						case INT:

							switch(lhs){

								case astInt:

									 fprintf(text,"push dword [%s]\n",rhs->pseudonym);

								break;
								case astReal:


									 fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
									 fprintf(text,"sub esp,8\n");
									 fprintf(text,"fstp qword [esp]\n");

								break;
								case astBool:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;

							}

						break;
						case REAL:

							switch(lhs){

									case astInt:
										 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
										 //fprintf(text,"fldcw [cw]\n");
										 fprintf(text,"fistp dword [esp]\n");

									break;
									case astReal:

										 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
										 fprintf(text,"sub esp,8\n");
										 fprintf(text,"fstp qword [esp]\n");

									break;
									case astBool:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;

								}


						break;
						case BOOL:

							switch(lhs){

								case astInt:

									 fprintf(text,"push dword [%s]\n",rhs->pseudonym);

								break;
								case astReal:

									printf("Error: bad operand types for binary operator \n");
									exit(1);

								break;
								case astBool:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;

							}

						break;
            case STR:

							switch(lhs){

                case astInt:

                    printf("Error: bad operand types for binary operator \n");
                    exit(1);

								break;

								case astString:

									 fprintf(text,"push dword [%s]\n",rhs->pseudonym);

								break;
								case astReal:

                    printf("Error: bad operand types for binary operator \n");
                    exit(1);

								break;
								case astBool:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;

							}

						break;

					}




		break;
		case REGISTER:

			switch(rhs->typos){

						case INT:

							switch(lhs){

								case astInt:

									 fprintf(text,"push dword [rgs]\n");

								break;
								case astReal:


									 fprintf(text,"fild dword [rgs]\n");
									 fprintf(text,"sub esp,8\n");
									 fprintf(text,"fstp qword [esp]\n");

								break;
								case astBool:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;

							}

						break;
						case REAL:

							switch(lhs){

									case astInt:
										 fprintf(text,"fld qword [frgs]\n");
										 //fprintf(text,"fldcw [cw]\n");
										 fprintf(text,"fistp dword [esp]\n");

									break;
									case astReal:

										 fprintf(text,"fld qword [frgs]\n");
										 fprintf(text,"sub esp,8\n");
										 fprintf(text,"fstp qword [esp]\n");

									break;
									case astBool:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;

								}


						break;
						case BOOL:

							switch(lhs){

								case astInt:

									    printf("Error: bad operand types for binary operator \n");
										exit(1);

								break;
								case astReal:

										printf("Error: bad operand types for binary operator \n");
										exit(1);

								break;
								case astBool:
										fprintf(text,"push dword [rgs]\n");
								break;

							}

						break;


					}



		break;
		case STACK:

			 fprintf(text,"ERROR DECLASSIGN[MEMORY-STACK]\n");

		break;


	}

	//Code Generation for next variables
	CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);

}

//Variables
void ProcessVarsSeq(AstNode *p,int lev,int lvalue,int leftChild) {

	symbol * lhs;
	lhs  = p->SymbolNode;

	switch(lhs->typos){

		case INT:

				//Variable Declaration
				fprintf(text,"v_iconst 0\n");
		break;
		case REAL:

				fprintf(text,"v_dconst 0.0\n");

		break;
		case BOOL:

				//Variable Declaration
				fprintf(text,"v_iconst 0\n");
		break;


	}





	//Code Generation for next variables
	CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);

}

//Variable Assign
void ProcessVarAssign(AstNode *p,int lev){

	symbol *lhs, *rhs;

	lhs = p -> SymbolNode;

	//Code Generation for expression
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	rhs = pop_vs();


	switch(rhs->sclass){

		case CONSTANT:

			switch(rhs->typos){

				case INT:

					switch(lhs->typos){

						case INT:

							 fprintf(text,"v_iconst %d\n",rhs->timi);

					    break;
						case REAL:

							 fprintf(text,"v_dconst %d\n",rhs->timi);

						break;
						case BOOL:

							printf("Error: bad operand types for binary operator \n");
							exit(1);

					    break;

					}

				break;
				case REAL:

					switch(lhs->typos){

							case INT:

								 fprintf(text,"v_iconst %d\n",(int) rhs->dtimi);

							break;
							case REAL:

								 fprintf(text,"v_dconst %lf\n",rhs->dtimi);

							break;
							case BOOL:

								printf("Error: bad operand types for binary operator \n");
								exit(1);

							break;

						}


				break;
				case BOOL:

					switch(lhs->typos){

						case INT:

							 printf("Error: bad operand types for binary operator \n");
							 exit(1);

					    break;
						case REAL:

							 printf("Error: bad operand types for binary operator \n");
							 exit(1);

						break;
						case BOOL:

							 fprintf(text,"v_iconst %d\n",rhs->timi);

					    break;

					}

				break;


			}
		break;
		case MEMORY:

				switch(rhs->typos){

						case INT:

							switch(lhs->typos){

								case INT:

									 fprintf(text,"iload_ %d\n",rhs->index);

								break;
								case REAL:

									 fprintf(text,"iload_ %d\n",rhs->index);

								break;
								case BOOL:

									 printf("Error: bad operand types for binary operator \n");
									 exit(1);

								break;

							}

						break;
						case REAL:

							switch(lhs->typos){

									case INT:
										  fprintf(text,"dload_ %d\n",rhs->index);

									break;
									case REAL:

										 fprintf(text,"dload_ %d\n",rhs->index);

									break;
									case BOOL:

										 printf("Error: bad operand types for binary operator \n");
										 exit(1);

									break;

								}


						break;
						case BOOL:

							switch(lhs->typos){

								case INT:

									 printf("Error: bad operand types for binary operator \n");
									 exit(1);

								break;
								case REAL:

									 printf("Error: bad operand types for binary operator \n");
									 exit(1);

								break;
								case BOOL:

									  fprintf(text,"iload_ %d\n",rhs->index);

								break;

							}

						break;


					}
		break;

		case STACK:

			 fprintf(text,"ERROR DECLASSIGN[MEMORY-STACK]\n");

		break;


	}

	//Code Generation for next variables
	CodeGeneration(p->pAstNode[1],lev+1,0,0);

}

//Parameters
void ProcessParamSeq(AstNode *p,int lev,int lvalue,int leftChild){

  BYTES_OF_PARAMETERS +=1;

	//Code Generation for previous parameters
	CodeGeneration(p->pAstNode[0],lev+1,0,0);

	push_vs(p->SymbolNode);

}

//Formals
void ProcessFormalsSeq(AstNode *p,int lev,int lvalue,int leftChild){

  BYTES_OF_PARAMETERS +=1;
	//Code Generation for previous parameters
	CodeGeneration(p->pAstNode[0],lev+1,0,0);

	push_vs(p->SymbolNode);

}


//Actuals
void  ProcessActuals(AstNode *p,int lev,int lvalue,int leftChild){

	symbol *rhs;



	//Code Generation for expression
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
	rhs = pop_vs();

	if(rhs->sclass == MEMORY){

		 switch(rhs->typos){

			 case INT:
           if(rhs->field == 0){
               fprintf(text,"iload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;
			 case REAL:
           if(rhs->field == 0){
               fprintf(text,"dload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;
			 case BOOL:
           if(rhs->field == 0){
               fprintf(text,"iload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;
       case STR:
           if(rhs->field == 0){
               fprintf(text,"sload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;
       default:
           if(rhs->field == 0){
               fprintf(text,"rload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;

		}

	}
	else if (rhs->sclass == CONSTANT){


		 switch(rhs->typos){


			 case INT:
				fprintf(text,"iconst %d\n",rhs->timi);
			 break;
			 case REAL:
				fprintf(text,"dconst %lf\n",rhs->dtimi);
			 break;
			 case BOOL:
				fprintf(text,"iconst %d\n",rhs->timi);
			 break;
       case STR:
				fprintf(text,"sconst \"%s\"\n",rhs->stimi);
			 break;

		}

	}


	//Code Generation for previous argument expressions
	CodeGeneration(p->pAstNode[0],lev+1,0,0);

  char snum[6];
  nitoa(rhs->typos,snum);
  strcat(PARAMETERS_CALL,snum);

}

//Args
void  ProcessArgsSeq(AstNode *p,int lev,int lvalue,int leftChild){

	symbol *rhs;


	//Code Generation for expression
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
	rhs = pop_vs();


  if(rhs->sclass == MEMORY){

		 switch(rhs->typos){

			 case INT:
           if(rhs->field == 0){
               fprintf(text,"iload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;
			 case REAL:
           if(rhs->field == 0){
               fprintf(text,"dload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;
			 case BOOL:
           if(rhs->field == 0){
               fprintf(text,"iload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;
       case STR:
           if(rhs->field == 0){
               fprintf(text,"sload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;
       default:
           if(rhs->field == 0){
               fprintf(text,"rload_ %d\n",rhs->index);
             }
           else{
               fprintf(text,"rload_ 1\n");
               fprintf(text,"getfield %s\n",rhs->name);
             }
			 break;

		}

	}
	else if (rhs->sclass == CONSTANT){


		 switch(rhs->typos){


			 case INT:
				fprintf(text,"iconst %d\n",rhs->timi);
			 break;
			 case REAL:
				fprintf(text,"dconst %lf\n",rhs->dtimi);
			 break;
			 case BOOL:
				fprintf(text,"iconst %d\n",rhs->timi);
			 break;
       case STR:
				fprintf(text,"sconst \"%s\"\n",rhs->stimi);
			 break;

		}

	}


	//Code Generation for previous argument expressions
	CodeGeneration(p->pAstNode[0],lev+1,0,0);

  char snum[6];
  nitoa(rhs->typos,snum);
  strcat(PARAMETERS_CALL,snum);

}


//Return Statement
void ProcessReturnStmt(AstNode *p,int lev,int lvalue,int leftChild){

	symbol *rhs;

	//Code Generation for expression
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	rhs = pop_vs();



	if(rhs->sclass == MEMORY){

		 switch(rhs->typos){

			case INT:
				//Push
        if(rhs->field == 0){
            fprintf(text,"iload_ %d\n",rhs->index);
          }
        else{
            fprintf(text,"rload_ 1\n");
            fprintf(text,"getfield %s\n",rhs->name);
          }

			break;
			case REAL:
				//Push
        if(rhs->field == 0){
            fprintf(text,"rload_ %d\n",rhs->index);
          }
        else{
            fprintf(text,"rload_ 1\n");
            fprintf(text,"getfield %s\n",rhs->name);
          }
			break;
			case BOOL:
				//Push
        if(rhs->field == 0){
            fprintf(text,"iload_ %d\n",rhs->index);
          }
        else{
            fprintf(text,"rload_ 1\n");
            fprintf(text,"getfield %s\n",rhs->name);
          }
			break;
      case STR:
				//Push
        if(rhs->field == 0){
            fprintf(text,"sload_ %d\n",rhs->index);
          }
        else{
            fprintf(text,"rload_ 1\n");
            fprintf(text,"getfield %s\n",rhs->name);
          }
			break;
      default:
				//Push
        if(rhs->field == 0){
            fprintf(text,"rload_ %d\n",rhs->index);
          }
        else{
            fprintf(text,"rload_ 1\n");
            fprintf(text,"getfield %s\n",rhs->name);
          }
			break;

		}


	}
  else if(rhs->sclass == STACK){

		 switch(rhs->typos){

			case INT:
				//Push
				//fprintf(text,"iload_ %d\n",rhs->index);
			break;
			case REAL:
				//Push
				//fprintf(text,"dload_ %d\n",rhs->index);
			break;
			case BOOL:
				//Push
				//fprintf(text,"iload_ %d\n",rhs->index);
			break;

		}


	}
	else if (rhs->sclass == CONSTANT){

		 switch(rhs->typos){

			case INT:

				//Push
				fprintf(text,"iconst %d\n",rhs->timi);
				//fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);

			break;
			case REAL:

				fprintf(text,"dconst %lf\n",rhs->dtimi);
				//fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);

			break;
			case BOOL:

				//Push
				fprintf(text,"iconst %d\n",rhs->timi);
				//fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);

			break;
      case STR:

				//Push
				fprintf(text,"sconst \"%s\"\n",rhs->stimi);
				//fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);

			break;
      default:
        fprintf(text,"rload_ 1\n");
      break;
		}


	}


	fprintf(data,"iconst %d\n",BYTES_OF_PARAMETERS);
	fprintf(data,"ret\n");
}



//Print Statement -DEAD
void ProcessPrintStmt(AstNode *p,int lev,int lvalue,int leftChild){

	//Code Generation for expression
	CodeGeneration(p->pAstNode[0],lev+1,0,1);
	//rhs = pop_vs();

}

//PrintLn Statement
void ProcessPrintLnStmt(AstNode *p,int lev,int lvalue,int leftChild){

	//Code Generation for expression
	CodeGeneration(p->pAstNode[0],lev+1,0,2);
	//rhs = pop_vs();

}


 void ProcessLiteralStmt(AstNode *p,int lev,int lvalue,int leftChild){


	 fprintf(text,"sconst \"%s\"\n",p->SymbolNode->stimi);


 }

void ProcessLiteralLnStmt(AstNode *p,int lev,int lvalue,int leftChild){


	 fprintf(text,"sconst \"%s\"\n",p->SymbolNode->stimi);


 }

//Print Literal Statement
void ProcessPrintLtStmt(AstNode *p,int lev,int lvalue,int leftChild){

  symbol *rhs;

	//Code Generation for literal
	ProcessLiteralLnStmt(p,lev+1,0,0);
	NUM_OF_LITERALS++;
  fprintf(text,"print\n");

}

//Println Literal Statement
void ProcessPrintLnLtStmt(AstNode *p,int lev,int lvalue,int leftChild){

	symbol *rhs;

	//Code Generation for literal
	ProcessLiteralLnStmt(p,lev+1,0,0);
	NUM_OF_LITERALS++;
  fprintf(text,"print\n");
  fprintf(text,"nl\n");
    //fprintf(text,"add  esp, 4\n");

}



void ProcessExprInline(AstNode *p,int lev,int lvalue,int leftChild){

   symbol *rhs;
   CodeGeneration(p->pAstNode[0],lev+1,0,0);
   rhs = pop_vs();

   if(rhs->sclass == MEMORY){

       		switch (rhs->typos){

       			case BOOL:


                if(rhs->field == 0){

                    fprintf(text,"iload_ %d\n",rhs->index);
                  }
                else{
                    fprintf(text,"rload_ 1\n");
                    fprintf(text,"getfield %s\n",rhs->name);
                  }

                fprintf(text,"i2s\n");
       					fprintf(text,"print\n");

       			break;

       			case INT:

                if(rhs->field == 0){

                    fprintf(text,"iload_ %d\n",rhs->index);
                  }
                else{
                    fprintf(text,"rload_ 1\n");
                    fprintf(text,"getfield %s\n",rhs->name);
                  }

                 fprintf(text,"i2s\n");
                 fprintf(text,"print\n");
       			break;
       			case REAL:

                if(rhs->field == 0){

                    fprintf(text,"dload_ %d\n",rhs->index);
                  }
                else{
                    fprintf(text,"rload_ 1\n");
                    fprintf(text,"getfield %s\n",rhs->name);
                  }

                 fprintf(text,"d2s\n");
                 fprintf(text,"print\n");
       			break;
             case STR:

               if(rhs->field == 0){

                   fprintf(text,"sload_ %d\n",rhs->index);
                 }
               else{
                   fprintf(text,"rload_ 1\n");
                   fprintf(text,"getfield %s\n",rhs->name);
                 }

                 fprintf(text,"print\n");
       			break;

       		}

 	}
   else if(rhs->sclass == STACK){

         		switch (rhs->typos){

         			case BOOL:


                   fprintf(text,"i2s\n");
         					fprintf(text,"print\n");

         			break;

         			case INT:

                   fprintf(text,"i2s\n");
                   fprintf(text,"print\n");
         			break;
         			case REAL:

                   fprintf(text,"d2s\n");
                   fprintf(text,"print\n");
         			break;
               case STR:
                   fprintf(text,"print\n");
         			break;

         		}

 	}
 	else if (rhs->sclass == CONSTANT){

       		switch (rhs->typos){

       			case BOOL:

                 fprintf(text,"iconst %d\n",rhs->timi);
                 fprintf(text,"i2s\n");
                 fprintf(text,"print\n");
       			break;

       			case INT:

                 fprintf(text,"iconst %d\n",rhs->timi);
                 fprintf(text,"i2s\n");
                 fprintf(text,"print\n");
       			break;
       			case REAL:

                 fprintf(text,"dconst %lf\n",rhs->dtimi);
                 fprintf(text,"d2s\n");
                 fprintf(text,"print\n");

       			break;
             case STR:

                 fprintf(text,"sconst \"%s\"\n",rhs->stimi);
                 fprintf(text,"print\n");

       			break;

       		}


 	}

	 CodeGeneration(p->pAstNode[1],lev+1,0,leftChild);

}

void ProcessLiteralInline(AstNode *p,int lev,int lvalue,int leftChild){

	 ProcessPrintLtStmt(p,lev+1,0,0);
	 CodeGeneration(p->pAstNode[0],lev+1,0,0);

}

void ProcessSingleExprInline(AstNode *p,int lev,int lvalue,int leftChild){

  symbol *rhs;
  CodeGeneration(p->pAstNode[0],lev+1,0,0);
  rhs = pop_vs();

  if(rhs->sclass == MEMORY){

         switch (rhs->typos){

           case BOOL:


               if(rhs->field == 0){

                   fprintf(text,"iload_ %d\n",rhs->index);
                 }
               else{
                   fprintf(text,"rload_ 1\n");
                   fprintf(text,"getfield %s\n",rhs->name);
                 }

               fprintf(text,"i2s\n");
               fprintf(text,"print\n");

           break;

           case INT:

               if(rhs->field == 0){

                   fprintf(text,"iload_ %d\n",rhs->index);
                 }
               else{
                   fprintf(text,"rload_ 1\n");
                   fprintf(text,"getfield %s\n",rhs->name);
                 }

                fprintf(text,"i2s\n");
                fprintf(text,"print\n");
           break;
           case REAL:

               if(rhs->field == 0){

                   fprintf(text,"dload_ %d\n",rhs->index);
                 }
               else{
                   fprintf(text,"rload_ 1\n");
                   fprintf(text,"getfield %s\n",rhs->name);
                 }

                fprintf(text,"d2s\n");
                fprintf(text,"print\n");
           break;
            case STR:

              if(rhs->field == 0){

                  fprintf(text,"sload_ %d\n",rhs->index);
                }
              else{
                  fprintf(text,"rload_ 1\n");
                  fprintf(text,"getfield %s\n",rhs->name);
                }

                fprintf(text,"print\n");
           break;

         }

 }
  else if(rhs->sclass == STACK){

           switch (rhs->typos){

             case BOOL:


                  fprintf(text,"i2s\n");
                 fprintf(text,"print\n");

             break;

             case INT:

                  fprintf(text,"i2s\n");
                  fprintf(text,"print\n");
             break;
             case REAL:

                  fprintf(text,"d2s\n");
                  fprintf(text,"print\n");
             break;
              case STR:
                  fprintf(text,"print\n");
             break;

           }

 }
 else if (rhs->sclass == CONSTANT){

         switch (rhs->typos){

           case BOOL:

                fprintf(text,"iconst %d\n",rhs->timi);
                fprintf(text,"i2s\n");
                fprintf(text,"print\n");
           break;

           case INT:

                fprintf(text,"iconst %d\n",rhs->timi);
                fprintf(text,"i2s\n");
                fprintf(text,"print\n");
           break;
           case REAL:

                fprintf(text,"dconst %lf\n",rhs->dtimi);
                fprintf(text,"d2s\n");
                fprintf(text,"print\n");

           break;
            case STR:

                fprintf(text,"sconst \"%s\"\n",rhs->stimi);
                fprintf(text,"print\n");

           break;

         }


 }

  switch(leftChild){

    case 1:
    break;
    case 2:
       fprintf(text,"nl\n");
    break;
  }

}

void ProcessSingleLiteralInline(AstNode *p,int lev,int lvalue,int leftChild){

	  ProcessPrintLnLtStmt(p,lev+1,0,0);
	 //CodeGeneration(p->pAstNode[1],lev+1,0,0);

}

 //Read Statement
void ProcessReadStmt(AstNode *p,int lev,int lvalue,int leftChild){

	symbol *lhs, *rhs;

	//Code Generation for literal
  CodeGeneration(p->pAstNode[0],lev+1,0,0);

	lhs = pop_vs();

  switch(lhs->sclass){

    case MEMORY:
      fprintf(text,"sload_ %d\n",lhs->index);
    break;
    case STACK:

    break;
    case CONSTANT:
      fprintf(text,"sconst \"%s\"\n",lhs->stimi);
    break;
  }

  NUM_OF_LITERALS++;

  fprintf(text,"print\n");
  fprintf(text,"read\n");
	//Code Generation for location
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
	rhs = pop_vs();

	if(rhs->sclass == MEMORY){

		switch(rhs->typos){

			case INT:
          fprintf(text,"s2i\n");
          if(rhs->field == 0){
              fprintf(text,"istore_ %d\n",rhs->index);
            }
          else{
              fprintf(text,"rload_ 1\n");
              fprintf(text,"putfield %s\n",rhs->name);
            }
			break;
			case REAL:
          fprintf(text,"s2d\n");
          if(rhs->field == 0){
              fprintf(text,"dstore_ %d\n",rhs->index);
            }
          else{
              fprintf(text,"rload_ 1\n");
              fprintf(text,"putfield %s\n",rhs->name);
            }

			break;
      case STR:
          if(rhs->field == 0){
              fprintf(text,"sstore_ %d\n",rhs->index);
            }
          else{
              fprintf(text,"rload_ 1\n");
              fprintf(text,"putfield %s\n",rhs->name);
            }

			break;



	}

	}
}

 /* ------------------------------------------------------------------------ */


/* CodeGeneration */

void CodeGeneration(AstNode *p, int lev, int lvalue, int leftChild)
{

    switch (p->NodeType)
      {
         case astEmptyProgram:
         break;
		 //case astLibList:
            // ProcessLibList(p,lev,0);
        // break;
		// case astEmptyLib:

        // break;
		 //case astLib:
             //ProcessLib(p,lev,0);
        // break;
         case astClassDef:
            ProcessClassDef(p,lev);
         break;
         case astFuncDef:
            ProcessFuncDef(p,lev);
         break;
         case astDeclDef:
            ProcessDeclDef(p,lev);
         break;
         case astClass:
            ProcessClass(p,lev);
         break;
         case astSelf:
            ProcessSelf(p);
         break;
         case astPrivateClassMod:
          //  ProcessPrivateClassMod(p,lev);
         break;
         case astPublicClassMod:
          //  ProcessPublicClassMod(p,lev);
         break;
         case astArrayIndex:
              ProcessArrayIndex(p,lev);
         break;
         case astAbstractClassMod:
          //  ProcessAbstractClassMod(p,lev);
         break;
         case astStr:
          //  ProcessAbstractClassMod(p,lev);
         break;
         case astBodyClass:
            ProcessBodyClass(p,lev);
         break;
         case astFields:
            ProcessFields(p,lev);
         break;
         case astEmptyFields:
            ProcessEmptyFields(p,lev);
         break;
         case astField:
            ProcessField(p,lev);
         break;
         case astFieldAssign:
            ProcessFieldAssign(p,lev);
         break;
         case astAttrs:
            ProcessAttrs(p,lev);
         break;
         case astAttrsAssign:
            ProcessAttrsAssign(p,lev);
         break;
         case astEmptyAttrs:
            ProcessEmptyAttrs(p,lev);
         break;
         case astPrivateMod:
          //  ProcessPrivateMod(p,lev);
         break;
         case astPublicMod:
        //    ProcessPublicMod(p,lev);
         break;
         case astEmptyDef:
            ProcessEmptyDef(p,lev);
         break;
         case astEmptyMethList:
            ProcessEmptyMethList(p,lev);
         break;
         case astFuncLast:
            ProcessFuncLast(p,lev);
         break;
         case astProgram:
             ProcessProgram(p,lev);
         break;
         case astMethSeq:
             ProcessMethSeq(p,lev);
         break;
         case astMethLast:
             ProcessMethLast(p,lev);
         break;
         case astParamSeq:
             ProcessParamSeq(p,lev,lvalue,leftChild);
         break;
         case astParamEmpty:
             //ProcessParamEmpty(p,lev,lvalue,leftChild);
         break;
         case astFormalsSeq:
             ProcessFormalsSeq(p,lev,lvalue,leftChild);
         break;
         case astFormalsEmpty:
             //ProcessFormalsEmpty(p,lev,lvalue,leftChild);
         break;
         case astInt:
             //ProcessInt(p,lev,lvalue,leftChild);
         break;
		 case astReal:
             //ProcessReal(p,lev,lvalue,leftChild);
         break;
		 case astIfStmt:
		     ProcessIfStmt(p,lev,lvalue,leftChild);
         break;
         case astIfElseStmt:
             ProcessIfElseStmt(p,lev,lvalue,leftChild);
         break;
		 case astSingleIfStmt:
			 ProcessSingleIfStmt(p,lev,lvalue,leftChild);
		 break;
		 case astSingleUnlessStmt:
			 ProcessSingleUnlessStmt(p,lev,lvalue,leftChild);
		 break;
         case astBody:
             ProcessBody(p,lev);
         break;
         case astDeclsSeq:
             ProcessDeclsSeq(p,lev,lvalue,leftChild);
         break;
         case astDeclsEmpty:
             //ProcessDeclsEmpty(p,lev,lvalue,leftChild);
         break;
         case astDeclListSeq:
             ProcessDeclListSeq(p,lev,lvalue,leftChild);
         break;
         case astDeclListEmpty:
             //ProcessDeclListEmpty(p,lev,lvalue,leftChild);
         break;
         case astDecl:
             ProcessDecl(p,lev,lvalue,leftChild);
         break;
         case astDeclAssign:
             ProcessDeclAssign(p,lev,lvalue,leftChild);
         break;
         case astVarsSeq:
             ProcessVarsSeq(p,lev,lvalue,leftChild);
         break;
         case astVarAssign:
             ProcessVarAssign(p,lev);
         break;
         case astVarEmpty:
             //ProcessVarEmpty(p,lev,lvalue,leftChild);
         break;
         case astStmtSeq:
             ProcessStmtSeq(p,lev);
         break;
         case astStmtEmpty:
             //ProcessStmtEmpty(p,lev,lvalue,leftChild);
         break;
         case astLocation:
             ProcessLocation(p);
         break;
         case astReturnStmt:
             ProcessReturnStmt(p,lev,lvalue,leftChild);
         break;
         case astMethodName:
             ProcessMethodName(p);
         break;
         case astWhileStmt:
             ProcessWhileStmt(p,lev,lvalue,leftChild);
         break;
		     case astTimesStmt:
             ProcessTimesStmt(p,lev,lvalue,leftChild);
         break;
         case astForStmt:
             ProcessForStmt(p,lev,lvalue,leftChild);
         break;
         case astBreakStmt:
             ProcessBreakStmt();
         break;
    		 case astExprInline:
    			  ProcessExprInline(p,lev,lvalue,leftChild);
    		 break;
    		 case astLiteralInline:
    			  ProcessLiteralInline(p,lev,lvalue,leftChild);
    		 break;
    		 case astSingleExprInline:
    			  ProcessSingleExprInline(p,lev,lvalue,leftChild);
    		 break;
    		 case astSingleLiteralInline:
    			  ProcessSingleLiteralInline(p,lev,lvalue,leftChild);
    		 break;
    		 case astPrintStmt:
    			 ProcessPrintStmt(p,lev,lvalue,leftChild);
    		 break;
         case astPointer:
    			//
    		 break;
    		 case astPrintLnStmt:
    			 ProcessPrintLnStmt(p,lev,lvalue,leftChild);
    		 break;
    		 case astReadStmt:
    			ProcessReadStmt(p,lev,lvalue,leftChild);
    		 break;
    		 case astPrintLtStmt:
    			 ProcessPrintLtStmt(p,lev,lvalue,leftChild);
    		 break;
    		 case astPrintLnLtStmt:
    			 ProcessPrintLnLtStmt(p,lev,lvalue,leftChild);
    		 break;
    		 case astExprStmt:
    			 ProcessExprStmt(p,lev,lvalue,leftChild);
    		 break;
    		 case astNotExpr:
            ProcessNotExpr(p,lev,lvalue,leftChild);
         break;
    		 case astAndExpr:
            ProcessAndExpr(p,lev,lvalue,leftChild);
         break;
    		 case astOrExpr:
            ProcessOrExpr(p,lev,lvalue,leftChild);
         break;
         case astCompExpr:
            ProcessCompExpr(p,lev,lvalue,leftChild);
         break;
    		 case astAddAssign:
            ProcessAddAssign(p,lev,0);
        break;
    		case astSubAssign:
            ProcessSubAssign(p,lev,0);
        break;
        case astAssign:
    			 ProcessUniqueAssign(p,lev,0);
        break;
    		case astAssignSeq:
    			 ProcessAboveMultiAssignSeq(p,lev,0);
    		break;
    		case astListedAssign:
    			 ProcessListedAssign(p,lev,0);
    		break;
    		case astNestedAssign:
    			 ProcessNestedAssign(p,lev,0);
    		break;
    		case astEmbedAssign:
    			 ProcessEmbedAssign(p,lev,0);
    		break;
        case astAddExpr:
           ProcessAddExpr(p,lev,lvalue,leftChild);
        break;
        case astAddExprLast:
           //ProcessAddExprLast(p,lev,lvalue,leftChild);
        break;
        case astNullStmt:
           //ProcessNullStmt(p,lev,lvalue,leftChild);
        break;
        case astFunctionCall:
           ProcessFunctionCall(p,lev,lvalue,leftChild);
        break;
        case astMethodCall:
           ProcessMethodCall(p,lev,lvalue,leftChild);
        break;
        case astStaticMethodCall:
           ProcessStaticMethodCall(p,lev,lvalue,leftChild);
        break;
        case astGeOp:
           //ProcessGeOp(p,lev,lvalue,leftChild);
        break;
        case astGOp:
           //ProcessGOp(p,lev,lvalue,leftChild);
        break;
        case astLeOp:
           //ProcessLeOp(p,lev,lvalue,leftChild);
        break;
    		case astLOp:
                 //ProcessLOp(p,lev,lvalue,leftChild);
        break;
    		case astNeOp:
                 //ProcessNeOp(p,lev,lvalue,leftChild);
        break;
    		case astEOp:
                 //ProcessEOp(p,lev,lvalue,leftChild);
        break;
    		case astAddOp:
                 //ProcessAddOp(p,lev,lvalue,leftChild);
        break;
    		case astSubOp:
                 //ProcessSubOp(p,lev,lvalue,leftChild);
        break;
    	  case astMulExpr:
            ProcessMulExpr(p,lev,lvalue,leftChild);
        break;
    		case astMulOp:
                 //ProcessMulOp(p,lev,lvalue,leftChild);
        break;
    		case astDivOp:
                 //ProcessDivOp(p,lev,lvalue,leftChild);
        break;
    		case astModOp:
                 //ProcessModOp(p,lev,lvalue,leftChild);
        break;
    		case astRealDeConst:
            ProcessRealDeConst(p);
        break;
        case astString:
            ProcessString(p);
        break;
    		case astDeConst:
                 ProcessDeConst(p);
        break;
    		 case astTrue:
                 ProcessTrue(p);
             break;
    		 case astIncreaseAfter:
    			 ProcessIncreaseAfter(p,lev,lvalue,leftChild);
    		 break;
    		 case astIncreaseBefore:
    			 ProcessIncreaseBefore(p,lev,lvalue,leftChild);
    		 break;
    		 case astDecreaseAfter:
    			 ProcessDecreaseAfter(p,lev,lvalue,leftChild);
    		 break;
    		 case astDecreaseBefore:
    			 ProcessDecreaseBefore(p,lev,lvalue,leftChild);
    		 break;
    		 case astActualsEmpty:
                 //ProcessActualsEmpty(p,lev,lvalue,leftChild);
             break;
    		 case astFalse:
                 ProcessFalse(p);
             break;
    		 case astActuals:
                 ProcessActuals(p,lev,lvalue,leftChild);
             break;
    		 case astArgsSeq:
                 ProcessArgsSeq(p,lev,lvalue,leftChild);
             break;
    		 case astArgsEmpty:
                 //ProcessArgsEmpty(p,lev,lvalue,leftChild);
             break;
         default:
            fprintf(text,"Unknown=%d\n",p->NodeType);
      }
}



void BeforeCodeGeneration(){
/*
	fprintf(data,"[BITS 32]\n");

	fprintf(text,"global    _main\n");

	fprintf(data,"    section .data\n\n");
	fprintf(data,"rgs    dd    0\n");
	fprintf(data,"frgs    dq    0\n");
	fprintf(data,"cw dw 043fH\n");

	fprintf(data,"format_print_int    db    \"%%d\",0\n");
	fprintf(data,"format_println_int    db    \"%%d\",10,0\n");
	fprintf(data,"format_print_real    db    \"%%0.4lf\",0\n");
	fprintf(data,"format_println_real    db    \"%%0.4lf\",10,0\n");
	fprintf(data,"format_read_int    db    \"%%d\", 0\n");
	fprintf(data,"format_read_real    db    \"%%lf\", 0\n");
	fprintf(data,"extern    _scanf\n");
	fprintf(data,"extern    _printf\n");

	fprintf(text,"    section .text\n\n");

*/

}

void AfterCodeGeneration(){

     //fprintf(text,"\n\nSTART EQU *\n");
	 //fprintf(text,"JMP MAIN\n");
	 //fprintf(text,"OVERFLOW HLT\n");
     //fprintf(text,"UNDERFLOW HLT\n");
	// fprintf(text,"TOOLARGE  HLT\n");
	 //fprintf(text,"DIVBYZERO  HLT\n");
     fprintf(data,"invoke_static main\n");
     fprintf(data,"pop\n");
}

int yywrap(void) {
    return 1;
}



void remExt(char* mystr) {
    char *lastdot;
    if (mystr == NULL)
         return;
    lastdot = strrchr (mystr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

// call this function to start a nanosecond-resolution timer
struct timespec timer_start(){
    struct timespec start_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
    struct timespec end_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
    return diffInNanos;
}


void main(int argc, char **argv)
{


   AstNode *p;
   int wrong,i;

   Init_Hash_Table();
   //Init_Array_Hash_Table();
   Init_while_stack();

   yyin = fopen(argv[1], "r");
   remExt(argv[1]);

   filename = argv[1];
   struct timespec vartime = timer_start();
   wrong=yyparse();
   yylex();

   if(!wrong)
   {
      p=TreeRoot;
      //traverse(p,-3);

    //text=fopen("text.asm","w");
	  data=fopen(concat(filename,".cex"),"w");
    text = data;

	  BeforeCodeGeneration();
    CodeGeneration(p,0,0,0);
	  AfterCodeGeneration();
    //fclose(text);
	  fclose(data);
    long time_elapsed_nanos = timer_end(vartime);
    printf("Success ...................... %ld nsec\n" ,time_elapsed_nanos);
	  //system("cat data.asm >> text.asm");
    //system("mv text.asm program.asm");
	  //system("rm data.asm");
	 // system("rm text.asm");


   }
}

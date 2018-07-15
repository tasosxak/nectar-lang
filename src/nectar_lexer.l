%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "y.tab.h"

#define NUM_RESERVED_NAMES 27

int id_or_keyword(char *name);

%}



%%

[0-9][0-9]*      {       //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(DEC_CONST);
                     }

[0-9]+"."[0-9]+      {       //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(REAL_DEC_CONST);
                     }

"//".*              {
                          //printf("COMMENT: %s\n",yytext);
                      }


\"(\\.|[^"])*\"       {       //printf("LITERAL : %s\n",yytext);
                              strcpy(yylval.ystr,yytext);
                              return(LITERAL);
                      }


"*"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('*');
                            }


"/"                        {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('/');
                            }

"%"                        {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('%');
                            }



"+"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('+');
                            }

"++"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(INC);
                            }

"-"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('-');
                            }

"--"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(DEC);
                            }


">"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('>');
                            }
">="                        {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(GE);
                            }
"<"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('<');
                            }
"<="                        {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(LE);
                            }
"=="                        {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(EQ);
                            }
"!="                        {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(NE);
                            }



"{"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('{');
                            }

"}"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('}');
                            }


"("                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('(');
                            }

")"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(')');
                            }

","                         {
                              // printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(',');
                            }

"+="                        {
                              // printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(ADDASSIGN);
                            }

"-="                        {
                              // printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(SUBASSIGN);
                            }

"="                         {
                              // printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return('=');
                            }

";"                         {
                               //printf("%s\n",yytext);
                               strcpy(yylval.ystr,yytext);
                               return(';');
                            }

"@"                         {
                                  //printf("%s\n",yytext);
                                  strcpy(yylval.ystr,yytext);
                                  return('@');
                            }
":"                         {
                                  //printf("%s\n",yytext);
                                  strcpy(yylval.ystr,yytext);
                                  return(':');
                            }


"->"                        {
                                //printf("%s\n",yytext);
                                strcpy(yylval.ystr,yytext);
                                return(RIGHTARROW);
                            }

[a-zA-Z]([a-zA-Z]|[0-9]|"_")*  {
                                   int i;
                    		  // printf("%s\n",yytext);
				   i = id_or_keyword(yytext);
                                   if(i == ID)
                                      strcpy(yylval.ystr,yytext);
				   else
		 		     yylval.yint = i;

				   return(i);
                               }



[ \f\n\r\t]+                { /*printf("%s\n",yytext);*/ }

.                           {
                               printf("Unrecognized character >%s<\n",yytext);
                            }

%%

static char *RESERVED_NAMES[NUM_RESERVED_NAMES] = {"false","true","int","return","if","else","while","break","print","read","println","times","use","unless","not","and","or","real","puts","bool","func","class","private","pub","abstract","meth","var"};
static int KEYWORD_VALUE[NUM_RESERVED_NAMES] = {FALSE,TRUE,INT,RETURN,IF,ELSE,WHILE,BREAK,PRINT,READ,PRINTLN,TIMES,USE,UNLESS,NOT,AND,OR,REAL,PUTS,BOOL,FUNC,CLASS,PRIVATE,PUBLIC,ABSTRACT,METH,VAR};

int id_or_keyword(char *name){
  int i,k;

  for(i=0; (i < NUM_RESERVED_NAMES) && (strcmp(name,RESERVED_NAMES[i]) != 0); i++);
   if(i < NUM_RESERVED_NAMES)
      return KEYWORD_VALUE[i];
   else
      return ID;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


void remExt(char* mystr) {
    char *lastdot;
    if (mystr == NULL)
         return;
    lastdot = strrchr (mystr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
}

int main(int argc, char* argv[]){
	
	int i;
	char* dot;
	char* filename;
	char str[255];
	int error = 0;
	if(strcmp(argv[1],"create") == 0){
		
		#ifdef __linux__
		sprintf(str,"rm -r -f %s",argv[2]);
		#ifdef _WIN32
		sprintf(str,"rmdir %s",argv[2]);
		#endif
		system(str);
		
		#ifdef __linux__
		sprintf(str,"mkdir %s",argv[2]);
		#ifdef _WIN32
		sprintf(str,"mkdir %s",argv[2]);
		#endif
		system(str);
		
		#ifdef __linux__
		sprintf(str,"mkdir %s/src",argv[2]);
		#ifdef _WIN32
		sprintf(str,"mkdir %s/src",argv[2]);
		#endif
		system(str);
		
		#ifdef __linux__
		sprintf(str,"mkdir %s/exec",argv[2]);
		#ifdef _WIN32
		sprintf(str,"mkdir %s/exec",argv[2]);
		#endif
		system(str);
		
		#ifdef __linux__
		sprintf(str,"echo \' func main() -> int { \n \n puts \"Hello world!\"\n\nreturn 0\n}\'>>%s/src/%s.nr",argv[2],argv[2]);
		#ifdef _WIN32
		sprintf(str,"@echo func main() -> int { >%s/src/%s.nr",argv[2],argv[2]);
		sprintf(str,"@echo puts \"Hello world!\">%s/src/%s.nr",argv[2],argv[2]);
		sprintf(str,"@echo return 0 >%s/src/%s.nr",argv[2],argv[2]);
		sprintf(str,"@echo } >%s/src/%s.nr",argv[2],argv[2]);
		#endif
		system(str);
	}
	else if(strcmp(argv[1],"build") == 0){
			
			sprintf(str,"./prenectar %s/src/%s.nr %s/src/",argv[2],argv[2],argv[2]);
			error = system(str);
			if(error) exit(1);
			sprintf(str,"./nectarc final.nrf");
		             error = system(str);
			sprintf(str,"mv final.cex %s.cex",argv[2]);
		             error = system(str);
			if(error) exit(1);
			sprintf(str,"mv final.nrf %s/",argv[2]);
			system(str);
			sprintf(str,"mv  %s.cex  %s/exec/",argv[2],argv[2]);
			system(str);
	}
	else if(strcmp(argv[1],"run") == 0){
			sprintf(str,"./colibri   %s/exec/%s.cex",argv[2],argv[2]);
			system(str);
	}

 
	
	return 0;
	
}

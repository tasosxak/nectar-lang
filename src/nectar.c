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
  char version[] = "0.2";
  char name[] = "birth";

	if(strcmp(argv[1],"create") == 0){

		#ifdef __linux__
		sprintf(str,"rm -r -f %s",argv[2]);
		#elif _WIN32
		sprintf(str,"del /f /s /q %s > nul 2> nul",argv[2]);
		system(str);
		sprintf(str,"rmdir /s /q %s > nul 2> nul",argv[2]);
		#endif
		system(str);

		#ifdef __linux__
		sprintf(str,"mkdir %s",argv[2]);
		#elif _WIN32
		sprintf(str,"mkdir %s",argv[2]);
		#endif
		system(str);

		#ifdef __linux__
		sprintf(str,"mkdir %s/src",argv[2]);
		#elif _WIN32
		sprintf(str,"mkdir %s\\src",argv[2]);
		#endif
		system(str);

		#ifdef __linux__
		sprintf(str,"mkdir %s/exec",argv[2]);
		#elif _WIN32
		sprintf(str,"mkdir %s\\exec",argv[2]);
		#endif
		system(str);

		#ifdef __linux__
		sprintf(str,"echo \'func main() -> int { \n \n say \"Hello world!\";\n\nreturn 0;\n}\'>>%s/src/%s.nec",argv[2],argv[2]);
		#elif _WIN32
		sprintf(str,"@echo func main() -^> int { >%s\\src\\%s.nec",argv[2],argv[2]);
		system(str);
		sprintf(str,"@echo say \"Hello world!\";>>%s\\src\\%s.nec",argv[2],argv[2]);
		system(str);
		sprintf(str,"@echo return 0; >>%s\\src\\%s.nec",argv[2],argv[2]);
		system(str);
		sprintf(str,"@echo } >>%s\\src\\%s.nec",argv[2],argv[2]);
		#endif
		system(str);
	}
	else if(strcmp(argv[1],"build") == 0){

			#ifdef __linux__
			sprintf(str,"prenectar %s/src/%s.nec %s/src/ %s",argv[2],argv[2],argv[2],argv[2]);
			#elif _WIN32
			sprintf(str,"prenectar %s\\src\\%s.nec %s\\src\\ %s",argv[2],argv[2],argv[2],argv[2]);
			#endif
			error = system(str);
			if(error) exit(1);

			#ifdef __linux__
			sprintf(str,"nectarc %s.nectar",argv[2]);
			#elif _WIN32
			sprintf(str,"nectarc %s.nectar",argv[2]);
			#endif
			error = system(str);


			#ifdef __linux__
			sprintf(str,"mv %s.nectar %s/",argv[2],argv[2]);
			#elif _WIN32
			sprintf(str,"move %s.nectar %s > nul 2> nul",argv[2],argv[2]);
			#endif
			system(str);

			#ifdef __linux__
			sprintf(str,"mv  %s.cex  %s/exec/",argv[2],argv[2]);
			#elif _WIN32
			sprintf(str,"move  %s.cex  %s\\exec > nul 2> nul",argv[2],argv[2]);
			#endif
			system(str);
	}
	else if(strcmp(argv[1],"run") == 0){

			#ifdef __linux__
			sprintf(str,"colibri   %s/exec/%s.cex",argv[2],argv[2]);
			#elif _WIN32
			sprintf(str,"colibri   %s\\exec\\%s.cex",argv[2],argv[2]);
			#endif
			system(str);
	}
  else if(strcmp(argv[1],"exec") == 0){

      #ifdef __linux__
      sprintf(str,"prenectar %s/src/%s.nec %s/src/ %s",argv[2],argv[2],argv[2],argv[2]);
      #elif _WIN32
      sprintf(str,"prenectar %s\\src\\%s.nec %s\\src\\ %s",argv[2],argv[2],argv[2],argv[2]);
      #endif
      error = system(str);
      if(error) exit(1);

      #ifdef __linux__
      sprintf(str,"nectarc %s.nectar",argv[2]);
      #elif _WIN32
      sprintf(str,"nectarc %s.nectar",argv[2]);
      #endif
      error = system(str);


      #ifdef __linux__
      sprintf(str,"mv %s.nectar %s/",argv[2],argv[2]);
      #elif _WIN32
      sprintf(str,"move %s.nectar %s > nul 2> nul",argv[2],argv[2]);
      #endif
      system(str);

      #ifdef __linux__
      sprintf(str,"mv  %s.cex  %s/exec/",argv[2],argv[2]);
      #elif _WIN32
      sprintf(str,"move  %s.cex  %s\\exec > nul 2> nul",argv[2],argv[2]);
      #endif
      system(str);

			#ifdef __linux__
			sprintf(str,"colibri   %s/exec/%s.cex",argv[2],argv[2]);
			#elif _WIN32
			sprintf(str,"colibri   %s\\exec\\%s.cex",argv[2],argv[2]);
			#endif
			system(str);
	}
  else if(strcmp(argv[1],"version") == 0){
			printf("Nectar %s - %s\n",version,name);
	}



	return 0;

}

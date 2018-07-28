#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *finalSrcFile;
char* includeStatement = "use ";
int lengthOfIncludeStatement;

void processFile(char *inputFileName,char *srcDirectory){

		FILE* file;
		char path[100];
		strcpy(path,srcDirectory);
		//printf("%s\n",srcDirectory);
		strcat(path,inputFileName);
		//printf("%s\n",inputFileName);
		strcat(path,".nr");
		//printf("%s\n",path);
		file = fopen(path, "r");

		if(file == NULL){
			strcpy(srcDirectory, "nectar-lang/lib/");
			strcpy(path,srcDirectory);
			strcat(path,inputFileName);
			strcat(path,".nr");
			file = fopen(path, "r");

			if(file == NULL){
				printf("Error: The library '%s' doesn't exist\n",path);
				exit(1);
			}

			int last_slash = 0;
			for(int h = strlen(inputFileName) - 1; h >=0; h--){
				if(inputFileName[h] == '/'){
					 last_slash = h;
					break;
				}
			}


			strncat(srcDirectory, inputFileName,last_slash +1);

			//printf("%s\n",srcDirectory);
		}

    char line[256];
    char firstNLetters[lengthOfIncludeStatement+2];
    char includedFileName[50];
    char *pos;
    int countSpaces;

    while (fgets(line, sizeof(line), file)) {
		countSpaces = 0;
        	while (isspace(line[countSpaces])){
          			  countSpaces++;
       	       }
      	  	strncpy(firstNLetters, line+countSpaces, lengthOfIncludeStatement);
        		firstNLetters[lengthOfIncludeStatement] = 0;

        	if (strcmp(firstNLetters, includeStatement) == 0){
            		// found include

           		 strcpy(includedFileName, line + countSpaces + lengthOfIncludeStatement ); // get the name of the file to be included

            	if ((pos=strchr(includedFileName, '\n')) != NULL)
                *pos = '\0'; // replace \n with \0

            //printf("!%s!\n", includedFileName);

	for(int t = 0; t < strlen(includedFileName); t++) {
		if (includedFileName[t] == '.') {
			includedFileName[t] = '/';
		}
	}
            processFile(includedFileName,srcDirectory);

        } else {
            fprintf(finalSrcFile, "%s", line);
        }
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

}

int main(int argc, char *argv[])
{
   	 lengthOfIncludeStatement = strlen(includeStatement);
    	char* srcFileName = argv[3];
    	char* srcDirectory= argv[2];
	char filename[50];
	sprintf(filename,"%s.nrf",argv[3]);

	finalSrcFile = fopen(filename, "w+");
    	processFile(srcFileName,srcDirectory);
    	fclose(finalSrcFile);

    	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *finalSrcFile;
char* includeStatement = "use ";
int lengthOfIncludeStatement;

void processFile(char *inputFileName,char *srcDirectory){


    FILE* file = fopen(inputFileName, "r"); /* should check the result */


	if(file == NULL){

		char path[100];
		strcpy(path,srcDirectory);
		strcat(path,inputFileName);
		strcat(path,".nr");
		file = fopen(path, "r");

		if(file == NULL){
			printf("Error: The library '%s' doesn't exist\n",inputFileName);
			exit(1);
		}
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


    char* srcFileName = argv[1];
    char* srcDirectory= argv[2];
		char filename[50];
		sprintf(filename,"%s.nrf",argv[3]);

	finalSrcFile = fopen(filename, "w+");
    processFile(srcFileName,srcDirectory);
    fclose(finalSrcFile);

    /*
    if (argc>1){



    } else {
        printf("No source file specified.\n");
    }
    */

    return 0;
}

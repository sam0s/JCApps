#include "stdio.h"
#include "string.h"

int main() {

	typedef int bool;
	enum {false,true };

	char full_file[999][500];
	char clinetext[500];
	int linemax = 0;
	int clinenum = 0;
	bool cmd = false;

	system("cls");
	char filename[32];
	printf("JCEdit Version 1.5 - Written by sam0s \nEnter file name: ");
	gets(filename);

	system("cls");
	printf("JCEdit Version 1.5 - Written by sam0s \n");
	printf("FILENAME: %s | LINEMAX: %d \n\n",filename,linemax);

	bool run = true;

	while(run){

		printf("%d| ", clinenum);
		gets(clinetext);

		if(strcmp(clinetext, ".qt") == 0){run=false;cmd=true;}

		if(strcmp(clinetext, ".ln") == 0){printf("> ");scanf("%d", &clinenum);cmd=true;}

		if(strcmp(clinetext, ".sv") == 0){
			FILE* file = fopen(filename, "w");
			for(int i=0;i<linemax;i+=1){
				fprintf(file,"%s\n",full_file[i]);fflush(file);
				}
			fflush(file);
			fclose(file);
			cmd=true;
		}

		if(strcmp(clinetext, ".ls") == 0){
			system("cls");printf("JCEdit Version 1.5 - Written by sam0s \n");cmd=true;
			printf("FILENAME: %s | LINEMAX: %d \n",filename,linemax);

			if(linemax>=1){
			printf("\n");
			for(int i=0;i<linemax;i+=1){
				printf("%d| %s\n",i,full_file[i]);
				}
			}

			printf("\n");
		}


		if(!cmd){
		strcpy(full_file[clinenum], clinetext);
		clinenum+=1;
		if (clinenum>linemax){linemax+=1;}
		}

		cmd = false;
		strcpy(clinetext, "");
		fflush(stdin);
	}

	return 0;
}

#include "stdio.h"
#include "string.h"

int file_exist(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

int main() {
	//create boolean
	typedef int bool;
	enum {false,true };

	//init variables
	const char header[50] = "JCEdit Version 2 - Written by sam0s";
	char full_file[999][500];
	char clinetext[500];
	int linemax = 0;
	int clinenum = 0;
	bool cmd = false;

	//file name prompt
	system("cls");
	char filename[50];
	printf("%s \nEnter file name: ",header);
	gets(filename);

	//load file if it exists
	if(file_exist(filename))
	{
		FILE *fp;
		fp = fopen(filename, "r");
		while(!feof(fp)){
		fgets(full_file[linemax], 500, fp);
		full_file[linemax][strcspn(full_file[linemax], "\n")] = 0;
		linemax+=1;
		}
		fclose(fp);
	}

	system("cls");
	printf("%s \n",header);
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
			system("cls");printf("%s \n",header);cmd=true;
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

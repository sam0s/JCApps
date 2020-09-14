// sam tubb, Homework 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>

#define RED "\033[91m"
#define GREEN "\033[92m"
#define CYAN "\033[96m"
#define BLUE "\033[94m"
#define YELLOW "\033[93m"
#define PURPLE "\033[1;35m"

struct token_struct{
	char** tokens;
	int length;
};

struct shell_vars{
	char *wd;
	char *lastdir;
	char *prompt;
	pid_t children[1000];
	int pn;
};

struct token_struct make_tokens(char* input){
    char * tokens;
    char* rest = input;

    int token_total=0;
    char ** token_list = malloc(sizeof(char*));

    while ((tokens = strtok_r(rest, " ", &rest)))
    {
        token_list = realloc(token_list, sizeof(char*)*(++token_total));
        token_list[token_total-1] = malloc(strlen(tokens)+1);
        token_list[token_total-1]=strdup(tokens);
    }
    struct token_struct ret;
    ret.tokens = token_list;
    ret.length = token_total;
    return ret;
}

int process_input(struct token_struct tokens,struct shell_vars* vars){
	int bg=0;
	if(tokens.tokens[tokens.length-1][0]=='&'){
		bg=WNOHANG;
	}
    if(strcmp(tokens.tokens[0],"exit")==0){
        printf("\nTerminating...\n");
        return -1;
    }

		if(strcmp(tokens.tokens[0],"prompt")==0){
			vars->prompt=strdup(tokens.tokens[1]);
			return 1;
		}

		if(strcmp(tokens.tokens[0],"cls")==0){
			printf("\x1b[?251\x1b[2J\x1b[H\x1b[?25h");
			return 1;
		}

		if(strcmp(tokens.tokens[0],"jobs")==0){
			for(int i=0;i<vars->pn;i++){
				if(vars->children[i]!=-999){
					printf("[%d]\n",vars->children[i]);
				}
			}
			return 1;
		}

	    if(strcmp(tokens.tokens[0],"cd")==0){
			if(strcmp(tokens.tokens[1],"-")==0){
				char * temp = strdup(vars->wd);
				chdir(vars->lastdir);
				vars->lastdir=strdup(temp);
				free(temp);
				return 1;
			}
			vars->lastdir=strdup(vars->wd);
			chdir(tokens.tokens[1]);
			return 1;
	    }

		int pid = fork(); //fork current process
		int exit_code;
		//create child process
		if(pid==0){
			execvp(tokens.tokens[0],tokens.tokens);
			fprintf(stderr, "%sEnter a valid command or process name. [failed to start process]\x1b[0m\n",RED);
    		exit(EXIT_FAILURE);
		}else{
			int process = waitpid(pid, &exit_code, bg);
			//printf("start: %d ",pid);
			if(bg!=0){vars->children[vars->pn++]=pid;}
		}

		return 0;
	}

//check if child has finished
void check_exit(struct shell_vars* vars){
	int f = waitpid(-1,NULL,WNOHANG);
	//printf("done: %d ",f);
	if(f!=-1){
		for(int i=0;i<vars->pn;i++){
			if(vars->children[i]==f){
				vars->children[i]=-999;
			}
		}
	}
}

int main(){
	char* lastdir = malloc(300);
    char* clinetext = malloc(128);
    struct token_struct tokens;
	struct shell_vars vars;
	vars.wd=malloc(300);
	vars.lastdir=malloc(300);
	vars.prompt=malloc(10);
	vars.prompt=strdup(">");
	vars.pn=0;
    tokens=make_tokens("empty");
    while(1){
		check_exit(&vars);
        getcwd(vars.wd,300);
        printf("%s%s\x1b[0m%s ",YELLOW,vars.wd,vars.prompt);
        fgets(clinetext,1001,stdin);
		clinetext[strcspn(clinetext, "\n")] = '\0';
		if(clinetext[0]==' ' || clinetext[0]=='\0'){
			continue;
		}
        tokens = make_tokens(clinetext);
        if(process_input(tokens,&vars)==-1){
            exit(0);
        }
    }

    return 0;
}

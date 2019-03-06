//-------------
//Hangman
//by
//sam0s
//-------------

#include <stdio.h>
#include <string.h>

int main()
{
    srand(time(0));
    int choice = rand() % (9 + 1 - 0) + 0;
    // [ number of words ] [ max word length ]
    char words[11][32] = {};
    char currentWord[32];

    strcpy(currentWord,words[choice]);
    for(int i=0;i<strlen(currentWord);i++){printf("%c.",currentWord[i]);}

    getchar();fflush(stdin);

    return 0;
}

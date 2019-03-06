//--------------------------------------
// tic.c
// by
// sam0s
// "a fun game"
//--------------------------------------


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define true & false boolean type
typedef int bool;
enum {false,true};


void drawTable(char tabl[3][3]){

    printf("\t----- ----- -----\n");
    printf("\tq %c - w %c - e %c -\n",tabl[0][0],tabl[0][1],tabl[0][2]);
    printf("\t----- ----- -----\n");

    printf("\t----- ----- -----\n");
    printf("\ta %c - s %c - d %c -\n",tabl[1][0],tabl[1][1],tabl[1][2]);
    printf("\t----- ----- -----\n");

    printf("\t----- ----- -----\n");
    printf("\tz %c - x %c - c %c -\n",tabl[2][0],tabl[2][1],tabl[2][2]);
    printf("\t----- ----- -----\n");

}

int drawMenu(){
    system("cls");
    printf("TIC TAC TOE by sam0s\n\nChoose an option:\ns) START GAME\nh) HELP\nq) QUIT\n\n> ");
    char b = getchar();fflush(stdin);
    if(b=='s'){return 1;}
    if(b=='h'){return 2;}
    if(b=='q'){return 0;}
}

int main()
{
    bool turn = false;
    char table[3][3] = {' '};
    int check = -1;

    // This table pair is used to convert char-input into coordinates on the grid (char-97 as index)
                     //0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    int pointRefx[26]={0,0,2,2,2,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0};
    int pointRefy[26]={1,0,2,1,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 2};
    // It works great

    //Seed the random
    srand(time(0));srand(rand());
    int a = 0;

    while(check!=0){

        check = drawMenu();

        while(check==1){
            system("cls");
            printf("%d,%d",pointRefx[a],pointRefy[a]);

            turn = !turn;

            drawTable(table);


            printf("Choose your next move (type h to toggle move reference): ");
            a = getchar()-97;fflush(stdin);
            table[pointRefy[a]][pointRefx[a]] = 'x';

        }

}
    return 0;
}

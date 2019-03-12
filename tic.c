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

//create boolean
typedef int bool;
enum {false,true };

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

void enemyMove(char tabl[3][3]){

    srand(time(0));
    int choice = rand() % (2 + 1 - 0) + 0;
    int choice2 = rand() % (2 + 1 - 0) + 0;

    while(tabl[choice][choice2] == 'x' || tabl[choice][choice2] == 'o'){
        choice = rand() % (2 + 1 - 0) + 0;
        choice2 = rand() % (2 + 1 - 0) + 0;
    }
    tabl[choice][choice2] = 'o';
    }

int winCheck(char board[3][3])
    {
        int count = 0;
        int row, col;

        // Check each of 3 rows:
        for(row = 0; row < 3; ++row)
        {
            count = 0;
            for(col=0; col < 3; ++col){
                count += (board[row][col] == 'x')?  1 :
                         (board[row][col] == 'o')? -1 : 0;}
            if (count == 3 || count == -3){
                return count / abs(count);}
        }

        // Check each of 3 columns.
        for(col = 0; col < 3; ++col){
            count = 0;
            for(row=0; row < 3; ++row){
                count += (board[row][col] == 'x')?  1 :
                         (board[row][col] == 'o')? -1 : 0;}
            if (count == 3 || count == -3){
                return count / abs(count); }
        }

        // Check Left-to-Right downward Diagonal:
        count = 0;
        for(col = 0; col < 3; ++col){
            count += (board[col][col] == 'x')?  1 :
                     (board[col][col] == 'o')? -1 : 0;}
        if (count == 3 || count == -3){
            return count / abs(count);}

        // Check Left-to-Right upward Diagonal
        count = 0;
        for(col = 0; col < 3; ++col){
            count += (board[col][2-col] == 'x')?  1 :
                     (board[col][2-col] == 'o')? -1 : 0;}
        if (count == 3 || count == -3){
            return count / abs(count);}

        return 0;
    }

int drawMenu(){
    system("cls");
    printf("TIC TAC TOE v1 by sam0s\n\nChoose an option:\n1) START GAME (2 Player)\n2) START GAME (1 Player)\n3) QUIT\n\n> ");
    char b = ' ';
    while(b!='1' && b!='2' && b!='3'){
    b = getchar();fflush(stdin);
    if(b=='1'){return 1;}
    if(b=='2'){return 2;}
    if(b=='3'){return 0;}
    }
}

int main()
{
    bool turn = true;
    bool singlep = false;
    char table[3][3] = {};
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
        if (check == 2){check-=1;singlep=!singlep;}
        if (check == 0){return 0;}

        while(check==1){

            while(turn){
            system("cls");
            drawTable(table);
            printf("Choose your next move (P1): ");
            a = getchar()-97;fflush(stdin);
            if(table[pointRefy[a]][pointRefx[a]] != 'x' && table[pointRefy[a]][pointRefx[a]] != 'o'){table[pointRefy[a]][pointRefx[a]] = 'x';turn=!turn;}
            }

            if(winCheck(table)!=0){check = -1;break;}

            if (singlep){
                enemyMove(table);
                if(winCheck(table)!=0){check = -1;break;}
                turn=!turn;
            }else{
                while(!turn){
                system("cls");
                drawTable(table);
                printf("Choose your next move (P2): ");
                a = getchar()-97;fflush(stdin);
                if(table[pointRefy[a]][pointRefx[a]] != 'x' && table[pointRefy[a]][pointRefx[a]] != 'o')
                {
                    table[pointRefy[a]][pointRefx[a]] = 'o';turn=!turn;
                }
            }
            }

            if(winCheck(table)!=0){check = -1;break;}
        }

        system("cls");
        drawTable(table);
        int win = winCheck(table);
        if(win<1){win=2;}
        printf("You win player %d",win);
        a = getchar();fflush(stdin);
        return 0;

}
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void endGame(int *player1plc, int *player2plc, int *row, int *coll, int *length);
int toss();
void boardPrint(int **board, int *row, int *coll, int *player1plc, int *player2plc, int ladd[6], int snk[6], int *length);
void boardInit(int **board, int *row, int *coll, int ladder[6], int snake[6], int *length);
int gamePlay(int **board, int *player1plc, int *player2plc, int ladd[6], int snk[6], int *row, int *coll, int choice, int *length);

int toss()
{
    int toss = 0;
    while (toss == 0)
    {
        toss = rand() % 7;
    }
    return toss;
}

void boardPrint(int **board, int *row, int *coll, int *player1plc, int *player2plc, int ladd[6], int snk[6], int *length)
{
    int count = 0, mark = 0;
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *coll; j++)
        {
            mark = 0;
            if (count == *player1plc) 
            {
                printf("%d_PL1", count);
                mark = 1;
            }
            else if (count == *player2plc && mark == 0) 
            {
                printf("%d_PL2_", count);
                mark = 1;
            }
            if (mark == 0) 
            {

                for (int h = 0; h < 6; h++)
                {
                    if (ladd[h] == count && h % 2 == 0)
                    {
                        printf(" %d_laddSt_", count);
                        mark = 1;
                    }
                    else if (ladd[h] == count && h % 2 == 1)
                    {
                        printf(" %d_laddEnd_", count);
                        mark = 1;
                    }
                    if (snk[h] == count && h % 2 == 0)
                    {
                        printf(" %d_snkEnd_", count);
                        mark = 1;
                    }
                    if (snk[h] == count && h % 2 == 1)
                    {
                        printf(" %d_snkSt_", count);
                        mark = 1;
                    }
                }
            }
            if (mark == 0) 
            {
                printf(" %d___", count);
            }
            count++;
        }
        printf("\n");
    }
}

void boardInit(int **board, int *row, int *coll, int ladder[6], int snake[6], int *length)
{
    printf("enter board size:\n");
    printf("row: \n");
    scanf("%d", row);
    printf("coll: \n");
    scanf("%d", coll);
    *length=(int)(*row**coll);
    board = (int **)malloc(*length * sizeof(int *));
    printf("place the start and end of your ladders:\n");
    printf("example: 6, 20 means you go from sqwer 6 to 20\n");
    for (int i = 0; i < 6; i++)
    {
        while (ladder[i] <= 1 || ladder[i] >= *length - 2)
        {
            scanf("%d", &ladder[i]);
        }
    }
    printf("place the start and end of your snakes:\n");
    printf("example: 20, 6 means you go from sqwer 20 to 6\n");
    for (int i = 0; i < 6; i++)
    {
        while (snake[i] <= 1 || snake[i] >= *length - 2)
        {
            scanf("%d", &snake[i]);
        }
    }
    return;
}

int gamePlay(int **board, int *player1plc, int *player2plc, int ladd[6], int snk[6], int *row, int *coll, int choice, int *length)
{
    int cubeval;
    switch (choice)
    {
    case 1: // player 1 turn
    
        cubeval = toss();
        printf("\nplayer 1 you tossed: %d\n", cubeval);
        *player1plc += cubeval;
        if (*player1plc == ladd[0])
        {
            *player1plc = ladd[1];
        }
        if (*player1plc == ladd[2])
        {
            *player1plc = ladd[3];
        }
        if (*player1plc == ladd[4])
        {
            *player1plc = ladd[5];
        }
        if (*player1plc == snk[0])
        {
            *player1plc = snk[1];
        }
        if (*player1plc == snk[2])
        {
            *player1plc = snk[3];
        }
        if (*player1plc == snk[4])
        {
            *player1plc = snk[5];
        }

        if (*player1plc >= *length-1)
        {
            *player1plc = *length - 1;
            boardPrint(board, row, coll, player1plc, player2plc, ladd, snk, length);
            endGame(player1plc, player2plc, row, coll, length);
            return 0;
        }
        boardPrint(board, row, coll, player1plc, player2plc, ladd, snk, length);
        break;

    case 2: // player 2 turn
        cubeval = toss();
        printf("\nplayer 2 you tossed: %d\n", cubeval);
        *player2plc += cubeval;
        if (*player2plc == ladd[0])
        {
            *player2plc = ladd[1];
        }
        if (*player2plc == ladd[2])
        {
            *player2plc = ladd[3];
        }
        if (*player2plc == ladd[4])
        {
            *player2plc = ladd[5];
        }
        if (*player2plc == snk[0])
        {
            *player2plc = snk[1];
        }
        if (*player2plc == snk[2])
        {
            *player2plc = snk[3];
        }
        if (*player2plc == snk[4])
        {
            *player2plc = snk[5];
        }

        if (*player2plc >= *length-1)
        {
            *player2plc = *length - 1;
            boardPrint(board, row, coll, player1plc, player2plc, ladd, snk, length);
            endGame(player1plc, player2plc, row, coll, length);
            return 0;
        }
        boardPrint(board, row, coll, player1plc, player2plc, ladd, snk, length);
        break;

    case 3: // exit game
        boardPrint(board, row, coll, player1plc, player2plc, ladd, snk, length);
        endGame(player1plc, player2plc, row, coll, length);
        return 0;
    }
    return 1;
}

void endGame(int *player1plc, int *player2plc, int *row, int *coll, int *length)
{
    if (*player1plc >= *length)
    {
        printf("\nplayer 1 wins!!\n");
        return;
    }
    if (*player2plc >= *length)
    {
        printf("\nplayer 2 wins!!\n");
        return;
    }
    if (*player1plc < *player2plc)
    {
        printf("\nplayer 2 wins!!\n");
        return;
    }
    if (*player1plc > *player2plc)
    {
        printf("\nplayer 1 wins!!\n");
        return;
    }
    if (*player1plc == *player2plc)
    {
        printf("it's a tie!!\n");
        return;
    }
}

int main() 
{
    srand(time(NULL));
    int **board;
    int row, coll, player1plc = 0, player2plc = 0, ladder[6] = {0}, snake[6] = {0}, choice, game = 1, len;
    printf("\nWelcome to the game of Snakes_and_Ladders.\n in this version you choose the size of your board\n and where to place the snakes and the ladders\n in this game there are 3 ladders and 3 snakes\n follow the instraction and enjoy!\n\n");
    boardInit(board, &row, &coll, ladder, snake, &len);
    while (game)
    {
        printf("\nchoose your option:\n 1: player 1 turn\n 2: player 2 turn\n 3: exit game\n");
        scanf("%d", &choice);
        game = gamePlay(board, &player1plc, &player2plc, ladder, snake, &row, &coll, choice, &len);
    }
    free(board);
    return 1;
}
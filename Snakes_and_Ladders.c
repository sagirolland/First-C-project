#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void endGame(int playerplc[2], int *length);
int toss();
void boardPrint(int **board, int *row, int *coll, int playerplc[2], int ladd[6], int snk[6], int *length);
void boardInit(int **board, int *row, int *coll, int ladder[6], int snake[6], int *length);
int gamePlay(int **board, int playerplc[2], int player, int ladd[6], int snk[6], int *row, int *coll, int choice, int *length);

void boardInit(int **board, int *row, int *coll, int ladder[6], int snake[6], int *length)//initiating the board, snakes and ladders
{
    printf("enter board size:\n");
    printf("row: \n");
    scanf("%d", row);
    printf("coll: \n");
    scanf("%d", coll);
    *length = (int)(*row * *coll);
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

void boardPrint(int **board, int *row, int *coll, int playerplc[2], int ladd[6], int snk[6], int *length)//printing the board and the locations of the players snakes and ladders
{
    int count = 0, mark = 0;
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *coll; j++)
        {
            mark = 0;
            if (count == playerplc[0])
            {
                printf("%d_PL1_", count);
                mark = 1;
            }
            else if (count == playerplc[1])
            {
                printf("%d_PL2_", count);
                mark = 1;
            }
            if (mark == 0)
            {

                for (int h = 0; h < 6 ; h = h + 2)
                {
                    if (ladd[h] == count)
                    {
                        printf(" %d_laddSt_", count);
                        mark = 1;
                        break;
                    }
                    if (ladd[h + 1] == count)
                    {
                        printf(" %d_laddEnd_", count);
                        mark = 1;
                        break;
                    }
                    if (snk[h] == count)
                    {
                        printf(" %d_snkSt_", count);
                        mark = 1;
                        break;
                    }
                    if (snk[h + 1] == count)
                    {
                        printf(" %d_snkEnd_", count);
                        mark = 1;
                        break;
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

int toss() // rolling the dice
{
    int toss = 0;
    while (toss == 0)
    {
        toss = rand() % 7;
    }
    return toss;
}

int gamePlay(int **board, int playerplc[2], int player, int ladd[6], int snk[6], int *row, int *coll, int choice, int *length)//tossing the cube and moving the pieces checking if landed on snake or ladder and moving according to it. checking for end of game. printing corrent board 
{
    int cubeval;
    cubeval = toss();
    printf("\nplayer %d you tossed: %d\n", choice, cubeval);
    playerplc[player] += cubeval;
    for (int i = 0; i < 6; i = 2 + i)
    {
        if (playerplc[player] == ladd[i])
        {
            playerplc[player] = ladd[i + 1];
        }
        else if (playerplc[player] == snk[i])
        {
            playerplc[player] = snk[i + 1];
        }
    }
    if (playerplc[player] >= *length - 1)
    {
        playerplc[player] = *length - 1;
        boardPrint(board, row, coll, playerplc, ladd, snk, length);
        endGame(playerplc, length);
        return 0;
    }
    boardPrint(board, row, coll, playerplc, ladd, snk, length);
    return 1;
}

void endGame(int playerplc[2], int *length) // check the location of each player and decide who wins
{
    if (playerplc[0] >= *length || playerplc[1] < playerplc[0])
    {
        printf("\nplayer 1 wins!!\n");
        return;
    }
    if (playerplc[1] >= *length || playerplc[0] < playerplc[1])
    {
        printf("\nplayer 2 wins!!\n");
        return;
    }
    if (playerplc[0] == playerplc[1])
    {
        printf("it's a tie!!\n");
        return;
    }
}

int main()
{
    srand(time(NULL));
    int **board;
    int row, coll, playerplc[2] = {0}, ladder[6] = {0}, snake[6] = {0}, choice, game = 1, len;
    printf("\nWelcome to the game of Snakes_and_Ladders.\n in this version you choose the size of your board\n and where to place the snakes and the ladders\n in this game there are 3 ladders and 3 snakes\n follow the instruction and enjoy!\n\n");
    boardInit(board, &row, &coll, ladder, snake, &len);
    while (game)
    {
        printf("\nchoose your option:\n 1: player 1 turn\n 2: player 2 turn\n 3: exit game\n");
        scanf("%d", &choice);
        if (choice == 3)//exit option (3)
        {
            boardPrint(board, &row, &coll, playerplc, ladder, snake, &len);
            endGame(playerplc, &len);
            game = 0;
            break;
        }
        game = gamePlay(board, playerplc, choice - 1, ladder, snake, &row, &coll, choice, &len);
    }
    free(board);
    return 1;
}
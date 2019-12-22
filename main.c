#include <stdio.h>
#include <stdbool.h>

void printBoard(int board[], int playerA, int playerB) {
    printf("\n");
    printf(" %c %c %c\n",board[0], board[1], board[2]);
    printf(" %c %c %c\n",board[3], board[4], board[5]);
    printf(" %c %c %c\n", board[6], board[7], board[8]);
    printf("\n");
}

int requestValidInput(int board[], int playerA, int playerB) {
    bool valid = false;
    int playerPos;
    printf("Please enter a valid position to play.\n");
    while(valid == false){
        scanf("%d",&playerPos);
        if(board[playerPos-1] == 'A' || board[playerPos-1] == 'B'){
            printf("That position has already been played, please try again.\n");
        } else if (playerPos < 1 || playerPos > 9){
            printf("Invalid input, please try again.\n");
        } else {
            if (playerA != 0){
                board[playerPos-1] = playerA;
            } else if (playerB!=0){
                board[playerPos-1] = playerB;
            }
            return 0;
        }
    }
}

int checkForWinner(int state[], int playerA, int playerB) {
    int win[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int winCountA = 0, winCountB = 0;
    for(int row = 0; row < 8; row++){
        winCountA = 0;
        winCountB = 0;
        for(int col = 0; col < 3; col++){
            if (state[win[row][col]] == playerA){
                winCountA++;
                if (winCountA == 3){
                    return playerA;
                }
            } else if (state[win[row][col]] == playerB){
                winCountB++;
                if (winCountB == 3){
                    return playerB;
                }
            }
        }
    }
    return 0;
}

bool checkForDraw(int state[], int playerA, int playerB){
    int filled = 0;
    for(int index = 0; index < 9; index++){
        if (state[index] == playerA || state[index] == playerB){
            filled++;
        }
    }
    if(filled == 9){
        return true;
    } else {
        return false;
    }
}

int main(void) {
    int board[9] = {49,50,51,52,53,54,55,56,57};
    bool end = false;
    int playerA = 65, playerB = 66, winner = 0;
    int playerATurn=playerA, playerBTurn=playerB;
    while (end == false){
        printf("The current state of the Tic-tac-toe Board:\n");
        printBoard(board, playerA, playerB);
        if (playerATurn!=0){
            printf("It is player %c's turn.\n", playerATurn);
            requestValidInput(board, playerATurn, playerBTurn);
            playerATurn = 0;
            playerBTurn = playerB;
        } else {
            printf("It is player %c's turn.\n", playerBTurn);
            requestValidInput(board, playerATurn, playerBTurn);
            playerBTurn = 0;
            playerATurn = playerA;
        }
        winner = checkForWinner(board, playerA, playerB);
        if(checkForDraw(board, playerA, playerB)==true){
            printf("It's a draw!\n");
            break;
        } else if (winner != 0){
            printf("Player %c wins!\n", winner);
            break;
        }
    }

    printBoard(board, playerA, playerB);
    return 0;
}

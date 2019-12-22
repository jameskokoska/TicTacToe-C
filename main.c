#include <stdio.h>
#include <stdbool.h>

//Display the board with letter positions surrounding
void printBoard(char board[26][26], int n){
    printf(" ");
    //Print the first row of the board
    for(int index = 0; index<n; index++){
        printf("%c",'a'+index);
    }
    //Print the remaining board
    for(int row = 0; row<n; row++){
        printf("\n%c",'a'+row);
        for(int col = 0; col<n; col++){
            printf("%c", board[row][col]);
        }
    }
}

//Check if a given position is within the board size
bool positionInBounds(int n, int row, int col){
    if((row>n || row<0)||(col>n || col<0)){
        return false;
    } else {
        return true;
    }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol, int checkPair[]){
    char checkBoard;
    for(int change=1;change<n;change++) {
        checkBoard = board[row + change * deltaRow][col + change * deltaCol];
        printf("\nCHECK: row: %d col: %d deltarow %d, deltaCol %d:", row, col, deltaRow, deltaCol);
        printf("CHECKBOARD: %c, BESIDE: %c CHANGE %d\n", checkBoard, board[row + change * deltaRow + deltaRow][col + change * deltaCol + deltaCol],change);
        if ((checkBoard != colour) && (checkBoard != 'U') && positionInBounds(n, row + change * deltaRow + deltaRow, col + change * deltaCol + deltaCol) ==true && board[row + change * deltaRow + deltaRow][col + change * deltaCol + deltaCol] =='U') { //if opposing colour team at this space, next space over in bounds and U
            if (checkPair == NULL) {
                printf("\n%c%c", 'a' + row + change * deltaRow + deltaRow,'a' + col + change * deltaCol + deltaCol);
                return true;
            } else if ((checkPair[0] == 'a' + row + change * deltaRow + deltaRow) &&(checkPair[1] == 'a' + col + change * deltaCol + deltaCol)) {
                checkPair[0] = -1;
                checkPair[1] = -1;
                return false;
            } else if ((checkPair[0] != 'a' + row + change * deltaRow + deltaRow) &&(checkPair[1] != 'a' + col + change * deltaCol + deltaCol)) {
                return false;
            }
        } else if (checkBoard != colour && checkBoard == board[row + change * deltaRow + deltaRow][col + change * deltaCol + deltaCol]){
            continue;
        }else {
            return false;
        }
    }
}

void checkLegalInDirectionLoop(char board[][26], int n, char colour, int checkPair[]){
    //Loop through deltas
            for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
                for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
                    if (deltaCol == 0 && deltaRow == 0)
                        continue;
                    for (int row = 0; row < n; row++) {
                        for (int col = 0; col < n; col++) {
                            if (board[row][col] == colour) {
                                checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol, checkPair);
                            }
                        }
                    }
                }
            }
        }

void flipTilesFound(char board[][26], int extend, int row, int col, char colour, int deltaRow, int deltaCol){
    for (int extend2 = 1; extend2 <= extend; extend2++) {
        //printf("MODIFY Board %c Row %d Col %d DeltaRow %d DeltaCol %d Extend %d \n", board[row+deltaRow*extend2][col+deltaCol*extend2], row, col, deltaRow, deltaCol, extend2);
        if (board[row + deltaRow * extend2][col + deltaCol * extend2] == colour || board[row + deltaRow * extend2][col + deltaCol * extend2] == 'U') {
            break;
        } else {
            board[row + deltaRow * extend2][col + deltaCol * extend2] = colour;
        }
    }
}

void flipTiles(char board[][26], int n, int row, int col, char colour){
    board[row][col] = colour;
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaCol == 0 && deltaRow == 0){
                continue;
            }
            for (int extend = 1; extend < n; extend++){
                if(positionInBounds(n, row+extend*deltaRow, col+extend*deltaCol)==true && board[row+deltaRow*extend][col+deltaCol*extend] == colour){
                    //printf("Board %c Row %d Col %d DeltaRow %d DeltaCol %d Extend %d \n", board[row+deltaRow*extend][col+deltaCol*extend], row, col, deltaRow, deltaCol, extend);
                    flipTilesFound(board, extend, row, col, colour, deltaRow, deltaCol);
                } else {
                    continue;
                }
            }
        }
    }
}

void userInput(char board[][26], int n){
    printf("Enter a move:\n");
    char row, col, colour, enter;
    scanf("%c%c%c%c",&enter,&colour,&row,&col);
    int checkPair[2] = {row,col};
    checkLegalInDirectionLoop(board, n, colour, checkPair);
    if (checkPair[0] != -1 && checkPair[1] != -1){
        printf("Invalid move\n");
    } else {
        flipTiles(board,n,row-'a',col-'a', colour);
    }
}

int main() {
    int n;
    printf("Enter the board dimension: ");
    scanf("%d",&n);

    //Initialize the board to empty spaces
    char board[26][26];
    for (int row = 0; row<n; row++){
        for (int col = 0; col<n; col++){
            board[row][col]='U';
        }
    }

    //Setup the middle spaces
    board[n/2][n/2-1] = 'B';
    board[n/2][n/2] = 'W';
    board[n/2-1][n/2] = 'B';
    board[n/2-1][n/2-1] = 'W';

    printBoard(board, n);

    //Ask the user to enter the board configuration
    printf("\nEnter board configuration: ");
    char row, col, colour, enter;
    do{
        scanf("%c%c%c%c",&enter,&colour,&row,&col);
        board[row-97][col-97]=colour;
    }while(row != '!' && col != '!' && colour != '!');

    printBoard(board, n);

    printf("\nAvailable moves for W:\n");
    checkLegalInDirectionLoop(board,n,'W',NULL);
    printf("Available moves for B:\n");
    checkLegalInDirectionLoop(board,n,'B',NULL);

    userInput(board, n);

    printBoard(board,n);

    return 0;
}
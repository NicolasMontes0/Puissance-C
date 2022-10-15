#include <stdio.h>
#include <stdlib.h>

void displayArray(char **gameBoard, int rows, int columns)
{
    for(int row = 0 ; row < rows ; row++) {
        printf("|");
        for (int column = 0; column < columns; column++) {
            printf(" %c |", gameBoard[row][column]);
        }
        printf("\n");
    }
    for(int i = 0 ; i < columns*2*2+1 ; i++){
        printf("=");
    }
    printf("\n");
}

int main() {
    //Initialisation
    int win = 0;
    char players[2][4] = {{1, 2, 3, 4}, {'X', 'O', 'Y', 'Z'}};
    int rows = 6;
    int columns = 7;
    int playerCount = 3;
    int pawnToWin = 4;

    printf("Nombre de lignes :");
    scanf("%d", &rows);
    printf("Nombre de colonnes :");
    scanf("%d", &columns);
    printf("Nombre de joueur :");
    scanf("%d", &playerCount);
    printf("Nombre de pion a placer :");
    scanf("%d", &pawnToWin);


    // construction du board
    char** gameBoard = malloc(sizeof (char*) * rows);
    for(int i=0 ; i < rows ; i++){
        gameBoard[i] = malloc(sizeof(char) * columns);
    }

    for(int row = 0 ; row < rows ; row++){
        for(int column = 0 ; column < columns ; column++) {
            gameBoard[row][column] = ' ';
        }
    }

    // end - construction du board

    int turn = 1;
    int currentPlayer = 0;
    int selectedColumn = 0;
    int selectedRow = 0;
    int played = 0;
    int alignatedPawn = 1;
    char currentPlayerPawn = 'X';
    int trueColumn = 0;

    //Boucle du jeu
    while(win == 0){
        printf("Tour :%d\n", turn);
        currentPlayer = (turn-1) % (playerCount);

        printf("Au joueur %d de jouer\n", currentPlayer+1);
        displayArray(gameBoard, rows, columns);

        do{
            do{
                printf("Choisissez la colonne :");
                scanf("%d", &selectedColumn);
                selectedColumn--;
                if(selectedColumn >= 0 && selectedColumn < columns && gameBoard[0][selectedColumn] == ' '){
                    trueColumn = 1;
                }else{
                    printf("COLONNE INEXISTANTE OU PLEINNE !\n\n");
                }
            }while(trueColumn == 0);
            trueColumn = 0;

            //Placement du pion
            currentPlayerPawn = players[1][currentPlayer];

            for(int i = rows-1 ; i >= 0 ; i--){
                if(gameBoard[i][selectedColumn] == ' '){
                    gameBoard[i][selectedColumn] = currentPlayerPawn;
                    played = 1;
                    selectedRow = i;
                    break;
                }
            }
        }while(played == 0);
        played = 1;

        //displayArray(gameBoard, rows, columns);

        //Verification de victoire horizontale
        for(int i = 1 ; i < columns-1 ; i++){
            if(selectedColumn+i >= columns || gameBoard[selectedRow][selectedColumn+i] == ' ') {
                break;
            }else if(gameBoard[selectedRow][selectedColumn+i] == currentPlayerPawn){
                alignatedPawn++;
            }
        }
        for(int i = 1 ; i < columns-1 ; i++){
            if(selectedColumn-i < 0 || gameBoard[selectedRow][selectedColumn-i] == ' ') {
                break;
            }else if(gameBoard[selectedRow][selectedColumn-i] == currentPlayerPawn){
                alignatedPawn++;
            }
        }
        if(alignatedPawn >= pawnToWin){
            win = 1;
            break;
        }
        alignatedPawn = 1;

        //Verification de victoire verticale
        for(int i = 1 ; i < rows ; i++){
            if(selectedRow+i >= rows || gameBoard[selectedRow+i][selectedColumn] != currentPlayerPawn) {
                break;
            }else {
                alignatedPawn++;
            }
        }
        for(int i = 1 ; i < rows ; i++){
            if(selectedRow-i < 0 || gameBoard[selectedRow-i][selectedColumn] != currentPlayerPawn) {
                break;
            }else{
                alignatedPawn++;
            }
        }
        if(alignatedPawn >= pawnToWin){
            win = 1;
            break;
        }
        alignatedPawn = 1;

        //Verification de victoire diagonale DL-UR
        for(int i = 1 ; i < rows && i < columns ; i++){
            if(selectedRow+i >= rows || selectedColumn-i <0 || gameBoard[selectedRow+i][selectedColumn-i] != currentPlayerPawn) {
                break;
            }else {
                alignatedPawn++;
            }
        }
        for(int i = 1 ; i < rows && i < columns ; i++){
            if(selectedRow-i < 0 || selectedColumn+i >= columns || gameBoard[selectedRow-i][selectedColumn+i] != currentPlayerPawn) {
                break;
            }else{
                alignatedPawn++;
            }
        }
        if(alignatedPawn >= pawnToWin){
            win = 1;
            break;
        }
        alignatedPawn = 1;

        //Verification de victoire diagonale DL-UR
        for(int i = 1 ; i < rows && i < columns ; i++){
            if(selectedRow+i >= rows || selectedColumn+i >= columns || gameBoard[selectedRow+i][selectedColumn+i] != currentPlayerPawn) {
                break;
            }else {
                alignatedPawn++;
            }
        }
        for(int i = 1 ; i < rows && i < columns ; i++){
            if(selectedRow-i < 0 || selectedColumn+i < 0 || gameBoard[selectedRow-i][selectedColumn-i] != currentPlayerPawn) {
                break;
            }else{
                alignatedPawn++;
            }
        }
        if(alignatedPawn >= pawnToWin){
            win = 1;
            break;
        }
        alignatedPawn = 1;


        turn++;
    }
    displayArray(gameBoard, rows, columns);
    printf("Joueur %c gagne !!!", currentPlayerPawn);
}
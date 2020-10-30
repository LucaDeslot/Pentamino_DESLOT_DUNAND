#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"

#define MAX_SIZE 5

int main() {
    bool exit=false;

    int grid[10][6];
    int(**pieces)[MAX_SIZE][MAX_SIZE];//tableau de pointeur
    //tableau de pointeur pour les pièces -> chaque pointeur renvoie vers un int[][] qui est une piece
    createPieces(pieces, "0");

    return 0;
}

void createPieces(int **pieces, char* levelNumber){
    //nom fichier
    char* fileName;
    if(atoi(levelNumber)>=10){
        fileName=(char*)malloc(sizeof(char)*15);
    }
    else{
        fileName=(char*)malloc(sizeof(char)*14);
    }
    strcpy(fileName,"../level");
    strcat(fileName, levelNumber);
    strcat(fileName, ".txt");

    FILE* file = NULL;
    file = fopen(fileName, "r");// ../ car l'exe se créer dans CMakeFiles/
    *pieces = malloc(findPiecesNumber(file)*sizeof(int*));
    if(file!=NULL){
        fclose(file);
    }
    else{
        printf("Le fichier n'a pas pu etre ouvert fonction createPieces");
    }




    free(fileName);
}

//Parcours le fichier pour trouver le nombre de pièces
int findPiecesNumber(FILE* file){
    int readChar = 0;
    int nbPiece = 0;
    bool emptyRow = true;

    do {
        readChar = fgetc(file);
        if(readChar == '#'){
            emptyRow = false;
        } else if(readChar == '\n'){
            if(emptyRow){ // si à la fin de la ligne emptyRow = true alors il n'y a pas/plus de pièce.
                nbPiece++;
                emptyRow = false;
            } else {
                emptyRow = true;
            }
        }
    }while(readChar != EOF);

    return nbPiece; // Le code compte à partir de la première pièce, inutile de retirer la grille en faisant -1
}
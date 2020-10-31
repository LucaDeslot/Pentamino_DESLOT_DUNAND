#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"

int main() {
    bool exit=false;

    int grid[10][6];
    int (*pieces) [MAX_SIZE][MAX_SIZE] = NULL; //Tableau dynamique de tableau 2D d'int, chaque rang du tableau correspond à une pièce
    createPieces(&pieces, "0");

    free(pieces);
    return 0;
}

void createPieces(int (**pieces)[MAX_SIZE][MAX_SIZE], char* levelNumber){
    //nom fichier
    //blablabladdddd
    char* fileName;
    if(atoi(levelNumber)>=10){
        fileName=(char*)malloc(sizeof(char)*15);
    }
    else{
        fileName=(char*)malloc(sizeof(char)*14);
    }
    //concaténation pour le nom du fichier à parcourir
    strcpy(fileName,"../level");
    strcat(fileName, levelNumber);
    strcat(fileName, ".txt");

    //ouverture du fichier et allocation mémoire du tableau de pièce
    FILE* file = NULL;
    file = fopen(fileName, "r");// ../ car l'exe se créer dans CMakeFiles/
    *pieces = malloc(sizeof(int[MAX_SIZE][MAX_SIZE])*findPiecesNumber(file)); //12 = nb pièces

    char readChar = 0;
    int numPiece = 0;
    bool endPiece = false;

    for (int i = 0; i < 67; i++){readChar = fgetc(file);} // passe le tableau de jeu :TODO MALLOC de grid

    do{
        for (int x = 0; x < MAX_SIZE; ++x) {
            for (int y = 0; y < MAX_SIZE; ++y) {
                if (endPiece){
                    readChar = fgetc(file);
                }
                if (readChar == '#') {
                    endPiece = true;
                    (*pieces)[numPiece][x][y] = 1;
                } else if(readChar == '\n'){
                    if(y < MAX_SIZE) { //Si on atteint la fin de la ligne et que on a pas atteint MAX_SIZE on rempli par des 0
                        while(y < MAX_SIZE){
                            (*pieces)[numPiece][x][y] = 0;
                            y++;
                        }
                        readChar = fgetc(file);
                        endPiece = false;
                        if(readChar == '\n'){
                            endPiece = true;
                            x++;
                            while(x < MAX_SIZE){
                                for (y = 0; y < MAX_SIZE; ++y) {
                                    (*pieces)[numPiece][x][y] = 0;
                                }
                                x++;
                            }
                            y = MAX_SIZE;
                            numPiece++;
                        }
                    }
//
                } else {
                    (*pieces)[numPiece][x][y] = 0;
                    endPiece = true;
                }
            }
        }
    }while (readChar != EOF);

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
    rewind(file); // on retourne au début du fichier pour les autres fonctions
    return nbPiece; // Le code compte à partir de la première pièce, inutile de retirer la grille en faisant -1
}
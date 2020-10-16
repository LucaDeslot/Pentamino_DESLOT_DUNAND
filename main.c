#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"

int main() {
    bool exit=false;

    int grid[10][6];
    int(*pieces[1])[3][3];//tableau de pointeur
    //tableau de pointeur pour les pièces -> chaque pointeur renvoie vers un int[][] qui est une piece

    int p1[3][3];
    p1[0][0]=1;
    p1[0][1]=1;
    p1[0][2]=1;

    p1[1][0]=0;
    p1[1][1]=1;
    p1[1][2]=0;

    p1[2][0]=0;
    p1[2][1]=1;
    p1[2][2]=0;

    pieces[0]=&p1;

    createPieces(pieces, "0");

    return 0;
}

void createPieces(int* pieces, char* levelNumber){
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

    printf("%s",fileName);
    FILE* file = NULL;
    file = fopen(fileName, "r");// ../ car l'exe se créer dans CMakeFiles/
    if(file!=NULL){
        fclose(file);
    }
    else{
        printf("Le fichier n'a pas pu etre ouvert fonction createPieces");
    }
    free(fileName);
}

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
/*#include <SDL2/SDL_ttf.h>
#include "SDL2_ttf/SDL_ttf.h"*/

#include "main.h"
#include "sdl_functions.h"

int main() {
    bool exit=false;//sortir de la boucle
    SDL_Event event;//évènement SDL par exemple saisie clavier
    SDL_Init(SDL_INIT_VIDEO);
    struct piece SDL_Pieces[12];

    for (int i = 0; i < 12; ++i) {
        SDL_Pieces[i].onGrid = 0;
    }
    //TODO: remplacer le 12 par du dynamisme

    //création de la fenêtre
    SDL_Window* window=SDL_CreateWindow("Pentamino DESLOT DUNAND", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_SCREEN, HEIGHT_SCREEN, 0);
    if(window == NULL){//Erreur fenetre
        printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
    }
    //Création du renderer
    SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,0);

    if(SDL_Init(SDL_INIT_VIDEO) < 0){// Initialisation de la SDL
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }// Créer la fenêtre

    if(window == NULL){// En cas d’erreur
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    /*if(TTF_Init()==-1){
        printf("Erreur lors de l'initialisation de la TTF : %s",TTF_GetError());
    }
    TTF_Font *font=TTF_OpenFont("./arial.ttf",28);*/


    // Mettre en place un contexte de rendu de l’écran
    int** grid = NULL;
    int (*pieces) [MAX_SIZE][MAX_SIZE] = NULL; //Tableau dynamique de tableau 2D d'int, chaque rang du tableau correspond à une pièce
    createPieces(&pieces, "0", &grid);

    SDL_Rect selectedPieceSavedCord[NUMBER_PART_PIECE];
    SDL_Point mousePosition;
    SDL_Point clickedPoint;
    int rankPieceSelected = -1;
    struct gridSquare *gridSquares = NULL;
    int isPieceBig = 0;
    while(!exit){//boucle principale du jeu
        //TODO: il faut que numberPieces soit dynamique, utiliser la fonction findPiecesNumber() ?

        while(SDL_PollEvent(&event))
            switch(event.type){
                case SDL_QUIT:exit = true;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            exit=true;
                            break;
                    }
                    break;

                case SDL_MOUSEMOTION:
                    mousePosition.x = event.motion.x;
                    mousePosition.y = event.motion.y;
                    if(rankPieceSelected != -1){
                        SDL_Pieces[rankPieceSelected].rects[0].x = mousePosition.x;
                        SDL_Pieces[rankPieceSelected].rects[0].y = mousePosition.y;

                            for (int j = 0; j < NUMBER_PART_PIECE; ++j) {

                                if (selectedPieceSavedCord[j].x < selectedPieceSavedCord[0].x) {
                                    SDL_Pieces[rankPieceSelected].rects[j].x = SDL_Pieces[rankPieceSelected].rects[0].x -
                                                          (selectedPieceSavedCord[0].x - selectedPieceSavedCord[j].x);
                                } else if (selectedPieceSavedCord[j].x >= selectedPieceSavedCord[0].x) {
                                    SDL_Pieces[rankPieceSelected].rects[j].x = SDL_Pieces[rankPieceSelected].rects[0].x +
                                                          (selectedPieceSavedCord[j].x - selectedPieceSavedCord[0].x);
                                }

                                if (selectedPieceSavedCord[j].y < selectedPieceSavedCord[0].y) {
                                    SDL_Pieces[rankPieceSelected].rects[j].y = SDL_Pieces[rankPieceSelected].rects[0].y -
                                                          (selectedPieceSavedCord[0].y - selectedPieceSavedCord[j].y);
                                } else if (selectedPieceSavedCord[j].y >= selectedPieceSavedCord[0].y) {
                                    SDL_Pieces[rankPieceSelected].rects[j].y = SDL_Pieces[rankPieceSelected].rects[0].y +
                                                          (selectedPieceSavedCord[j].y - selectedPieceSavedCord[0].y);
                                }

                            }
                    }

                    if (gridSquares != NULL){
                        setGrid(gridSquares, &(SDL_Pieces[rankPieceSelected]), 60, SDL_Pieces[rankPieceSelected].color,
                                rankPieceSelected);
                    }

                    break;

                case SDL_MOUSEBUTTONDOWN:
                    printf("Souris : %d,%d\n",event.motion.x,event.motion.y);
                    printf("Rectangle : %d,%d",SDL_Pieces[3].rects[0].x,SDL_Pieces[3].rects[0].y);
                    if (rankPieceSelected == -1){
                        for (int i = 0; i < 12; ++i) {
                            for (int j = 0; j < NUMBER_PART_PIECE; ++j) {
                                if(SDL_PointInRect(&mousePosition,&(SDL_Pieces[i].rects[j]))){
                                    rankPieceSelected = i;
                                    clickedPoint.y = SDL_Pieces[i].rects[0].y;
                                    clickedPoint.x = SDL_Pieces[i].rects[0].x;
                                    if (getGridSquareWithPiece(gridSquares,60,SDL_Pieces[rankPieceSelected].rects[0]) != -1){
                                        setSizePiece(&(SDL_Pieces[rankPieceSelected]), 1);
                                    } else {
                                        setSizePiece(&(SDL_Pieces[rankPieceSelected]), 0);
                                    }
                                    for (int k = 0; k < NUMBER_PART_PIECE; ++k) {
                                        selectedPieceSavedCord[k].x = SDL_Pieces[rankPieceSelected].rects[k].x;
                                        selectedPieceSavedCord[k].y = SDL_Pieces[rankPieceSelected].rects[k].y;
                                    }
                                }
                            }
                        }
                    } else {
                        putPieceOnGrid(gridSquares,60,&SDL_Pieces,SDL_Pieces[rankPieceSelected].color,&rankPieceSelected);
                    }

                    break;
            }

        SDL_SetRenderDrawColor(renderer, 255,255,255,255);//couleur du fond
        SDL_RenderClear(renderer);

        SDL_Rect partDisplayPiece={0,0,WIDTH_SCREEN/4,HEIGHT_SCREEN};//partie gauche de l'écran qui contient l'affichage des pièces
        SDL_SetRenderDrawColor(renderer, 125, 125, 125, 0);
        SDL_RenderFillRect(renderer,&partDisplayPiece);

        SDL_Rect partDispalyScore={0,HEIGHT_SCREEN-(HEIGHT_SCREEN/4),WIDTH_SCREEN,HEIGHT_SCREEN/4};//partie basse de la fenêtre, affichage des scores
        SDL_SetRenderDrawColor(renderer, 125, 125, 125, 0);
        SDL_RenderFillRect(renderer,&partDispalyScore);

        displayPieces(&window,&SDL_Pieces, &pieces, 12, rankPieceSelected);
        displayGrid(10, 6, &window, &gridSquares, SDL_Pieces);
        SDL_RenderPresent(renderer);
    }

    free(pieces);
    SDL_DestroyWindow(window);
    /*TTF_CloseFont(font);//on désaloue TTF
    TTF_Quit();*/
    return 0;
}

void createPieces(int (**pieces)[MAX_SIZE][MAX_SIZE], char* levelNumber, int*** grid){

    //ouverture du fichier et allocation mémoire du tableau de pièce
    char* fileName = getFileNameFromLevel(levelNumber);
    FILE* file = fopen(fileName, "r");
    free(fileName);
    *pieces = malloc(sizeof(int[MAX_SIZE][MAX_SIZE])*findPiecesNumber(levelNumber));

    char readChar = 0; //Pour lire le charactère du fichier
    int numPiece = 0; //numéro de la pièce lu

    int endGrid = 0;
    int row = 0;
    int col = 0;

    readChar = fgetc(file);
    while (!endGrid){
        while (readChar != '\n'){
            col++;
            readChar = fgetc(file);
        }
        readChar = fgetc(file);
        if (readChar == '\n'){
            endGrid = 1;
        } else {
            row++;
        }
    }

    *grid = (int**) malloc(col*sizeof(int*));
    for (int i = 0; i < col; i++){
        (*grid)[i] = (int*) malloc(row*sizeof(int));
        for(int j = 0; j < row; j++){
            (*grid)[i][j] = 0;
        }
    }

    readChar = fgetc(file);
    do{
        for (int x = 0; x < MAX_SIZE; ++x) {
            for (int y = 0; y < MAX_SIZE; ++y) {
                if(readChar == '\n'){ // si on arrive à la fin de la ligne
                    while(y < MAX_SIZE){//Si on atteint la fin de la ligne et que on a pas atteint MAX_SIZE on rempli par des 0
                        (*pieces)[numPiece][x][y] = 0;
                        y++;
                    }
                    readChar = fgetc(file);
                    if(readChar == '\n'){ // si on est encore en fin de ligne -> fin de la pièce
                        x++;
                        while(x < MAX_SIZE){ //on rempli de 0 les lignes restantes.
                            for (y = 0; y < MAX_SIZE; ++y) {
                                (*pieces)[numPiece][x][y] = 0;
                            }
                            x++;
                        }
                        numPiece++; // on passe à la pièce suivante
                        readChar = fgetc(file); // on lit la première partie de la pièce suivante
                    }

                } else if (readChar == '#'){ // 1 correspond à la présence d'une pièce
                    readChar = fgetc(file);
                    (*pieces)[numPiece][x][y] = 1;
                } else { // si readChar == ' ' || readChar == EOF
                    readChar = fgetc(file);
                    (*pieces)[numPiece][x][y] = 0;
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
}

//Parcours le fichier pour trouver le nombre de pièces
int findPiecesNumber(char *levelNumber){
    int readChar = 0;
    int nbPiece = 0;
    bool emptyRow = true;
    FILE* file = fopen(getFileNameFromLevel(levelNumber), "r");

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
    fclose(file);
    return nbPiece; // Le code compte à partir de la première pièce, inutile de retirer la grille en faisant -1
}

char* getFileNameFromLevel(char* levelNumber) {
    char* fileName;
    if(atoi(levelNumber)>=10){
        fileName=(char*)malloc(sizeof(char)*15);
    }
    else{
        fileName=(char*)malloc(sizeof(char)*14);
    }
    //concaténation pour le nom du fichier à parcourir
    strcpy(fileName,"../level");// ../ car l'exe se créer dans CMakeFiles/
    strcat(fileName, levelNumber);
    strcat(fileName, ".txt");
    return fileName;
}
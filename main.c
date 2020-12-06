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


    SDL_Rect** selectedPiece = malloc(sizeof(SDL_Rect*)*5);
    SDL_Rect selectedPieceSavedCord[NUMBER_PART_PIECE];
    int isPieceSelected = 0;
    SDL_Point mousePosition;
    SDL_Point clickedPoint;
    int rankPieceSelected = -1;
    SDL_Rect* gridSquares;
    int squareOverGrid[NUMBER_PART_PIECE] = {0};
    while(!exit){//boucle principale du jeu
        //TODO: il faut que numberPieces soit dynamique, utiliser la fonction findPiecesNumber() ?

        while( SDL_PollEvent( &event ) )
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

                    if(isPieceSelected){
                        selectedPiece[0]->x = mousePosition.x;
                        selectedPiece[0]->y = mousePosition.y;
                        if (isSquareOverGrid(selectedPiece[0], gridSquares, &renderer, 60)){// on vérifie si des carré sont sur la grille
                            squareOverGrid[0] = 1;

                        } else {
                            squareOverGrid[0] = 0;
                        }
                        for (int i = 1; i < NUMBER_PART_PIECE; ++i) {
                            if (isSquareOverGrid(selectedPiece[i], gridSquares, &renderer, 60)){// on vérifie si des carré sont sur la grille
                                squareOverGrid[i] = 1;
                            } else {
                                squareOverGrid[i] = 0;
                            }
                            if (selectedPieceSavedCord[i].x < selectedPieceSavedCord[0].x){
                                selectedPiece[i]->x = selectedPiece[0]->x - (selectedPieceSavedCord[0].x - selectedPieceSavedCord[i].x);
                            } else if (selectedPieceSavedCord[i].x >= selectedPieceSavedCord[0].x){
                                selectedPiece[i]->x = selectedPiece[0]->x + (selectedPieceSavedCord[i].x - selectedPieceSavedCord[0].x);
                            }

                            if (selectedPieceSavedCord[i].y < selectedPieceSavedCord[0].y){
                                selectedPiece[i]->y = selectedPiece[0]->y - (selectedPieceSavedCord[0].y - selectedPieceSavedCord[i].y);
                            } else if (selectedPieceSavedCord[i].y >= selectedPieceSavedCord[0].y){
                                selectedPiece[i]->y = selectedPiece[0]->y + (selectedPieceSavedCord[i].y - selectedPieceSavedCord[0].y);
                            }

                        }
                    }
                    break;

                case SDL_MOUSEBUTTONUP:

                    break;

                case SDL_MOUSEBUTTONDOWN:
                    for (int i = 0; i < 12; ++i) {
                        for (int j = 0; j < NUMBER_PART_PIECE; ++j) {
                            if(SDL_PointInRect(&mousePosition,&SDL_Pieces[i].rects[j])){
                                rankPieceSelected = i;
                                clickedPoint.y = SDL_Pieces[i].rects[0].y;
                                clickedPoint.x = SDL_Pieces[i].rects[0].x;
                                isPieceSelected = 1;
                                for (int k = 0; k < NUMBER_PART_PIECE; ++k) {
                                    selectedPiece[k] = &SDL_Pieces[rankPieceSelected].rects[k];
                                }
                                setSizePiece(selectedPiece, 1);
                                for (int k = 0; k < NUMBER_PART_PIECE; ++k) {
                                    selectedPieceSavedCord[k].x = selectedPiece[k]->x;
                                    selectedPieceSavedCord[k].y = selectedPiece[k]->y;
                                }
                            }
                        }
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

        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j <NUMBER_PART_PIECE; ++j) {
                for (int k = 0; k < NUMBER_PART_PIECE; ++k) {
                    if(isPieceSelected){ // si un carré et sur la grille on ne touche pas sa couleur.
                        if (1 == squareOverGrid[k]){
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0); // on fait disparaitre le carré
                        } else {
                            SDL_SetRenderDrawColor(renderer, SDL_Pieces[rankPieceSelected].color.r, SDL_Pieces[rankPieceSelected].color.g, SDL_Pieces[rankPieceSelected].color.b, 0);
                        }
                        SDL_RenderFillRect(renderer, selectedPiece[k]);
                    }
                }
            }
        }

        gridSquares = displayGrid(10, 6, &window);
        displayPieces(&window,rankPieceSelected ,&SDL_Pieces, &pieces, 12, MAX_SIZE, MAX_SIZE);
        SDL_RenderPresent(renderer);
    }

    free(pieces);
    free(selectedPiece);
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
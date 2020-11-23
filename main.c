#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "main.h"
#include "sdl_functions.h"

int main() {
    bool exit=false;//sortir de la boucle
    SDL_Event event;//évènement SDL par exemple saisie clavier
    SDL_Init(SDL_INIT_VIDEO);

    //création de la fenêtre
    SDL_Window* window=SDL_CreateWindow("TESTWINDOW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    if(window == NULL){//Erreur fenetre
        printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    //Création du renderer
    SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    bool exit=false;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){// Initialisation de la SDL
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }// Créer la fenêtre

    window = SDL_CreateWindow("Pentamino DESLOT DUNAND", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_RESIZABLE);
    if(window == NULL){// En cas d’erreur
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int** grid = NULL;
    int (*pieces) [MAX_SIZE][MAX_SIZE] = NULL; //Tableau dynamique de tableau 2D d'int, chaque rang du tableau correspond à une pièce
    createPieces(&pieces, "0", &grid);


    SDL_SetRenderDrawColor(renderer,255,255,255,255);//couleur du fond de la parie des pièces
    SDL_Rect pieceArea={0,0,250,720};
    SDL_RenderFillRect(renderer,&pieceArea);

    displayPieces(&window,&pieces,12,MAX_SIZE,MAX_SIZE);

    SDL_RenderPresent(renderer);

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
                        /*case SDLK_q://on saisit la touche q au clavier
                            //exit = true;
                            break;*/
                        /*case SDLK_UP:
                            direction=UP;
                            break;
                        case SDLK_DOWN:
                            direction=DOWN;
                            break;
                        case SDLK_RIGHT:
                            direction=RIGHT;
                            break;
                        case SDLK_LEFT:
                            direction=LEFT;
                            break;*/
                    }
            }
    }
    free(pieces);//libération
    afficherPlateau(10, 6, &window);
    //displayPiece(&pieces,findPiecesNumber("0"),MAX_SIZE,MAX_SIZE);
    free(pieces);
    SDL_DestroyWindow(window);
    SDL_Delay(5000);
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
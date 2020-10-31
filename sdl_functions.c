//
// Created by nathand on 31/10/2020.
//
#include <SDL2/SDL.h>
#include "sdl_functions.h"

void displayPiece(int (**pieces)[5][5],int numberPieces,int firstDimensionTab,int secondDimensionTab){//pour le moment elle ne prend rien

    for(int k=0;k<numberPieces;k++) {//affichage des pieces
        for(int i=0;i<firstDimensionTab;i++){
            for(int j=0;j<secondDimensionTab;j++){
                printf("%i",(*pieces)[k][i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    //Déclaration
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect partPiece[PIECE_SIZE];//sous partie des pièces:TODO régler la taille du tableau des parties d'une pièce

    //SDL_Point ligne_depart,ligne_arrivee; // Déclaration du point de départ et du point d'arrivée d'une ligne

    //Création d'une fenêtre
    window=SDL_CreateWindow("TESTWINDOW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    if(window == NULL){//Erreur fenetre
        printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    //Création du renderer
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer==NULL){//Erreur renderer
        printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer,0,0,0,255);//couleur du fond
    SDL_RenderClear(renderer);//permet de nettoyer le renderer et de pouvoir appliquer d'autres couleur (?)

    SDL_SetRenderDrawColor(renderer,120,120,120,255);//couleur des cases

    partPiece[0].x=partPiece[0].y=0;
    partPiece[0].w=partPiece[0].h=0;

    for(int i = 1; i != PIECE_SIZE; i++)//TODO: modifier ce truc, actuellement il configure un damier
    {
        partPiece[i].x = partPiece[i-1].x + 200;
        partPiece[i].y = partPiece[i-1].y;

        if(i%4 == 0) //retour à la ligne
        {
            partPiece[i].x = (i%8 == 0) ? 0 : 100;
            partPiece[i].y = partPiece[i-1].y + 100;
        }
        partPiece[i].w = partPiece[i].h = 100; //taille d'une case : 100 x 100
    }

    if(SDL_RenderFillRects(renderer, partPiece, PIECE_SIZE)<0){//on colore les parties de la pièce
        printf("Erreur lors de la coloration des parties d'une piece : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_RenderPresent(renderer);//rendu et affichage
    SDL_Delay(2000);

    //liberation mémoire
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

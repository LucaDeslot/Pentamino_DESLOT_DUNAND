//
// Created by nathand on 31/10/2020.
//
#include "SDL2/SDL.h"
#include <stdbool.h>

#include "sdl_functions.h"

void displayPieces(int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE],int numberPieces,int firstDimensionTab,int secondDimensionTab)//affiche toutes les pièces
{
    //Déclaration
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect partPiece[12][NUMBER_PART_PIECE];//sous partie des pièces
    //TODO: malloc à faire pour le nombre de pièce

    //Création d'une fenêtre
    window=SDL_CreateWindow("TESTWINDOW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
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

    SDL_SetRenderDrawColor(renderer,255,0,255,255);//couleur des cases

    int shiftOrdinate=0;//décallage des ordonnées
    int shiftAbscissa=0;//décallage des abscisses

    for(int i=0;i<12;i++){
        displayPiece(pieces,i,numberPieces,&partPiece,shiftOrdinate,shiftAbscissa);
        SDL_RenderFillRects(renderer, partPiece[i], NUMBER_PART_PIECE);
        shiftOrdinate+=0;
        shiftAbscissa+=75;
    }

    //SDL_RenderFillRects(renderer, partPiece[1], NUMBER_PART_PIECE);
    if(SDL_RenderFillRects(renderer, partPiece[0], NUMBER_PART_PIECE)<0){//on colore les parties de la pièce
        printf("Erreur lors de la coloration des parties d'une piece : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_RenderPresent(renderer);//rendu et affichage
    SDL_Delay(5000);

    //liberation mémoire
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void displayPiece(int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE],int pieceAfficher,int numberPiece,SDL_Rect (*partPiece)[12][NUMBER_PART_PIECE],int shiftOrdinate,int shiftAbscissa)//affiche une pièce
{
    int countTemporary=0;
    int countReturnLine=0;//peut être pas indispensable, à voir
    int l=0;//compteur interne pour numéroter partPiece[l]
    bool isEndOfLine=false;
    bool flag=false;//utilisé pour bloquer le while() et passer ou non à la ligne suivante de l'affichage
    int countSpaceInPiece=0;//espace de x blocs entre différentes parties d'une pièce

    for(int i=0;i<NUMBER_PART_PIECE;i++){
        for(int j=0;j<NUMBER_PART_PIECE;j++){
            if(!isEndOfLine){
                if((*pieces)[pieceAfficher][i][j]==1) {//si on doit afficher un carré de couleur
                    if(l==0){//toute première itération, il faut donc set partPiece[0] puisqu'on va ensuite se servir de partPiece[l-1]
                        if(countSpaceInPiece!=0){//si on a une pièce qui commence par un vide en haut à gauche
                            (*partPiece)[pieceAfficher][0].x=j*(SPACING_PX+PIECE_SIZE_PX)+shiftAbscissa;
                            (*partPiece)[pieceAfficher][0].y=0+shiftOrdinate;
                        }else{//on a une pièce qui commence par un plein en haut à gauche
                            (*partPiece)[pieceAfficher][0].x=0+shiftAbscissa;
                            (*partPiece)[pieceAfficher][0].y=0+shiftOrdinate;
                        }
                        (*partPiece)[pieceAfficher][0].w=(*partPiece)[pieceAfficher][0].h=PIECE_SIZE_PX;
                    } else{
                        if(j==0 || countSpaceInPiece!=0){//on est sur une nouvelle ligne
                            //nouvelle ligne -> j==0 ou alors si countSpaceInPice!=0 ça veut dire qu'on a un espace en début de ligne
                            if(j==0){//si c'est vraiment le début d'une ligne
                                (*partPiece)[pieceAfficher][l].x = 0+shiftAbscissa;
                                (*partPiece)[pieceAfficher][l].y = i*(SPACING_PX+PIECE_SIZE_PX)+shiftOrdinate;
                            } else{//si la ligne a déjà commencé (j>0)
                                (*partPiece)[pieceAfficher][l].x = j*(SPACING_PX+PIECE_SIZE_PX)+shiftAbscissa;
                                (*partPiece)[pieceAfficher][l].y = i*(SPACING_PX+PIECE_SIZE_PX)+shiftOrdinate;
                            }
                        } else{//on est pas sur un nouvelle ligne, on continue
                            (*partPiece)[pieceAfficher][l].x = j*(SPACING_PX+PIECE_SIZE_PX)+shiftAbscissa;
                            (*partPiece)[pieceAfficher][l].y = i*(SPACING_PX+PIECE_SIZE_PX)+shiftOrdinate;
                        }
                        (*partPiece)[pieceAfficher][l].w = (*partPiece)[pieceAfficher][l].h = PIECE_SIZE_PX; //taille d'une case de la piece
                    }
                    l++;
                } else{//=0, deux possibilités encore ...
                    countTemporary=j+1;//reboot du compteur temporaire à la case suivante
                    countSpaceInPiece=1;//il y a au moins 1 espace
                    while(countTemporary<NUMBER_PART_PIECE && !flag){//on vérifie qu'il existe encore un 1 dans la ligne
                        if((*pieces)[pieceAfficher][i][countTemporary]==1){
                            isEndOfLine=false;//il existe encore un 1, la ligne n'est pas terminée d'être affichée
                            flag=true;
                        } else{//si ==0
                            countSpaceInPiece++;//on a sauté un espace en plus
                        }
                        countTemporary++;
                    }
                    if(!flag){//si flag reste à faux alors il n'y a aucun 1 dans le restant de la ligne
                        isEndOfLine=true;//c'est donc qu'on doit passer à la ligne suivante
                    }
                    if(isEndOfLine){//... s'il n'y a plus de 1 jusqu'à la fin de la ligne
                        countReturnLine++;
                    }
                }
            }
        }
        countSpaceInPiece=0;//reboot du compteur
        isEndOfLine=false;//il faut la remettre à false puisqu'on passe à la ligne suivante
    }
}

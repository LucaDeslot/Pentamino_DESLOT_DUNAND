//
// Created by nathand on 31/10/2020.
//
#include "SDL2/SDL.h"
#include <stdbool.h>

#include "sdl_functions.h"

void initColor(SDL_Color (*color)[12]){
    color[0]->r = 30; color[0]->g = 144; color[0]->b = 255; color[0]->a = 255; //dodgerblue
    color[1]->r = 0; color[1]->g = 0; color[1]->b = 139; color[1]->a = 255; //darkblue
    color[2]->r = 255; color[2]->g = 0; color[2]->b = 0; color[2]->a = 255; //red
    color[3]->r = 219; color[3]->g = 112; color[3]->b = 147; color[3]->a = 255; //palevioletred
    color[4]->r = 0; color[4]->g = 0; color[4]->b = 0; color[4]->a = 255; // black
    color[5]->r = 255; color[5]->g = 69; color[5]->b = 0; color[5]->a = 255; //orangered
    color[6]->r = 30; color[6]->g = 144; color[6]->b = 255; color[6]->a = 255;
    color[7]->r = 30; color[7]->g = 144; color[7]->b = 255; color[7]->a = 255;
    color[8]->r = 30; color[8]->g = 144; color[8]->b = 255; color[8]->a = 255;
    color[9]->r = 30; color[9]->g = 144; color[9]->b = 255; color[9]->a = 255;
    color[10]->r = 30; color[10]->g = 144; color[10]->b = 255; color[10]->a = 255;
    color[11]->r = 30; color[11]->g = 144; color[11]->b = 255; color[11]->a = 255;
}

void displayPieces(SDL_Window (**window),int selectedRect,struct piece (*partPiece)[12],int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE],int numberPieces,int firstDimensionTab,int secondDimensionTab)//affiche toutes les pièces
{
    SDL_Color color[12];
    initColor(&color);

    //Déclaration
    SDL_Renderer* renderer;
    //TODO: malloc à faire pour le nombre de pièce

    //Obtention du renderer à partir de la window
    renderer=SDL_GetRenderer(*window);

    if(renderer==NULL){
        printf("Erreur lors de l'initialisation du renderer : %s", SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer,255,0,255,255);//couleur des cases

    int shiftOrdinate=0;//décallage des ordonnées
    int shiftAbscissa=0;//décallage des abscisses

    for(int i=0;i<12;i++){//TODO  12 doit être dynamique ici

        if (selectedRect != i){
            displayPiece(pieces,i,numberPieces,partPiece,shiftOrdinate,shiftAbscissa);
            SDL_RenderFillRects(renderer, (*partPiece)[i].rects, NUMBER_PART_PIECE);
        }
        shiftOrdinate+=0;
        shiftAbscissa+=75;
    }

    if(SDL_RenderFillRects(renderer, (*partPiece)[0].rects, NUMBER_PART_PIECE)<0){//on colore les parties de la pièce
        printf("Erreur lors de la coloration des parties d'une piece : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void displayPiece(int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE],int pieceAfficher,int numberPiece,struct piece (*partPiece)[12],int shiftOrdinate,int shiftAbscissa)//affiche une pièce
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
                            (*partPiece)[pieceAfficher].rects[0].x=j*(SPACING_PX+PIECE_SIZE_PX)+shiftAbscissa;
                            (*partPiece)[pieceAfficher].rects[0].y=0+shiftOrdinate;
                        }else{//on a une pièce qui commence par un plein en haut à gauche
                            (*partPiece)[pieceAfficher].rects[0].x=0+shiftAbscissa;
                            (*partPiece)[pieceAfficher].rects[0].y=0+shiftOrdinate;
                        }
                        (*partPiece)[pieceAfficher].rects[0].w=(*partPiece)[pieceAfficher].rects[0].h=PIECE_SIZE_PX;
                    } else{
                        if(j==0 || countSpaceInPiece!=0){//on est sur une nouvelle ligne
                            //nouvelle ligne -> j==0 ou alors si countSpaceInPice!=0 ça veut dire qu'on a un espace en début de ligne
                            if(j==0){//si c'est vraiment le début d'une ligne
                                (*partPiece)[pieceAfficher].rects[l].x = 0+shiftAbscissa;
                                (*partPiece)[pieceAfficher].rects[l].y = i*(SPACING_PX+PIECE_SIZE_PX)+shiftOrdinate;
                            } else{//si la ligne a déjà commencé (j>0)
                                (*partPiece)[pieceAfficher].rects[l].x = j*(SPACING_PX+PIECE_SIZE_PX)+shiftAbscissa;
                                (*partPiece)[pieceAfficher].rects[l].y = i*(SPACING_PX+PIECE_SIZE_PX)+shiftOrdinate;
                            }
                        } else{//on est pas sur un nouvelle ligne, on continue
                            (*partPiece)[pieceAfficher].rects[l].x = j*(SPACING_PX+PIECE_SIZE_PX)+shiftAbscissa;
                            (*partPiece)[pieceAfficher].rects[l].y = i*(SPACING_PX+PIECE_SIZE_PX)+shiftOrdinate;
                        }
                        (*partPiece)[pieceAfficher].rects[l].w = (*partPiece)[pieceAfficher].rects[l].h = PIECE_SIZE_PX; //taille d'une case de la piece
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

/*
 * set : la paramètrage de la taille
 * si set = 0 alors la taille redevient normal quand aucun pièce n'est sélectionnée
 * si set = 1 alors chaque partie de la pièce prend la taille d'un carré de la grille
 */
void setSizePiece(SDL_Rect **piece, int set) {
    int ratio = PIECE_SIZE_GRID_PX/PIECE_SIZE_PX;
    if (set){
        for (int i = 0; i < NUMBER_PART_PIECE; ++i) {
            piece[i]->x *= ratio;
            piece[i]->y *= ratio;
            piece[i]->h *= ratio;
            piece[i]->w *= ratio;
        }
    }
}

SDL_Rect * displayGrid(int x, int y, SDL_Window **window) {

    //Déclaration
    SDL_Rect *rect = malloc(x * y * sizeof(SDL_Rect));
    SDL_Renderer* renderer = SDL_GetRenderer(*window);
    int width = x;
    int gridStartX;
    SDL_GetWindowSize(*window, &gridStartX, NULL);
    gridStartX /= 3;
    SDL_SetRenderDrawColor(renderer,182,182,182,255); //Couleur des cases du plateau

    rect[0].x = gridStartX;
    rect[0].y = HEIGHT_SCREEN/12;
    rect[0].w = PIECE_SIZE_GRID_PX;
    rect[0].h = rect[0].w;

    int gridSize = x * y;
    for (int i = 1; i < gridSize; ++i) {
        if(i == x){ //retour à la ligne
            x += width;
            rect[i].x = gridStartX;
            rect[i].y = rect[i-1].h + rect[i-1].y + SPACING_PX_GRID;
        } else {
            rect[i].x = rect[i-1].x + rect[i-1].w + SPACING_PX_GRID;
            rect[i].y = rect[i-1].y;
        }
        rect[i].w = rect[0].w;
        rect[i].h = rect[0].h;
    }

    SDL_RenderFillRects(renderer, rect, gridSize);

    return rect;

}

int isSquareOverGrid(SDL_Rect *square, SDL_Rect *grid, SDL_Renderer **renderer, int gridSize) { //retourne le rang du carré de la pièce sur le plateau
    int squareOver = 0;
    int pX, pY, pH, pW, gX, gY, gH, gW;
    pX = square->x;
    pY = square->y;
    pH = square->h;
    pW = square->w;
    for (int j = 0; j < gridSize; ++j) {
        gX = grid[j].x;
        gY = grid[j].y;
        gH = grid[j].h;
        gW = grid[j].w;
        if(pX >= gX && pX <= gX + gW){
            if((pY + pH > gY && pY + pH < gY + gH) || (pY > gY && pY < gY + gH)){
                squareOver = 1;
            }
        } else if (pY >= gY && pY <= gY + gH){
            if ((pX + pW > gX && pX + pW < gX + gW) || (pX < gX + gW && pX > gX)){
                squareOver = 1;
            }
        }
    }
    return squareOver;
}

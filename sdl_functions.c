//
// Created by nathand on 31/10/2020.
//
#include <stdbool.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

#include "sdl_functions.h"

void initColor(struct piece (*piece)[12]){
    (*piece)[0].color.r = 30; (*piece)[0].color.g = 144; (*piece)[0].color.b = 255; //dodgerblue
    (*piece)[1].color.r = 0; (*piece)[1].color.g = 0; (*piece)[1].color.b = 139; //darkblue
    (*piece)[2].color.r = 255; (*piece)[2].color.g = 0; (*piece)[2].color.b = 0; //red
    (*piece)[3].color.r = 219; (*piece)[3].color.g = 112; (*piece)[3].color.b = 147; //palevioletred
    (*piece)[4].color.r = 0; (*piece)[4].color.g = 0; (*piece)[4].color.b = 0; // black
    (*piece)[5].color.r = 255; (*piece)[5].color.g = 69; (*piece)[5].color.b = 0; //orangered
    (*piece)[6].color.r = 255; (*piece)[6].color.g = 0; (*piece)[6].color.b = 255; //fuchsia
    (*piece)[7].color.r = 75; (*piece)[7].color.g = 0; (*piece)[7].color.b = 130; //indigo
    (*piece)[8].color.r = 255; (*piece)[8].color.g = 192; (*piece)[8].color.b = 203; //pink
    (*piece)[9].color.r = 165; (*piece)[9].color.g = 42; (*piece)[9].color.b = 42; //brown
    (*piece)[10].color.r = 222; (*piece)[10].color.g = 184; (*piece)[10].color.b = 135; //burlywood
    (*piece)[11].color.r = 188; (*piece)[11].color.g = 143; (*piece)[11].color.b = 143; //rosybrown
}

void displayPieces(SDL_Window (**window), int selectedRect, struct piece (*partPiece)[12], int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE], int numberPieces, int firstDimensionTab, int secondDimensionTab)//affiche toutes les pièces
{
    initColor(partPiece);

    //Déclaration
    SDL_Renderer* renderer = SDL_GetRenderer(*window);
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
        }
        SDL_SetRenderDrawColor(renderer,(*partPiece)[i].color.r,(*partPiece)[i].color.g,(*partPiece)[i].color.b,255);//couleur des cases
        SDL_RenderFillRects(renderer, (*partPiece)[i].rects, NUMBER_PART_PIECE);
        shiftOrdinate+=0;
        shiftAbscissa+=100;
    }

    if(SDL_RenderFillRects(renderer, (*partPiece)[0].rects, NUMBER_PART_PIECE)<0){//on colore les parties de la pièce
        printf("Erreur lors de la coloration des parties d'une piece : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void displayPiece(int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE],int pieceAfficher,int numberPiece,struct piece(*partPiece)[12],int shiftOrdinate,int shiftAbscissa)//affiche une pièce
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

    setDisplayPieces(partPiece);//réglage de l'affichage des pièces sur le côté gauche de l'écran
}

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

void setDisplayPieces(struct piece(*partPiece)[12]){//réglage de l'affichage des pièces sur la partie prévue à cet effet, sinon elles débordent de l'affichage
    int shiftOrdinate=100;
    int abscissa=0;
    for(int i=0;i<12;i++){//toutes les pieces de la première à la 12ème
        if(i%3==0 && i!=0){
            for(int k=i;k<12;k++){
                for(int j=0;j<5;j++){//toutes les partie d'une pièce
                    if(j==0){
                        if(k%3==0){
                            abscissa=(*partPiece)[k].rects[j].x;
                        }else if(k%3==1){
                            abscissa=(*partPiece)[k].rects[j].x-((k%3)*100);
                        }else{
                            abscissa=(*partPiece)[k].rects[j].x-((k%3)*100);
                        }
                    }
                    (*partPiece)[k].rects[j].x-=abscissa;
                    (*partPiece)[k].rects[j].y+=shiftOrdinate;
                }
            }
        }
    }
}

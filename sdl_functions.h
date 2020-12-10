//
// Created by nathand on 31/10/2020.
//
#include "SDL2/SDL.h"

#ifndef PENTAMINO_DESLOT_DUNAND_SDL_FUNCTIONS_H
#define PENTAMINO_DESLOT_DUNAND_SDL_FUNCTIONS_H

#endif //PENTAMINO_DESLOT_DUNAND_SDL_FUNCTIONS_H

#define PIECE_SIZE_PX 14
#define PIECE_SIZE_GRID_PX 70 //Vérifier que le ratio PIECE_SIZE_GRID_PX/PIECE_SIZE_PX == SPACING_PX_GRID/SPACING_PX
#define SPACING_PX_GRID 5
#define SPACING_PX 1
#define WIDTH_SCREEN 1280
#define HEIGHT_SCREEN 720
#define NUMBER_PART_PIECE 5//nombre de carré d'affichage d'une pièce, ici 5 par 5

typedef struct color {
    int r;
    int g;
    int b;
} piece_color;

struct piece {
    SDL_Rect rects[5];
    piece_color color;
};

struct gridSquare {
    SDL_Rect rect;
    piece_color color;
};

void initColor(struct piece (*piece)[12]);

void setSizePiece(SDL_Rect **piece, int set);

void displayPieces(SDL_Window (**window),struct piece (*partPiece)[12],int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE],int numberPieces, struct SDL_Rect **selectedPiece,int rankSelectedPiece);//affiche toutes les pièces
void displayPiece(int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE], int pieceAfficher,int numberPiece, struct piece (*partPiece)[12],int shiftOrdinate,int shiftAbscissa);//affiche une pièce

void displayGrid(int x, int y, SDL_Window **window, struct gridSquare **grid, struct piece *pieces);

void setDisplayPieces(struct piece(*partPiece)[12]);
void setGrid(struct gridSquare *grid, SDL_Rect **selectedPiece, int gridSize, struct color pieceColor);

void
placePiece(struct gridSquare *grid, int gridSize, int squareIndex, SDL_Rect **selectedPiece, struct color pieceColor);

int getGridSquareWithPiece(struct gridSquare *grid, int gridSize ,SDL_Rect piece);


//
// Created by nathand on 31/10/2020.
//
#include "SDL2/SDL.h"

#ifndef PENTAMINO_DESLOT_DUNAND_SDL_FUNCTIONS_H
#define PENTAMINO_DESLOT_DUNAND_SDL_FUNCTIONS_H

#endif //PENTAMINO_DESLOT_DUNAND_SDL_FUNCTIONS_H

#define PIECE_SIZE 25
#define PIECE_SIZE_PX 10
#define SPACING_PX 2
#define NUMBER_PART_PIECE 5//nombre de carré d'affichage d'une pièce, ici 5 par 5

void displayPieces(SDL_Window (**window),int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE],int numberPieces,int firstDimensionTab, int secondDimensionTab);//affiche toutes les pièces
void displayPiece(int (**pieces)[NUMBER_PART_PIECE][NUMBER_PART_PIECE], int pieceAfficher,int numberPiece, SDL_Rect (*partPiece)[12][NUMBER_PART_PIECE],int shiftOrdinate,int shiftAbscissa);//affiche une pièce

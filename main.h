//
// Created by nathand on 16/10/2020.
//

#ifndef PENTAMINO_DESLOT_DUNAND_MAIN_H
#define PENTAMINO_DESLOT_DUNAND_MAIN_H

#endif //PENTAMINO_DESLOT_DUNAND_MAIN_H

#define MAX_SIZE 5
#define WIDTH_SCREEN 1280
#define HEIGHT_SCREEN 720

void createPieces(int (**pieces)[MAX_SIZE][MAX_SIZE], char* levelNumber, int*** grid);

int findPiecesNumber(char *levelNumber);

char* getFileNameFromLevel(char* levelNumber);
#ifndef _FILE_H
#define _FILE_H
#include "structs.h"
#include "level.h"
#include "enemy.h"
#include "animations.h"


void FILE_exportLevelToFile(Map_STRUCT *map, char* fileName);

/*
USAGE:
    1. LEVEL_deleteMap(&map);
    2. map = FILE_importFileFromLevel("filename.map", renderer, mapElementsScreens, itemtypesCount);
*/

Map_STRUCT FILE_importLevelFromFile(char* fileName, System* system_data, Player *player, Level *level);

void FILE_updateScoreList(char playerName[21], int score);

#endif //_FILE_H

#ifndef  _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include "structs.h"
#include "player.h"
#include "enemy.h"
#include "level.h"
#include "mainMenu.h"
#include "file.h"
#include "animations.h"

void loadMenu(System *system_data);

void loading(System *system_data);

void lastLevelInfo(System *system_data);

void playerDiedInfo(System *system_data);

void noLevelInfo(System *system_data);

void submitLastScore(System *system_data, Player *player, Level *level);

void openLevelGenerator(System *system_data);

void getLevel(Player *player, Level *level, System *system_data);

void playGame(Player *player, Level *level, System *system_data);

void init(System *system_data, Level *level, Player *player);

void cleanUp(System *system_data);

void runGame();



#endif //_GAME_MANAGER_H

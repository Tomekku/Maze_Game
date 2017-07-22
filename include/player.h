#ifndef  _PLAYER_H
#define _PLAYER_H

#include <stdio.h>
#include "structs.h"
#include "mainMenu.h"
#include "level.h"


void PLAYER_updatePlayer(Player *player, Level *level);

void PLAYER_updatePlayerRect(Player *player, Level *level);

void PLAYER_processEvents(System *system_data, Player *player);

void PLAYER_getTextFromUser(System *system_data, SDL_Rect rect, char* entryText, char* inputText, int inputTextSize);

void PLAYER_updatePlayerScore(System *system_data, Player *player, SDL_Texture** scoreTextTexture);

void PLAYER_updatePlayerKeyCount(System *system_data, Player *player, SDL_Texture** keyCountTextTexture);

void PLAYER_deletePlayer(Player *player);

#endif

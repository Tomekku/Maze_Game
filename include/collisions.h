#ifndef  _COLLISIONS_H
#define _COLLISIONS_H

#include "structs.h"


bool isOverRect(SDL_Rect rect, int coordX, int coordY);

bool isEqualRect(SDL_Rect rect1, SDL_Rect rect2);

bool isCollision(SDL_Rect rect1, SDL_Rect rect2);

bool isCollideWithWalls(SDL_Rect objectRect, Wall* walls);

bool isCollideWithEnemies(SDL_Rect objectRect, Enemy_STRUCT *enemies);

bool isCollideWithCoins(SDL_Rect objectRect, Coin_STRUCT *coins);

bool isCollideWithKeys(SDL_Rect objectRect, Key_STRUCT *keys);

bool isCollideWithDoors(SDL_Rect objectRect, Door_STRUCT *doors);

bool isPlayerCollideWithDoors(Player *player, SDL_Rect objectRect, Door_STRUCT *doors);

bool isOutsideMap(SDL_Rect objectRect, Level *level);

#endif

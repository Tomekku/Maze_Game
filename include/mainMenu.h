#ifndef  _MAINMENU_H
#define _MAINMENU_H

#include "structs.h"
#include "collisions.h"


SDL_Surface* MENU_generateTextsSurface(char* text, bool active, int fontSize);

TEXT* MENU_generateTexts(SDL_Renderer *renderer, int *textsCount);

void MENU_freeTexts(TEXT_STRUCT* menuTexts);

void MENU_changeTextColor(TEXT_STRUCT* menuTexts, SDL_Renderer *renderer, int mouseX, int mouseY);

void MENU_processKeyEvent(System *system_data, TEXT_STRUCT* menuTexts);

void MENU_processEvents(System *system_data, TEXT_STRUCT* menuTexts, int mouseX, int mouseY);


#endif

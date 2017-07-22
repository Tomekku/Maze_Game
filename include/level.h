#ifndef _LEVEL_H
#define _LEVEL_H

#include "structs.h"
#include "mainMenu.h"
#include "file.h"
#include "player.h"


void LEVEL_deleteButton(Button *button);

void LEVEL_deleteMapElement(MapElement *element);

void LEVEL_deleteMap(Map_STRUCT *map);

void LEVEL_deleteDoors(Door_STRUCT *door);

void LEVEL_deleteCoins(Coin_STRUCT *coin );

void LEVEL_deleteKeys(Key_STRUCT *key);

void LEVEL_deleteEnemies(Enemy_STRUCT *enemy);

void LEVEL_deleteWalls(Wall *wall);

void LEVEL_deleteLevel(Level *level);

void LEVEL_deleteLegend(Legend_STRUCT *legend);

void LEVEL_deleteMapElementScreens(MapElementScreen *mapElementsScreens, int elementScreensCount);

MapElementScreen LEVEL_createMapElementsScreen(ItemType itemtype, System *system_data);

SDL_Surface* LEVEL_findSurfaceByItemType(ItemType itemtype, MapElementScreen *elementScreens, int elementScreensCount);

MapElement LEVEL_generateMapElement(SDL_Rect rect, SDL_Renderer *renderer, ItemType itemtype, bool isHighlighted, MapElementScreen *elementScreens, int elementScreensCount);

TEXT LEVEL_generateLegendText(SDL_Renderer *renderer, TEXT *legendText, char* text, int ordinal);

MapElement LEVEL_generateMapElementLeftToText(TEXT *text, SDL_Renderer *renderer, ItemType itemtype, MapElementScreen *elementScreens, int elementScreensCount);

Legend* LEVEL_generateLegends(SDL_Renderer *renderer, int *legendsCount, MapElementScreen *elementScreens, int elementScreensCount);

MapElement** LEVEL_generateMap(int *mapSizeX, int *mapSizeY, SDL_Renderer *renderer, MapElementScreen *elementScreens, int elementScreensCount, int posX, int posY);

void LEVEL_highlightMapElement(MapElement *element, SDL_Renderer *renderer, MapElementScreen *elementScreens, int elementScreensCount);

void LEVEL_unHighlightMapElement(MapElement *element, SDL_Renderer *renderer, MapElementScreen *elementScreens, int elementScreensCount);

void LEVEL_changeHighlight(Map_STRUCT *map, Legend_STRUCT *legend, SDL_Renderer *renderer, MapElementScreen *elementScreens, int elementScreensCount, int mouseX, int mouseY);

void LEVEL_setOtherElementToMap(MapElement *element, SDL_Renderer *renderer, ItemType itemType, MapElementScreen *elementScreens, int elementScreensCount);

void LEVEL_fileGeneratedSplashScreen(System *system_data);

void LEVEL_CantCreateInfo(System *system_data);

void LEVEL_processClickEvent(Map_STRUCT *map, Legend_STRUCT *legend, Button *createButton, Button *backButton, System *system_data, int mouseX, int mouseY);

void LEVEL_processEvent(System *system_data, Map_STRUCT *map, Legend_STRUCT *legend, Button *createButton, Button *backButton);

Button LEVEL_generateButton(SDL_Renderer *renderer, ButtonType buttonType, SDL_Rect rect);

void LEVEL_updateLevelNumber(System *system_data, Level *level, SDL_Texture** levelTextTexture);

void LEVEL_generateMapTexture(System *system_data, Map_STRUCT *map, SDL_Texture** texture);

bool LEVEL_getNextLevel(int *currentLevel, char filename[8]);

void LEVEL_renderLevelItems(Level *level, System *system_data);

void LEVEL_deleteCoinAtRect(Coin_STRUCT** head, SDL_Rect target);

void LEVEL_deleteKeyAtRect(Key_STRUCT** head, SDL_Rect target);


#endif //LEVEL_H

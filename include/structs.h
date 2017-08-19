#ifndef _STRUCTS_H
#define _STRUCTS_H

#define NAME_BUFFER_SIZE 101
#define MAP_SIZE_X 35
#define MAP_SIZE_Y 30
#define BOX_SIZE 17

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "enums.h"


typedef struct AnimationSurfaces AnimationSurfaces;
struct AnimationSurfaces{
  SDL_Surface* surface;
  AnimationSurfaces* next;
};

typedef struct {
  AnimationSurfaces* animationSurfaces;
}Animation_STUCT;

typedef struct{
    char* text;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;
    bool highlighted;
} TEXT;


typedef struct{
    TEXT* texts;
    int textsCount;
} TEXT_STRUCT;


typedef struct {
    ItemType itemType;
    SDL_Surface* surface;
} MapElementScreen;


typedef struct {
    MapElementScreen elementScreen;
    SDL_Texture* texture;
    SDL_Rect rect;
    bool isHighlighted;
    bool isActive;
} MapElement;


typedef struct {
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;
} Button;


typedef struct {
    MapElement **mapElements;
    int mapSizeX;
    int mapSizeY;
    int posX;
    int posY;
} Map_STRUCT;


typedef struct {
    TEXT text;
    MapElement element;
} Legend;


typedef struct {
    Legend* legends;
    int legendsCount;
    int activelegendIndex;
    int playerPosX, playerPosY;
    int playerDestX, playerDestY;
} Legend_STRUCT;



typedef struct Wall Wall;
struct Wall{
    SDL_Rect rect;
    Wall *next;
};


typedef struct {
    SDL_Surface surface;
    SDL_Texture* texture;
    SDL_Rect rect;
} Coin;


typedef struct Coin_STRUCT Coin_STRUCT;
struct Coin_STRUCT{
    Coin coin;
    Coin_STRUCT *next;
};


typedef struct {
    SDL_Surface surface;
    SDL_Texture* openTexture;
    SDL_Texture* closedTexture;
    SDL_Rect rect;
    bool isClosed;
} Door;


typedef struct Door_STRUCT Door_STRUCT;
struct Door_STRUCT{
    Door door;
    Door_STRUCT *next;
};


typedef struct {
    SDL_Surface surface;
    SDL_Texture* texture;
    SDL_Rect rect;
} Key;


typedef struct Key_STRUCT Key_STRUCT;
struct Key_STRUCT{
    Key key;
    Key_STRUCT *next;
};


typedef struct {
    bool isAlive;
    int keyCount;
    int score;
    int speed;
    Direction direction;
    Animation_STUCT* animationStruct;
    SDL_Texture* texture;
    SDL_Rect rect;
} Player;


typedef struct {
    Animation_STUCT* animationStruct;
    SDL_Texture* texture;
    SDL_Rect rect;
    int speed;
    Direction direction;
} Enemy;


typedef struct Enemy_STRUCT Enemy_STRUCT;
struct Enemy_STRUCT{
    Enemy enemy;
    Enemy_STRUCT *next;
};


typedef struct {
    Map_STRUCT map;
    int order;
    SDL_Rect endRect;
    Wall *walls;
    Coin_STRUCT *coins;
    Door_STRUCT *doors;
    Key_STRUCT *keys;
    Enemy_STRUCT *enemies;
} Level;


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameState gameState;
    TTF_Font* font;
    MapElementScreen *mapElementsScreens;
    int MapElementScreenCount;
} System;

#endif // _STRUCTS_H

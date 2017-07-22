#ifndef _ENUMS_H
#define _ENUMS_H


typedef enum {
    MENU,
    END,
    GAME,
    LEVEL,
    CREATE_LEVEL
}GameState;


typedef enum {
    LEFT,
    RIGHT_DOWN,
    UP,
    LEFT_DOWN,
    RIGHT,
    LEFT_UP,
    DOWN,
    RIGHT_UP,
    STOP
} Direction;


typedef enum {
    IT_WALL = 'W',
    IT_ENEMY = 'E',
    IT_DOOR = 'D',
    IT_O_DOOR = 'O',
    IT_COIN = 'C',
    IT_KEY = 'K',
    IT_EMPTY = '0',
    IT_PPOS = 'P',
    IT_PFIN = 'F',
    //IT_H_WALL = IT_WALL + 'H'
    IT_H_WALL = 159,
    IT_H_ENEMY = 141,
    IT_H_DOOR = 140,
    IT_H_COIN = 139,
    IT_H_KEY = 147,
    IT_H_EMPTY = 120,
    IT_H_PPOS = 152,
    IT_H_PFIN = 142,
} ItemType;


typedef enum
{
    B_CREATE, 
    B_BACK
} ButtonType;

#endif //_ENUMS_H

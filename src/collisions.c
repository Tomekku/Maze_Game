#include "../include/collisions.h"

bool isOverRect(SDL_Rect rect, int coordX, int coordY)
{
    if((coordX >= rect.x && coordX <= rect.x+rect.w) && (coordY >= rect.y && coordY <= rect.y+rect.h))
        return true;
    return false;
}

bool isEqualRect(SDL_Rect rect1, SDL_Rect rect2)
{
    if(rect1.x == rect2.x && rect1.y == rect2.y && rect1.w == rect2.w && rect1.h == rect2.h)
        return true;
    return false;
}

bool isCollision(SDL_Rect rect1, SDL_Rect rect2)
{
    rect1.x += 4;
    rect1.y += 8;
    rect1.w -= 8;
    rect1.h -= 8;
    if(isOverRect(rect2, rect1.x, rect1.y) || isOverRect(rect2, rect1.x + rect1.w, rect1.y) || 
        isOverRect(rect2, rect1.x, rect1.y + rect1.h) || isOverRect(rect2, rect1.x + rect1.w, rect1.y + rect1.h))
        return true;
    return false;
}

bool isCollideWithWalls(SDL_Rect objectRect, Wall* walls)
{
    Wall *tmp = walls;
    while(tmp)
    {
        if(isCollision(objectRect, tmp->rect))
            return true;
        tmp = (Wall*)tmp->next;
    }
    return false;
}

bool isCollideWithEnemies(SDL_Rect objectRect, Enemy_STRUCT *enemies)
{
    Enemy_STRUCT *tmp = enemies;
    while(tmp)
    {
        if(isCollision(objectRect, tmp->enemy.rect))
            return true;
        tmp = (Enemy_STRUCT*)tmp->next;
    }
    return false;
}

bool isCollideWithCoins(SDL_Rect objectRect, Coin_STRUCT *coins)
{
    Coin_STRUCT *tmp = coins;
    while(tmp)
    {
        if(isCollision(objectRect, tmp->coin.rect))
            return true;
        tmp = (Coin_STRUCT*)tmp->next;
    }
    return false;
}

bool isCollideWithKeys(SDL_Rect objectRect, Key_STRUCT *keys)
{
    Key_STRUCT *tmp = keys;
    while(tmp)
    {
        if(isCollision(objectRect, tmp->key.rect))
            return true;
        tmp = tmp->next;
    }
    return false;
}

bool isCollideWithDoors(SDL_Rect objectRect, Door_STRUCT *doors)
{
    Door_STRUCT *tmp = doors;
    while(tmp)
    {
        if(tmp->door.isClosed && isCollision(objectRect, tmp->door.rect))
            return true;
        tmp = tmp->next;
    }
    return false;
}

bool isPlayerCollideWithDoors(Player *player, SDL_Rect objectRect, Door_STRUCT *doors)
{
    Door_STRUCT *tmp = doors;
    while(tmp)
    {
        if(isCollision(objectRect, tmp->door.rect))
        {
            if(tmp->door.isClosed)
            {
                if(player->keyCount < 1)
                    return true;
                else
                {
                    player->keyCount--;
                    tmp->door.isClosed = false;
                }
            }
        }
        tmp = tmp->next;
    }
    return false;
}

bool isOutsideMap(SDL_Rect objectRect, Level *level)
{
    if(level->map.mapElements != NULL)
    {
        int mapSizeX = level->map.mapSizeX-1, mapSizeY = level->map.mapSizeY-1;
        int topBorder = level->map.mapElements[0][0].rect.x;
        int bottomBorder = level->map.mapElements[mapSizeX][mapSizeY].rect.x + level->map.mapElements[mapSizeX][mapSizeY].rect.h;
        int leftBorder = level->map.mapElements[0][0].rect.y;
        int rightBorder = level->map.mapElements[mapSizeX][mapSizeY].rect.y + level->map.mapElements[mapSizeX][mapSizeY].rect.w;

        if(objectRect.x < topBorder || objectRect.x + objectRect.h > bottomBorder || objectRect.y < leftBorder || objectRect.y + objectRect.w > rightBorder)
            return true;
    }
    else
        printf("ERROR: There is no map\n");
    return false;
}

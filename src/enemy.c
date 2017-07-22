#include "../include/enemy.h"


void ENEMY_updateEnemy(Enemy *enemy, Level *level)
{
    SDL_Rect tmp_rect = enemy->rect;
    switch (enemy->direction) {
        case LEFT:
            tmp_rect.x -= enemy->speed;
            break;
        case LEFT_UP:
            tmp_rect.y -= enemy->speed;
            tmp_rect.x -= enemy->speed;
            break;
        case LEFT_DOWN:
            tmp_rect.y += enemy->speed;
            tmp_rect.x -= enemy->speed;
            break;
        case RIGHT:
            tmp_rect.x += enemy->speed;
            break;
        case RIGHT_UP:
            tmp_rect.y -= enemy->speed;
            tmp_rect.x += enemy->speed;
            break;
        case RIGHT_DOWN:
            tmp_rect.y += enemy->speed;
            tmp_rect.x += enemy->speed;
            break;
        case UP:
            tmp_rect.y -= enemy->speed;
            break;
        case DOWN:
            tmp_rect.y += enemy->speed;
            break;
        default:
            break;
    }
    if(!isCollideWithWalls(tmp_rect, level->walls) && !isCollideWithDoors(tmp_rect, level->doors) && !isOutsideMap(tmp_rect, level))
        enemy->rect = tmp_rect;
    else
    {
        if(enemy->direction == STOP-1)
            enemy->direction = LEFT;
        else
            enemy->direction++;
    }
}

void ENEMY_updateEnemies(Level *level)
{
    Enemy_STRUCT *tmp = level->enemies;
    while(tmp)
    {
        ENEMY_updateEnemy(&tmp->enemy, level);
        tmp = (Enemy_STRUCT*)tmp->next;
    }
}
#include "../include/enemy.h"


AnimationSurfaces* ENEMY_addAnimationSurfaces(Direction direction)
{
  AnimationSurfaces* animationSurfaces = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
  switch(direction)
  {
    case LEFT:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_lf1.png");
      tmp->surface = IMG_Load("../res/spd1_lf2.png");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case RIGHT_DOWN:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_rt1.png");
      tmp->surface = IMG_Load("../res/spd1_rt2.png");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case UP:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_bk1.png");
      tmp->surface = IMG_Load("../res/spd1_bk2.png");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case LEFT_DOWN:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_lf1.png");
      tmp->surface = IMG_Load("../res/spd1_lf2.png");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case RIGHT:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_rt1.png");
      tmp->surface = IMG_Load("../res/spd1_rt2.png");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case LEFT_UP:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_lf1.png");
      tmp->surface = IMG_Load("../res/spd1_lf2.png");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case DOWN:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_fr1.png");
      tmp->surface = IMG_Load("../res/spd1_fr2.png");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case RIGHT_UP:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_rt1.png");
      tmp->surface = IMG_Load("../res/spd1_rt2.png");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    default:
    {
      free(animationSurfaces);
      animationSurfaces = NULL;
    }break;
  }

  return animationSurfaces;
}


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

void ENEMY_animateEnemy(System *system_data, Enemy* enemy)
{
  enemy->texture = SDL_CreateTextureFromSurface(system_data->renderer, enemy->animationStruct[enemy->direction].animationSurfaces->surface);
  enemy->animationStruct[enemy->direction].animationSurfaces = enemy->animationStruct[enemy->direction].animationSurfaces->next;
}

void ENEMY_updateEnemies(System *system_data, Level *level)
{
    Enemy_STRUCT *tmp = level->enemies;
    while(tmp)
    {
        ENEMY_updateEnemy(&tmp->enemy, level);
        animate(system_data, 'E', 1, &tmp->enemy);
        tmp = (Enemy_STRUCT*)tmp->next;
    }
}

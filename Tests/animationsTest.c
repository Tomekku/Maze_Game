#include "../include/structs.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/level.h"
#include "../include/mainMenu.h"
#include "../include/file.h"
#include "../include/gameManager.h"
#include "../include/animations.h"
#include <stdarg.h>



/*
*
* TODO: sprawdź gdzie leci błąd + dodaj usuwanie nowozaalokowanej pamięci
*
*/



AnimationSurfaces* ENEMY_addAnimationSurfaces(Direction direction)
{
  AnimationSurfaces* animationSurfaces = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
  switch(direction)
  {
    case LEFT:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_lf1.gif");
      tmp->surface = IMG_Load("../res/spd1_lf2.gif");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case RIGHT_DOWN:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_rt1.gif");
      tmp->surface = IMG_Load("../res/spd1_rt2.gif");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case UP:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_bk1.gif");
      tmp->surface = IMG_Load("../res/spd1_bk2.gif");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case LEFT_DOWN:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_lf1.gif");
      tmp->surface = IMG_Load("../res/spd1_lf2.gif");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case RIGHT:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_rt1.gif");
      tmp->surface = IMG_Load("../res/spd1_rt2.gif");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case LEFT_UP:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_lf1.gif");
      tmp->surface = IMG_Load("../res/spd1_lf2.gif");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case DOWN:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_fr1.gif");
      tmp->surface = IMG_Load("../res/spd1_fr2.gif");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case RIGHT_UP:
    {
      AnimationSurfaces* tmp = (AnimationSurfaces*)malloc(sizeof(AnimationSurfaces*));
      animationSurfaces->surface = IMG_Load("../res/spd1_rt1.gif");
      tmp->surface = IMG_Load("../res/spd1_rt2.gif");
      tmp->next = (AnimationSurfaces*)animationSurfaces;
      animationSurfaces->next = (AnimationSurfaces*)tmp;
    }break;
    case STOP:
    {
      animationSurfaces->surface = IMG_Load("../res/spd1_st1.gif");
      animationSurfaces->next = (AnimationSurfaces*)animationSurfaces;
    }break;
    default:
    {
      free(animationSurfaces);
      animationSurfaces = NULL;
    }break;
  }

  return animationSurfaces;
}



// void ENEMY_animateEnemy(System *system_data, Enemy* enemy)
// {
//   enemy->texture = SDL_CreateTextureFromSurface(system_data->renderer, enemy->animationStruct[enemy->direction].animationSurfaces.surface);
//   enemy->animationStruct[enemy->direction].animationSurfaces = enemy->animationStruct[enemy->direction].animationSurfaces->next;
// }





int main(int argc, char const *argv[])
{
  System system_data;
  Player player;
  Level level;
  init(&system_data, &level, &player);
  initAnimate(&system_data, &player.animationStruct, 'P');
  SDL_Rect rect = {0,0,100,100};
  while(system_data.gameState != END)
  {
    animate(&system_data, 'P', 1, &player);
    PLAYER_processEvents(&system_data, &player);
    SDL_RenderClear(system_data.renderer);
    SDL_RenderCopy(system_data.renderer, player.texture, NULL, &rect);
    SDL_RenderPresent(system_data.renderer);
    SDL_Delay(50);
  }
  PLAYER_deletePlayer(&player);
  cleanUp(&system_data);
  return 0;
}

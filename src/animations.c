#include "../include/animations.h"


void deleteAnimations(Animation_STUCT *animationStruct)
{
  int directionsCount = STOP+1;
  for(int i=0; i<directionsCount; i++)
  {
    AnimationSurfaces *node = animationStruct[i].animationSurfaces;
    while(node)
    {
      if(node == node->next)
      {
        SDL_FreeSurface(node->surface);
        free(node);
        node = NULL;
      }
      else
      {
        AnimationSurfaces *tmp = node->next->next;
        SDL_FreeSurface(node->next->surface);
        free(node->next);
        node->next = tmp;
      }
    }
  }
  free(animationStruct);
}


void initAnimate(System *system_data, Animation_STUCT **animationStruct, char format)
{
  int directionsCount = STOP+1;
  *animationStruct = (Animation_STUCT*)malloc(directionsCount*sizeof(Animation_STUCT*));
  for(int i=LEFT; i<directionsCount; i++)
  {
    if(format == 'P')
      (*animationStruct)[i].animationSurfaces = (AnimationSurfaces*) PLAYER_addAnimationSurfaces(i);
    else if(format == 'E')
      (*animationStruct)[i].animationSurfaces = (AnimationSurfaces*) ENEMY_addAnimationSurfaces(i);
  }
}

void animate(System *system_data, char format, int argNum, ...)
{
  va_list valist;
  va_start(valist, argNum);
  if(format == 'P')
  {
    Player* player = va_arg(valist, Player*);
    va_end(valist);
    PLAYER_animatePlayer(system_data, player);
  }
  if(format == 'E')
  {
    Enemy* enemy = va_arg(valist, Enemy*);
    va_end(valist);
    ENEMY_animateEnemy(system_data, enemy);
  }

}

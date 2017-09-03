#ifndef  _ENEMY_H
#define _ENEMY_H

#include "structs.h"
#include "collisions.h"
#include "animations.h"

void ENEMY_updateEnemy(Enemy *enemy, Level *level);

void ENEMY_updateEnemies(System *system_data, Level *level);

AnimationSurfaces* ENEMY_addAnimationSurfaces(Direction direction);

void ENEMY_animateEnemy(System *system_data, Enemy* enemy);

void ENEMY_placeEnemy(System *system_data, Level *level);

#endif

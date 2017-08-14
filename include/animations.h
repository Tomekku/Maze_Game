#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "structs.h"
#include "player.h"
#include "enemy.h"

void deleteAnimations(Animation_STUCT *animationStruct);

void initAnimate(System *system_data, Animation_STUCT **animationStruct, char format);

void animate(System *system_data, char format, int argNum, ...);

#endif //ANIMATIONS_H

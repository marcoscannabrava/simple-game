#ifndef PHYSICS_H
#define PHYSICS_H

#include "game.h"

#define GRAVITY_FORCE 980.0f;  // 980 pixels per second squared, divided by 3 for a slower fall

void movement(GameObject *object, const InputState *input, float delta_time);

void gravity(GameObject *object, float delta_time);

void collisions(GameObject *object, int screen_width, int screen_height);


#endif // PHYSICS_H
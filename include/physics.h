#ifndef PHYSICS_H
#define PHYSICS_H

#include "game.h"

#define GRAVITY_FORCE 980.0f;

void physics_update(GameObject *object, const InputState *input, float delta_time, int screen_width, int screen_height);

#endif // PHYSICS_H
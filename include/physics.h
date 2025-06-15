
#ifndef PHYSICS_H
#define PHYSICS_H


void movement(GameObject *object, const InputState *input, float delta_time);

void gravity(GameObject *object, float gravity, float terminal_velocity, bool apply);

void collisions(GameObject *object, int screen_width, int screen_height);


#endif // PHYSICS_H
#include "game.h"
#include "raylib.h"
#include <math.h>
#include <stdbool.h>

const float speed = 300.0f;

// Handles movement for any game object based on input
void movement(GameObject *object, const InputState *input, float delta_time) {
    if (input->up) {
        object->position.y -= speed * delta_time;
        object->direction = NORTH;
    }
    if (input->down) {
        object->position.y += speed * delta_time;
        object->direction = SOUTH;
    }
    if (input->left) {
        object->position.x -= speed * delta_time;
        object->direction = WEST;
    }
    if (input->right) {
        object->position.x += speed * delta_time;
        object->direction = EAST;
    }

    object->position.x += object->velocity.x * delta_time;
    object->position.y += object->velocity.y * delta_time;

    bool moving = input->up || input->down || input->left || input->right;
    if (moving) {
        object->frame_timer += delta_time;
        float frame_duration = 0.15f;
        int frame_count = (object->direction == NORTH) ? SPRITE_BACK_FRAME_COUNT : SPRITE_FRAME_COUNT;
        if (object->frame_timer >= frame_duration) {
            object->frame_timer = 0.0f;
            object->current_frame = (object->current_frame + 1) % frame_count;
        }
    } else {
        object->current_frame = 0;
        object->frame_timer = 0.0f;
    }
}

// Applies gravity to any game object
void gravity(GameObject *object, float gravity, float terminal_velocity, bool apply) {
    if (apply) {
        object->velocity.y += gravity;
        if (object->velocity.y > terminal_velocity) {
            object->velocity.y = terminal_velocity;
        }
    } else {
        object->velocity.y = 0;
    }
}

// Handles screen boundary collisions and bounce for any game object
void collisions(GameObject *object, int screen_width, int screen_height) {
    // Bottom boundary
    if (object->position.y + object->height > screen_height) {
        object->position.y = screen_height - object->height;
        object->velocity.y *= -object->elasticity;
        if (fabs(object->velocity.y) < 10.0f) {
            object->velocity.y = 0.0f;
        }
    }
    // Top boundary
    if (object->position.y < 0) {
        object->position.y = 0;
        if (object->velocity.y < 0) object->velocity.y = 0;
    }
    // Left boundary
    if (object->position.x < 0) {
        object->position.x = 0;
        if (object->velocity.x < 0) object->velocity.x = 0;
    }
    // Right boundary
    if (object->position.x + object->width > screen_width) {
        object->position.x = screen_width - object->width;
        if (object->velocity.x > 0) object->velocity.x = 0;
    }
}

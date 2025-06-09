#include "input.h"
#include "renderer.h" // Input handling for the game engine from raylib

void input_poll(InputState *input) {
    input->up = IsKeyDown(KEY_UP);
    input->down = IsKeyDown(KEY_DOWN);
    input->left = IsKeyDown(KEY_LEFT);
    input->right = IsKeyDown(KEY_RIGHT);
}

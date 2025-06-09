#include "renderer.h"

void renderer_init(int width, int height, const char* title) {
    InitWindow(width, height, title);
}

void renderer_begin_drawing(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void renderer_draw_player(const Texture2D* sprite, Vector2 position) {
    DrawTextureV(*sprite, position, WHITE);
}

void renderer_end_drawing(void) {
    EndDrawing();
}

void renderer_shutdown(void) {
    CloseWindow();
}

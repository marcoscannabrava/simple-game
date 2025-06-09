#include "renderer.h"

void renderer_init(int width, int height, const char* title) {
    InitWindow(width, height, title);
}

void renderer_begin_drawing(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void renderer_draw_player(const char* emoji, Vector2 position, int fontSize) {
    DrawText(emoji, (int)position.x, (int)position.y, fontSize, BLACK);
}

void renderer_end_drawing(void) {
    EndDrawing();
}

void renderer_shutdown(void) {
    CloseWindow();
}

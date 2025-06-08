#include "renderer.h"
#include <raylib.h>

void renderer_init(Renderer *renderer, int width, int height, const char* title) {
    renderer->width = width;
    renderer->height = height;
    renderer->title = title;
    InitWindow(width, height, title);
}

void renderer_begin_drawing(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void renderer_draw_emoji(const char* emoji, Vector2 position, int fontSize) {
    DrawText(emoji, (int)position.x, (int)position.y, fontSize, BLACK);
}

void renderer_end_drawing(void) {
    EndDrawing();
}

void renderer_shutdown(void) {
    CloseWindow();
}

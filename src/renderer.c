#include "renderer.h"
#include <raylib.h>
#include <string.h>


static PlayerRenderer player_renderer;

PlayerSize renderer_init(int width, int height, const char* title) {
    InitWindow(width, height, title);
    player_renderer.sprite_frames[0] = LoadTexture(RESOURCES_PATH "space-invaders/si1.png");
    player_renderer.sprite_frames[1] = LoadTexture(RESOURCES_PATH "space-invaders/si2.png");
    player_renderer.sprite_frames[2] = LoadTexture(RESOURCES_PATH "space-invaders/si3.png");
    player_renderer.sprite_back_frames[0] = LoadTexture(RESOURCES_PATH "space-invaders/si1b.png");
    player_renderer.sprite_back_frames[1] = LoadTexture(RESOURCES_PATH "space-invaders/si2b.png");
    player_renderer.current_frame = 0;
    player_renderer.frame_timer = 0.0f;
    PlayerSize result = { player_renderer.sprite_frames[0].width, player_renderer.sprite_frames[0].height };
    return result;
}

void renderer_begin_drawing(void) {
    BeginDrawing();
    ClearBackground(DARKGRAY);
}

void renderer_draw_player(Vector2 position, Direction direction) {
    // Animation logic: update frame based on timer
    float frame_speed = 8.0f; // frames per second
    player_renderer.frame_timer += GetFrameTime();
    int max_frames = (direction == NORTH) ? SPRITE_BACK_FRAME_COUNT : SPRITE_FRAME_COUNT;
    if (player_renderer.frame_timer >= 1.0f / frame_speed) {
        player_renderer.current_frame = (player_renderer.current_frame + 1) % max_frames;
        player_renderer.frame_timer = 0.0f;
    }
    Texture2D sprite = (direction == NORTH)
        ? player_renderer.sprite_back_frames[player_renderer.current_frame]
        : player_renderer.sprite_frames[player_renderer.current_frame];
    DrawTextureV(sprite, position, WHITE);
}

void renderer_end_drawing(void) { EndDrawing(); }

void renderer_shutdown(void) {
    for (int i = 0; i < SPRITE_FRAME_COUNT; i++) UnloadTexture(player_renderer.sprite_frames[i]);
    for (int i = 0; i < SPRITE_BACK_FRAME_COUNT; i++) UnloadTexture(player_renderer.sprite_back_frames[i]);
    CloseWindow();
}

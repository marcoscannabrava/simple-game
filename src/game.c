#include "game.h"
#include "renderer.h"
#include "raylib.h"
#include <stdbool.h>

// Place player in the center of the screen
void game_init(GameState *game) {
    game->player.position.x = (float)GetScreenWidth() / 2.0f;
    game->player.position.y = (float)GetScreenHeight() / 2.0f;
    game->player.sprite_frames[0] = LoadTexture(RESOURCES_PATH "space-invaders/si1.png");
    game->player.sprite_frames[1] = LoadTexture(RESOURCES_PATH "space-invaders/si2.png");
    game->player.sprite_frames[2] = LoadTexture(RESOURCES_PATH "space-invaders/si3.png");
    game->player.sprite_back_frames[0] = LoadTexture(RESOURCES_PATH "space-invaders/si1b.png");
    game->player.sprite_back_frames[1] = LoadTexture(RESOURCES_PATH "space-invaders/si2b.png");
    game->player.current_frame = 0;
    game->player.frame_timer = 0.0f;
    game->player.direction = SOUTH;
}

void game_update(GameState *game, const InputState *input) {
    const float speed = 300.0f; // Pixels per second
    float delta_time = GetFrameTime(); // Time since last frame

    if (input->up) {
        game->player.position.y -= speed * delta_time;
        game->player.direction = NORTH;
    }
    if (input->down) {
        game->player.position.y += speed * delta_time;
        game->player.direction = SOUTH;
    }
    if (input->left) {
        game->player.position.x -= speed * delta_time;
        game->player.direction = WEST;
    }
    if (input->right) {
        game->player.position.x += speed * delta_time;
        game->player.direction = EAST;
    }

    bool moving = input->up || input->down || input->left || input->right;
    if (moving) {
        game->player.frame_timer += delta_time;
        float frame_duration = 0.15f;
        int frame_count = (game->player.direction == NORTH) ? SPRITE_BACK_FRAME_COUNT : SPRITE_FRAME_COUNT;
        if (game->player.frame_timer >= frame_duration) {
            game->player.frame_timer = 0.0f;
            game->player.current_frame = (game->player.current_frame + 1) % frame_count;
        }
    } else {
        game->player.current_frame = 0;
        game->player.frame_timer = 0.0f;
    }
}

void game_draw(const GameState *game) {
    int frame = game->player.current_frame;
    Texture2D sprite;
    if (game->player.direction == NORTH) {
        sprite = game->player.sprite_back_frames[frame % SPRITE_BACK_FRAME_COUNT];
    } else {
        sprite = game->player.sprite_frames[frame % SPRITE_FRAME_COUNT];
    }
    renderer_draw_player(&sprite, game->player.position);
}

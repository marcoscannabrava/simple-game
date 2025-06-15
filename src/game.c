#include "game.h"

#include <math.h>
#include <stdbool.h>

#include "physics.h"
#include "raylib.h"
#include "renderer.h"

// Place player in the center of the screen
void game_init(GameState *game) {
    game->player.position.x = (float)GetScreenWidth() / 2.0f;
    game->player.position.y = (float)GetScreenHeight() / 2.0f;
    // REFACTOR: could be in renderer init?
    game->player.sprite_frames[0] = LoadTexture(RESOURCES_PATH "space-invaders/si1.png");
    game->player.sprite_frames[1] = LoadTexture(RESOURCES_PATH "space-invaders/si2.png");
    game->player.sprite_frames[2] = LoadTexture(RESOURCES_PATH "space-invaders/si3.png");
    game->player.sprite_back_frames[0] = LoadTexture(RESOURCES_PATH "space-invaders/si1b.png");
    game->player.sprite_back_frames[1] = LoadTexture(RESOURCES_PATH "space-invaders/si2b.png");
    game->player.width = game->player.sprite_frames[0].width;
    game->player.height = game->player.sprite_frames[0].height;
    game->player.current_frame = 0;
    game->player.frame_timer = 0.0f;
    game->player.direction = SOUTH;
    game->player.velocity = (Vector2){0.0f, 0.0f};
    game->player.elasticity = 0.5f;
}

void game_update(GameState *game, const InputState *input) {
    float delta_time = GetFrameTime();

    movement(&game->player, input, delta_time);
    collisions(&game->player, GetScreenWidth(), GetScreenHeight());
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

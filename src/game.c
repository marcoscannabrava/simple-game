#include "game.h"

#include <math.h>
#include <stdbool.h>

#include "physics.h"
#include "raylib.h"
#include "renderer.h"

// Place player in the center of the screen
void game_init(GameState *game, PlayerSize player_size) {
    game->player.position.x = (float)GetScreenWidth() / 2.0f;
    game->player.position.y = (float)GetScreenHeight() / 2.0f;
    game->player.width = player_size.width;
    game->player.height = player_size.height;
    game->player.current_frame = 0;
    game->player.frame_timer = 0.0f;
    game->player.direction = SOUTH;
    game->player.velocity = (Vector2){0.0f, 0.0f};
    game->player.elasticity = 0.5f;
}

void game_update(GameState *game, const InputState *input) {
    float delta_time = GetFrameTime();
    physics_update(&game->player, input, delta_time, GetScreenWidth(), GetScreenHeight());
}

void game_draw(const GameState *game) {
    renderer_draw_player(game->player.position, game->player.direction);
}

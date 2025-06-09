#include "game.h"
#include "renderer.h"

void game_init(GameState *game) {
    // Place player in the center of the screen
    game->player_position.x = (float)GetScreenWidth() / 2.0f;
    game->player_position.y = (float)GetScreenHeight() / 2.0f;
    game->player_emoji = "O";
}

void game_update(GameState *game, const InputState *input) {
    const float speed = 300.0f; // Pixels per second
    float delta_time = GetFrameTime(); // Time since last frame

    if (input->up) {
        game->player_position.y -= speed * delta_time;
    }
    if (input->down) {
        game->player_position.y += speed * delta_time;
    }
    if (input->left) {
        game->player_position.x -= speed * delta_time;
    }
    if (input->right) {
        game->player_position.x += speed * delta_time;
    }
}

void game_draw(const GameState *game) {
    const int font_size = 40;
    
    int text_width = MeasureText(game->player_emoji, font_size);
    
    Vector2 centered_position = {
        game->player_position.x - (float)text_width / 2.0f,
        game->player_position.y - (float)font_size / 2.0f
    };

    renderer_draw_emoji(game->player_emoji, centered_position, font_size);
}

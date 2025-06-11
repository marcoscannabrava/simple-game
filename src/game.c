#include "game.h"
#include "renderer.h"
#include "raylib.h"
#include <math.h>
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
    game->player.velocity = (Vector2){0.0f, 0.0f};
    game->player.elasticity = 0.5f;
}

void game_update(GameState *game, const InputState *input) {
    const float speed = 300.0f; // Pixels per second
    float delta_time = GetFrameTime(); // Time since last frame

   // Physics constants
   const float gravity = 980.0f; // Pixels per second per second
   const float terminal_velocity = 400.0f; // Pixels per second

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

   // Apply gravity if no input is given
   if (!(input->up || input->down || input->left || input->right)) {
       game->player.velocity.y += gravity * delta_time;
       if (game->player.velocity.y > terminal_velocity) {
           game->player.velocity.y = terminal_velocity;
       }
   } else {
       // Reset vertical velocity if player is actively moving with arrows
       game->player.velocity.y = 0;
   }

   // Update position based on velocity
   game->player.position.x += game->player.velocity.x * delta_time;
   game->player.position.y += game->player.velocity.y * delta_time;

   // Screen boundaries and bounce
   // Bottom boundary
   if (game->player.position.y + game->player.sprite_frames[0].height > GetScreenHeight()) {
       game->player.position.y = GetScreenHeight() - game->player.sprite_frames[0].height;
       game->player.velocity.y *= -game->player.elasticity;
       // If velocity is very small after bounce, set to 0 to prevent jittering
       if (fabs(game->player.velocity.y) < 10.0f) { 
           game->player.velocity.y = 0.0f;
       }
   }
   // Top boundary
   if (game->player.position.y < 0) {
       game->player.position.y = 0;
       if (game->player.velocity.y < 0) game->player.velocity.y = 0; // Stop upward movement
   }
   // Left boundary
   if (game->player.position.x < 0) {
       game->player.position.x = 0;
       if (game->player.velocity.x < 0) game->player.velocity.x = 0;
   }
   // Right boundary
   if (game->player.position.x + game->player.sprite_frames[0].width > GetScreenWidth()) {
       game->player.position.x = GetScreenWidth() - game->player.sprite_frames[0].width;
       if (game->player.velocity.x > 0) game->player.velocity.x = 0;
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

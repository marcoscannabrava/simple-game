#ifndef GAME_H
#define GAME_H

#include "input.h"   // Game logic needs to know about input state
#include "renderer.h" // Game logic needs to issue draw commands


#define SPRITE_FRAME_COUNT 3
#define SPRITE_BACK_FRAME_COUNT 2

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef struct {
    Vector2 position;
    Direction direction;
    Texture2D sprite_frames[SPRITE_FRAME_COUNT];
    Texture2D sprite_back_frames[SPRITE_BACK_FRAME_COUNT];
    int current_frame;
    float frame_timer;
} Player;

// GameState holds all data related to the game world.
typedef struct {
    Player player;
} GameState;

// Initializes the game state.
void game_init(GameState *game);

// Updates the game state based on player input.
void game_update(GameState *game, const InputState *input);

// Draws the current game state to the screen.
void game_draw(const GameState *game);

#endif // GAME_H

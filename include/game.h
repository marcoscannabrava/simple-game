#ifndef GAME_H
#define GAME_H

#include "input.h"   // Game logic needs to know about input state
#include "renderer.h" // Game logic needs to issue draw commands

// GameState holds all data related to the game world.
typedef struct GameState {
    Vector2 player_position;
    const char* player_emoji;
} GameState;

// Initializes the game state.
void game_init(GameState *game);

// Updates the game state based on player input.
void game_update(GameState *game, const InputState *input);

// Draws the current game state to the screen.
void game_draw(const GameState *game);

#endif // GAME_H

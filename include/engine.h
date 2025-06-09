#ifndef ENGINE_H
#define ENGINE_H

#include "input.h"
#include "game.h"

// The Engine struct is the central context, holding all subsystems.
typedef struct Engine {
    InputState input;
    GameState game;
} Engine;

// Initializes all engine subsystems.
void engine_init(Engine *engine);

// Runs the main game loop (for desktop platforms).
void engine_run(Engine *engine);

// Performs a single frame update and draw.
void engine_update_and_draw_frame(Engine *engine);

// Shuts down all engine subsystems.
void engine_shutdown(Engine *engine);

#endif // ENGINE_H

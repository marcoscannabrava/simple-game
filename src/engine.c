#include "engine.h"
#include <raylib.h>

// Define screen dimensions and title
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "Emoji Game"

void engine_init(Engine *engine) {
    renderer_init(&engine->renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    game_init(&engine->game);
    SetTargetFPS(60);
}

void engine_update_and_draw_frame(Engine *engine) {
    // 1. Poll Input
    input_poll(&engine->input);

    // 2. Update Game State
    game_update(&engine->game, &engine->input);

    // 3. Draw Frame
    renderer_begin_drawing();
    game_draw(&engine->game, &engine->renderer);
    renderer_end_drawing();
}

void engine_run(Engine *engine) {
    while (!WindowShouldClose()) {
        engine_update_and_draw_frame(engine);
    }
}

void engine_shutdown(Engine *engine) {
    renderer_shutdown();
}

#include "engine.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

// Global engine instance for the web platform's main loop
static Engine engine;

// Update and draw one frame, intended for the web loop.
// Note: emscripten_set_main_loop_arg expects a function pointer
// that takes a void* argument.
void update_and_draw_web(void *arg) {
    Engine *engine_ptr = (Engine*)arg;
    engine_update_and_draw_frame(engine_ptr);
}

int main(void) {
    engine_init(&engine);

#if defined(PLATFORM_WEB)
    // For web, we set a callback function that will be called each frame.
    emscripten_set_main_loop_arg(update_and_draw_web, &engine, 0, 1);
#else
    // For desktop, we run a traditional game loop.
    engine_run(&engine);
#endif

    engine_shutdown(&engine);

    return 0;
}

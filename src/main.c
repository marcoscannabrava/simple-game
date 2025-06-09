#include "engine.h"

// Global engine instance for the web platform's main loop
static Engine engine;

int main(void) {
    engine_init(&engine);
    engine_run(&engine);
    engine_shutdown(&engine);
    return 0;
}

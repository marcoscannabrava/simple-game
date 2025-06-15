#ifndef RENDERER_H
#define RENDERER_H

#include <raylib.h>

#define SPRITE_FRAME_COUNT 3
#define SPRITE_BACK_FRAME_COUNT 2

// TODO: this is dependent on the placement of the binary and does not work in the Web, how to fix this?
#define RESOURCES_PATH "assets/"

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef struct {
    int width;
    int height;
} PlayerSize;

// Holds all textures and animation state for the player
typedef struct {
    Texture2D sprite_frames[SPRITE_FRAME_COUNT];
    Texture2D sprite_back_frames[SPRITE_BACK_FRAME_COUNT];
    int current_frame;
    float frame_timer;
} PlayerRenderer;

// Initializes the window, rendering context, and loads all player sprites.
PlayerSize renderer_init(int width, int height, const char* title);

// Begins a drawing frame. Clears the background.
void renderer_begin_drawing(void);

// Draws player at a given position and with animation state.
void renderer_draw_player(Vector2 position, Direction direction);

// Ends a drawing frame. Swaps buffers.
void renderer_end_drawing(void);

// Shuts down the rendering context and closes the window.
void renderer_shutdown(void);

#endif // RENDERER_H

#ifndef RENDERER_H
#define RENDERER_H

#include <raylib.h>

// Initializes the window and rendering context.
void renderer_init(int width, int height, const char* title);

// Begins a drawing frame. Clears the background.
void renderer_begin_drawing(void);

// Draws an emoji (as text) at a given position.
void renderer_draw_emoji(const char* emoji, Vector2 position, int fontSize);

// Ends a drawing frame. Swaps buffers.
void renderer_end_drawing(void);

// Shuts down the rendering context and closes the window.
void renderer_shutdown(void);

#endif // RENDERER_H

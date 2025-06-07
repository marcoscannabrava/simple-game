#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// InputState captures the state of relevant keys for a single frame.
typedef struct InputState {
    bool up;
    bool down;
    bool left;
    bool right;
} InputState;

// Polls hardware and updates the input state struct.
void input_poll(InputState *input);

#endif // INPUT_H

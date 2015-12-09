/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHBOARD_TYPEDEFS_H_
#define SRC_SWITCHBOARD_TYPEDEFS_H_

#include <Bounce2.h>

#include "../globals.h"

namespace switch_board {

typedef enum event_t {
    UP, DOWN,
} event_t;

typedef struct protokey_event_t {
    event_t event;
    switch_event::SwitchEvent switch_event;
    bool is_chord;
} protokey_event_t;

} // namespace switch_board

#endif  // SRC_SWITCHBOARD_TYPEDEFS_H_

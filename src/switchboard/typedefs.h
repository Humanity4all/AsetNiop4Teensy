/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHBOARD_TYPEDEFS_H_
#define SRC_SWITCHBOARD_TYPEDEFS_H_

#include <Bounce2.h>

#include "../globals.h"
#include "../switchevent/switchevent.h"

namespace switch_board_n {

typedef enum event_t {
    UP, DOWN, RESET,
} event_t;

typedef struct protokey_event_t {
    event_t event;
    switch_event_n::SwitchEvent* switch_event;
    bool is_chord;
    protokey_event_t(event_t event, switch_event_n::SwitchEvent* switch_event, bool is_chord) :
        event(event), switch_event(switch_event), is_chord(is_chord) {}
} protokey_event_t;

} // namespace switch_board_n

#endif  // SRC_SWITCHBOARD_TYPEDEFS_H_

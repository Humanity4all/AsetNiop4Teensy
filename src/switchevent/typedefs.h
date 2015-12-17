/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHEVENT_TYPEDEFS_H_
#define SRC_SWITCHEVENT_TYPEDEFS_H_

#include "../globals.h"

namespace switch_event_n {

typedef enum switch_state_t {
    PRESSED = 1 , RELEASED = 0,
} key_state_t;

typedef enum edge_t {
    E_FALLING, E_RISING,
} event_t;

} // namespace switch_event_n

#endif  // SRC_SWITCHEVENT_TYPEDEFS_H_

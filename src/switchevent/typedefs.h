/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCH_EVENT_TYPEDEFS_H_
#define SRC_SWITCH_EVENT_TYPEDEFS_H_

#include "../globals.h"

namespace switch_event_n {

typedef enum edge_t {
    E_FALLING, E_RISING,
} event_t;

} // namespace switch_event_n

#endif  // SRC_SWITCH_EVENT_TYPEDEFS_H_

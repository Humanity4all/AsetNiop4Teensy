/*
Copyright Stichting Humanity4all 2015
*/

#ifndef SRC_PRINTSWITCHSTATE_H_
#define SRC_PRINTSWITCHSTATE_H_

#include "Arduino.h"

#include "./globals.h"
#include "./switchevent/typedefs.h"

namespace debug_n {

void print_switch_state(
    switch_event_n::switch_state_t switch_state[N_SWITCHES]);

} // namespace debug_n

#endif // SRC_PRINTSWITCHSTATE_H_

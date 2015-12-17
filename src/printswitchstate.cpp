/*
Copyright Stichting Humanity4all 2015
*/
#include "./printswitchstate.h"

namespace debug_n {

void print_switch_state(switch_event_n::switch_state_t switch_state[N_SWITCHES]) {
    char str[N_SWITCHES];
    for (int i = 0; i < N_SWITCHES; i++) {
        if (switch_state[i] == switch_event_n::switch_state_t::PRESSED) {
            str[i] = '1';
        } else {
            str[i] = '0';
        }
    }
    Serial.println(str);
}

} // namespace debug_n

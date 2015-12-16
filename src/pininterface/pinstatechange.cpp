/*
Copyright Stichting Humanity4all 2015
*/

#include "./pinstatechange.h"

namespace pin_interface_n {

PinStateChange::PinStateChange(
        int pin_number,
        switch_event_n::switch_state_t switch_state) {
    pinNumber = pin_number;
    switchState = switch_state;
}

} // namespace pin_interface_n

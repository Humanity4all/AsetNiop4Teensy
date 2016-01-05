/*
Copyright Stichting Humanity4all 2015
*/

#include "./pinstatechange.h"

namespace pin_interface_n {

PinStateChange::PinStateChange() {
    isActive = false;
}

PinStateChange::PinStateChange(
        uint8_t pin_number,
        switch_event_n::switch_state_t switch_state) {
    isActive = true;
    pinNumber = pin_number;
    switchState = switch_state;
}

PinStateChange::~PinStateChange() {
    isActive = false;
}

} // namespace pin_interface_n

/*
Copyright Stichting Humanity4all 2015
*/

#include "./pinstatechange.h"

namespace pin_interface_n {

PinStateChange::PinStateChange(int pin_number, switch_event_n::edge_t edge_) {
    pinNumber = pin_number;
    edge = edge_;
}

} // namespace pin_interface_n

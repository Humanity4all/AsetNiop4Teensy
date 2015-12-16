/*
Copyright Stichting Humanity4all 2015
*/

#ifndef SRC_PININTERFACE_PINSTATECHANGE_H_
#define SRC_PININTERFACE_PINSTATECHANGE_H_

#include "../globals.h"
#include "../switchevent/switchevent.h"

namespace pin_interface_n {

class PinStateChange{
 public:
    PinStateChange(int pin_number, switch_event_n::edge_t edge_);
    int pinNumber;
    switch_event_n::edge_t edge;
};

struct pin_state_change_compare {
    bool operator()(const PinStateChange &p1, const PinStateChange &p2) const {
        int vp1 = 0;
        int vp2 = 0;
        if (p1.edge == switch_event_n::edge_t::E_FALLING) {
            vp1 = 1;
        }
        if (p2.edge == switch_event_n::edge_t::E_FALLING) {
            vp2 = 1;
        }
        return vp1 < vp2;
    }
};

} // namespace pin_interface_n

#endif  // SRC_PININTERFACE_PINSTATECHANGE_H_

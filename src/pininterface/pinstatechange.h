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
    PinStateChange();
    PinStateChange(uint8_t pin_number, switch_event_n::switch_state_t switch_state);
    uint8_t pinNumber;
    switch_event_n::switch_state_t switchState;
    bool isActive;
    ~PinStateChange();
};

struct pin_state_change_compare {
    bool operator()(const PinStateChange* p1, const PinStateChange* p2) const {
        uint8_t vp1 = 0;
        uint8_t vp2 = 0;
        if (p1->switchState == switch_event_n::switch_state_t::PRESSED) {
            vp1 = 1;
        }
        if (p2->switchState == switch_event_n::switch_state_t::RELEASED) {
            vp2 = 1;
        }
        return vp1 < vp2;
    }
};

} // namespace pin_interface_n

#endif  // SRC_PININTERFACE_PINSTATECHANGE_H_

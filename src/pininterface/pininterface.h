/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_PININTERFACE_PININTERFACE_H_
#define SRC_PININTERFACE_PININTERFACE_H_

#include "Arduino.h"
#include <Bounce2.h>
#include <queue>
#include <cstdlib>

#include "../globals.h"
#include "../switchboard/machine.h"
#include "../switchevent/switchevent.h"

namespace pin_interface_n {

class PinInterface {
 public:
    PinInterface();
    void init_pins();
    void update(std::queue<switch_event_n::SwitchEvent>* switch_event_queue);
    ~PinInterface();
 private:
    Bounce * debouncedSwitches[N_SWITCHES];
};

} // namespace pin_interface_n


#endif // SRC_PININTERFACE_PININTERFACE_H_

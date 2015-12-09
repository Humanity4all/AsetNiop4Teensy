/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_PININTERFACE_PININTERFACE_H_
#define SRC_PININTERFACE_PININTERFACE_H_

#include <Bounce2.h>

#include "../globals.h"
#include "../switchboard/machine.h"
#include "../switchevent/switchevent.h"

namespace pin_interface_n {

class PinInterface {
 public:
    PinInterface();
    void update();
    ~PinInterface();
 private:
    Bounce * debouncedSwitches[N_SWITCHES];
    switch_event::SwitchEvent lastEvent;
};

} // namespace pin_interface_n


#endif // SRC_PININTERFACE_PININTERFACE_H_

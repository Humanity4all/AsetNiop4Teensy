/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_PININTERFACE_PININTERFACE_H_
#define SRC_PININTERFACE_PININTERFACE_H_

#include "Arduino.h"
#include <Bounce2.h>
#include <queue>
#include <vector>
#include <cstdlib>

#include "../globals.h"
#include "../buffers/buffers.h"
#ifdef DEBUG
  #include "../printswitchstate.h"
#endif
#include "./pinstatechange.h"
#include "../switchboard/machine.h"
#include "../switchevent/switchevent.h"

namespace pin_interface_n {

class PinInterface {
 public:
    PinInterface();
    void init_pins();
    void update(
        buffers_n::SwitchEventBuffer & switch_event_buffer,
        std::queue<switch_event_n::SwitchEvent*> & switch_event_queue);
    ~PinInterface();
 private:
    void copy(
        switch_event_n::switch_state_t new_switch_state[N_SWITCHES],
        bool old_to_new=false);
    Bounce debouncedSwitches[N_SWITCHES];
    switch_event_n::switch_state_t lastSwitchState[N_SWITCHES];
    buffers_n::PinStateChangeBuffer pinStateChangeBuffer;
    std::priority_queue<
        PinStateChange*,
        std::vector<PinStateChange*>,
        pin_state_change_compare> pinStateChangeQueue;
};

/*
 * For debugging purposes
 */
void print_switch_state(switch_event_n::switch_state_t switch_state[N_SWITCHES]);

} // namespace pin_interface_n


#endif // SRC_PININTERFACE_PININTERFACE_H_

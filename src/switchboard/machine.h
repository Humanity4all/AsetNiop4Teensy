/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHBOARD_MACHINE_H_
#define SRC_SWITCHBOARD_MACHINE_H_

#include <queue>

#include "../globals.h"
#include "./machinestates.h"
#include "./typedefs.h"
#include "../switchevent/switchevent.h"

#ifdef DEBUG
  #include "Arduino.h"
#endif

namespace switch_board_n {

class AbstractState;

class Machine {
 public:
    Machine();
    void change_state(AbstractState* new_state);
    void process_switch_event(
        switch_event_n::SwitchEvent* switch_event,
        std::queue<protokey_event_t> & protokey_event_queue);
    ~Machine();
 private:
    AbstractState* currentState;
};


} // namespace switch_board_n

#endif // SRC_SWITCHBOARD_MACHINE_H_

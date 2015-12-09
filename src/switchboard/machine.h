/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHBOARD_MACHINE_H_
#define SRC_SWITCHBOARD_MACHINE_H_

#include "../globals.h"
#include "./machinestates.h"
#include "../switchevent/switchevent.h"

namespace switch_board {

class AbstractState;

class Machine {
 public:
    Machine();
    void change_state(AbstractState* new_state);
    void process_switch_event(switch_event::SwitchEvent switch_event);
    ~Machine();
 private:
    AbstractState* currentState;
};


} // namespace switch_board

#endif // SRC_SWITCHBOARD_MACHINE_H_

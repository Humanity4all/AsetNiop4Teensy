/*
Copyright 2015 Stichting Humanity4all
*/

#include "./machine.h"

namespace switch_board_n {

Machine::Machine() {
    currentState = new Idle();
}

Machine::~Machine() {
}

void Machine::change_state(AbstractState* new_state) {
    AbstractState* oldState = currentState;
    currentState = new_state;
    delete oldState;
}

void Machine::process_switch_event(
        switch_event_n::SwitchEvent switch_event,
        protokey_event_t* return_event) {
    if (switch_event.edge == switch_event_n::event_t::E_FALLING) {
        currentState->release(*this, switch_event, return_event);
    } else if (switch_event.edge == switch_event_n::event_t::E_RISING) {
        currentState->press(*this, switch_event, return_event);
    } else {
        /* kick watchdog! */
    }
}


} // namespace switch_board_n

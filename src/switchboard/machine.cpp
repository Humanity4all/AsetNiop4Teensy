/*
Copyright 2015 Stichting Humanity4all
*/

#include <queue>

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
        switch_event_n::SwitchEvent* switch_event,
        std::queue<protokey_event_t> & protokey_event_queue) {
    if (switch_event->switch_state == switch_event_n::switch_state_t::RELEASED) {
        #ifdef DEBUG
          Serial.println("machine.h: SwitchRelease");
        #endif
        currentState->release(*this, switch_event, protokey_event_queue);
    } else if (switch_event->switch_state == switch_event_n::switch_state_t::PRESSED) {
        #ifdef DEBUG
          Serial.println("machine.h: SwitchPress");
        #endif
        currentState->press(*this, switch_event, protokey_event_queue);
    } else {
        #ifdef DEBUG
          Serial.println("machine.h: No valid switch state...");
        #endif
        /* kick watchdog! */
    }
}


} // namespace switch_board_n

/*
Copyright 2015 Stichting Humanity4all
*/

#include <vector>
#include <queue>
#include "./pininterface.h"

namespace pin_interface_n {

PinInterface::PinInterface() {
    for (uint8_t i=0; i < N_SWITCHES; i++) {
        lastSwitchState[i] = switch_event_n::switch_state_t::RELEASED;
    }
}

void PinInterface::init_pins() {
    uint8_t pins_to_use[] = { SWITCH_PINS };
    for (uint8_t i=0; i < N_SWITCHES; i++) {
        pinMode(pins_to_use[i], INPUT_PULLUP);
        debouncedSwitches[i].interval(10);
        debouncedSwitches[i].attach(pins_to_use[i]);
    }
}

void PinInterface::update(
        buffers_n::SwitchEventBuffer & switch_event_buffer,
        queue_n::SwitchEventQueue & switch_event_queue) {
    for (uint8_t i=0; i < N_SWITCHES; i++) {
        if (debouncedSwitches[i].update()) {
            #ifdef DEBUG
            Serial.println("pininterface.cpp: Detected pinstatechange event");
            #endif
            switch_event_n::switch_state_t new_switch_state[N_SWITCHES];
            this->copy(new_switch_state, true);
            if (debouncedSwitches[i].read() == 0) {
                new_switch_state[i] = switch_event_n::switch_state_t::PRESSED;
            } else {
                new_switch_state[i] = switch_event_n::switch_state_t::RELEASED;
            }
            #ifdef DEBUG
              Serial.print("pininterface.cpp: old switch state: ");
              debug_n::print_switch_state(lastSwitchState);
              Serial.print("pininterface.cpp: new switch state: ");
              debug_n::print_switch_state(new_switch_state);
            #endif
            switch_event_n::SwitchEvent* tmp_event;
            tmp_event = switch_event_buffer.get_free();
            *tmp_event = switch_event_n::SwitchEvent(lastSwitchState, new_switch_state);
            switch_event_queue.push(tmp_event);
            this->copy(new_switch_state, false);
            #ifdef DEBUG
              Serial.print("pininterface.cpp: Updated old switch state: ");
              debug_n::print_switch_state(lastSwitchState);
            #endif
        }
    }
}

PinInterface::~PinInterface() {
}

void PinInterface::copy(
        switch_event_n::switch_state_t new_switch_state[N_SWITCHES],
        bool old_to_new) {
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (old_to_new) {
            new_switch_state[i] = lastSwitchState[i];
        } else {
            lastSwitchState[i] = new_switch_state[i];
        }
    }
}


} // namespace pin_interface_n

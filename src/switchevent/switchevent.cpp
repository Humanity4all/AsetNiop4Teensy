/*
Copyright Stichting Humanity4all 2015
*/
#include "./switchevent.h"

namespace switch_event_n {

SwitchEvent::SwitchEvent() {
    isActive = false;
}

SwitchEvent::SwitchEvent(
        switch_state_t old_switch_state[N_SWITCHES],
        switch_state_t new_switch_state[N_SWITCHES]) {
    isActive = true;
    /*
     * a really ugly solution for copying over the data
     * but my experience with pointers and stuff is too
     * limited to do this in a more elegant way
     */
    // oldSwitchState = old_switch_state;
    // newSwitchState = new_switch_state;
    for (uint8_t i=0; i < N_SWITCHES; i++) {
        oldSwitchState[i] = old_switch_state[i];
        newSwitchState[i] = new_switch_state[i];
    }
    this->update_effective_switch_state();
    #ifdef DEBUG
      Serial.print("switchevent.cpp: oldSwitchState: ");
      debug_n::print_switch_state(oldSwitchState);
      Serial.print("switchevent.cpp: newSwitchState: ");
      debug_n::print_switch_state(newSwitchState);
      Serial.print("switchevent.cpp: effectiveSwitchState: ");
      debug_n::print_switch_state(effectiveSwitchState);
    #endif
}

void SwitchEvent::new_event(
        switch_state_t new_switch_state[N_SWITCHES],
        SwitchEvent* return_event) {
    return_event = new SwitchEvent(newSwitchState, new_switch_state);
}

uint8_t SwitchEvent::count_active() {
    uint8_t acc = 0;
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (effectiveSwitchState[i] == switch_state_t::PRESSED) {
            acc += 1;
        }
    }
    return acc;
}

int8_t SwitchEvent::get_active_switch(uint8_t n) {
    uint8_t nth = 0;
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        #ifdef DEBUG
        debug_n::print_switch_state(effectiveSwitchState);
        Serial.println(effectiveSwitchState[i]);
        #endif
        if (effectiveSwitchState[i] == switch_state_t::PRESSED) {
            nth += 1;
            #ifdef DEBUG
            Serial.print("switch_event.get_active_switch: found match at ");
            Serial.println(i);
            #endif
            if (n == nth) {
                return i;
            }
        }
    }
    return -1;
}

int8_t SwitchEvent::state_diff() {
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (
                (oldSwitchState[i] == switch_state_t::PRESSED) ^
                (newSwitchState[i] == switch_state_t::PRESSED)) {
            return i;
        }
    }
    return -1;
}

SwitchEvent::~SwitchEvent() {
    isActive = false;
}

void SwitchEvent::update_effective_switch_state() {
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (
                oldSwitchState[i] == switch_state_t::PRESSED ||
                newSwitchState[i] == switch_state_t::PRESSED) {
            effectiveSwitchState[i] = switch_state_t::PRESSED;
        }
    }
    switch_state = newSwitchState[this->state_diff()];
}

} // namespace switch_event_n

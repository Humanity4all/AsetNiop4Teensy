/*
Copyright Stichting Humanity4all 2015
*/
#include "./switchevent.h"

namespace switch_event_n {

SwitchEvent::SwitchEvent(
        switch_state_t old_switch_state[N_SWITCHES],
        switch_state_t new_switch_state[N_SWITCHES]) {
    /*
     * a really ugly solution for copying over the data
     * but my experience with pointers and stuff is too
     * limited to do this in a more elegant way
     */
    // oldSwitchState = old_switch_state;
    // newSwitchState = new_switch_state;
    for (int i=0; i < N_SWITCHES; i++) {
        oldSwitchState[i] = old_switch_state[i];
        newSwitchState[i] = new_switch_state[i];
    }
    this->update_effective_switch_state();
}

void SwitchEvent::new_event(
        switch_state_t new_switch_state[N_SWITCHES],
        SwitchEvent* return_event) {
    return_event = new SwitchEvent(newSwitchState, new_switch_state);
}

int SwitchEvent::count_active() {
    int acc = 0;
    for (int i = 0; i < N_SWITCHES; i++) {
        if (effectiveSwitchState[i] == 1) {
            acc += 1;
        }
    }
    return acc;
}

int SwitchEvent::get_active_switch(int n) {
    int nth = 0;
    for (int i = 0; i < N_SWITCHES; i++) {
        if (effectiveSwitchState[i] == 1) {
            nth += 1;
            if (n == nth) {
                return i;
            }
        }
    }
    return -1;
}

int SwitchEvent::state_diff() {
    for (int i = 0; i < N_SWITCHES; i++) {
        if ((oldSwitchState[i] ^ newSwitchState[i]) == 1) {
            return i;
        }
    }
    return -1;
}

SwitchEvent::~SwitchEvent() {
}

void SwitchEvent::update_effective_switch_state() {
    for (int i = 0; i < N_SWITCHES; i++) {
        if (oldSwitchState[i] || newSwitchState[i]) {
            effectiveSwitchState[i] = switch_state_t::PRESSED;
        }
    }
}

} // namespace switch_event_n

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
    // for debug purposes
    // pinMode(LED_PIN, OUTPUT);
    uint8_t pins_to_use[] = { SWITCH_PINS };
    for (uint8_t i=0; i < N_SWITCHES; i++) {
        pinMode(pins_to_use[i], INPUT_PULLUP);
        debouncedSwitches[i].interval(10);
        debouncedSwitches[i].attach(pins_to_use[i]);
    }
}

void PinInterface::update(
        buffers_n::SwitchEventBuffer & switch_event_buffer,
        std::queue<switch_event_n::SwitchEvent*> & switch_event_queue) {
    for (uint8_t i=0; i < N_SWITCHES; i++) {
        if (debouncedSwitches[i].update()) {
            PinStateChange* tmp_event;
            tmp_event = pinStateChangeBuffer.get_free();
            if (debouncedSwitches[i].read() == 0) {
                /* pressed */
                *tmp_event = PinStateChange(
                    i,
                    switch_event_n::switch_state_t::PRESSED);
                pinStateChangeQueue.push(tmp_event);
                #ifdef DEBUG
                  Serial.print("pininterface.cpp: Pressed switch ");
                  Serial.println(i);
                #endif
                // digitalWrite(LED_PIN, HIGH);
            } else {
                /* released */
                *tmp_event = PinStateChange(
                    i,
                    switch_event_n::switch_state_t::RELEASED);
                pinStateChangeQueue.push(tmp_event);
                #ifdef DEBUG
                  Serial.print("pininterface.cpp: Released switch ");
                  Serial.println(i);
                #endif
                // digitalWrite(LED_PIN, LOW);
            }

            while (!pinStateChangeQueue.empty()) {
                PinStateChange* p = pinStateChangeQueue.top();
                #ifdef DEBUG
                  Serial.println("pininterface.cpp: Detected pinstatechange event");
                #endif
                switch_event_n::switch_state_t new_switch_state[N_SWITCHES];
                // std::copy(
                //    std::begin(lastSwitchState),
                //    std::end(lastSwitchState),
                //    std::begin(new_switch_state));
                this->copy(new_switch_state, true);
                new_switch_state[p->pinNumber] = p->switchState;
                #ifdef DEBUG
                  Serial.print("pininterface.cpp: old switch state: ");
                  debug_n::print_switch_state(lastSwitchState);
                  Serial.print("pininterface.cpp: new switch state: ");
                  debug_n::print_switch_state(new_switch_state);
                #endif
                /*
                 * NOFIXME this line is necessary but creates compiler errors.
                 * undefined references to _kill, _getpid and _write
                 *
                 * According to:
                 * https://forum.pjrc.com/threads/29177-Teensy-3-1-signalr-c-%28-text-_kill_r-0xe%29-undefined-reference-to-_kill-error
                 *
                 * Normally this error occurs when code using C
                 * varrargs (va_arg, va_list, va_star, va_end)
                 * uses an invalid type. 
                 *
                 * We fixed it by declaring the missing functions in global...
                 */
                // switch_event_queue.emplace(lastSwitchState, new_switch_state);
                switch_event_n::SwitchEvent* tmp_event;
                tmp_event = switch_event_buffer.get_free();
                *tmp_event = switch_event_n::SwitchEvent(lastSwitchState, new_switch_state);
                switch_event_queue.push(tmp_event);
                // std::copy(
                //    std::begin(new_switch_state),
                //    std::end(new_switch_state),
                //    std::begin(lastSwitchState));
                this->copy(new_switch_state, false);
                #ifdef DEBUG
                  Serial.print("pininterface.cpp: Updated old switch state: ");
                  debug_n::print_switch_state(lastSwitchState);
                #endif
                pinStateChangeQueue.pop();
            }
            pinStateChangeBuffer.empty();
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

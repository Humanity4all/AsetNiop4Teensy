/*
Copyright 2015 Stichting Humanity4all
*/

#include <vector>
#include <queue>
#include "./pininterface.h"

namespace pin_interface_n {

PinInterface::PinInterface() {
    for (int i=0; i < N_SWITCHES; i++) {
        lastSwitchState[i] = switch_event_n::switch_state_t::RELEASED;
        debouncedSwitches[i] = (Bounce *)malloc(sizeof(Bounce));
        *debouncedSwitches[i] = Bounce();
    }
}

void PinInterface::init_pins() {
    // for debug purposes
    // pinMode(LED_PIN, OUTPUT);
    int pins_to_use[] = { SWITCH_PINS };
    for (int i=0; i < N_SWITCHES; i++) {
        pinMode(pins_to_use[i], INPUT_PULLUP);
        debouncedSwitches[i]->interval(10);
        debouncedSwitches[i]->attach(pins_to_use[i]);
    }
}

void PinInterface::update(std::queue<switch_event_n::SwitchEvent> & switch_event_queue) {
    /*
     * Caveat: priority queues probably allocate memory dynamically.
     * This is not a good idea to do in the loop() part of arduino.
     * If we experience memory problems, this might be the cause.
     */
    std::priority_queue<
        PinStateChange,
        std::vector<PinStateChange>,
        pin_state_change_compare> pin_change_queue;
    for (int i=0; i < N_SWITCHES; i++) {
        if (debouncedSwitches[i]->update()) {
            if (debouncedSwitches[i]->read() == 0) {
                /* pressed */
                pin_change_queue.emplace(
                    i,
                    switch_event_n::switch_state_t::PRESSED);
                // digitalWrite(LED_PIN, HIGH);
            } else {
                /* released */
                pin_change_queue.emplace(
                    i,
                    switch_event_n::switch_state_t::RELEASED);
                // digitalWrite(LED_PIN, LOW);
            }

            while (!pin_change_queue.empty()) {
                PinStateChange p = pin_change_queue.top();
                switch_event_n::switch_state_t new_switch_state[N_SWITCHES];
                std::copy(
                    std::begin(lastSwitchState),
                    std::end(lastSwitchState),
                    std::begin(new_switch_state));
                new_switch_state[p.pinNumber] = p.switchState;
                /*
                 * FIXME this line is necessary but creates compiler errors.
                 * undefined references to _kill, _getpid and _write
                 *
                 * According to:
                 * https://forum.pjrc.com/threads/29177-Teensy-3-1-signalr-c-%28-text-_kill_r-0xe%29-undefined-reference-to-_kill-error
                 *
                 * Normally this error occurs when code using C
                 * varrargs (va_arg, va_list, va_star, va_end)
                 * uses an invalid type. 
                 */
                // switch_event_queue.emplace(lastSwitchState, new_switch_state);
                std::copy(
                    std::begin(new_switch_state),
                    std::end(new_switch_state),
                    std::begin(lastSwitchState));
                pin_change_queue.pop();
            }
        }
    }
}

PinInterface::~PinInterface() {
    for (int i = 0; i < N_SWITCHES; i++) {
        delete debouncedSwitches[i];
    }
}

} // namespace pin_interface_n

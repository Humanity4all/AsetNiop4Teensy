/*
Copyright 2015 Stichting Humanity4all
*/

#include "./pininterface.h"

namespace pin_interface_n {

PinInterface::PinInterface() {
    for (int i=0; i < N_SWITCHES; i++) {
        debouncedSwitches[i] = (Bounce *)malloc(sizeof(Bounce));
        *debouncedSwitches[i] = Bounce();
    }
}

void PinInterface::init_pins() {
    // for debug purposes
    pinMode(LED_PIN, OUTPUT);
    int pins_to_use[] = { SWITCH_PINS };
    for (int i=0; i < N_SWITCHES; i++) {
        pinMode(pins_to_use[i], INPUT_PULLUP);
        debouncedSwitches[i]->interval(10);
        debouncedSwitches[i]->attach(pins_to_use[i]);
    }
}

void PinInterface::update(std::queue<switch_event_n::SwitchEvent>* switch_event_queue) {
    for (int i=0; i < N_SWITCHES; i++) {
        if (debouncedSwitches[i]->update()) {
            if (debouncedSwitches[i]->read() == 0) {
                /* pressed */
                // TODO process switch_press
                digitalWrite(LED_PIN, HIGH);
            } else {
                /* released */
                // TODO process switch_press
                digitalWrite(LED_PIN, LOW);
            }
            // TODO add event to event queue
            // TODO add priority: releases should go first when there are multiple events
        }
    }
}

PinInterface::~PinInterface() {
    for (int i = 0; i < N_SWITCHES; i++) {
        delete debouncedSwitches[i];
    }
}

} // namespace pin_interface_n

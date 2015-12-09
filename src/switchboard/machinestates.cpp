/*
Copyright 2015 Stichting Humanity4all
*/

#include "./machinestates.h"

namespace switch_board_n {

protokey_event_t AbstractState::press(
        Machine& machine,
        switch_event_n::SwitchEvent switch_event) {
}

protokey_event_t AbstractState::release(
        Machine& machine,
        switch_event_n::SwitchEvent switch_event) {
    throw std::runtime_error("Invalid state: this method should only be inherited.");
}

AbstractState::~AbstractState() {
}

protokey_event_t Idle::press(
        Machine& machine,
        switch_event_n::SwitchEvent switch_event) {
    machine.change_state(new OneSwitch());
    protokey_event_t event;
    event.event = event_t::DOWN;
    event.switch_event = switch_event;
    event.is_chord = false;
    return event;
}

protokey_event_t Idle::release(
        Machine& machine,
        switch_event_n::SwitchEvent switch_event) {
    /*
     * TODO Kick the dog here, there is clearly memory corruption!
     */
    throw std::runtime_error("Invalid state: can't release switches in idle");
}

Idle::~Idle() {
}






} // namespace switch_board_n

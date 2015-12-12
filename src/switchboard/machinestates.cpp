/*
Copyright 2015 Stichting Humanity4all
*/

#include "./machinestates.h"

namespace switch_board_n {

void AbstractState::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
}

void AbstractState::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
    throw std::runtime_error("Invalid state: this method should only be inherited.");
}

AbstractState::~AbstractState() {
}

void Idle::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
    machine.change_state(new OneSwitch());
    return_event->event = event_t::DOWN;
    return_event->switch_event = switch_event;
    return_event->is_chord = false;
}

void Idle::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
    /*
     * TODO Kick the dog here, there is clearly memory corruption!
     */
    throw std::runtime_error("Invalid state: can't release switches in idle");
}

Idle::~Idle() {
}






} // namespace switch_board_n

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
    //throw std::runtime_error("Invalid state: this method should only be inherited.");
}

AbstractState::~AbstractState() {
}

void Idle::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
    return_event->event = event_t::DOWN;
    return_event->switch_event = switch_event;
    return_event->is_chord = false;
    machine.change_state(new OneSwitch());
}

void Idle::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
    /*
     * TODO Kick the dog here, there is clearly memory corruption!
     */
    //throw std::runtime_error("Invalid state: can't release switches in idle");
}

Idle::~Idle() {
}

void OneSwitch::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
    return_event->event = event_t::DOWN;
    return_event->switch_event = switch_event;
    return_event->is_chord = true;
    machine.change_state(new TwoSwitch());
}

void OneSwitch::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
    /*
     * TODO: this method should return 2 events, one down and one up.
     */
    return_event->event = event_t::UP;
    return_event->switch_event = switch_event;
    return_event->is_chord = true;
    machine.change_state(new Idle());
}

OneSwitch::~OneSwitch() {
}

void TwoSwitch::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
    /*
     * TODO: this method should return 2 events, one down and one reset
     */
    return_event->event = event_t::DOWN;
    return_event->switch_event = switch_event;
    return_event->is_chord = false;
    machine.change_state(new ManySwitch());
}

void TwoSwitch::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        protokey_event_t* return_event) {
    return_event->event = event_t::UP;
    return_event->switch_event = switch_event;
    return_event->is_chord = true;
    machine.change_state(new OneSwitchUsed());
}

TwoSwitch::~TwoSwitch() {
}




} // namespace switch_board_n

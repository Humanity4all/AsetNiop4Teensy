/*
Copyright 2015 Stichting Humanity4all
*/

#include <queue>

#include "./machinestates.h"

namespace switch_board_n {

void AbstractState::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
}

void AbstractState::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // throw std::runtime_error("Invalid state: this method should only be inherited.");
}

AbstractState::~AbstractState() {
}

void Idle::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // protokey_event_queue.emplace(event_t::DOWN, switch_event, false);
    protokey_event_t* tmp_event;
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::DOWN, switch_event, false);
    protokey_event_queue.push(tmp_event);
    #ifdef DEBUG
      Serial.println("machinestates.h: Enter OneSwitch");
    #endif
    machine.change_state(new OneSwitch());
}

void Idle::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    /*
     * TODO Kick the dog here, there is clearly memory corruption!
     */
    // throw std::runtime_error("Invalid state: can't release switches in idle");
}

Idle::~Idle() {
}

void OneSwitch::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // protokey_event_queue.emplace(event_t::DOWN, switch_event, true);
    protokey_event_t* tmp_event;
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::DOWN, switch_event, true);
    protokey_event_queue.push(tmp_event);
    #ifdef DEBUG
      Serial.println("machinestates.h: Enter TwoSwitch");
    #endif
    machine.change_state(new TwoSwitch());
}

void OneSwitch::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // protokey_event_queue.emplace(event_t::DOWN, switch_event, true);
    protokey_event_t* tmp_event;
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::DOWN, switch_event, true);
    protokey_event_queue.push(tmp_event);
    // protokey_event_queue.emplace(event_t::UP, switch_event, true);
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::UP, switch_event, true);
    protokey_event_queue.push(tmp_event);
    #ifdef DEBUG
      Serial.println("machinestates.h: Enter Idle");
    #endif
    machine.change_state(new Idle());
}

OneSwitch::~OneSwitch() {
}

void OneSwitchUsed::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // protokey_event_queue.emplace(event_t::DOWN, switch_event, true);
    protokey_event_t* tmp_event;
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::DOWN, switch_event, true);
    protokey_event_queue.push(tmp_event);
    #ifdef DEBUG
      Serial.println("machinestates.h: Enter TwoSwitch");
    #endif
    machine.change_state(new TwoSwitch());
}

void OneSwitchUsed::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // protokey_event_queue.emplace(event_t::UP, switch_event, false);
    protokey_event_t* tmp_event;
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::UP, switch_event, false);
    protokey_event_queue.push(tmp_event);
    #ifdef DEBUG
      Serial.println("machinestates.h: Enter Idle");
    #endif
    machine.change_state(new Idle());
}

OneSwitchUsed::~OneSwitchUsed() {
}

void TwoSwitch::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // protokey_event_queue.emplace(event_t::DOWN, switch_event, false);
    protokey_event_t* tmp_event;
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::DOWN, switch_event, false);
    protokey_event_queue.push(tmp_event);
    // protokey_event_queue.emplace(event_t::RESET, switch_event, true);
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::RESET, switch_event, true);
    protokey_event_queue.push(tmp_event);
    #ifdef DEBUG
      Serial.println("machinestates.h: Enter ManySwitch");
    #endif
    machine.change_state(new ManySwitch());
}

void TwoSwitch::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // protokey_event_queue.emplace(event_t::UP, switch_event, true);
    protokey_event_t* tmp_event;
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::UP, switch_event, true);
    protokey_event_queue.push(tmp_event);
    #ifdef DEBUG
      Serial.println("machinestates.h: Enter OneSwitchUsed");
    #endif
    machine.change_state(new OneSwitchUsed());
}

TwoSwitch::~TwoSwitch() {
}


void ManySwitch::press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // protokey_event_queue.emplace(event_t::DOWN, switch_event, false);
    protokey_event_t* tmp_event;
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::DOWN, switch_event, false);
    protokey_event_queue.push(tmp_event);
    // don't change state here
}

void ManySwitch::release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        std::queue<protokey_event_t*> & protokey_event_queue) {
    // protokey_event_queue.emplace(event_t::UP, switch_event, false);
    protokey_event_t* tmp_event;
    tmp_event = protokey_event_buffer.get_free();
    *tmp_event = protokey_event_t(event_t::UP, switch_event, false);
    protokey_event_queue.push(tmp_event);
    if (switch_event->count_active() <= 1) {
        #ifdef DEBUG
          Serial.println("machinestates.h: Enter Idle");
        #endif
        machine.change_state(new Idle());
    }
}

ManySwitch::~ManySwitch() {
}

} // namespace switch_board_n

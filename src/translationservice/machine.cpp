/*
Copyright 2016 Stichting Humanity4all
*/

#include "./machine.h"

namespace translation_service_n {

Machine::Machine(buffers_n::LayerBuffer* state_buffer) {
    stateBuffer = state_buffer;
    currentState = stateBuffer->new_layer(0);
}

void Machine::process_protokey_event(
        switch_board_n::protokey_event_t* protokey_event) {
    currentState->process_protokey_event(protokey_event);
}

void Machine::change_state(uint8_t layer) {
    currentState = stateBuffer->new_layer(layer);
}

void Machine::set_modifier(key_t key) {
}

int* Machine::use_modifiers() {
}

} // namespace translation_service_n

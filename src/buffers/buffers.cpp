/*
Copyright 2016 Stichting Humanity4all
*/

#include "./buffers.h"

namespace buffers_n {

pin_interface_n::PinStateChange* PinStateChangeBuffer::get_free() {
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (!eventBuffer[i].isActive) {
            return &eventBuffer[i];
        }
    }
    /*
     * TODO: kick watchdog! Ran out of buffer
     */
    #ifdef DEBUG
    Serial.println("PinStateChangeBuffer ran out of space!");
    #endif
    // Better to overwrite the first event than to do random stuff...
    return &eventBuffer[0];
}

void PinStateChangeBuffer::empty() {
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (eventBuffer[i].isActive) {
            eventBuffer[i].~PinStateChange();
        }
    }
}

switch_event_n::SwitchEvent* SwitchEventBuffer::get_free() {
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (!eventBuffer[i].isActive) {
            return &eventBuffer[i];
        }
    }
    /*
     * TODO: kick watchdog! Ran out of buffer
     */
    #ifdef DEBUG
    Serial.println("SwitchEventBuffer ran out of space!");
    #endif
    // Better to overwrite the first event than to do random stuff...
    return &eventBuffer[0];
}

void SwitchEventBuffer::empty() {
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (eventBuffer[i].isActive) {
            eventBuffer[i].~SwitchEvent();
        }
    }
}

switch_board_n::protokey_event_t* ProtokeyEventBuffer::get_free() {
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (!eventBuffer[i].is_active) {
            return &eventBuffer[i];
        }
    }
    /*
     * TODO: kick watchdog! Ran out of buffer
     */
    #ifdef DEBUG
    Serial.println("ProtoKeyEventBuffer ran out of space!");
    #endif
    // Better to overwrite the first event than to do random stuff...
    return &eventBuffer[0];
}

void ProtokeyEventBuffer::empty() {
    for (uint8_t i = 0; i < N_SWITCHES; i++) {
        if (eventBuffer[i].is_active) {
            eventBuffer[i].~protokey_event_t();
        }
    }
}

translation_service_n::Layer* LayerBuffer::new_layer(uint8_t layer) {
    uint8_t buffer_index;
    if (layerBuffer[0].isActive) {
        buffer_index = 1;
        layerBuffer[0].~Layer();
    } else {
        buffer_index = 0;
        layerBuffer[1].~Layer();
    }
    layerBuffer[buffer_index] = translation_service_n::Layer(layer);
    return &layerBuffer[buffer_index];
}


} // namespace buffers_n

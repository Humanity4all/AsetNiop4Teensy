/*
Copyright 2016 Stichting Humanity4all
*/

#include "./machine.h"

namespace translation_service_n {

Machine::Machine() {
    currentState = new Layer(0);
}

void Machine::process_protokey_event(
        switch_board_n::protokey_event_t* protokey_event) {
    currentState->process_protokey_event(this, protokey_event);
}

void Machine::change_state(int layer) {
    int buffer_index;
    if (stateBuffer[0].isActive) {
        buffer_index = 1;
        stateBuffer[0].~Layer();
    } else {
        buffer_index = 0;
        stateBuffer[1].~Layer();
    }
    stateBuffer[buffer_index] = Layer(layer);
}

void Machine::send_key(key_t key, switch_board_n::event_t event) {
    #ifdef DEBUG
    Serial.print("translation_service: send key ");
    Serial.print(key);
    Serial.print(" ");
    Serial.println(event);
    #endif
    uint16_t key_code;
    switch (key) {
        case key_t::K_A: {
            key_code = KEY_A;
            #ifdef DEBUG
            Serial.println("translation_service: it's an A!");
            #endif
            break;
        }
        case key_t::K_B: {
            key_code = KEY_B;
            #ifdef DEBUG
            Serial.println("translation_service: it's a B!");
            #endif
            break;
        }
        case key_t::K_C: {
            key_code = KEY_C;
            #ifdef DEBUG
            Serial.println("translation_service: it's a C!");
            #endif
            break;
        }
        case key_t::K_D: {
            key_code = KEY_D;
            #ifdef DEBUG
            Serial.println("translation_service: it's a D!");
            #endif
            break;
        }
        case key_t::K_E: {
            key_code = KEY_E;
            #ifdef DEBUG
            Serial.println("translation_service: it's an E!");
            #endif
            break;
        }
        case key_t::K_F: {
            key_code = KEY_F;
            #ifdef DEBUG
            Serial.println("translation_service: it's an F!");
            #endif
            break;
        }
        default: {
            // TODO kick watchdog
            #ifdef DEBUG
            Serial.print("translation_service: unrecognized key: ");
            Serial.println(key);
            #endif
        }
    }
    #ifdef DEBUG
    Serial.print("translation_service: key code: ");
    Serial.println(key_code);
    #endif

    if (event == switch_board_n::event_t::UP) {
        Keyboard.release(key_code);
        #ifdef DEBUG
        Serial.println("translation_service: release!");
        #endif
    } else if (event == switch_board_n::event_t::DOWN) {
        Keyboard.press(key_code);
        #ifdef DEBUG
        Serial.println("translation_service: press!");
        #endif
    } else if (event == switch_board_n::event_t::RESET) {
        #ifdef DEBUG
        Serial.println("translation_service: reset!");
        #endif
        Keyboard.releaseAll();
    } else {
        // TODO kick watchdog
        #ifdef DEBUG
        Serial.print("translation_service: unrecognized event: ");
        Serial.println(event);
        #endif
    }
}

void Machine::set_modifier(key_t key) {
}

int* Machine::use_modifiers() {
}

} // namespace translation_service_n

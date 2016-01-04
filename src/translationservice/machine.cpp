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
    currentState->process_protokey_event(*this, protokey_event);
}

void Machine::change_state(Layer* new_state) {
    Layer* oldState = currentState;
    currentState = new_state;
    delete oldState;
}

void Machine::send_key(key_t key, switch_board_n::event_t event) {
    #ifdef DEBUG
    Serial.print("translation_service: send key ");
    Serial.print(key);
    Serial.print(" ");
    Serial.println(event);
    #endif
    char key_code;
    switch (key) {
        case key_t::K_A: {
            key_code = KEY_A;
            break;
        }
        case key_t::K_B: {
            key_code = KEY_B;
            break;
        }
        case key_t::K_C: {
            key_code = KEY_C;
            break;
        }
        case key_t::K_D: {
            key_code = KEY_D;
            break;
        }
        case key_t::K_E: {
            key_code = KEY_E;
            break;
        }
        case key_t::K_F: {
            key_code = KEY_F;
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

    if (event == switch_board_n::event_t::UP) {
        Keyboard.release(key);
    } else if (event == switch_board_n::event_t::DOWN) {
        Keyboard.press(key);
    } else if (event == switch_board_n::event_t::RESET) {
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

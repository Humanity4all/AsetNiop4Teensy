/*
Copyright 2016 Stichting Humanity4all
*/

#include "./translationservice.h"

namespace translation_service_n {

void TranslationService::send_key(key_t key, switch_board_n::event_t event) {
    #ifdef DEBUG
    Serial.print("translation_service: send key ");
    Serial.print(key);
    Serial.print(" ");
    Serial.println(event);
    #endif
    uint16_t key_code;
    bool is_modifier = false;
    bool is_layer = false;
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
        case key_t::K_G: {
            key_code = KEY_G;
            #ifdef DEBUG
            Serial.println("translation_service: it's a G!");
            #endif
            break;
        }
        case key_t::K_H: {
            key_code = KEY_H;
            #ifdef DEBUG
            Serial.println("translation_service: it's an H!");
            #endif
            break;
        }
        case key_t::K_I: {
            key_code = KEY_I;
            #ifdef DEBUG
            Serial.println("translation_service: it's an I!");
            #endif
            break;
        }
        case key_t::K_J: {
            key_code = KEY_J;
            #ifdef DEBUG
            Serial.println("translation_service: it's a J!");
            #endif
            break;
        }
        case key_t::K_K: {
            key_code = KEY_K;
            #ifdef DEBUG
            Serial.println("translation_service: it's a K!");
            #endif
            break;
        }
        case key_t::K_L: {
            key_code = KEY_L;
            #ifdef DEBUG
            Serial.println("translation_service: it's an L!");
            #endif
            break;
        }
        case key_t::K_M: {
            key_code = KEY_M;
            #ifdef DEBUG
            Serial.println("translation_service: it's an M!");
            #endif
            break;
        }
        case key_t::K_N: {
            key_code = KEY_N;
            #ifdef DEBUG
            Serial.println("translation_service: it's an N!");
            #endif
            break;
        }
        case key_t::K_O: {
            key_code = KEY_O;
            #ifdef DEBUG
            Serial.println("translation_service: it's an O!");
            #endif
            break;
        }
        case key_t::K_P: {
            key_code = KEY_P;
            #ifdef DEBUG
            Serial.println("translation_service: it's a P!");
            #endif
            break;
        }
        case key_t::K_Q: {
            key_code = KEY_Q;
            #ifdef DEBUG
            Serial.println("translation_service: it's a Q!");
            #endif
            break;
        }
        case key_t::K_R: {
            key_code = KEY_R;
            #ifdef DEBUG
            Serial.println("translation_service: it's an R!");
            #endif
            break;
        }
        case key_t::K_S: {
            key_code = KEY_S;
            #ifdef DEBUG
            Serial.println("translation_service: it's an S!");
            #endif
            break;
        }
        case key_t::K_T: {
            key_code = KEY_T;
            #ifdef DEBUG
            Serial.println("translation_service: it's a T!");
            #endif
            break;
        }
        case key_t::K_U: {
            key_code = KEY_U;
            #ifdef DEBUG
            Serial.println("translation_service: it's a U!");
            #endif
            break;
        }
        case key_t::K_V: {
            key_code = KEY_V;
            #ifdef DEBUG
            Serial.println("translation_service: it's a V!");
            #endif
            break;
        }
        case key_t::K_W: {
            key_code = KEY_W;
            #ifdef DEBUG
            Serial.println("translation_service: it's a W!");
            #endif
            break;
        }
        case key_t::K_X: {
            key_code = KEY_X;
            #ifdef DEBUG
            Serial.println("translation_service: it's an X!");
            #endif
            break;
        }
        case key_t::K_Y: {
            key_code = KEY_Y;
            #ifdef DEBUG
            Serial.println("translation_service: it's a Y!");
            #endif
            break;
        }
        case key_t::K_Z: {
            key_code = KEY_Z;
            #ifdef DEBUG
            Serial.println("translation_service: it's a Z!");
            #endif
            break;
        }
        case key_t::K_SHIFT: {
            is_modifier = true;
            #ifdef DEBUG
            Serial.println("translation_service: it's a SHIFT!");
            #endif
            break;
        }
        case key_t::K_LAYER_0: {
            is_layer = true;
            if (event == switch_board_n::event_t::DOWN) {
                layerNumber = 0;
                #ifdef DEBUG
                Serial.println("translation_service: switch to layer 0");
                #endif
            }
            break;
        }
        case key_t::K_LAYER_1: {
            is_layer = true;
            if (event == switch_board_n::event_t::UP) {
                layerNumber = 1;
                #ifdef DEBUG
                Serial.println("translation_service: switch to layer 1");
                #endif
            }
            break;
        }
        case key_t::K_LAYER_2: {
            is_layer = true;
            if (event == switch_board_n::event_t::UP) {
                layerNumber = 2;
                #ifdef DEBUG
                Serial.println("translation_service: switch to layer 2");
                #endif
            }
            break;
        }
        case key_t::K_LAYER_3: {
            is_layer = true;
            if (event == switch_board_n::event_t::UP) {
                layerNumber = 3;
                #ifdef DEBUG
                Serial.println("translation_service: switch to layer 3");
                #endif
            }
            break;
        }
        case key_t::K_LAYER_4: {
            is_layer = true;
            if (event == switch_board_n::event_t::UP) {
                layerNumber = 4;
                #ifdef DEBUG
                Serial.println("translation_service: switch to layer 4");
                #endif
            }
            break;
        }
        case key_t::K_LAYER_5: {
            is_layer = true;
            if (event == switch_board_n::event_t::UP) {
                layerNumber = 5;
                #ifdef DEBUG
                Serial.println("translation_service: switch to layer 5");
                #endif
            }
            break;
        }
        case key_t::K_LAYER_6: {
            is_layer = true;
            if (event == switch_board_n::event_t::UP) {
                layerNumber = 6;
                #ifdef DEBUG
                Serial.println("translation_service: switch to layer 6");
                #endif
            }
            break;
        }
        case key_t::K_LAYER_7: {
            is_layer = true;
            if (event == switch_board_n::event_t::UP) {
                layerNumber = 7;
                #ifdef DEBUG
                Serial.println("translation_service: switch to layer 7");
                #endif
            }
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
    if (is_layer) {
        // do nothing - we already switched layers
    } else if (event == switch_board_n::event_t::UP and !is_modifier) {
        // Keyboard.release(key_code);
        Keyboard.set_key1(0);
        #ifdef DEBUG
        Serial.println("translation_service: release!");
        #endif
    } else if (event == switch_board_n::event_t::DOWN and !is_modifier) {
        // Keyboard.press(key_code);
        Keyboard.set_key1(key_code);
        #ifdef DEBUG
        Serial.println("translation_service: press!");
        #endif
    } else if (event == switch_board_n::event_t::UP and is_modifier) {
        // ignore this, releasing a modifier doesn't do anything
        #ifdef DEBUG
        Serial.println("translation_service: release modifier (ignore)");
        #endif
    } else if (event == switch_board_n::event_t::DOWN and is_modifier) {
        set_modifier(key);
        #ifdef DEBUG
        Serial.println("translation_service: press modifier");
        #endif
    } else if (event == switch_board_n::event_t::RESET) {
        #ifdef DEBUG
        Serial.println("translation_service: reset!");
        #endif
        // Keyboard.releaseAll();
        Keyboard.set_key1(0);
        Keyboard.set_key2(0);
        Keyboard.set_key3(0);
        Keyboard.set_key4(0);
        Keyboard.set_key5(0);
        Keyboard.set_key6(0);
        // TODO: figure out what to do with modifiers in case of reset
    } else {
        // TODO kick watchdog
        #ifdef DEBUG
        Serial.print("translation_service: unrecognized event: ");
        Serial.println(event);
        #endif
    }
    Keyboard.send_now();
    if (!is_modifier and !is_layer) {
        #ifdef DEBUG
        Serial.println("translation_service: use up modifier");
        #endif
        use_modifiers();
    }
}

} // namespace translation_service_n

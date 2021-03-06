/*
Copyright 2016 Stichting Humanity4all
*/

#include "./translationservice.h"

namespace translation_service_n {

TranslationService::TranslationService() {
    layerNumber = 0;
    for (uint8_t i = 0; i < NUM_MODIFIERS; i++) {
        modState[i] = modifier_t::IDLE;
    }
}

void TranslationService::process_protokey_event(
        switch_board_n::protokey_event_t* protokey_event) {
    uint8_t switch1;
    uint8_t switch2;
    int8_t tmp;
    key_t key;
    /*
     * How many switches are active?
     * if zero, kick the dog
     * if one, our job is easy,
     * if two, it gets hairy
     */
    switch (protokey_event->switch_event->count_active()) {
        case 0: {
            // TODO kick the dog
            break;
        }
        case 1: {
            /*
             * is_chord == True & event == DOWN
             * only send if this is a purely chorded switch
             *
             * is_chord == True & event == UP
             * always send
             *
             * is_chord == False & event == DOWN
             * only send if this is a non-chorded switch
             *
             * is_chord == False & event == UP
             * kick the dog, this is not allowed to occur!
             */
            tmp = protokey_event->switch_event->get_active_switch(1);
            if (tmp < 0) {
                // TODO kick watchdog
                break;
            } else {
                switch1 = (uint8_t)tmp;
            }
            #ifdef DEBUG
            Serial.print("translation_service_layer: switch1=");
            Serial.println(switch1);
            #endif
            if (
                    protokey_event->is_chord &&
                    protokey_event->event == switch_board_n::event_t::UP) {
                /* is_chord=True, event=UP */
                key = keymap_n::get_key(layerNumber, switch1, switch1);
                #ifdef DEBUG
                Serial.println("translation_service_layer: chord, up");
                #endif
            } else if (
                    !protokey_event->is_chord &&
                    protokey_event->event == switch_board_n::event_t::UP) {
                /* is_chord=False, event=UP */
                // TODO kick the dog
                #ifdef DEBUG
                Serial.println("translation_service_layer: nochord, up");
                #endif
                break;
            } else if (
                    protokey_event->is_chord &&
                    protokey_event->event == switch_board_n::event_t::DOWN) {
                /* is_chord=True, event=DOWN */
                // only send if this is a purely chorded switch
                bool chorded = true;
                for (uint8_t i = 0; i < N_SWITCHES; i++) {
                    if (keymap_n::get_key(layerNumber, switch1, i) == key_t::K_NOP) {
                        chorded = false;
                    }
                }
                #ifdef DEBUG
                Serial.println("translation_service_layer: chord, down");
                #endif
                if (chorded) {
                    key = keymap_n::get_key(layerNumber, switch1, switch1);
                } else {
                    break;
                }
            } else if (
                    !protokey_event->is_chord &&
                    protokey_event->event == switch_board_n::event_t::DOWN) {
                /* is_chord=False, event=DOWN */
                // only send if this is a non-chorded switch
                bool non_chorded = true;
                for (uint8_t i = 0; i < N_SWITCHES; i++) {
                    if (
                            i != switch1 &&
                            keymap_n::get_key(layerNumber, switch1, i) != key_t::K_NOP) {
                        non_chorded = false;
                    }
                }
                #ifdef DEBUG
                Serial.println("translation_service_layer: nochord, down");
                #endif
                if (non_chorded) {
                    key = keymap_n::get_key(layerNumber, switch1, switch1);
                } else {
                    break;
                }
            }
            send_key(key, protokey_event->event);
            break;
        }
        case 2: {
            /*
             * What we do here depends on a number of factors.
             * Is the event chorded?
             * Is the switch combo chorded or non chorded?
             */

            /*
             * Get the switch which was pressed or released last
             */
            tmp = protokey_event->switch_event->state_diff();
            if (tmp < 0) {
                // TODO kick watchdog
                break;
            } else {
                switch2 = (uint8_t) tmp;
                #ifdef DEBUG
                Serial.print("translation_service_layer: last activity on switch ");
                Serial.println(switch2);
                #endif
            }

            /*
             * switch_event.get_active_switch does nothing with
             * the order in which switches are pressed. So we need to
             * make sure we don't have the wrong one.
             */
            tmp = protokey_event->switch_event->get_active_switch(1);
            if (tmp < 0) {
                // TODO kick watchdog
                break;
            } else {
                switch1 = (uint8_t) tmp;
            }
            if (switch1 == switch2) {
                tmp = protokey_event->switch_event->get_active_switch(2);
                if (tmp < 0) {
                    // TODO kick watchdog
                    break;
                } else {
                    switch1 = (uint8_t) tmp;
                }
            }
            key_t key_1_first = keymap_n::get_key(layerNumber, switch1, switch2);
            key_t key_2_first = keymap_n::get_key(layerNumber, switch2, switch1);
            if (key_1_first == key_2_first) {
                // This is easy, it's a chord!
                send_key(key_1_first, protokey_event->event);
                break;
            }
            /*
             * Hybrid behavior, act as if switch2 was pressed alone
             */
            key = keymap_n::get_key(layerNumber, switch2, switch2);
            send_key(key, protokey_event->event);
            break;
        }
        default: {
            /* 3 or more switches are active.
             * We either need to reset, or act as if these are non-chorded
             * keys. Since send_key will check for reset,
             * we can act as if there's just a single switch active.
             */
            tmp = protokey_event->switch_event->state_diff();
            if (tmp < 0) {
                // TODO kick watchdog
                break;
            } else {
                switch1 = (uint8_t) tmp;
            }
            key = keymap_n::get_key(layerNumber, switch1, switch1);
            send_key(key, protokey_event->event);
            break;
        }
    }
}

void TranslationService::set_modifier(key_t key) {
    uint8_t index;
    switch (key) {
        case key_t::K_SHIFT: {
            index = I_SHIFT;
            break;
        }
        case key_t::K_SHIFT_L: {
            index = I_SHIFT_L;
            break;
        }
        case key_t::K_SHIFT_R: {
            index = I_SHIFT_R;
            break;
        }
        case key_t::K_CTRL: {
            index = I_CTRL;
            break;
        }
        case key_t::K_CTRL_L: {
            index = I_CTRL_L;
            break;
        }
        case key_t::K_CTRL_R: {
            index = I_CTRL_R;
            break;
        }
        case key_t::K_ALT: {
            index = I_ALT;
            break;
        }
        case key_t::K_ALT_L: {
            index = I_ALT_L;
            break;
        }
        case key_t::K_ALT_R: {
            index = I_ALT_R;
            break;
        }
        case key_t::K_GUI: {
            index = I_GUI;
            break;
        }
        case key_t::K_GUI_L: {
            index = I_GUI_L;
            break;
        }
        case key_t::K_GUI_R: {
            index = I_GUI_R;
            break;
        }
        case key_t::K_CAPSLOCK: {
            index = I_CAPS_LOCK;
            break;
        }
    }
    if (modState[index] == modifier_t::IDLE) {
        modState[index] = modifier_t::ACTIVE;
        #ifdef DEBUG
        Serial.println("translation_service: set mod to active");
        #endif
    } else if (modState[index] == modifier_t::ACTIVE) {
        modState[index] = modifier_t::LAZY;
        #ifdef DEBUG
        Serial.println("translation_service: set mod to lazy");
        #endif
    } else if (modState[index] == modifier_t::LAZY) {
        modState[index] = modifier_t::IDLE;
        #ifdef DEBUG
        Serial.println("translation_service: set mod to idle");
        #endif
    } else {
        // TODO Kick watchdog
        #ifdef DEBUG
        Serial.println("translation_service: unknown modifier state");
        #endif
    }
    send_modifiers(false);
}

void TranslationService::send_modifiers(bool tmp_shift) {
    uint16_t mods = 0;
    // shifts
    if (modState[I_SHIFT] != modifier_t::IDLE or tmp_shift) {
        mods = mods | MODIFIERKEY_SHIFT;
    }
    if (modState[I_SHIFT_L] != modifier_t::IDLE) {
        mods = mods | MODIFIERKEY_LEFT_SHIFT;
    }
    if (modState[I_SHIFT_R] != modifier_t::IDLE) {
        mods = mods | MODIFIERKEY_RIGHT_SHIFT;
    }
    // controls
    if (modState[I_CTRL] != modifier_t::IDLE or tmp_shift) {
        mods = mods | MODIFIERKEY_CTRL;
    }
    if (modState[I_CTRL_L] != modifier_t::IDLE) {
        mods = mods | MODIFIERKEY_LEFT_CTRL;
    }
    if (modState[I_CTRL_R] != modifier_t::IDLE) {
        mods = mods | MODIFIERKEY_RIGHT_CTRL;
    }
    // alts
    if (modState[I_ALT] != modifier_t::IDLE or tmp_shift) {
        mods = mods | MODIFIERKEY_ALT;
    }
    if (modState[I_ALT_L] != modifier_t::IDLE) {
        mods = mods | MODIFIERKEY_LEFT_ALT;
    }
    if (modState[I_ALT_R] != modifier_t::IDLE) {
        mods = mods | MODIFIERKEY_RIGHT_ALT;
    }
    // guis
    if (modState[I_GUI] != modifier_t::IDLE or tmp_shift) {
        mods = mods | MODIFIERKEY_GUI;
    }
    if (modState[I_GUI_L] != modifier_t::IDLE) {
        mods = mods | MODIFIERKEY_LEFT_GUI;
    }
    if (modState[I_GUI_R] != modifier_t::IDLE) {
        mods = mods | MODIFIERKEY_RIGHT_GUI;
    }
    // caps_lock is not technically a modifier, we just put it here
    // for the led effects
    #ifdef DEBUG
    Serial.print("translation_service: sending modifiers ");
    Serial.println(mods);
    #endif
    Keyboard.set_modifier(mods);
    Keyboard.send_now();
}

void TranslationService::use_modifiers() {
    #ifdef DEBUG
    Serial.println("translation_service: eat up a modifier");
    #endif
    for (uint8_t i = 0; i < NUM_MODIFIERS; i++) {
        if (modState[i] == modifier_t::ACTIVE) {
            modState[i] = modifier_t::IDLE;
        }
    }
    send_modifiers(false);
}

} // namespace translation_service_n

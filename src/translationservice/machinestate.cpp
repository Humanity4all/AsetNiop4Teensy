/*
Copyright 2016 Stichting Humanity4all
*/

#include "./machinestate.h"

namespace translation_service_n {

Layer::Layer(int layer) {
    layerNumber = layer;
}

void Layer::process_protokey_event(
        Machine& machine,
        switch_board_n::protokey_event_t* protokey_event) {
    int switch1;
    int switch2;
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
            switch1 = protokey_event->switch_event->get_active_switch(1);
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
                for (int i = 0; i < N_SWITCHES; i++) {
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
                for (int i = 0; i < N_SWITCHES; i++) {
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
            machine.send_key(key, protokey_event->event);
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
            switch2 = protokey_event->switch_event->state_diff();
            #ifdef DEBUG
            Serial.print("translation_service_layer: last activity on switch ");
            Serial.println(switch2);
            #endif
            if (switch2 < 0) {
                // TODO kick dog
                break;
            }

            /*
             * switch_event.get_active_switch does nothing with
             * the order in which switches are pressed. So we need to
             * make sure we don't have the wrong one.
             */
            switch1 = protokey_event->switch_event->get_active_switch(0);
            if (switch1 == switch2) {
                switch1 = protokey_event->switch_event->get_active_switch(1);
            }
            key_t key_1_first = keymap_n::get_key(layerNumber, switch1, switch2);
            key_t key_2_first = keymap_n::get_key(layerNumber, switch2, switch1);
            if (key_1_first == key_2_first) {
                // This is easy, it's a chord!
                machine.send_key(key_1_first, protokey_event->event);
                break;
            }
            /*
             * Hybrid behavior, act as if switch2 was pressed alone
             */
            key = keymap_n::get_key(layerNumber, switch2, switch2);
            machine.send_key(key, protokey_event->event);
            break;
        }
        default: {
            /* 3 or more switches are active.
             * We either need to reset, or act as if these are non-chorded
             * keys. Since machine.send_key will check for reset,
             * we can act as if there's just a single switch active.
             */
            switch1 = protokey_event->switch_event->state_diff();
            key = keymap_n::get_key(layerNumber, switch1, switch1);
            machine.send_key(key, protokey_event->event);
            break;
        }
    }
    delete protokey_event->switch_event;
}

} // namespace translation_service_n

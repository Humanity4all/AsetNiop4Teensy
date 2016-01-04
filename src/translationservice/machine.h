/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_TRANSLATIONSERVICE_MACHINE_H_
#define SRC_TRANSLATIONSERVICE_MACHINE_H_

#include "Arduino.h"

#include "../globals.h"
#include "./typedefs.h"
#include "./machinestate.h"
#include "../switchboard/typedefs.h"
#include "../keymap/getkey.h"

namespace translation_service_n {

class Layer;

class Machine {
 public:
    Machine();
    void process_protokey_event(
        switch_board_n::protokey_event_t* protokey_event);
    void change_state(Layer* new_state);
    void send_key(key_t key, switch_board_n::event_t event);
    void set_modifier(key_t key);
    int* use_modifiers();
 private:
    Layer* currentState;
};

} // namespace translation_service_n

#endif // SRC_TRANSLATIONSERVICE_MACHINE_H_

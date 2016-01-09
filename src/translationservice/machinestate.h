/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_TRANSLATIONSERVICE_MACHINESTATE_H_
#define SRC_TRANSLATIONSERVICE_MACHINESTATE_H_

#include "Arduino.h"

#include "../globals.h"
#include "./typedefs.h"
#include "./sendkey.h"
#include "../switchboard/typedefs.h"
#include "../keymap/getkey.h"

namespace translation_service_n {

class Layer {
 public:
     Layer();
     ~Layer();
     bool isActive;
    explicit Layer(uint8_t layer);
    void process_protokey_event(
        switch_board_n::protokey_event_t* protokey_event);
 private:
    uint8_t layerNumber;
};

} // namespace translation_service_n

#endif // SRC_TRANSLATIONSERVICE_MACHINESTATE_H_

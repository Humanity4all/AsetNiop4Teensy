/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_TRANSLATIONSERVICE_MACHINESTATE_H_
#define SRC_TRANSLATIONSERVICE_MACHINESTATE_H_

#include "Arduino.h"

#include "../globals.h"
#include "./machine.h"
#include "./typedefs.h"
#include "../switchboard/typedefs.h"

namespace translation_service_n {

class Machine;

class Layer {
 public:
    explicit Layer(int layer);
    void process_protokey_event(
        Machine& machine,
        switch_board_n::protokey_event_t* protokey_event);
 private:
    int layerNumber;
};

} // namespace translation_service_n

#endif // SRC_TRANSLATIONSERVICE_MACHINESTATE_H_

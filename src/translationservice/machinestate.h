/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_TRANSLATIONSERVICE_MACHINESTATE_H_
#define SRC_TRANSLATIONSERVICE_MACHINESTATE_H_

#include "../globals.h"
#include "./machine.h"
#include "./typedefs.h"
#include "../switchevent/switchevent.h"

namespace translation_service_n {

class Machine;

class AbstractState {
 public:
    virtual void process_key_event(
        Machine machine,
        switch_event::SwitchEvent switch_event,
        bool is_chord,
        bool reset);
 private:
    key_t keyMap[N_SWITCHES][N_SWITCHES];
};

} // namespace translation_service_n

#endif // SRC_TRANSLATIONSERVICE_MACHINESTATE_H_

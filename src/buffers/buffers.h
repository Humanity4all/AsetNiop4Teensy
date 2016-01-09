/*
Copyright 2016 Stichting Humanity4all
*/

#ifndef SRC_BUFFERS_BUFFERS_H_
#define SRC_BUFFERS_BUFFERS_H_

#include "Arduino.h"

#include "../globals.h"
#include "../pininterface/pinstatechange.h"
#include "../switchevent/switchevent.h"
#include "../switchboard/typedefs.h"
#include "../translationservice/machinestate.h"

namespace buffers_n {

/*
 * Buffers, to prevent memory fragmentation
 */

class PinStateChangeBuffer {
 public:
    pin_interface_n::PinStateChange eventBuffer[N_SWITCHES];
    pin_interface_n::PinStateChange* get_free();
    void empty();
};

class SwitchEventBuffer {
 public:
    switch_event_n::SwitchEvent eventBuffer[N_SWITCHES];
    switch_event_n::SwitchEvent* get_free();
    void empty();
};

class LayerBuffer {
 public:
    translation_service_n::Layer layerBuffer[2];
    translation_service_n::Layer* new_layer(uint8_t layer);
};

class ProtokeyEventBuffer {
 public:
    switch_board_n::protokey_event_t eventBuffer[N_SWITCHES];
    switch_board_n::protokey_event_t* get_free();
    void empty();
};

} // namespace buffers_n


#endif // SRC_BUFFERS_BUFFERS_H_

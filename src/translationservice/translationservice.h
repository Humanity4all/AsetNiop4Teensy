/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_TRANSLATIONSERVICE_TRANSLATIONSERVICE_H_
#define SRC_TRANSLATIONSERVICE_TRANSLATIONSERVICE_H_

#include "Arduino.h"

#include "../globals.h"
#include "./typedefs.h"
#include "../buffers/buffers.h"
#include "../switchboard/typedefs.h"
#include "../keymap/getkey.h"

namespace translation_service_n {

class TranslationService {
 public:
    TranslationService();
    void process_protokey_event(
        switch_board_n::protokey_event_t* protokey_event);
    void set_modifier(key_t key);
    void send_modifiers(bool tmp_shift);
    void use_modifiers();
    void send_key(key_t key, switch_board_n::event_t event);
 private:
    uint8_t layerNumber;
    modifier_t modState[NUM_MODIFIERS];
};

} // namespace translation_service_n
#endif // SRC_TRANSLATIONSERVICE_TRANSLATIONSERVICE_H_

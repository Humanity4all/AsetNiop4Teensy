/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_TRANSLATIONSERVICE_TRANSLATIONSERVICE_H_
#define SRC_TRANSLATIONSERVICE_TRANSLATIONSERVICE_H_

#include "Arduino.h"

#include "../globals.h"
#include "./typedefs.h"
#include "./sendkey.h"
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
    int* use_modifiers();
 private:
    uint8_t layerNumber;
};

} // namespace translation_service_n
#endif // SRC_TRANSLATIONSERVICE_TRANSLATIONSERVICE_H_

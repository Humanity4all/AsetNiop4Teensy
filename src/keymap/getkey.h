/*
Copyright 2016 Stichting Humanity4all
*/

#ifndef SRC_KEYMAP_GETKEY_H_
#define SRC_KEYMAP_GETKEY_H_

#include "Arduino.h"
#include <EEPROM.h>

#include "../globals.h"
#include "../translationservice/typedefs.h"

namespace keymap_n {

translation_service_n::key_t get_key(uint8_t layer, uint8_t switch1, uint8_t switch2);

} // namespace keymap_n

#endif // SRC_KEYMAP_GETKEY_H_

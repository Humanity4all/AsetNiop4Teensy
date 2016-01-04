/*
Copyright 2016 Stichting Humanity4all
*/

#ifndef SRC_KEYMAP_INITKEYMAP_H_
#define SRC_KEYMAP_INITKEYMAP_H_

#include "Arduino.h"
#include <EEPROM.h>
#include <SD.h>

#include "../globals.h"
#include "../translationservice/typedefs.h"

namespace keymap_n {

/*
 * init_keymap checks the keymap version in eeprom.
 * if this is different than the version on the sdcard,
 * it copies the sd card contents over to the eeprom.
 */
void init_keymap();

} // namespace keymap_n

#endif // SRC_KEYMAP_INITKEYMAP_H_

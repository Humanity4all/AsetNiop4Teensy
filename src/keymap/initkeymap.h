/*
Copyright 2016 Stichting Humanity4all
*/

#ifndef SRC_KEYMAP_INITKEYMAP_H_
#define SRC_KEYMAP_INITKEYMAP_H_

#include "Arduino.h"
#include <EEPROM.h>
#include <SD.h>

#include "../globals.h"

// TODO: maybe put this in globals, so all the settings are in 1 place
/*
 * addresses of settings in eeprom
 */
#define EEPROM_KEYMAP_VERSION 0

/*
 * Chip select pin for the sd card reader
 */
#define SD_CS_PIN 10

namespace keymap_n {

/*
 * init_keymap checks the keymap version in eeprom.
 * if this is different than the version on the sdcard,
 * it copies the sd card contents over to the eeprom.
 */
void init_keymap();

} // namespace keymap_n

#endif // SRC_KEYMAP_INITKEYMAP_H_

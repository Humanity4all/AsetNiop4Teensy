/*
Copyright 2016 Stichting Humanity4all
*/

#include "./getkey.h"

namespace keymap_n {

translation_service_n::key_t get_key(int switch1, int switch2) {
    // TODO kick watchdog if switch1 or switch2 >= N_SWITCHES
    int address = switch1 * N_SWITCHES + switch2 + EEPROM_SETTINGS_OFFSET;
    return (translation_service_n::key_t) EEPROM.read(address);
}

} // namespace keymap_n

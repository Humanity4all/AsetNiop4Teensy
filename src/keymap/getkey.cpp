/*
Copyright 2016 Stichting Humanity4all
*/

#include "./getkey.h"

namespace keymap_n {

translation_service_n::key_t get_key(int layer, int switch1, int switch2) {
    // TODO kick watchdog if switch1 or switch2 >= N_SWITCHES
    int address =
        layer * N_SWITCHES * N_SWITCHES +
        switch1 * N_SWITCHES +
        switch2 +
        EEPROM_SETTINGS_OFFSET;
    using translation_service_n::key_t;
    key_t key = (key_t)EEPROM.read(address);
    #ifdef DEBUG
    Serial.print("get_key: address=");
    Serial.print(address);
    Serial.print(", key=");
    Serial.print(key);
    Serial.print(", num=");
    Serial.println(EEPROM.read(address));
    #endif
    return key;
}

} // namespace keymap_n

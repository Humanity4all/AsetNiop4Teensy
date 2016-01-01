/*
Copyright 2016 Stichting Humanity4all
*/

#include "./initkeymap.h"

namespace keymap_n {

void init_keymap() {
    uint8_t keymap_version = EEPROM.read(EEPROM_KEYMAP_VERSION);
    /*
     * turn on sd card reader by setting chip select pin to low,
     * it will now listen on the spi interface.
     */
    pinMode(SD_CS_PIN, OUTPUT);
    digitalWrite(SD_CS_PIN, LOW);

    if (!SD.begin(SD_CS_PIN)) {
        #ifdef DEBUG
        Serial.println("initkeymap.cpp: error initializing SD");
        #endif
    }

    if (!SD.exists("keymap")) {
        #ifdef DEBUG
        Serial.println("initkeymap.cpp: file 'keymap' does not exist");
        #endif
        return;
    }

    File keymap = SD.open("keymap", FILE_READ);
    if (!keymap) {
        #ifdef DEBUG
        Serial.println("initkenmap.cpp: error opening file 'keymap'");
        #endif
    }

    uint8_t sd_keymap_version =  keymap.read();

    if (sd_keymap_version != keymap_version) {
        /*
         * we've just read address 0 (the keymap version), so now
         * we start counting from 1.
         */
        int address = 1;
        while (keymap.available()) {
            // write to eeprom
            EEPROM.update(address, keymap.read());
            address++;
        }
    }
    keymap.close();
    /*
     * disable the sd reader by setting chip select pin to high,
     * this frees up the spi interface for other use.
     */
    digitalWrite(SD_CS_PIN, HIGH);
}

} // namespace keymap_n

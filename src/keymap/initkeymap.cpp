/*
Copyright 2016 Stichting Humanity4all
*/

#include "./initkeymap.h"

namespace keymap_n {
uint16_t get_address(uint8_t layer, uint8_t switch1, uint8_t switch2) {
    /*
     * calculate eeprom address
     */
    return layer * N_SWITCHES * N_SWITCHES +
        switch1 * N_SWITCHES +
        switch2 +
        EEPROM_SETTINGS_OFFSET;
}

void init_keymap() {
    uint8_t keymap_version = EEPROM.read(EEPROM_KEYMAP_VERSION);
    /*
     * turn on sd card reader by setting chip select pin to low,
     * it will now listen on the spi interface.
     */
    pinMode(SD_CS_PIN, OUTPUT);
    digitalWrite(SD_CS_PIN, LOW);
    delay(20);

    if (!SD.begin(SD_CS_PIN)) {
        #ifdef DEBUG
        Serial.println("initkeymap.cpp: error initializing SD");
        #endif
        #ifdef INITKEYMAP
        /*
         * During testing, we can't always rely on the sd reader.
         * Read: we're having issues, we can't solve them right
         * away because we don't have the right hardware, and
         * we want to continue testing anyway.
         *
         * So we're writing a basic keymap to the eeprom manually.
         * We assume there's 3 switches in this testing keyboard.
         */
        EEPROM.update(EEPROM_KEYMAP_VERSION, 0);

        using translation_service_n::key_t;

        // Layer 0
        // First, handle the single switch presses
        EEPROM.update(get_address(0, 0, 0), (uint8_t)key_t::K_SHIFT);
        EEPROM.update(get_address(0, 1, 1), (uint8_t)key_t::K_LAYER_1);
        EEPROM.update(get_address(0, 2, 2), (uint8_t)key_t::K_C);

        // Now the chords, let's make this a purely chorded layer
        EEPROM.update(get_address(0, 0, 1), (uint8_t)key_t::K_D);
        EEPROM.update(get_address(0, 1, 0), (uint8_t)key_t::K_D);
        EEPROM.update(get_address(0, 0, 2), (uint8_t)key_t::K_E);
        EEPROM.update(get_address(0, 2, 0), (uint8_t)key_t::K_E);
        EEPROM.update(get_address(0, 1, 2), (uint8_t)key_t::K_F);
        EEPROM.update(get_address(0, 2, 1), (uint8_t)key_t::K_F);

        // Layer 1
        // First, handle the single switch presses
        EEPROM.update(get_address(0, 0, 0), (uint8_t)key_t::K_SHIFT);
        EEPROM.update(get_address(0, 1, 1), (uint8_t)key_t::K_LAYER_0);
        EEPROM.update(get_address(0, 2, 2), (uint8_t)key_t::K_A);

        // Now the chords, let's make this a purely chorded layer
        EEPROM.update(get_address(0, 0, 1), (uint8_t)key_t::K_B);
        EEPROM.update(get_address(0, 1, 0), (uint8_t)key_t::K_B);
        EEPROM.update(get_address(0, 0, 2), (uint8_t)key_t::K_G);
        EEPROM.update(get_address(0, 2, 0), (uint8_t)key_t::K_G);
        EEPROM.update(get_address(0, 1, 2), (uint8_t)key_t::K_H);
        EEPROM.update(get_address(0, 2, 1), (uint8_t)key_t::K_H);



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
        uint16_t address = 1;
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

/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#define N_SWITCHES 3
/*
 * This tells us which pins correspond to switches.
 * It's assumed that left-most value corresponds to the
 * left pinky, the thumbs are in the middle, and the right
 * pinky is the last value.
 */
#define SWITCH_PINS 0, 1, 2

#ifndef LED_PIN
  #define LED_PIN 13
#endif

/*
 * Mouse pins
 */
#define VRX A2
#define VRY A3
#define MOUSE_SWITCH 18

/*
 * Turns on the serial monitor and prints debug messages.
 * For production, turn this off. It's a waste of resources.
 */
#ifndef DEBUG
  #define DEBUG
#endif

/*
 * This turns on writing a basic keymap to eeprom if there's no sd
 * card present.
 */
#define INITKEYMAP

/*
 * eeprom settings
 */

/*
 * The first 100 addresses are reserved for settings
 */
#define EEPROM_SETTINGS_OFFSET 100

/*
 * Address where keymap version is stored
 */
#define EEPROM_KEYMAP_VERSION 0


/*
 * Chip select pin for the sd card reader
 */
#define SD_CS_PIN 10


#endif // SRC_GLOBALS_H_

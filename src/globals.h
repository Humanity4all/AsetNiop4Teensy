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
 * Fix unimplemented errors for calling template functions with unrestricted
 * arguments (read: we got in trouble with the event queues)
 */
extern "C" {
    int _getpid() { return -1; }
    int _kill(int pid, int sig) { return -1; }
    int _write() { return -1; }
}

#endif // SRC_GLOBALS_H_

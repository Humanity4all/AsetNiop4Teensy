/*
Copyright 2015 Stichting Humanity4all
*/

#ifdef ENERGIA
  #include "Energia.h"
#else
  #include "Arduino.h"
#endif

#ifndef LED_PIN
  // Most Arduino boards already have a LED attached to pin 13 on the board itself
  #define LED_PIN 13
#endif

#define BOUNCE_LOCK_OUT
#include <Bounce2.h>

#include "./typedefs.h"

#define N_KEYS 4
#define DEBUG

Bounce debugkey;

keyboard_t k;

void setup() {
    pinMode(LED_PIN, OUTPUT);     // set pin as output
    // our meager debug key - just so we know it's doing something
    pinMode(0, INPUT_PULLUP);
    debugkey.attach(0);
    debugkey.interval(10);

    // now the real setup
    // debug("Initializing...");
    // TODO set pins to use from left to right (counting thumbs)
    int pinsToUse[N_KEYS]={1, 2, 3, 4};
    for (int i=0; i < N_KEYS; i++) {
        int pin = pinsToUse[i];
        pinMode(pin, INPUT_PULLUP);
        // debug("--set pinmode to pullup");

        /*
        cpplint: using C-style cast because cpp style cast
        results in compiler errors
        */
        k.keys[i] = (Bounce *)malloc(sizeof(Bounce)); // NOLINT
        *k.keys[i] = Bounce();
        k.keys[i]->attach(pin);
        k.keys[i]->interval(10);
        // debug("--initialized bounce object");
        k.keyState[i] = IDLE;
        // debug("--set keystate to idle");
    }

    // debug("Finished initializing");
}

void loop() {

    // check if it's responding at all
    if (debugkey.update()) {
        if (debugkey.read() == 0) digitalWrite(LED_PIN, HIGH); // pressed
        if (debugkey.read() == 1) digitalWrite(LED_PIN, LOW);  // released
    }
}

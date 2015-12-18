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
#include <stdlib.h>
#include <Bounce2.h>
#include <queue>

#include "./globals.h"
#include "./switchboard/machine.h"
#include "./switchboard/typedefs.h"
#include "./switchevent/switchevent.h"
#include "./pininterface/pininterface.h"


extern "C" {
    int _getpid() { return -1; }
    int _kill(int pid, int sig) { return -1; }
    int _write() { return -1; }
}

Bounce debugkey;
std::queue<switch_event_n::SwitchEvent> switch_event_queue;
std::queue<switch_board_n::protokey_event_t> protokey_event_queue;

pin_interface_n::PinInterface pin_interface;
switch_board_n::Machine switch_board;

void setup() {
    #ifdef DEBUG
      Serial.begin(38400);
    #endif
    pinMode(LED_PIN, OUTPUT);     // set pin as output
    // our meager debug key - just so we know it's doing something
    // pinMode(0, INPUT_PULLUP);
    // debugkey.attach(0);
    // debugkey.interval(10);

    pin_interface.init_pins();

    // thumbstick initialization
    pinMode(MOUSE_SWITCH, INPUT_PULLUP);
    Mouse.begin();

    /*
     * Test eventqueue - because we keep getting errors
     */
    /*switch_event_n::switch_state_t tmp1[N_SWITCHES] = {
        switch_event_n::switch_state_t::RELEASED,
        switch_event_n::switch_state_t::RELEASED,
        switch_event_n::switch_state_t::RELEASED};
    switch_event_n::switch_state_t tmp2[N_SWITCHES] = {
        switch_event_n::switch_state_t::PRESSED,
        switch_event_n::switch_state_t::RELEASED,
        switch_event_n::switch_state_t::RELEASED};

    switch_event_queue.emplace(tmp1, tmp2);*/
}

void loop() {

    // check if it's responding at all
    // if (debugkey.update()) {
    //    if (debugkey.read() == 0) digitalWrite(LED_PIN, HIGH); // pressed
    //    if (debugkey.read() == 1) digitalWrite(LED_PIN, LOW);  // released
    // }
    pin_interface.update(switch_event_queue);
    while (!switch_event_queue.empty()) {
        switch_event_n::SwitchEvent e = switch_event_queue.front();
        int active_switch = e.get_active_switch(1);
        if (active_switch == 1) digitalWrite(LED_PIN, HIGH);
        #ifdef DEBUG
          Serial.print("main.cpp: Key event for switch ");
          Serial.println(active_switch);
          Serial.print("main.cpp: Number of active switches: ");
          Serial.println(e.count_active());
        #endif
        switch_board.process_switch_event(&e, protokey_event_queue);
        switch_event_queue.pop();
    }
    if (!switch_event_queue.empty()) {
        #ifdef DEBUG
          Serial.println("main.cpp: Error, switch_event_queue not empty!");
        #endif
    }

    /*
     * Mouse logic
     */
    /*Serial.print("vrx: ");
    Serial.println(analogRead(VRX));
    Serial.print("vry: ");
    Serial.println(analogRead(VRY));
    Serial.print("sw: ");
    Serial.println(digitalRead(MOUSE_SWITCH));*/
    int vrx = analogRead(VRX) - 512;
    int vry = analogRead(VRY) - 512;
    if (abs(vrx) <= 50) vrx = 0;
    if (abs(vry) <= 50) vry = 0;
    vrx = vrx/150;
    vry = vry/150;
    if (abs(vrx) > 0 || abs(vry) > 0) {
        Mouse.move(vrx, vry, 0);
    }
}

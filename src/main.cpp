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
#include "./buffers/buffers.h"
#include "./queue/queue.h"
#include "./keymap/initkeymap.h"
#include "./switchboard/machine.h"
#include "./switchboard/typedefs.h"
#include "./switchevent/switchevent.h"
#include "./pininterface/pininterface.h"
#include "./translationservice/translationservice.h"


extern "C" {
    int _getpid() { return -1; }
    int _kill(int pid, int sig) { return -1; }
    int _write() { return -1; }
}

buffers_n::SwitchEventBuffer switch_event_buffer;
buffers_n::ProtokeyEventBuffer protokey_event_buffer;

Bounce debugkey;
queue_n::SwitchEventQueue switch_event_queue;
std::queue<switch_board_n::protokey_event_t*> protokey_event_queue;

pin_interface_n::PinInterface pin_interface;
switch_board_n::Machine switch_board;
translation_service_n::TranslationService translation_service;

void setup() {
    #ifdef DEBUG
      Serial.begin(38400);
    #endif

    keymap_n::init_keymap();

    pin_interface.init_pins();

    // thumbstick initialization
    pinMode(MOUSE_SWITCH, INPUT_PULLUP);
    Mouse.begin();
    Keyboard.begin();
}

void loop() {
    pin_interface.update(switch_event_buffer, switch_event_queue);
    while (!switch_event_queue.isEmpty()) {
        switch_event_n::SwitchEvent* e = switch_event_queue.pop();
        switch_board.process_switch_event(e, protokey_event_buffer, protokey_event_queue);
    }
    if (!switch_event_queue.isEmpty()) {
        #ifdef DEBUG
          Serial.println("main.cpp: Error, switch_event_queue not empty!");
        #endif
    }

    /*
     * Now loop through the protokey event queue
     */
    while (!protokey_event_queue.empty()) {
        switch_board_n::protokey_event_t* e = protokey_event_queue.front();
        translation_service.process_protokey_event(e);
        protokey_event_queue.pop();
    }

    /*
     * empty event buffers
     * No event should carry over to the next loop
     */
    switch_event_buffer.empty();
    protokey_event_buffer.empty();

    /*
     * Mouse logic
     */
    int16_t vrx = analogRead(VRX) - 512;
    int16_t vry = analogRead(VRY) - 512;
    if (abs(vrx) <= 50) vrx = 0;
    if (abs(vry) <= 50) vry = 0;
    vrx = vrx/150;
    vry = vry/150;
    if (abs(vrx) > 0 || abs(vry) > 0) {
        Mouse.move(vrx, vry, 0);
    }
}

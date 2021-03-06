/*
Copyright 2016 Stichting Humanity4all
*/

#ifndef SRC_QUEUE_QUEUE_H_
#define SRC_QUEUE_QUEUE_H_

#include "Arduino.h"
#include "../globals.h"
#include "../switchevent/switchevent.h"
#include "../switchboard/typedefs.h"

namespace queue_n {

class SwitchEventQueue {
 public:
    SwitchEventQueue();
    switch_event_n::SwitchEvent* pop();
    void push(switch_event_n::SwitchEvent* switch_event);
    bool isEmpty();
 private:
    switch_event_n::SwitchEvent* circularBuffer[N_SWITCHES];
    uint8_t start;
    uint8_t end;
};

class ProtokeyEventQueue {
 public:
    ProtokeyEventQueue();
    switch_board_n::protokey_event_t* pop();
    void push(switch_board_n::protokey_event_t* protokey_event);
    bool isEmpty();
 private:
    switch_board_n::protokey_event_t* circularBuffer[N_SWITCHES];
    uint8_t start;
    uint8_t end;
};

} // namespace queue_n
#endif // SRC_QUEUE_QUEUE_H_

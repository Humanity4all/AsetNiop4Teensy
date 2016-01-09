/*
Copyright 2016 Stichting Humanity4all
*/

#include "./queue.h"

namespace queue_n {

SwitchEventQueue::SwitchEventQueue() {
    start = 0;
    end = 0;
}

switch_event_n::SwitchEvent* SwitchEventQueue::pop() {
    if (!isEmpty()) {
        switch_event_n::SwitchEvent* event = circularBuffer[start];
        start++;
        if (start >= N_SWITCHES) {
            start = 0;
        }
        return event;
    } else {
        // You can't pop something which is empty!
        // TODO: Kick watchdog
        #ifdef DEBUG
        Serial.println("switcheventqueue: trying to pop() an empty queue!");
        #endif
    }
}

void SwitchEventQueue::push(switch_event_n::SwitchEvent* switch_event) {
    circularBuffer[end] = switch_event;
    end++;
    if (end >= N_SWITCHES) {
        end = 0;
    }
}

bool SwitchEventQueue::isEmpty() {
    if (start == end) {
        return true;
    } else {
        return false;
    }
}

ProtokeyEventQueue::ProtokeyEventQueue() {
    start = 0;
    end = 0;
}

switch_board_n::protokey_event_t* ProtokeyEventQueue::pop() {
    if (!isEmpty()) {
        switch_board_n::protokey_event_t* event = circularBuffer[start];
        start++;
        if (start >= N_SWITCHES) {
            start = 0;
        }
        return event;
    } else {
        // You can't pop when there's nothing here...
        // TODO: kick watchdog
        #ifdef DEBUG
        Serial.println("protokeyeventqueue: trying to pop() an empty queue!");
        #endif
    }
}

void ProtokeyEventQueue::push(switch_board_n::protokey_event_t* protokey_event) {
    circularBuffer[end] = protokey_event;
    end++;
    if (end >= N_SWITCHES) {
        end = 0;
    }
}

bool ProtokeyEventQueue::isEmpty() {
    if (start == end) {
        return true;
    } else {
        return false;
    }
}

} // namespace queue_n

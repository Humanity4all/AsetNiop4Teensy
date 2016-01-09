/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHBOARD_MACHINESTATES_H_
#define SRC_SWITCHBOARD_MACHINESTATES_H_

#include "../globals.h"
#include "./machine.h"
#include "./typedefs.h"
#include "../buffers/buffers.h"
#include "../queue/queue.h"
#include "../switchevent/switchevent.h"

#ifdef DEBUG
  #include "Arduino.h"
#endif

namespace switch_board_n {

class Machine;

class AbstractState {
 public:
    virtual void press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual void release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual ~AbstractState();
};

class Idle : public AbstractState {
 public:
    virtual void press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual void release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual ~Idle();
};

class OneSwitch : public AbstractState {
 public:
    virtual void press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual void release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual ~OneSwitch();
};

class OneSwitchUsed: public AbstractState {
 public:
    virtual void press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual void release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual ~OneSwitchUsed();
};

class TwoSwitch : public AbstractState {
 public:
    virtual void press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual void release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual ~TwoSwitch();
};

class ManySwitch : public AbstractState {
 public:
    virtual void press(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual void release(
        Machine& machine,
        switch_event_n::SwitchEvent* switch_event,
        buffers_n::ProtokeyEventBuffer & protokey_event_buffer,
        queue_n::ProtokeyEventQueue & protokey_event_queue);
    virtual ~ManySwitch();
};


} // namespace switch_board_n





#endif // SRC_SWITCHBOARD_MACHINESTATES_H_

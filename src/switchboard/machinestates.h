/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHBOARD_MACHINESTATES_H_
#define SRC_SWITCHBOARD_MACHINESTATES_H_

#include "../globals.h"
#include "./machine.h"
#include "../switchevent/switchevent.h"

namespace switch_board {

class Machine;

class AbstractState {
 public:
    virtual void press(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual void release(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual ~AbstractState();
};

class Idle : public AbstractState {
 public:
    virtual void press(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual void release(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual ~Idle();
};

class OneSwitch : public AbstractState {
 public:
    virtual void press(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual void release(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual ~OneSwitch();
};

class TwoSwitch : public AbstractState {
 public:
    virtual void press(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual void release(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual ~TwoSwitch();
};

class ManySwitch : public AbstractState {
 public:
    virtual void press(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual void release(Machine& machine, switch_event::SwitchEvent switch_event);
    virtual ~Invalid();
};


} // namespace switch_board





#endif // SRC_SWITCHBOARD_MACHINESTATES_H_
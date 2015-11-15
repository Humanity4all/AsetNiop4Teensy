/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHBOARDSTATEMACHINE_MACHINESTATES_H_
#define SRC_SWITCHBOARDSTATEMACHINE_MACHINESTATES_H_

#include "switchboardstatemachine/machine.h"
#include "./typedefs.h"

namespace switch_board_state_machine {

class Machine;

class AbstractState {
 public:
    virtual void press(Machine& machine, int n_switch);
    virtual void release(Machine& machine, int n_switch);
    virtual ~AbstractState();
 protected:
    void set_state(Machine& machine, AbstractState* st);
    void update_switch_vector(Machine& machine, switch_vector_t switch_vector);
};

class Idle : public AbstractState {
 public:
    virtual void press(Machine& machine, int n_switch);
    virtual void release(Machine& machine, int n_switch);
    virtual ~Idle();
};

class OneSwitch : public AbstractState {
 public:
    virtual void press(Machine& machine, int n_switch);
    virtual void release(Machine& machine, int n_switch);
    virtual ~OneSwitch();
};

class TwoSwitch : public AbstractState {
 public:
    virtual void press(Machine& machine, int n_switch);
    virtual void release(Machine& machine, int n_switch);
    virtual ~TwoSwitch();
};

class Invalid : public AbstractState {
 public:
    virtual void press(Machine& machine, int n_switch);
    virtual void release(Machine& machine, int n_switch);
    virtual ~Invalid();
}


} // namespace switch_board_state_machine





#endif // SRC_SWITCHBOARDSTATEMACHINE_MACHINESTATES_H_
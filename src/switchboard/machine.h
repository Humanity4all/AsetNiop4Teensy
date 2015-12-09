/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHBOARDSTATEMACHINE_MACHINE_H_
#define SRC_SWITCHBOARDSTATEMACHINE_MACHINE_H_

#include "./machinestates.h"
#include "../switchvector/switchvector.h"

namespace switch_board_state_machine {

class AbstractState;

class Machine {
    friend class AbstractState;
 public:
    Machine();
    void press(int n_key);
    void release(int n_key);
    int get_current_switch_vector();
    ~Machine();
 private:
    switch_vector::SwitchVector switchVector;
    AbstractState* mState;
};


} // namespace switch_board_state_machine

#endif // SRC_SWITCHBOARDSTATEMACHINE_MACHINE_H_

/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHBOARDSTATEMACHINE_MACHINE_H_
#define SRC_SWITCHBOARDSTATEMACHINE_MACHINE_H_

#include "./machinestates.h"

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
    int switchVectot;
    AbstractState* mState;
};


} // namespace switch_board_state_machine

#endif // SRC_SWITCHBOARDSTATEMACHINE_MACHINE_H_

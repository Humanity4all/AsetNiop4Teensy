/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHEVENT_SWITCHEVENT_H_
#define SRC_SWITCHEVENT_SWITCHEVENT_H_

#include "Arduino.h"

#include "../globals.h"
#ifdef DEBUG
  #include "../printswitchstate.h"
#endif
#include "./typedefs.h"

namespace switch_event_n {


class SwitchEvent {
 public:
    SwitchEvent(
        switch_state_t new_switch_state[N_SWITCHES],
        switch_state_t old_switch_state[N_SWITCHES]);
    void new_event(
        switch_state_t new_switch_state[N_SWITCHES],
        SwitchEvent* return_event);
    int count_active();
    int get_active_switch(int n=1);
    int state_diff();
    ~SwitchEvent();
    edge_t edge;
 private:
    void update_effective_switch_state();
    switch_state_t oldSwitchState[N_SWITCHES];
    switch_state_t newSwitchState[N_SWITCHES];
    switch_state_t effectiveSwitchState[N_SWITCHES];
};

} // namespace switch_event_n


#endif // SRC_SWITCHEVENT_SWITCHEVENT_H_

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
    SwitchEvent();
    SwitchEvent(
        switch_state_t new_switch_state[N_SWITCHES],
        switch_state_t old_switch_state[N_SWITCHES]);
    void new_event(
        switch_state_t new_switch_state[N_SWITCHES],
        SwitchEvent* return_event);
    uint8_t count_active();
    int8_t get_active_switch(uint8_t n=1);
    int8_t state_diff();
    ~SwitchEvent();
    /* State of the changed switch */
    switch_state_t switch_state;
    bool isActive;
 private:
    void update_effective_switch_state();
    switch_state_t oldSwitchState[N_SWITCHES];
    switch_state_t newSwitchState[N_SWITCHES];
    switch_state_t effectiveSwitchState[N_SWITCHES];
};

} // namespace switch_event_n


#endif // SRC_SWITCHEVENT_SWITCHEVENT_H_

/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHEVENT_SWITCHEVENT_H_
#define SRC_SWITCHEVENT_SWITCHEVENT_H_

#include "../globals.h"
#include "./typedefs.h"

namespace switch_event_n {

typedef enum switch_state_t {
    PRESSED, RELEASED,
} key_state_t;

class SwitchEvent {
 public:
    SwitchEvent();
    void new_event(switch_state_t new_switch_state, SwitchEvent* return_event);
    int count_active();
    int get_active_switch(int n=1);
    int state_diff();
    ~SwitchEvent();
    edge_t edge;
 private:
    void update_effective_switch_state();
    const switch_state_t oldSwitchState[N_SWITCHES];
    const switch_state_t newSwitchState[N_SWITCHES];
    const switch_state_t effectiveSwitchState[N_SWITCHES];
};

} // namespace switch_event_n


#endif // SRC_SWITCHEVENT_SWITCHEVENT_H_

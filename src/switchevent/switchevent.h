/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_SWITCHEVENT_SWITCHEVENT_H_
#define SRC_SWITCHEVENT_SWITCHEVENT_H_

#define N_SWITCHES 4

namespace switch_event {

typedef enum switch_state_t {
    PRESSED, RELEASED,
} key_state_t;

class SwitchEvent {
 public:
    SwitchEvent();
    private void update_effective_switch_state();
    void new_event(switch_state_t new_switch_state);
    int count_active();
    int get_active_switch(int n=1);
    int state_diff();
    ~SwitchEvent();
 private:
    const switch_state_t oldSwitchState[N_SWITCHES];
    const switch_state_t newSwitchState[N_SWITCHES];
    const switch_state_t effectiveSwitchState[N_SWITCHES];
};

} // namespace switch_event


#endif // SRC_SWITCHEVENT_SWITCHEVENT_H_

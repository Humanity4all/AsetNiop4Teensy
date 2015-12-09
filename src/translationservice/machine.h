/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_TRANSLATIONSERVICE_MACHINE_H_
#define SRC_SWITCHBOARD_MACHINE_H_

#include "./typedefs.h"
#include "./machinestates.h"

namespace translation_service {

class AbstractState;

class Machine {
    public:
      Machine();
      void process_protokey_event(protokey_event_t protokey_event);
      void change_state(AbstractState new_state);
      void send_key(key_t key, event_t event);
      void set_modifier(key_t key);
      int[] use_modifiers();
    private:
      AbstractState currentState;
};

} // namespace translation_service

#endif // SRC_TRANSLATION_SERVICE_MACHINE_H_

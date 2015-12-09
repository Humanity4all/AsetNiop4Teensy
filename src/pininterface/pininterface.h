/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_PININTERFACE_PININTERFACE_H_
#define SRC_PININTERFACE_PININTERFACE_H_
#include <Bounce2.h>
#include "../switchboard/machine.h"
#define N_KEYS 4

namespace pin_interface {

class PinInterface {
 public:
    PinInterface();
    void update();
    ~PinInterface();
 private:
    Bounce * debouncedSwitches[N_KEYS];
    switch_board::Machine switchBoard;
};

} // namespace pin_interface


#endif // SRC_PININTERFACE_PININTERFACE_H_

/*
Copyright 2016 Stichting Humanity4all
*/

#ifndef SRC_BUFFERS_BUFFERS_H_
#define SRC_BUFFERS_BUFFERS_H_

#include "../globals.h"
#include "../switchevent/switchevent.h"
#include "../switchboard/typedefs.h"

namespace buffers_n {

/*
 * Buffers, to prevent memory fragmentation
 */

class SwitchEventBuffer {
 public:
    switch_event_n::SwitchEvent eventBuffer[N_SWITCHES];
    switch_event_n::SwitchEvent* get_free();
    void empty();
};

class ProtokeyEventBuffer {
 public:
    switch_board_n::protokey_event_t eventBuffer[N_SWITCHES];
    switch_board_n::protokey_event_t* get_free();
    void empty();
};

} // namespace buffers_n


#endif // SRC_BUFFERS_BUFFERS_H_

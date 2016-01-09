/*
Copyright 2016 Stichting Humanity4all
*/

#ifndef SRC_TRANSLATIONSERVICE_SENDKEY_H_
#define SRC_TRANSLATIONSERVICE_SENDKEY_H_

#include "../globals.h"
#include "./typedefs.h"
#include "../switchboard/typedefs.h"

namespace translation_service_n {

void send_key(key_t key, switch_board_n::event_t event);

} // namespace translation_service_n

#endif // SRC_TRANSLATIONSERVICE_SENDKEY_H_

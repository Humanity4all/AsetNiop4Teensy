/*
Copyright 2015 Stichting Humanity4all
*/

#ifndef SRC_TRANSLATIONSERVICE_TYPEDEFS_H_
#define SRC_TRANSLATIONSERVICE_TYPEDEFS_H_

#include <Bounce2.h>

#include "../globals.h"

namespace translation_service_n {

typedef enum key_t {
    /*
    These are all the possible keys on a
    keyboard, not all are implemented at this time.

    Mostly sourced from arduino's keylayouts.h, with the
    addition of the layer control keys, the nop key
    and a lot of the symbols, since those go two a key,
    but we need them one a key to allow
    for flexibility in writing keymaps.
    */

    // alphabetical characters
    K_A, K_B, K_C, K_D, K_E, K_F, K_G,
    K_H, K_I, K_J, K_K, K_L, K_M, K_N, K_O,
    K_P, K_Q, K_R, K_S, K_T, K_U, K_V, K_W,
    K_X, K_Y, K_Z,

    // numerical characters
    K_0, K_1, K_2, K_3, K_4, K_5, K_6,
    K_7, K_8, K_9,

    // symbol characters
    K_ASTERISK, K_AMPERSAND, K_DOLLAR, K_POUND,
    K_AT, K_PERCENT, K_DASH, K_UNDERSCORE, K_SLASH,
    K_BACKSLASH, K_PIPE, K_EQUAL, K_PLUS, K_TILDE,
    K_CARET,

    // punctuation characters
    K_DOT, K_COMMA, K_QUESTION, K_EXCLAMATION,
    K_COLON, K_SEMICOLON, K_SINGLE_QUOTE, K_DOUBLE_QUOTE,
    K_BACK_QUOTE,

    // bracket characters
    K_PAREN_L, K_PAREN_R, K_BRACKET_L, K_BRACKET_R,
    K_ACCOLADE_L, K_ACCOLADE_R, K_SMALLER_THAN,
    K_GREATER_THAN,

    // control keys
    K_ENTER, K_BACKSPACE, K_SPACE, K_ESCAPE, K_TAB,
    K_DELETE, K_INSERT,
    K_UP, K_DOWN, K_LEFT, K_RIGHT,
    K_PGUP, K_PGDOWN, K_HOME, K_END,

    // modifier keys
    K_SHIFT, K_SHIFT_L, K_SHIFT_R,
    K_CTRL, K_CTRL_L, K_CTRL_R,
    K_ALT, K_ALT_L, K_ALT_R,
    K_GUI, K_GUI_L, K_GUI_R,
    K_CAPSLOCK,

    // function keys
    K_F1, K_F2, K_F3, K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_F10,
    K_F11, K_F12, K_F13, K_F14, K_F15, K_F16, K_F17, K_F18, K_F19,
    K_F20, K_F21, K_F22, K_F23, K_F24,

    // numpad keys
    K_PAD_SLASH, K_PAD_ASTERIX, K_PAD_MINUS, K_PAD_PLUS, K_PAD_ENTER,
    K_PAD_0, K_PAD_1, K_PAD_2, K_PAD_3, K_PAD_4, K_PAD_5, K_PAD_6,
    K_PAD_7, K_PAD_8, K_PAD_9,
    K_PAD_PERIOD,

    // mouse buttons
    M_LEFT, M_MIDDLE, M_RIGHT,

    // special keys
    K_NOP,

    // layer keys
    K_LAYER_0, K_LAYER_1, K_LAYER_2, K_LAYER_3, K_LAYER_4, K_LAYER_5,
    K_LAYER_6, K_LAYER_7,

    // media keys
    K_PRINTSCRN, K_NUMLOCK, K_SCROLL_LOCK, K_PAUSE, K_MENU,
    K_MEDIA_VOLUME_INC, K_MEDIA_VOLUME_DEC, K_MEDIA_VOLUME_MUTE,
    K_MEDIA_PLAY_PAUSE, K_MEDIA_NEXT_TRACK, K_MEDIA_PREV_TRACK,
    K_MEDIA_STOP, K_MEDIA_EJECT,
} key_t;


} // namespace translation_service_n

#endif  // SRC_TRANSLATIONSERVICE_TYPEDEFS_H_

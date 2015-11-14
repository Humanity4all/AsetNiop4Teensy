#include <Bounce2.h>

//type declarations
typedef enum key_char { //these are all the possible keys on a keyboard, not all are implemented at this time
	//alphabetical characters
	CHAR_A, CHAR_B, CHAR_C, CHAR_D, CHAR_E, CHAR_F, CHAR_G, CHAR_H, CHAR_I, CHAR_J, CHAR_K, CHAR_L, CHAR_M, CHAR_N,
	CHAR_O, CHAR_P, CHAR_Q, CHAR_R, CHAR_S, CHAR_T, CHAR_U, CHAR_V, CHAR_W, CHAR_X, CHAR_Y, CHAR_Z,
	//numerical characters
	CHAR_0, CHAR_1, CHAR_2, CHAR_3, CHAR_4, CHAR_5, CHAR_6, CHAR_7, CHAR_8, CHAR_9,
	//symbol characters
	CHAR_ASTERISK, CHAR_AMPERSAND, CHAR_DOLLAR, CHAR_POUND, CHAR_AT, CHAR_PERCENT, CHAR_DASH, CHAR_UNDERSCORE,
	CHAR_SLASH, CHAR_BACKSLASH, CHAR_PIPE, CHAR_EQUAL, CHAR_PLUS, CHAR_TILDE, CHAR_CARET,
	//punctuation characters
	CHAR_DOT, CHAR_COMMA, CHAR_QUESTION, CHAR_EXCLAMATION, CHAR_COLON, CHAR_SEMICOLON, CHAR_SINGLE_QUOTE,
	CHAR_DOUBLE_QUOTE, CHAR_BACK_QUOTE,
	//bracket characters
	CHAR_PAREN_L, CHAR_PAREN_R, CHAR_BRACKET_L, CHAR_BRACKET_R,
	CHAR_ACCOLADE_L, CHAR_ACCOLADE_R, CHAR_SMALLER_THAN, CHAR_GREATER_THAN,
	//control keys
	
	// naming conflict! we used KEY_ naming, but that conflicts with the main teensy library
	K_ENTER, K_RETURN, K_BACKSPACE, K_DELETE, K_INSERT, K_ESCAPE, K_TAB,
	K_UP, K_DOWN, K_LEFT, K_RIGHT, K_PGUP, K_PGDOWN, K_HOME, K_END,
	
	//modifier keys
	K_SHIFT_L, K_SHIFT_R, K_CAPSLOCK, K_CTRL_L, K_CTRL_R, K_ALT_L, K_ALT_R, K_MOD4_L, K_MOD4_R,
	K_FN, K_LAYER, K_NUMLOCK, K_SCRLOCK,
	
	//f# keys //naming conflict!
	K_F1, K_F2, K_F3, K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_F10, K_F11, K_F12, K_F13,
	K_F14, K_F15,
	//media keys
	K_PRINTSCRN, K_WAKE, K_SLEEP, K_POWER, 
	//numpad keys

	//mouse buttons
	
	//special keys
	CHAR_NIL
} key_char;

typedef enum key_state {
	IDLE, PRESSED, RELEASED, USED, USEDREL, LAZY, LOCKED,
} key_state;

//some global vars needed by keyboard struct, and other functions
//TODO set the right number of keys here
//int n=4; //total number of keys in keyboard
#define NumKeys 4
typedef struct keyboard {
	Bounce * keys[NumKeys]; // button objects
	key_state keyState[NumKeys]; //keystates
	key_state shift;
	key_state control;
	key_state command;
	key_state option;
	key_state function;	
	
} keyboard;



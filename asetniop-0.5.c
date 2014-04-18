#include <Bounce.h>

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
	KEY_ENTER, KEY_RETURN, KEY_BACKSPACE, KEY_DELETE, KEY_INSERT, KEY_ESCAPE, KEY_TAB,
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_PGUP, KEY_PGDOWN, KEY_HOME, KEY_END,
	//modifier keys
	KEY_SHIFT_L, KEY_SHIFT_R, KEY_CAPSLOCK, KEY_CTRL_L, KEY_CTRL_R, KEY_ALT_L, KEY_ALT_R, KEY_MOD4_L, KEY_MOD4_R,
	KEY_FN, KEY_LAYER, KEY_NUMLOCK, KEY_SCRLOCK,
	//f# keys
	KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_F13,
	KEY_F14, KEY_F15,
	//media keys
	KEY_PRINTSCRN, KEY_WAKE, KEY_SLEEP, KEY_POWER, 
	//numpad keys

	//mouse buttons
	
};

typedef enum key_state{
	IDLE, PRESSED, RELEASED, LAZY, LOCKED,
};

//some global vars needed by keyboard struct, and other functions
//TODO set the right number of keys here
int n=4; //number of non-modifier keys in keyboard
int m=1; //number of modifier keys in keyboard
typedef struct keyboard {
	Bounce keys[n+m]; // button objects
	key_state keyState[n+m]; //keystates	
	
};

//functions
bool init(); //populates k
bool keystate(); //updates keystates in k
bool asetniop(); //translates keystates in k to characters using key_char
bool sendkeys(int size, key_char keys[]); //sends proper keys to pc

//global vars
keyboard k;

bool init()
{
	//TODO set pins to use (modifier keys last)
	int pinsToUse[n+m]={1, 2, 3, 4, 5};
	for (int i=0; i<n+m; i++) {
		int pin = pinsToUse[i];
		pinMode(pin,INPUT_PULLUP);
		k.keys[i]=Boune(pin, 10);
		k.keyState[i]=IDLE;
	}

	return true;
}

bool keystate()
{
	for(int i=0; i<n+m; i++) {
		if(k.keys[i].update()){
			if(k.keys[i].fallingEdge()) {
				if(i>=n){ //modifier keys
					if(k.keyState[i]==IDLE){
						k.keyState[i]=LAZY;
					}
					else if(k.keyState[i]==LAZY){
						k.keyState[i]=LOCKED;
					}
					else if(k.keyState[i]==LOCKED){
						k.keyState[i]=IDLE;
					}
				}
				else{ //normal keys
				
					if(k.keyState[i]==IDLE){
						k.keyState[i]=PRESSED;
					}
					else if(k.keyState[i]==RELEASED){
						k.keyState[i]=PRESSED;
					}
					}
				}
			}	
			else if(k.keys[i].risingEdge()) {
				if(i<n){//we're only interested in normal keys here
					if(k.keyState[i]==PRESSED){
						k.keyState[i]=RELEASED;
					}
				}
			}
		}
	}
	return true;
}

bool asetniop()
{//translate the keyboard state to a character & modkeys
	//TODO initialize empty mod array (0=inactive, 1=active)
	int mods[m]={0}

	sendkeys(size, keytosend, mods);
	return true;
}

bool sendkeys(int size, key_char keys, int mods[m])
{
	//reset keys
	
	for(int i=0; i<size; i++)
	{
		switch(keys[i]){

			case KEY_A:

				break;
			case KEY_B:

				break;
			//etc
		}


	}
	//send keys
	
	return true;
}

void setup() {
	init();
}

void loop() {
	keystate();
	asetniop();

}

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
	IDLE, PRESSED, RELEASED, USED, USEDREL, LAZY, LOCKED,
};

//some global vars needed by keyboard struct, and other functions
//TODO set the right number of keys here
int n=4; //total number of keys in keyboard
typedef struct keyboard {
	Bounce keys[n]; // button objects
	key_state keyState[n]; //keystates
	key_state shift;
	key_state control;
	key_state command;
	key_state option;
	key_state function;	
	
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
	//TODO set pins to use from left to right (counting thumbs)
	int pinsToUse[n]={1, 2, 3, 4};
	for (int i=0; i<n; i++) {
		int pin = pinsToUse[i];
		pinMode(pin,INPUT_PULLUP);
		k.keys[i]=Boune(pin, 10);
		k.keyState[i]=IDLE;
	}

	return true;
}

bool keystate()
{
	for(int i=0; i<n; i++) {
		if(k.keys[i].update()){
			if(k.keys[i].fallingEdge()) {
				if(k.keyState[i]==IDLE){
					k.keyState[i]=PRESSED;
				}
				else if(k.keyState[i]==RELEASED){
					k.keyState[i]=PRESSED;					
				}
			}	
			else if(k.keys[i].risingEdge()) {
					if(k.keyState[i]==PRESSED){
						k.keyState[i]=RELEASED;
					}
					else if(k.keyState[i]==USED){
						k.keyState[i]=USEDREL;
					}
			}
		}
	}
	return true;
}

bool asetniop()
{//translate the keyboard state to a character & modkeys
	//modifiers	shift	ctrl	cmd	opt	fn
	//int mods[5]={	0,	0,	0,	0,	0}; //0=inactive, 1=active
	//test table for one handed, 4 key keyboard prototype
	key_char keyTable[n][n]={
		{CHAR_A, CHAR_W, CHAR_X, CHAR_F},
		{CHAR_W, CHAR_S, CHAR_D, CHAR_C},
		{CHAR_X, CHAR_D, CHAR_E, CHAR_R},
		{CHAR_F, CHAR_C, CHAR_R, CHAR_T}
		}

	//check how many keys are held down, and if one is released
	int n=0; //number of pressed keys detected
	int r=0; //number of released keys detected
	int u=0; //number of keys already used
	int key1; //index of first key
	int key2; //index of second key

	for(int i=0; i<n; i++) {
		key_state st = k.keyState[i];
			if(st==RELEASED or st==USEDREL){
				r++;
				n++;
				if(st==USEDREL){u++;}
				key2=i;
				if(n<2){
					key1=i;
				}
				k.keyState[i]=IDLE;
			}
			else if (st==PRESSED or st==USED) {
				n++;
				if(st==USED){u++;}
				key2=i;
				if(n<2){
					key1=i;
				}
			}
	}

	if((n>1 or r>0) and u<n){ //send conditions met (2 keys, or 1 key released, and at less used keys than keys pressed)
		//select correct character from keytable
		key_char keyToSend=keyTable[key1][key2];
		
		//send keys
		sendkeys(keytosend, r>0);
		
		//update keystates
		if(k.keyState[key1]==PRESSED) {k.keyState[key1]=USED;}
		if(k.keyState[key2]==PRESSED) {k.keyState[key2]=USED;}
	}		
	return true;
}

//var to check if this character was already sent for an unreleased key
key_char lastSent=CHAR_NIL;
bool sendkeys(key_char key, bool release)
{
	//set modifiers
	
	//set keys
	switch(key){

		case CHAR_A:
			Keyboard.set_key1(KEY_A);
			break;
		case CHAR_B:
			Keyboard.set_key1(KEY_B);
			break;
		case CHAR_C:
			Keyboard.set_key1(KEY_C);
			break;
		case CHAR_D:
			Keyboard.set_key1(KEY_D);
			break;
		case CHAR_E:
			Keyboard.set_key1(KEY_E);
			break;
		case CHAR_F:
			Keyboard.set_key1(KEY_F);
			break;
		case CHAR_G:
			Keyboard.set_key1(KEY_G);
			break;
		case CHAR_H:
			Keyboard.set_key1(KEY_H);
			break;
		case CHAR_I:
			Keyboard.set_key1(KEY_I);
			break;
		case CHAR_J:
			Keyboard.set_key1(KEY_J);
			break;
		case CHAR_K:
			Keyboard.set_key1(KEY_K);
			break;
		case CHAR_L:
			Keyboard.set_key1(KEY_L);
			break;
		case CHAR_M:
			Keyboard.set_key1(KEY_M);
			break;
		case CHAR_N:
			Keyboard.set_key1(KEY_N);
			break;
		case CHAR_O:
			Keyboard.set_key1(KEY_O);
			break;
		case CHAR_P:
			Keyboard.set_key1(KEY_P);
			break;
		case CHAR_Q:
			Keyboard.set_key1(KEY_Q);
			break;
		case CHAR_R:
			Keyboard.set_key1(KEY_R);
			break;
		case CHAR_S:
			Keyboard.set_key1(KEY_S);
			break;
		case CHAR_T:
			Keyboard.set_key1(KEY_T);
			break;
		case CHAR_U:
			Keyboard.set_key1(KEY_U);
			break;
		case CHAR_V:
			Keyboard.set_key1(KEY_V);
			break;
		case CHAR_W:
			Keyboard.set_key1(KEY_W);
			break;
		case CHAR_X:
			Keyboard.set_key1(KEY_X);
			break;
		case CHAR_Y:
			Keyboard.set_key1(KEY_Y);
			break;
		case CHAR_Z:
			Keyboard.set_key1(KEY_Z);
			break;
		default:
			//error, unhandled character
			Keyboard.set_key1(0);
			break;
		}



	//send keys
	Keyboard.send_now();

	//reset keys and reset lastSent
	if(reset){
		Keyboard.set_key1(0);
		Keyboard.set_key2(0);
		Keyboard.set_key3(0);
		Keyboard.set_Key4(0);
		Keyboard.set_key5(0);
		Keyboard.set_key6(0);
		Keyboard.send_now();
	}
	return true;
}

void setup() {
	init();
}

void loop() {
	keystate();
	asetniop();

}

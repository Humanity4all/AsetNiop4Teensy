#include <Bounce.h>
#include "typedefs.h"

#define NumKeys 4
#define DEBUG 1

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
	if(lastSent!=key){
		Keyboard.send_now();
	}

	//reset keys and reset lastSent
	if(reset){
		lastSent=CHAR_NIL;
		Keyboard.set_key1(0);
		Keyboard.set_key2(0);
		Keyboard.set_key3(0);
		Keyboard.set_Key4(0);
		Keyboard.set_key5(0);
		Keyboard.set_key6(0);
		Keyboard.send_now();
	}
	else{
		lastSent=key; 
		//indicate this key combination has been sent already, no need to resend until key release.
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

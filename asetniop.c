// assign pins to fingers (keys)
const int lp=5;   //left pink
const int lpm=6;  //left pink mod
const int lr=7;   //left ring finger
const int lrm=8;  //left ring finger mod
const int lm=9;   //left middle finger
const int lmm=10; //left middle finger mod
const int li=11;  //left index finger
const int lim=12; //left index finger mod
const int lt=13;  //left thumb
const int ltm=14; //left thumb mod

const int rt=15;  //right thumb
const int rtm=16; //right thumb mod
const int ri=17;  //right index finger
const int rim=18; //right index finger mod
const int rm=19;  //right middle finger
const int rmm=20; //right middle finger mod
const int rr=21;  //right ring finger
const int rrm=22; //right ring finger mod
const int rp=23;  //right pink
const int rpm=24; //right pink mod

const int power=25;
const int debug=1;

const char keys[rows][cols]={
    //A    S    E    T    N    I    O    P
    {'a', 'w', 'x', 'f', 'q', '!', '(', '?'}, //A - lp
    {'w', 's', 'd', 'c', 'j', 'z', '.', ')'}, //S - lr
    {'x', 'd', 'e', 'r', 'y', ',', '-', "'"}, //E - lm
    {'f', 'c', 'r', 't', 'b', 'v', 'g', '\b'}, //T - li
    {'q', 'j', 'y', 'b', 'n', 'h', 'u', 'm'}, //N - ri
    {'!', 'z', ',', 'v', 'h', 'i', 'l', 'k'}, //I - rm
    {'(', '.', '-', 'g', 'u', 'l', 'o', ';'}, //O - rr
    {'?', ')', "'", '\b', 'm', 'k', ';', 'p'} //P - rp
};

const char shiftkeys[rows][cols]={
    //A    S    E    T    N    I    O    P
    {'A', 'W', 'X', 'F', 'Q', '\\', '[', '/'}, //A - lp
    {'W', 'S', 'D', 'C', 'J', 'Z', '>', ']'}, //S - lr
    {'X', 'D', 'E', 'R', 'Y', '<', '_', '"'}, //E - lm
    {'F', 'C', 'R', 'T', 'B', 'V', 'G', '\b'}, //T - li
    {'Q', 'J', 'Y', 'B', 'N', 'H', 'U', 'M'}, //N - ri
    {'\\', 'Z', '<', 'V', 'H', 'I', 'L', 'K'}, //I - rm
    {'[', '>', '_', 'G', 'U', 'L', 'O', ':'}, //O - rr
    {'/', ']', '"', '\b', 'M', 'K', ':', 'P'} //P - rp
};

const char numerical[rows][cols]={
    //A    S    E    T    N    I    O    P
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //A
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //S
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //E
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //T
    {' ', ' ', ' ', ' ', '>', ' ', ' ', ' '}, //N
    {' ', ' ', ' ', ' ', ' ', '^', ' ', ' '}, //I
    {' ', ' ', ' ', ' ', ' ', ' ', 'd', ' '}, //O
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', '>'} //P
};

const char numericalshift[rows][cols]={
    //A    S    E    T    N    I    O    P
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //A
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //S
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //E
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //T
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //N
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //I
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, //O
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} //P
};

void debug(char* text) {
    if (debug==1){
        Serial.println(text);
    }
}

void process() {
    //act on the detected key settings
    
    //mod keys - these are lazy: one press is on for the next keypress, two presses caps, 3rd press off
    for (i=0; i<5; i++){
        if (mods[i][1]==1) { 
            if (mods[i][2]<2) { mods[i][2]+=1; }
            else { mods[i][2]=0; }
        }
    }
    
    int shift;
    int ctrl;
    int mod4;
    int alt;
    int fn;
    //set modifier keys
    if (mods[0][0]==1 or mods[0][2]>0) { snift=1 }
    if (mods[1][0]==1 or mods[1][2]>0) { ctrl=1 }
    if (mods[2][0]==1 or mods[2][2]>0) { mod4=1 }
    if (mods[3][0]==1 or mods[3][2]>0) { alt=1 }
    if (mods[4][0]==1 or mods[4][2]>0) { fn=1 }
    if (mods[5][1]>0) { if (mode==1) { mode=0 } else { mode=1 } }
    //send modifier keys (we skip the individual shift because it has special meaning)
    //we ignore fn for now, there's no real support for it in teensy right now
    if (ctrl==1 and shift==1 and mod4==1 and alt==1) { //4 mod keys
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_SHIFT | MODIFIERKEY_GUI | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (shift==1 and mod4==1 and alt==1) { //3 mod keys, no ctrl
        Keyboard.set_modifier(MODIFIERKEY_SHIFT | MODIFIERKEY_GUI | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (ctrl==1 and mod4==1 and alt==1) { //3 mod keys, no shift
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_GUI | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (ctrl==1 and shift==1 and alt==1) { //3 mod keys, no mod4
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_SHIFT | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (ctrl==1 and shift==1 and mod4==1) { //3 mod keys, no alt
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MOIFIERKEY_SHIFT | MODIFIERKEY_GUI);
        Keyboard.send_now();
    }
    else if (ctrl==1 and shift==1) { //2 mod keys, ctrl - shift
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_SHIFT);
        Keyboard.send_now();
    }
    else if (ctrl==1 and mod4==1) { //2 mod keys, ctrl - mod4
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_GUI);
        Keyboard.send_now();
    }
    else if (ctrl==1 and alt==1) { //2 mod keys, ctrl - alt
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (mod4==1 and shift==1) { //2 mod keys, mod4 - shift
        Keyboard.set_modifier(MODIFIERKEY_GUI | MODIFIERKEY_SHIFT);
        Keyboard.send_now();
    }
    else if (mod4==1 and alt==1) { //2 mod keys, mod4 - alt
        Keyboard.set_modifier(MODIFIERKEY_GUI | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (alt==1 and shift==1) { //2 mod keys, alt - shift
        Keyboard.set_modifier(MODIFIERKEY_ALT | MODIFIERKEY_SHIFT);
        Keyboard.send_now();
    }
    else if (ctrl==1) { //1 mod key
        Keyboard.set_modifier(MODIFIERKEY_CTRL);
        Keyboard.send_now();
    }
    else if (mod4==1) { //1 mod key
        Keyboard.set_modifier(MODIFIERKEY_GUI);
        Keyboard.send_now();
    }
    else if (alt==1) { //1 mod key
        Keyboard.set_modifier(MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    
   for (i=0; i<5; i++) {
       if (i>0 and (mods[i][2]<2 or mods[i][0]>0)) { mods[i][1]=0; mods[i][2]=0; } 

    }
    
    //Handle mouse buttons, including dragging
    if (mouse[0][0]==1) { //dragging
        Mouse.set_buttons(1,0,0);
    }
    else if (mouse[0][1]==1) {
        //Mouse.set_buttons(1,0,0); //this should not be necessary
        Mouse.set_buttons(0,0,0);
        mouse[0][0]=0;
    }
    else if (mouse[1][0]==1) { //right click dragging
        Mouse.set_buttons(0,1,0);
    }
    else if (mouse[1][1]==1) {
        Mouse.set_buttons(0,0,0);
        mouse[1][1]==0;
    }//no middle click yet
    //scrolling
    if (mouse[2][1]==1) { //scroll up
        Mouse.scroll(1);
        mouse[2][1]=0;
    }
    if(mouse[3][1]==1) { //scroll down
        Mouse.scroll(-1);
        mouse[3][1]=0;
    }

    //Check mode
    if(mode==0) {
        //'normal' mode - alphabetic
        
        //Check shift

        //Determine what key to send
    }
    else if(mode==1) {
        //numeric mode

        //Check shift

        //Determine what key to send
    }
    else{ //not implemented yet, but other modes should go here
        //Check shift
        
        //Determine what key to send
    }

    //Now send the keys
    Keyboard.send_now();
    
    //Now reset the keys
    Keyboard.set_key1(0);
    Keyboard.set_key2(0);
    Keyboard.set_key3(0);
    Keyboard.set_key4(0);
    Keyboard.set_key5(0);
    Keyboard.set_key6(0);
    //Only reset the modifierkeys that aren't sticky

    //send modifier keys (we skip the individual shift because it has special meaning)
    //we ignore fn for now, there's no real support for it in teensy right now
    if (ctrl==1 and shift==1 and mod4==1 and alt==1) { //4 mod keys
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_SHIFT | MODIFIERKEY_GUI | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (shift==1 and mod4==1 and alt==1) { //3 mod keys, no ctrl
        Keyboard.set_modifier(MODIFIERKEY_SHIFT | MODIFIERKEY_GUI | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (ctrl==1 and mod4==1 and alt==1) { //3 mod keys, no shift
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_GUI | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (ctrl==1 and shift==1 and alt==1) { //3 mod keys, no mod4
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_SHIFT | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (ctrl==1 and shift==1 and mod4==1) { //3 mod keys, no alt
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MOIFIERKEY_SHIFT | MODIFIERKEY_GUI);
        Keyboard.send_now();
    }
    else if (ctrl==1 and shift==1) { //2 mod keys, ctrl - shift
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_SHIFT);
        Keyboard.send_now();
    }
    else if (ctrl==1 and mod4==1) { //2 mod keys, ctrl - mod4
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_GUI);
        Keyboard.send_now();
    }
    else if (ctrl==1 and alt==1) { //2 mod keys, ctrl - alt
        Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (mod4==1 and shift==1) { //2 mod keys, mod4 - shift
        Keyboard.set_modifier(MODIFIERKEY_GUI | MODIFIERKEY_SHIFT);
        Keyboard.send_now();
    }
    else if (mod4==1 and alt==1) { //2 mod keys, mod4 - alt
        Keyboard.set_modifier(MODIFIERKEY_GUI | MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else if (alt==1 and shift==1) { //2 mod keys, alt - shift
        Keyboard.set_modifier(MODIFIERKEY_ALT | MODIFIERKEY_SHIFT);
        Keyboard.send_now();
    }
    else if (ctrl==1) { //1 mod key
        Keyboard.set_modifier(MODIFIERKEY_CTRL);
        Keyboard.send_now();
    }
    else if (mod4==1) { //1 mod key
        Keyboard.set_modifier(MODIFIERKEY_GUI);
        Keyboard.send_now();
    }
    else if (alt==1) { //1 mod key
        Keyboard.set_modifier(MODIFIERKEY_ALT);
        Keyboard.send_now();
    }
    else{ //no mod keys
        Keyboard.set_modifier(0);
        Keyboard.send_now();
    }
}

void setup() {
    Keyboard.begin();
    Serial.begin(38400);
    pinMode(lp, INPUT);
    pinMode(lpm, INPUT);
    pinMode(lr, INPUT);
    pinMode(lrm, INPUT);
    pinMode(lm, INPUT);
    pinMode(lmm, INPUT);
    pinMode(li, INPUT);
    pinMode(lim, INPUT);
    pinMode(lt, INPUT);
    pinMode(ltm, INPUT);
    pinMode(rt, INPUT);
    pinMode(rtm, INPUT);
    pinMode(ri, INPUT);
    pinMode(rim, INPUT);
    pinMode(rm, INPUT);
    pinMode(rmm, INPUT);
    pinMode(rr, INPUT);
    pinMode(rrm, INPUT);
    pinMode(rp, INPUT);
    pinMode(rpm, INPUT);
    pinMode(power, INPUT);
}

int mode=0;
int status=0;
int mods[key][state]={
    // pressed released state
    {  0,      0,       0   }, //shift - rt
    {  0,      0,       0   }, //ctrl - lim
    {  0,      0,       0   }, //mod4 - lmm
    {  0,      0,       0   }, //alt - lrm
    {  0,      0,       0   }, //fn - lpm
    {  0,      0,       0   } //mode - rtm
};

int thumbs[key][state]={
    // pressed released
    {  0,      0  }, //space - lt
    {  0,      0  } //enter - ltm
};

int keys[key][state]={
    // pressed released
    {  0,      0 }, //A - lp
    {  0,      0 }, //S - lr
    {  0,      0 }, //E - lm
    {  0,      0 }, //T - li
    {  0,      0 }, //N - ri
    {  0,      0 }, //I - rm
    {  0,      0 }, //O - rr
    {  0,      0 } //P - rp
};

int mouse[key][state]={
    // pressed released
    {  0,      0 }, //leftbutton - rim
    {  0,      0 }, //rightbutton - rmm
    {  0,      0 }, //scrollup   - rrm
    {  0,      0 } //scrolldown - rpm
};

void loop() {
    debug("Loop...")
    if (digitalRead(power) == LOW) {
        status=0; //keyboard is off
        debug("Keyboard is off")
        delay(5000); //only check every 5 seconds to save power
    } else {
        status=1;
        debug("Keyboard is on")
        //now check for pressed keys
        //left hand character keys
        if (digitalRead(lp) == HIGH) { keys[0][0]=1; }
        else { if (keys[0][0]==1) { keys[0][0]=0; keys[0][1]=1; }}
        if (digitalRead(lr) == HIGH) { keys[1][0]=1; }
        else { if (keys[1][0]==1) { keys[1][0]=0; keys[1][1]=1; }}
        if (digitalRead(lm) == HIGH) { keys[2][0]=1; }
        else { if (keys[2][0]==1) { keys[2][0]=0; keys[2][1]=1; }}
        if (digitalRead(li) == HIGH) { keys[3][0]=1; }
        else { if (keys[3][0]==1) { keys[3][0]=0; keys[3][1]=1; }}
        
        //right hand character keys
        if (digitalRead(ri) == HIGH) { keys[4][0]==1; }
        else { if (keys[4][0]==1) { keys[4][0]=0; keys[4][1]=1; }}
        if (digitalRead(rm) == HIGH) { keys[5][0]==1; }
        else { if (keys[5][0]==1) { keys[5][0]=0; keys[5][1]=1; }}
        if (digitalRead(rr) == HIGH) { keys[6][0]==1; }
        else { if (keys[6][0]==1) { keys[6][0]=0; keys[6][1]=1; }}
        if (digitalRead(rp) == HIGH) { keys[7][0]==1; }
        else { if (keys[7][0]==1) { keys[7][0]=0; keys[7][1]=1; }}
        
        //modifierkeys
        if (digitalRead(rt) == HIGH) { mods[0][0]=1; }
        else { if (mods[0][0]==1) { mods[0][0]=0; mods[0][1]=1; }}
        if (digitalRead(lim) == HIGH) { mods[1][0]=1; }
        else { if (mods[1][0]==1) { mods[1][0]=0; mods[1][1]=1; }}
        if (digitalRead(lmm) == HIGH) { mods[2][0]=1; }
        else { if (mods[2][0]==1) { mods[2][0]=0; mods[2][1]=1; }}
        if (digitalRead(lrm) == HIGH) { mods[3][0]=1; }
        else { if (mods[3][0]==1) { mods[3][0]=0; mods[3][1]=1; }}
        if (digitalRead(lpm) == HIGH) { mods[4][0]=1; }
        else { if (mods[4][0]==1) { mods[4][0]=0; mods[4][1]=1; }}
        if (digitalRead(rtm) == HIGH) { mods[5][0]=1; }
        else { if (mods[5][0]==1) { mods[5][0]=0; mods[5][1]=1; }}
        
        //thumbs (these are separate from the right thumbs because these are direct action keys)
        if (digitalRead(lt) == HIGH) { thumbs[0][0]=1; }
        else { if (thumbs[0][0]==1) { thumbs[0][0]=0; thumbs[0][1]=1; }}
        if (digitalRead(ltm) == HIGH) { thumbs[1][0]=1; }
        else { if (thumbs[1][0]==1) { thumbs[1][0]=0; thumbs[1][1]=1; }}
        
        //mousekeys (direct action too)
        if (digitalRead(rim) == HIGH) { mouse[0][0]=1; }
        else { if (mouse[0][0]==1) { mouse[0][0]=0; mouse[0][1]=1; }}
        if (digitalRead(rmm) == HIGH) { mouse[1][0]=1; }
        else { if (mouse[1][0]==1) { mouse[1][0]=0; mouse[1][1]=1; }}
        if (digitalRead(rrm) == HIGH) { mouse[2][0]=1; }
        else { if (mouse[2][0]==1) { mouse[2][0]=0; mouse[2][1]=1; }}
        if (digitalRead(rpm) == HIGH) { mouse[3][0]=1; }
        else { if (mouse[3][0]==1) { mouse[3][0]=0; mouse[3][1]=1; }}
        
        process()
        
        //delay(10); //short delay for fast typing
    }
}

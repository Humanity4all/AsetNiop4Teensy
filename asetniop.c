// assign pins to fingers (keys)
int lp=5;   //left pink
int lpm=6;  //left pink mod
int lr=7;   //left ring finger
int lrm=8;  //left ring finger mod
int lm=9;   //left middle finger
int lmm=10; //left middle finger mod
int li=11;  //left index finger
int lim=12; //left index finger mod
int lt=13;  //left thumb
int ltm=14; //left thumb mod

int rt=15;  //right thumb
int rtm=16; //right thumb mod
int ri=17;  //right index finger
int rim=18; //right index finger mod
int rm=19;  //right middle finger
int rmm=20; //right middle finger mod
int rr=21;  //right ring finger
int rrm=22; //right ring finger mod
int rp=23;  //right pink
int rpm=24; //right pink mod

int power=25;
int debug=1;

char keys[rows][cols]={
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

char shiftkeys[rows][cols]={
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

char numerical[rows][cols]={
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

char numericalshift[rows][cols]={
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

void debug(char text) {
    if (debug==1){
        Serial.println(text);
    }
}

void process() {
    //act on the detected key settings
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

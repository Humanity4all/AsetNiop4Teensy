#ifdef ENERGIA
  #include "Energia.h"
#else
  #include "Arduino.h"
#endif

#ifndef LED_PIN
  // Most Arduino boards already have a LED attached to pin 13 on the board itself
  #define LED_PIN 13
#endif

#define BOUNCE_LOCK_OUT
#include <Bounce2.h>

#include "typedefs.h"

Bounce debugkey;

void setup()
{
  pinMode(LED_PIN, OUTPUT);     // set pin as output
  pinMode(0, INPUT_PULLUP);
  debugkey.attach(0);
  debugkey.interval(10);
}

void loop()
{
  //digitalWrite(LED_PIN, HIGH);  // set the LED on
  //delay(1000);                  // wait for a second
  //digitalWrite(LED_PIN, LOW);   // set the LED off
  //delay(1000);                  // wait for a second
  if(debugkey.update())
  {
    if(debugkey.read()==0) digitalWrite(LED_PIN, HIGH); // pressed
    if(debugkey.read()==1) digitalWrite(LED_PIN, LOW);  // released
  }
}

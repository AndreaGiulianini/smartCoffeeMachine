#include "Arduino.h"
#include "globalvar.h"
#define BAUD_RATE 20000 // se non invia i dati velocemente entra in sleep prima di aver finito

void setup() {
  // put your setup code here, to run once:
  Serial.begin( BAUD_RATE );

  pinMode(SP_TRIG_PIN, OUTPUT);
  pinMode(SP_ECHO_PIN, INPUT);  
}

void loop() {
  
}

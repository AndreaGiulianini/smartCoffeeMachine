#include "Arduino.h"

Distance::Distance( GlobalVar_t* gv ) {
  this->gv = gv;
}

void Distance::Exec() {
  Serial.println("exec sp");
  
  if ( gv->state == ON && GetDistance() <= DIST1 )//Per passare a READY
    gv->hc_in_range = true;
  else if ( gv->state == TAKING_COFFEE && GetDistance() <= DIST2 )//Per prendere caffè
    gv->hc_in_range = true;
  else 
    gv->hc_in_range = false;
}

void Distance::GetDistance() {
    /* invio impulso */
    digitalWrite(SP_TRIG_PIN,LOW);
    delayMicroseconds(3);
    digitalWrite(SP_TRIG_PIN,HIGH);
    delayMicroseconds(5);
    digitalWrite(SP_TRIG_PIN,LOW);
    
    /* ricevi l’eco */
    float tUS = pulseIn(SP_ECHO_PIN, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*SP_CONST;
    return d;
}

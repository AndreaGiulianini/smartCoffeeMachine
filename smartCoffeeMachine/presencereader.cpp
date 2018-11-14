#include "globalvar.h"
#include "presencereader.h"
#include "Arduino.h"

PresenceReader::PresenceReader( GlobalVar_t* gv ) {
  this->gv = gv;
}

void PresenceReader::Exec() {
  Serial.println("ex presence");
  gv->pir_present = digitalRead( PIR_PIN ) == HIGH;
}

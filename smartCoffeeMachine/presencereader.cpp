#include "globalvar.h"
#include "presencereader.h"
#include "Arduino.h"

PresenceReader::PresenceReader( GlobalVar_t* gv ) {
  this->gv = gv;
}

void PresenceReader::Exec() {
  gv->pir_present = digitalRead( PIR_PIN ) == HIGH;
}

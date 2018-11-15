#include "globalvar.h"
#include "presencetask.h"
#include "Arduino.h"

PresenceTask::PresenceTask( GlobalVar_t* gv ) {
  	this->gv = gv;
}

void PresenceTask::Exec() {
  	gv->pir_present = digitalRead( PIR_PIN ) == HIGH;
}

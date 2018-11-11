#include "global_var.h"
#include "presencereader.h"
#include "Arduino.h"

bool pir_presence;

void PresenceReader::Exec() {
  pir_presence = digitalRead( PIR_PIN ) == HIGH;
}

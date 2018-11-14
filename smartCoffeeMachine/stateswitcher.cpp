#include "stateswitcher.h"
#include "Arduino.h"

StateSwitcher::StateSwitcher( GlobalVar_t* gv ) {
  this->gv = gv;
  gv->state = STAND_BY;
}

void StateSwitcher::Exec() {
  /*
   * [...] Quando viene rilevata la presenza di qualcuno nelle vicinanze allora 
   * esce dalla modalità di risparmio, entrando in una modalità ON.
   */
  if ( gv->state == STAND_BY && gv->pir_present ) {
    gv->state = ON;
    Serial.println("STB to ON");
  }

  /*
   * Dalla modalità ON la macchina torna in modalità STAND BY se non viene rilevata 
   * la presenza di nessuno per DT2b secondi.
   */
  if ( gv->state == ON && gv->time_elapsed && !gv->time_acquired && !gv->pir_present ) {
    gv->state = STAND_BY;
    gv->time_acquired = true;
    Serial.println("ON to STB");
  }
  /*
   * Se viene rilevato qualcuno  ad una distanza inferiore a DIST1 cm per un certo 
   * numero DT1 secondi [...]e la macchina entra in una modalità READY.
   */
  Serial.print("Range: ");
  Serial.println(gv->hc_in_range);
  Serial.print("Time: ");
  Serial.println(gv->time_elapsed);
  if ( gv->state == ON && gv->time_elapsed && !gv->time_acquired && gv->hc_in_range ) {
    gv->state = READY;
    gv->time_acquired = true;
    Serial.println("ON to READY");
  }

  /*
   * Se la macchina non rileva più nessuno entro quella distanza per DT2a secondi, 
   * la macchina torna nella modalità ON.
   */
  if ( gv->state == READY && gv->time_elapsed && !gv->time_acquired && !gv->pir_present ) {
    gv->state = ON;
    gv->time_acquired = true;
    Serial.println("READY to ON");
  }

  /*
   * Quando preme il pulsante, parte il processo [...] della durata di DT3 secondi.
   */
  if ( gv->state == READY && gv->make_coffee ) {
    gv->state = MAKING_COFFEE;
    Serial.println("READY to MKG");
  }

  /*
   * 
   */
  if ( gv->state == MAKING_COFFEE && gv->coffee_ready && gv->coffee_pods != 0 ) {
    gv->state = STAND_BY;
    Serial.println("MKG to STB");
  }

  /*
   * 
   */
  if ( gv->state == MAKING_COFFEE && gv->coffee_ready && gv->coffee_pods == 0 ) {
    gv->state = MAINTENANCE;
    Serial.println("MKG to MAIN");
  }
}

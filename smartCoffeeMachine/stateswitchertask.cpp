#include "stateswitchertask.h"
#include "Arduino.h"

StateSwitcherTask::StateSwitcherTask( GlobalVar_t* gv ) {
	this->gv = gv;
	gv->state = STAND_BY;
}

void StateSwitcherTask::Exec() {
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
	if ( gv->state == ON && gv->time_elapsed && !gv->time_acquired && gv->hc_in_range ) {
		gv->state = READY;
		gv->time_acquired = true;
		gv->msgs.add( "Welcome!" );
		Serial.println("ON to READY");
	}

	/*
	* Se la macchina non rileva più nessuno entro quella distanza per DT2a secondi, 
	* la macchina torna nella modalità ON.
	*/
	if ( gv->state == READY && gv->time_elapsed && !gv->time_acquired && !gv->hc_in_range ) {
		gv->state = ON;
		gv->time_acquired = true;
		Serial.println("READY to ON");
	}

	/*
	* Quando preme il pulsante, parte il processo [...] della durata di DT3 secondi.
	*/
	if ( gv->state == READY && digitalRead(BUTTON_PIN) == HIGH ) {
		gv->state = MAKING_COFFEE;
		Serial.println("READY to MKG");
	}

	/*
	* 
	*/
	if ( gv->state == MAKING_COFFEE && gv->coffee_ready ) {
		gv->state = TAKING_COFFEE;
		Serial.println("MKG to TKG");
	}

 /*
 * 
  */
  if ( gv->state == TAKING_COFFEE 
       && gv->coffee_pods > 0 
       && ( ( gv->time_elapsed && !gv->time_acquired ) || gv->hc_in_range ) ) {
    gv->state = STAND_BY;
    gv->coffee_ready = false;
    Serial.println("TKG to STB");
  }

	/*
	* 
	*/
	if ( gv->state == TAKING_COFFEE 
	     && ( ( gv->time_elapsed && !gv->time_acquired ) || gv->hc_in_range ) 
	     && gv->coffee_pods == 0 ) {
		gv->state = MAINTENANCE;
    gv->coffee_ready = false;
		Serial.println("TKG to MAIN");
	}

	if ( gv->state == MAINTENANCE && gv->coffee_pods > 0 ) {
		gv->state = STAND_BY;
		Serial.println("MAIN to STB");
	}
}

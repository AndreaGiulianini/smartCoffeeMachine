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
	}

	/*
	* Dalla modalità ON la macchina torna in modalità STAND BY se non viene rilevata 
	* la presenza di nessuno per DT2b secondi.
	*/
	if ( gv->state == ON && gv->time_elapsed && !gv->time_acquired && !gv->pir_present ) {
		gv->state = STAND_BY;
		gv->time_acquired = true;
	}
	/*
	* Se viene rilevato qualcuno  ad una distanza inferiore a DIST1 cm per un certo 
	* numero DT1 secondi [...]e la macchina entra in una modalità READY.
	*/
	if ( gv->state == ON && gv->time_elapsed && !gv->time_acquired && gv->hc_in_range ) {
		gv->state = READY;
		gv->time_acquired = true;
		gv->msgs.add( "Welcome!" );
	}

	/*
	* Se la macchina non rileva più nessuno entro quella distanza per DT2a secondi, 
	* la macchina torna nella modalità ON.
	*/
	if ( gv->state == READY && gv->time_elapsed && !gv->time_acquired && !gv->hc_in_range ) {
		gv->state = ON;
		gv->time_acquired = true;
	}

	/*
	* Quando preme il pulsante, parte il processo [...] della durata di DT3 secondi.
	*/
	if ( gv->state == READY && digitalRead(BUTTON_PIN) == HIGH ) {
		gv->state = MAKING_COFFEE;
	}

	/*
	* 
	*/
	if ( gv->state == MAKING_COFFEE && gv->coffee_ready ) {
		gv->state = TAKING_COFFEE;
	}

 /*
 * 
  */
  if ( gv->state == TAKING_COFFEE 
       && gv->coffee_pods > 0 
       && ( ( gv->time_elapsed && !gv->time_acquired ) || gv->hc_in_range ) ) {
    gv->state = STAND_BY;
    gv->coffee_ready = false;
    gv->msgs.add( "Coffee taken" );
  }

	/*
	* 
	*/
	if ( gv->state == TAKING_COFFEE 
	     && ( ( gv->time_elapsed && !gv->time_acquired ) || gv->hc_in_range ) 
	     && gv->coffee_pods == 0 ) {
    //gv->msgs.add( "Coffee taken" );
		gv->state = MAINTENANCE;
    gv->coffee_ready = false;
    if ( gv->coffee_pods == 0 )
      gv->msgs.add( "No more coffee. Waiting for recharge" );
	}

	if ( gv->state == MAINTENANCE && gv->coffee_pods > 0 ) {
		gv->state = STAND_BY;
   Serial.println("STDB");
	}
}

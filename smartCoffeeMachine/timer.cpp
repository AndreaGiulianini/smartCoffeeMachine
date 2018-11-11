#include "timer.h"
#include "Arduino.h"

Timer::Timer( GlobalVar_t* gv ) {
  this->gv = gv;
}

void Timer::Exec() {
  void CheckTimerReset();
  // ON to STAND BY
  StartTimer( gv->state == ON && !gv->pir_present, DT2b );
  void CheckTimerReset();
  // ON to READY
  StartTimer( gv->state == ON && gv->hc_in_range, DT1 );
  void CheckTimerReset();
  // READY to ON
  StartTimer( gv->state == READY && !gv->hc_in_range, DT2a );
}

void Timer::CheckTimerReset() {
  //if ( gv->state == ON && ( gv->time_elapsed || ( gv->pir_present && !gv->hc_in_range ) )
  //  || gv->state == READY && ( gv->time_elapsed || gv->pir_present ) )
  if ( ( gv->state == ON && gv->pir_present && !gv->hc_in_range )
    || ( gv->state == READY && gv->pir_present ) )
    timer_started = false;
}

void Timer::StartTimer( bool condition, unsigned long time_to_reach ) {
  if ( condition ) {
    if ( !timer_started ) {
      timer_started = true;
      initial_time = millis();
    }
    gv->time_elapsed = millis() - initial_time > time_to_reach;
  }
}

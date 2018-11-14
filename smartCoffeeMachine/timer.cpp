#include "timer.h"
#include "Arduino.h"
#include "scheduler.h"

extern int wdt_call_cicle;

Timer::Timer( GlobalVar_t* gv ) {
  this->gv = gv;
}

void Timer::Exec() {
  CheckTimerReset();
  // ON to STAND BY
  StartTimer( gv->state == ON && !gv->pir_present, DT2b );
  CheckTimerReset();
  // ON to READY
  StartTimer( gv->state == ON && gv->hc_in_range, DT1 );
  CheckTimerReset();
  // READY to ON
  StartTimer( gv->state == READY && !gv->hc_in_range, DT2a );
}

void Timer::CheckTimerReset() {
  if ( ( gv->state == ON && gv->pir_present && !gv->hc_in_range )
    || ( gv->state == READY && gv->pir_present ) ) {
    timer_started = false;
  }
}

void Timer::StartTimer( bool condition, unsigned long time_to_reach ) {
  if ( condition ) {
    if ( !timer_started ) {
      timer_started = true;
      initial_time = wdt_call_cicle / 4;
    }
    if ( ( wdt_call_cicle / 4 ) - initial_time > time_to_reach && gv->time_acquired ) {
      gv->time_elapsed = true;
      gv->time_acquired = false;
    } else
      gv->time_elapsed = false;
  }
}

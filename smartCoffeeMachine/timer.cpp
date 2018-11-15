#include "timer.h"
#include "Arduino.h"

Timer::Timer( GlobalVar_t* gv, Scheduler* scheduler ) {
  this->gv = gv;
  this->scheduler = scheduler;
}

void Timer::Exec() {
  if ( gv->time_acquired )
    gv->time_elapsed = false;
  CheckTimerReset();
  // ON to STAND BY
  StartTimer( gv->state == ON && !gv->pir_present, DT2b );
  //CheckTimerReset();
  // ON to READY
  StartTimer( gv->state == ON && gv->hc_in_range, DT1 );
  //CheckTimerReset();
  // READY to ON
  StartTimer( gv->state == READY && !gv->hc_in_range, DT2a );
  //CheckTimerReset();
  StartTimer( gv->state == MAKING_COFFEE, DT3 / 3.0 );
}

void Timer::CheckTimerReset() {
  if ( timer_started && ( ( gv->state == ON && gv->pir_present && !gv->hc_in_range )
    || ( gv->state == READY && gv->hc_in_range ) ) ) {
    timer_started = false;
  }
}

void Timer::StartTimer( bool condition, unsigned long time_to_reach ) {
  if ( condition ) {
    if ( !timer_started ) {
      timer_started = true;
      initial_time = scheduler->GetTime();
    }
    if ( ( scheduler->GetTime() - initial_time >= ( time_to_reach * 1000 ) ) && gv->time_acquired ) {
      gv->time_elapsed = true;
      gv->time_acquired = false;
    } else
      gv->time_elapsed = false;
  }
}

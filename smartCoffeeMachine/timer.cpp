#include "timer.h"
#include "Arduino.h"

Timer::Timer( GlobalVar_t* gv, Scheduler* scheduler ) {
  this->gv = gv;
  this->scheduler = scheduler;
  next_state = UNKNOWN_STATE;
}

void Timer::Exec() {
  CheckTimerReset();
  // ON to STAND BY
  StartTimer( gv->state == ON && !gv->pir_present, DT2b, STAND_BY );
  // ON to READY
  StartTimer( gv->state == ON && gv->hc_in_range, DT1, READY );
  // READY to ON
  StartTimer( gv->state == READY && !gv->hc_in_range, DT2a, ON );
  // 
  StartTimer( gv->state == MAKING_COFFEE, DT3 / 3.0 );
}

void Timer::CheckTimerReset() {
  if ( gv->time_acquired 
      || ( gv->state == ON && next_state == STAND_BY && gv->pir_present && !gv->time_acquired ) 
      || ( gv->state == ON && next_state == READY && !gv->hc_in_range && !gv->time_acquired ) 
      || ( gv->state == READY && next_state == ON && gv->hc_in_range && !gv->time_acquired ) ) {
    timer_started = false;
    gv->time_elapsed = false;
    gv->time_acquired = false;
  }
}

void Timer::StartTimer( bool condition, unsigned long time_to_reach, State_t next_state ) {
  if ( condition ) {
    if ( !timer_started ) {
      timer_started = true;
      initial_time = scheduler->GetTime();
      gv->time_elapsed = false;
      gv->time_acquired = false;
      this->next_state = next_state;
    }
    gv->time_elapsed = timer_started && ( scheduler->GetTime() - initial_time >= ( time_to_reach * 1000 ) );
  }
}

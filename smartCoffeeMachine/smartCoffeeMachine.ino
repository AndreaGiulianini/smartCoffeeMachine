#include "globalvar.h"
#include "scheduler.h"
#include "stateswitcher.h"
#include "timer.h"
#include "presencereader.h"

#define BAUD_RATE 9600

void setup() {
  Serial.begin( BAUD_RATE );
  
  GlobalVar_t gv {
    .state = STAND_BY,
    .pir_present = false,
    .hc_in_range = false,
    .time_elapsed = false,
    .make_coffee = false,
    .coffee_ready = false,
    .coffee_pods = NMAX_CAFFEE
  };
  
  Scheduler s = Scheduler();
  s.SetPeriod( 1000 );
  s.AttachTask( new StateSwitcher( &gv ) );
  s.AttachTask( new Timer( &gv ) );
  s.AttachTask( new PresenceReader( &gv ) );
  s.StartSchedule();
}

void loop() {
}

// interrupt del pir esce da sleep e fa partire scheduler

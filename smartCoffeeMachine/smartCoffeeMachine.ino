#include "globalvar.h"
#include "scheduler.h"
#include "stateswitcher.h"
#include "timer.h"
#include "presencereader.h"

#define BAUD_RATE 2000000 // se non invia i dati velocemente entra in sleep prima di aver finito

void setup() {
  Serial.begin( BAUD_RATE );
  pinMode(SP_TRIG_PIN, OUTPUT);
  pinMode(SP_ECHO_PIN, INPUT);
  
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
  s.AttachTask( new StateSwitcher( &gv ) );
  s.AttachTask( new Timer( &gv ) );
  s.AttachTask( new PresenceReader( &gv ) );
  s.StartSchedule();
}

void loop() {
}


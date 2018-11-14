#include "globalvar.h"
#include "scheduler.h"
#include "stateswitcher.h"
#include "timer.h"
#include "presencereader.h"
#include "distance_task.h"
#include "make_coffee_tash.h"

#define BAUD_RATE 2000000 // se non invia i dati velocemente entra in sleep prima di aver finito
Scheduler s;
void setup() {
  Serial.begin( BAUD_RATE );
  pinMode(PIR_PIN, INPUT);
  pinMode(SP_TRIG_PIN, OUTPUT);
  pinMode(SP_ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  
  GlobalVar_t gv {
    .state = STAND_BY,
    .pir_present = false,
    .hc_in_range = false,
    .time_elapsed = false,
    .time_acquired = true,
    .make_coffee = false,
    .coffee_ready = false,
    .coffee_pods = NMAX_CAFFEE
  };

  s = Scheduler();
  s.AttachTask( new StateSwitcher( &gv ) );
  s.AttachTask( new Timer( &gv, &s ) );
  s.AttachTask( new PresenceReader( &gv ) );
  s.AttachTask( new Distance( &gv ) );
  s.StartSchedule();
}

void loop() {}

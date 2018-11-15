#include "globalvar.h"
#include "scheduler.h"
#include "stateswitcher.h"
#include "timer.h"
#include "presencereader.h"
#include "distance_task.h"
#include "make_coffee_task.h"
#include "postman.h"
#include "src/lib/msgservice.h"

void setup() {
  pinMode( PIR_PIN, INPUT );
  pinMode( SP_TRIG_PIN, OUTPUT );
  pinMode( SP_ECHO_PIN, INPUT );
  pinMode( BUTTON_PIN, INPUT );
  pinMode( LED1_PIN, OUTPUT );
  pinMode( LED2_PIN, OUTPUT );
  pinMode( LED3_PIN, OUTPUT );
  pinMode( POT_PIN, INPUT );
  
  GlobalVar_t gv {
    .state = STAND_BY,
    .pir_present = false,
    .hc_in_range = false,
    .time_elapsed = false,
    .time_acquired = true,
    .make_coffee = false,
    .coffee_ready = false,
    .coffee_pods = NMAX_CAFFEE,
    .msgs = LinkedList< String >()
  };

  MsgService.init( BAUD_RATE );

  Scheduler s = Scheduler();
  s.AttachTask( new StateSwitcher( &gv ) );
  s.AttachTask( new Timer( &gv, &s ) );
  s.AttachTask( new PresenceReader( &gv ) );
  s.AttachTask( new Distance( &gv ) );
  s.AttachTask( new Coffee( &gv ) );
  s.AttachTask( new Postman( &gv ) );
  s.StartSchedule();
}

void loop() {}

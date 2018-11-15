#include "globalvar.h"
#include "scheduler.h"
#include "stateswitchertask.h"
#include "timertask.h"
#include "presencetask.h"
#include "distancetask.h"
#include "makecoffeetask.h"
#include "postmantask.h"
#include "potentiometertask.h"
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
		.coffee_ready = false,
		.coffee_pods = NMAX_CAFFEE,
		.msgs = LinkedList< String >()
	};

	MsgService.init( BAUD_RATE );

	Scheduler s = Scheduler();
	s.AttachTask( new StateSwitcherTask( &gv ) );
	s.AttachTask( new TimerTask( &gv, &s ) );
	s.AttachTask( new MakeCoffeeTask( &gv ) );
	s.AttachTask( new PostmanTask( &gv ) );
	s.AttachTask( new PresenceTask( &gv ) );
	s.AttachTask( new DistanceTask( &gv ) );
	s.AttachTask( new PotentiometerTask( &gv ) );
	s.StartSchedule();
}

void loop() {}

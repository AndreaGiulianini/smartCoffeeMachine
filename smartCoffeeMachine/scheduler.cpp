#include "scheduler.h"
#include "avr/sleep.h"
#include "avr/power.h"
#include "avr/wdt.h"
#include "Arduino.h"
#include "math.h"

Scheduler::Scheduler() {
	tasks = LinkedList< TaskData_t* >();
	wdt_call_count = 0;
}

void Scheduler::AttachTask( ITask* task, unsigned long period ) {
	tasks.add( new TaskData_t { task, period, 0 } );
}

void Scheduler::DetachTask( ITask* task ) {
	for ( int i = 0; i < tasks.size(); i++ )
		if ( task == tasks.get( i )->task )
			tasks.remove( i );
}

void Scheduler::StartSchedule( bool _start ) {
	while( _start ) {
		Sleep();
	  for ( int i = 0; i < tasks.size(); i++ ) {
			TaskData_t* td = tasks.get( i );
			if ( td != nullptr && td->period - ( ( micros() - wakeup_time ) / 1000 + wdt_call_count * SCHED_SPEED ) ) {
				td->last_exec = wdt_call_count * SCHED_SPEED + ( micros() - wakeup_time ) / 1000 ;
				td->task->Exec();
			}
		}
	}
}

long Scheduler::GetTime() {
	return wdt_call_count * SCHED_SPEED + round( ( micros() - wakeup_time ) / 1000.0 );
}

void Scheduler::Sleep() { 
	cli();                                                               // no interrupts

	MCUSR = 0x00;                         /* The MCU Status Register provides information 
											* on which reset source caused an MCU reset:
											* - Power-on Reset Flag            ( BIT0 )  ;
											* - External Reset Flag            ( BIT1 )  ;
											* - Brown-out Reset Flag           ( BIT2 )  ;
											* - Watchdog System Reset Flag     ( BIT3 );*/
									
	WDTCSR = (1 << WDCE) | (1 << WDE);  /* "Explain" that WDE has to be set before change 
			the WDT prescaler: http://forum.arduino.cc/index.php?topic=48626.0#msg347960 */

	/* WDTCSR – Watchdog Timer Control Register:
	* - WDIF: Watchdog Interrupt Flag: 
	*   This bit is set when a time-out occurs in the Watchdog Timer and the Watchdog 
	*   Timer is configured for interrupt. WDIF is cleared by hardware when executing the 
	*   corresponding interrupt handling vector
	* - WDIE: Watchdog Interrupt Enable:
	*   Used to set ( in combination with WDE ) wdt timeout mode ( none, interrupt, reset, 
	*   interrupt + reset )
	* - WDCE: Watchdog Change Enable:
	*   This bit is used in timed sequences for changing WDE and prescaler bits. To clear 
	*   the WDE bit, and/or change the prescaler bits, WDCE must be set.
	* - WDE: Watchdog System Reset Enable
	*   Used to set ( in combination with WDIE ) wdt timeout mode ( none, interrupt, re-
	*   set, interrupt + reset )
	* - WDP[3:0]: Watchdog Timer Prescaler 3, 2, 1 and 0
	*/
	WDTCSR = (0 << WDIF) | (1 << WDIE) | (0 << WDP3) | (1 << WDCE) 
			| (1 << WDE) | (1 << WDP2) | (0 << WDP1) | (0 << WDP0);
			
	WDTCSR &= ~(1 << WDE);                                       /* set the WDE pin to 0: 
										1 << WDE = 0b00001000 -> ~ = NOT -> 0b11110111 */
	
	set_sleep_mode (SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
	sei();  // interrupts
	sleep_enable();
	sleep_cpu ();            // now goes to sleep and waits for the interrupt
	
	wakeup_time = micros();
	wdt_call_count++;
}

ISR (WDT_vect) {
	WDTCSR = 0x00;      // reset all
}

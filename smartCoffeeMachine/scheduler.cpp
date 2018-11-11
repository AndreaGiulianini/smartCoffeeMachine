#include "scheduler.h"
#include "avr/sleep.h"
#include "avr/power.h"
#include "avr/wdt.h"
#include "Arduino.h"

Scheduler::Scheduler() {
  tasks = LinkedList< ITask* >();
}

void Scheduler::AttachTask( ITask* task ) {
  tasks.add( task );
}

void Scheduler::DetachTask( ITask* task ) {
  for ( int i = 0; i < tasks.size(); i++ )
    if ( task == tasks.get( i ) )
      tasks.remove( i );
}

void Scheduler::StartSchedule( bool _start ) {
  int i = 0;
  while( _start ) {
  // if pir -> attiva timer + intrpt
    Sleep();
    if ( tasks.size() > 0 ) {
      if ( i >= tasks.size() )
        i = 0;
      tasks.get( i++ )->Exec();
    }
  }
}

void Scheduler::Sleep() { 
  noInterrupts ();   // timed sequence below

  MCUSR = 0;                          // reset various flags
  WDTCSR |= 0b00011000;               // see docs, set WDCE, WDE
  WDTCSR =  0b01000000 | WDTO_120MS;    // set WDIE, and appropriate delay
  wdt_reset();
  
  byte adcsra_save = ADCSRA;
  ADCSRA = 0;  // disable ADC
  power_all_disable ();   // turn off all modules
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
  sleep_enable();
  interrupts ();
  sleep_cpu ();            // now goes to Sleep and waits for the interrupt

  ADCSRA = adcsra_save;  // stop power reduction
  power_all_enable ();   // turn on all modules
}

// watchdog interrupt
ISR (WDT_vect) {
  wdt_disable();
}

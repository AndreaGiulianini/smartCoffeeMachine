#include "scheduler.h"
#include "avr/sleep.h"
#include "avr/power.h"
#include "Arduino.h"

LinkedList< ITask* > tasks;

Scheduler::Scheduler() {
  tasks = LinkedList< ITask* >();
}

void Scheduler::SetPeriod( unsigned int period ) {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 16.384*period; 
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void Scheduler::StartSchedule( bool _start ) {
  while( true )
  // if pir -> attiva timer + intrpt
    Sleep();
}

void Scheduler::AttachTask( ITask* task ) {
  tasks.add( task );
}

void Scheduler::DetachTask( ITask* task ) {
  for ( int i = 0; i < tasks.size(); i++ )
    if ( task == tasks.get( i ) )
      tasks.remove( i );
}

void Scheduler::Sleep(){
  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();
  power_adc_disable();
  power_spi_disable();
  power_timer0_disable();
  power_timer2_disable();
  power_twi_disable();
  sleep_mode();
  sleep_disable();
  power_all_enable();  
}

ISR(TIMER1_COMPA_vect) {
  static int i = 0;
  if ( tasks.size() > 0 ) {
    if ( i >= tasks.size() )
      i = 0;
    tasks.get( i++ )->Exec();
  }
}

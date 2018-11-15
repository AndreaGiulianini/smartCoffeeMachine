#include "make_coffee_task.h"
#include "src/lib/msgservice.h"
#include "Arduino.h"

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

Coffee::Coffee( GlobalVar_t* gv ) {
  this->gv = gv;
  button_flag = true;
  l1_state = l2_state = l3_state = LOW;
}

void Coffee::Exec() {
  // SPOSTA IN STATE SWITCHER
  if( digitalRead(BUTTON_PIN) == HIGH && button_flag && l1_state == LOW ){
    gv->coffee_pods--;
    gv->msgs.add( "Making a coffee" );
    l1_state = HIGH;
    button_flag = false;
  } else if ( digitalRead(BUTTON_PIN) == LOW )
    button_flag = true;
    
  if ( l1_state == HIGH && l2_state == LOW && gv->time_elapsed && !gv->time_acquired ) {
    l2_state = HIGH;
    gv->time_acquired = true;
  }
  
  if ( l2_state == HIGH && l3_state == LOW && gv->time_elapsed && !gv->time_acquired ) {
    l3_state = HIGH;
    gv->time_acquired = true;
  }
  
  if ( l3_state == HIGH && !gv->coffee_ready && gv->time_elapsed && !gv->time_acquired ) {
    gv->time_acquired = true;
    gv->coffee_ready = true;
    gv->msgs.add( "The coffee is ready" );
    gv->msgs.add( STR(DT4) );
  }
  
  if ( gv->coffee_ready && gv->time_elapsed && !gv->time_acquired ) {
    l1_state = l2_state = l3_state = LOW;
    gv->time_acquired = true;
  }
  
  digitalWrite( LED1_PIN, l1_state );
  digitalWrite( LED2_PIN, l2_state );
  digitalWrite( LED3_PIN, l3_state );
  
  if( gv->coffee_pods == 0 )
    gv->msgs.add( "No more coffee. Waiting for recharge" );

}

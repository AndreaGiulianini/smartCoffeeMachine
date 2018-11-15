#include "make_coffee_task.h"
#include "src/lib/msgservice.h"
#include "Arduino.h"

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

Coffee::Coffee( GlobalVar_t* gv ) {
  this->gv = gv;
  msgs = LinkedList< String >();
  l1_state = l2_state = l3_state = LOW;
}

void Coffee::Exec() {
  if( digitalRead(BUTTON_PIN) == HIGH ){
    gv->coffee_pods--;
    msgs.add( "Making coffee" );
    l1_state = HIGH;
  }
  if ( l1_state == HIGH && l2_state == LOW && gv->time_elapsed && !gv->time_acquired ) {
    l2_state = HIGH;
    gv->time_acquired = true;//time acquired
  }
  if ( l2_state == HIGH && l3_state == LOW && gv->time_elapsed && !gv->time_acquired ) {
    l3_state = HIGH;
    gv->time_acquired = true;
  }
  if ( l3_state == HIGH && !gv->coffee_ready && gv->time_elapsed && !gv->time_acquired ) {
    gv->time_acquired = true;
    gv->coffee_ready = true;
    msgs.add( "The coffee is ready" );
    msgs.add( STR(DT4) );
  }
  if ( gv->coffee_ready && gv->time_elapsed && !gv->time_acquired ) {
    l1_state = l2_state = l3_state = LOW;
    gv->time_acquired = true;
  }
  digitalWrite( LED1_PIN, l1_state );
  digitalWrite( LED2_PIN, l2_state );
  digitalWrite( LED3_PIN, l3_state );
  
  if( gv->coffee_pods == 0 )
    msgs.add( "No more coffee. Waiting for recharge" );

  if ( msgs.size() > 0 && gv->msg_to_send == "" )
    gv->msg_to_send = msgs.remove(0);

}

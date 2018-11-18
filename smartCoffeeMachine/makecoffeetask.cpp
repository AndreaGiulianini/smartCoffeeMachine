#include "makecoffeetask.h"
#include "src/lib/msgservice.h"
#include "Arduino.h"

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

MakeCoffeeTask::MakeCoffeeTask( GlobalVar_t* gv ) {
  this->gv = gv;
  l1_state = l2_state = l3_state = LOW;
}

void MakeCoffeeTask::Exec() {
  if ( gv->state == MAKING_COFFEE && l1_state == LOW ) {
    gv->coffee_pods--;
    gv->msgs.add( "Making a coffee" );
    l1_state = HIGH;
  }

  if ( l1_state == HIGH && l2_state == LOW && gv->time_elapsed && !gv->time_acquired ) {
    l2_state = HIGH;
    gv->time_acquired = true;
  }

  if ( l2_state == HIGH && l3_state == LOW && gv->time_elapsed && !gv->time_acquired ) {
    l3_state = HIGH;
    gv->time_acquired = true;
  }

  if ( l3_state == HIGH && !gv->coffee_ready && gv->time_elapsed && !gv->time_acquired ) {
    l1_state = l2_state = l3_state = LOW;
    gv->time_acquired = true;
    gv->coffee_ready = true;
    gv->msgs.add( "The coffee is ready" );
  }

  digitalWrite( LED1_PIN, l1_state );
  digitalWrite( LED2_PIN, l2_state );
  digitalWrite( LED3_PIN, l3_state );

}

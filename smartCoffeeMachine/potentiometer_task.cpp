#include "potentiometer_task.h"
#include "src/lib/msgservice.h"
#include "Arduino.h"

Sugar::Sugar( GlobalVar_t* gv ) {
    this->gv = gv;
    msgs = LinkedList< String >();
    sugar = 0;
}

void Sugar::Exec() {
    float val = analogRead(POT_PIN);
    if( gv->state == READY && val != sugar){
        sugar = val;
        msgs.add( String( "sugar: " + String( sugar ) ) );
    }

    if ( msgs.size() > 0 )
        gv->msg_to_send = msgs.remove( 0 );
}

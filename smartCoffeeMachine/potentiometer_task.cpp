#include "potentiometer_task.h"
#include "src/lib/msgservice.h"
#include "Arduino.h"

Sugar::Sugar( GlobalVar_t* gv ) {
    this->gv = gv;
    sugar = 0;
}

void Sugar::Exec() {
    float val = analogRead(POT_PIN);
    if( gv->state == READY && val != sugar){
        sugar = val;
        gv->msgs.add( String( "sugar: " + String( sugar ) ) );
    }
    
}

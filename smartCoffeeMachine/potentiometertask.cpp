#include "potentiometertask.h"
#include "src/lib/msgservice.h"
#include "Arduino.h"

PotentiometerTask::PotentiometerTask( GlobalVar_t* gv ) {
    this->gv = gv;
    sugar_quantity = 0;
}

void PotentiometerTask::Exec() {
    float new_sugar_quantity = analogRead(POT_PIN);
    if( gv->state == READY && new_sugar_quantity != sugar_quantity){
        sugar_quantity = static_cast< int >( new_sugar_quantity / POSSIBLE_QUANTITY );
        gv->msgs.add( String( "Sugar: " + String( sugar_quantity ) ) );
    }
    
}

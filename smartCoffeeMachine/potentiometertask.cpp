#include "potentiometertask.h"
#include "src/lib/msgservice.h"
#include "Arduino.h"
#include "math.h"

PotentiometerTask::PotentiometerTask( GlobalVar_t* gv ) {
    this->gv = gv;
    sugar_quantity = round( analogRead(POT_PIN) / POSSIBLE_QUANTITY );
}

void PotentiometerTask::Exec() {
    float new_sugar_quantity = round( analogRead(POT_PIN) / POSSIBLE_QUANTITY );
    if( gv->state == READY && new_sugar_quantity != sugar_quantity){
        sugar_quantity = new_sugar_quantity; 
        gv->msgs.add( new String( "Sugar: " + String( sugar_quantity ) ) );
    }

}

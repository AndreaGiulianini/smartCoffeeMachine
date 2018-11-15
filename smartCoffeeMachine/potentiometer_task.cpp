#include "potentiometer_task.h"
#include "msgservice.h"
#include "Arduino.h"

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

Sugar::Sugar( GlobalVar_t* gv ) {
    this->gv = gv;
    MsgService.init();
    sugar = 0;
}

void Sugar::Exec() {
    float val = analogRead(POT_PIN);
    if( gv->state == READY && val != sugar){
        sugar = val;
        String s = String("sugar:"+sugar);
        MsgService.sendMsg(s);
    }
}

#include "make_coffee_task.h"
#include "msgservice.h"
#include "Arduino.h"

Coffee::Coffee( GlobalVar_t* gv ) {
    this->gv = gv;
    MsgService.init();
}

void Coffee::Exec() {
    btn_pressed = digitalRead(BUTTON_PIN) == HIGH ? true : false; 
    if( btn_pressed ){
        gv->coffee_pods--;
        String s = "Making coffee";
        MsgService.sendMsg(s);
        digitalWrite(LED1_PIN,HIGH);
        delay(DT3/3);
        digitalWrite(LED2_PIN,HIGH);
        delay(DT3/3);
        digitalWrite(LED3_PIN,HIGH);
        delay(DT3/3);
        gv->coffee_ready = true;
        s = "The coffee is ready";
        MsgService.sendMsg(s);
        MsgService.sendMsg(DT4);
        delay(DT4);
    }
    if( gv->coffee_pods = 0 ){
      String s = "No more coffee. Waiting for recharge";
        MsgService.sendMsg(s);
        if (MsgService.isMsgAvailable()) {
            Msg* msg = MsgService.receiveMsg();    
            if(msg->getContent()){
                gv->coffee_pods = NMAX_CAFFEE;
            }
            delete msg;
        }
    }
}

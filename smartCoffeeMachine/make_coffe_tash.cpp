#include "make_coffee_task.h"
#include "msgservice.h"
#include "Arduino.h"

Coffee::Coffee( GlobalVar_t* gv ) {
    this->gv = gv;
    MsgService.init();
}

void Coffee::Exec() {
    btn_pressed = digitalRead(BUTTON_PIN) ? true : false; 
    if( btn_pressed ){
        gv->coffee_pods--;
        MsgService.sendMsg("Making coffee");
        digitalWrite(LED1_PIN,HIGH)
        delay(DT3/3);
        digitalWrite(LED2_PIN,HIGH)
        delay(DT3/3);
        digitalWrite(LED3_PIN,HIGH)
        delay(DT3/3);
        gv->coffee_ready = true;
        MsgService.sendMsg("The coffee is ready");
        MsgService.sendMsg(DT4);
        delay(DT4);
    }
    if( gv->coffee_pods = 0 ){
        MsgService.sendMsg("No more coffee. Waiting for recharge");
        if (MsgService.isMsgAvailable()) {
            Msg* msg = MsgService.receiveMsg();    
            if(msg->getContent()){
                gv->coffe_pods = NMAX_CAFFEE;
            }
            delete msg;
        }
    }
}
#include "postman.h"
#include "src/lib/msgservice.h"

Postman::Postman( GlobalVar_t* gv ) {
  this->gv = gv;

  MsgService.init( BAUD_RATE );
}

void Postman::Exec() {
  if( gv->msg_to_send != "" ) {
    MsgService.sendMsg( gv->msg_to_send );
    gv->msg_to_send = "";
  }

  if ( MsgService.isMsgAvailable() ) {
    Msg *msg = MsgService.receiveMsg();    
    if( msg->getContent() )
      gv->coffee_pods = NMAX_CAFFEE;
    delete msg;
  }
}

#include "postman.h"
#include "src/lib/msgservice.h"

Postman::Postman( GlobalVar_t* gv ) {
  this->gv = gv;
}

void Postman::Exec() {
  if( gv->msgs.size() > 0 )
    MsgService.sendMsg( gv->msgs.remove( 0 ) );

  if ( MsgService.isMsgAvailable() ) {
    Msg *msg = MsgService.receiveMsg();    
    if( msg->getContent() )
      gv->coffee_pods = NMAX_CAFFEE;
    delete msg;
  }
}

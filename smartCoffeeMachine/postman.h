#ifndef __MESSAGE_DELIVER__
#define __MESSAGE_DELIVER__

#include "globalvar.h"
#include "itask.h"

class Postman : public ITask {

  private:

    GlobalVar_t* gv;

  public:

    Postman( GlobalVar_t* gv );

    void Exec() override;
  
};

#endif

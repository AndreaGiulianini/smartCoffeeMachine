#ifndef __SUGAR__
#define __SUGAR__

#include "globalvar.h"
#include "itask.h"
#include "LinkedList.h"

class Sugar : public ITask {

  private:

    GlobalVar_t* gv;

    LinkedList< String > msgs;
    
    float sugar;

  public:

    Sugar( GlobalVar_t* gv );

    void Exec() override;

};

#endif

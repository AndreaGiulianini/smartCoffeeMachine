#ifndef __COFFEE__
#define __COFFEE__

#include "globalvar.h"
#include "itask.h"
#include "LinkedList.h"

class Coffee : public ITask {

  private:

    GlobalVar_t* gv;

    LinkedList< String > msgs;
    
    int l1_state, l2_state, l3_state;

  public:

    Coffee( GlobalVar_t* gv );

    void Exec() override;

};

#endif

#ifndef __COFFEE__
#define __COFFEE__

#include "globalvar.h"
#include "itask.h"

class Coffee : public ITask {

  private:

    GlobalVar_t* gv;
    
    int l1_state, l2_state, l3_state;

  public:

    Coffee( GlobalVar_t* gv );

    void Exec() override;

};

#endif

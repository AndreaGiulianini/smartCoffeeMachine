#ifndef __SUGAR__
#define __SUGAR__

#include "globalvar.h"
#include "itask.h"

class Sugar : public ITask {

  private:

    GlobalVar_t* gv;
    
    float sugar;

  public:

    Sugar( GlobalVar_t* gv );

    void Exec() override;

};

#endif

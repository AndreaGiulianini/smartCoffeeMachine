#ifndef __DISTANCE__
#define __DISTANCE__

#include "globalvar.h"
#include "itask.h"

class Distance : public ITask {

  private:

    GlobalVar_t* gv;
    

  public:

    Distance( GlobalVar_t* gv );

    void Exec() override;

  private:
    
    void getDistance();
  
};

#endif
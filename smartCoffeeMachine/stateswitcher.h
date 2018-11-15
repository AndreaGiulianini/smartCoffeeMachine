#ifndef __STATE__
#define __STATE__

#include "globalvar.h"
#include "itask.h"

class StateSwitcher : public ITask {

  private:

    GlobalVar_t* gv;

    bool button_flag;

  public:

    StateSwitcher( GlobalVar_t* gv );

    void Exec() override;
  
};

#endif

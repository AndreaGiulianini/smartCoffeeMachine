#ifndef __COFFEE__
#define __COFFEE__

#include "globalvar.h"
#include "itask.h"

class Coffee : public ITask {

  private:

    GlobalVar_t* gv;
    bool btn_pressed;
    

  public:

    Coffee( GlobalVar_t* gv );

    void Exec() override;

};

#endif

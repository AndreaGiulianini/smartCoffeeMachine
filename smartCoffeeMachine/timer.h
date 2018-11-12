#ifndef __TIMER__
#define __TIMER__

#include "globalvar.h"
#include "itask.h"

class Timer : public ITask {

  private:

    GlobalVar_t* gv;

    bool timer_started;

    unsigned long initial_time;

  public:

    Timer( GlobalVar_t* gv );

    void Exec() override;

  private:
    
    void CheckTimerReset();

    void StartTimer( bool condition, unsigned long time_to_reach );
  
};

#endif

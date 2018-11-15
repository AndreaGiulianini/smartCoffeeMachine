#ifndef __TIMER_TASK__
#define __TIMER_TASK__

#include "globalvar.h"
#include "itask.h"
#include "scheduler.h"

class TimerTask : public ITask {

  private:

    GlobalVar_t* gv;

    Scheduler* scheduler;

    bool timer_started;

    unsigned long initial_time;

    State_t next_state;

  public:

    TimerTask( GlobalVar_t* gv, Scheduler* scheduler );

    void Exec() override;

  private:
    
    void CheckTimerReset();

    void StartTimer( bool condition, unsigned long time_to_reach, State_t next_state = UNKNOWN_STATE );
  
};

#endif

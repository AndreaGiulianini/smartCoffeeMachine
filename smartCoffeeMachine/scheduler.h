#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "globalvar.h"
#include "itask.h"
#include "LinkedList.h"

class Scheduler {

  private:

    LinkedList< ITask* > tasks;

  public:

    Scheduler();

    void AttachTask( ITask* task );

    void DetachTask( ITask* task );

    void StartSchedule( bool _true = true);

  private:

    void Sleep();
    
};

#endif

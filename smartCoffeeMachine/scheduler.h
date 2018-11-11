#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "LinkedList.h"
#include "itask.h"

class Scheduler {

  public:

    Scheduler();

    void SetPeriod( unsigned int period );

    void AttachTask( ITask* task );

    void DetachTask( ITask* task );

    void Start( bool _true = true);

  private:

    void Sleep();
    
};

#endif

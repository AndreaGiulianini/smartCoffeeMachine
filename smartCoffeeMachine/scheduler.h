#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "globalvar.h"
#include "itask.h"

#define DEFAULT_PERIOD 50
#define IN_SIZE 10

typedef struct TASK_DATA {
  ITask* task;
  unsigned long period;
  unsigned long last_exec;
} TaskData_t;

class Scheduler {

  private:

    TaskData_t** tasks;

    int vect_size;

    int vect_elem;

    unsigned long wakeup_time;

    long wdt_call_count;

  public:

    Scheduler();

    void AttachTask( ITask* task, unsigned long period = DEFAULT_PERIOD );

    void DetachTask( ITask* task );

    void StartSchedule( bool _true = true);

    long GetTime();

  private:

    void Sleep();
    
};

#endif

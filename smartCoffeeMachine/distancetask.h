#ifndef __DISTANCE_TASK__
#define __DISTANCE_TASK__

#include "globalvar.h"
#include "itask.h"

class DistanceTask : public ITask {

  	private:

    	GlobalVar_t* gv;

  	public:

    	DistanceTask( GlobalVar_t* gv );

    	void Exec() override;

  	private:

    	float GetDistance();
  
};

#endif

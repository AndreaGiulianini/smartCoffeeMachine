#ifndef __MAKE_COFFEE_TASK__
#define __MAKE_COFFEE_TASK__

#include "globalvar.h"
#include "itask.h"

class MakeCoffeeTask : public ITask {

	private:

		GlobalVar_t* gv;
	
		int l1_state, l2_state, l3_state;

	public:

		MakeCoffeeTask( GlobalVar_t* gv );

		void Exec() override;

};

#endif

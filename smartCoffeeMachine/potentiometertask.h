#ifndef __POTENTIOMETER_TASK__
#define __POTENTIOMETER_TASK__

#include "globalvar.h"
#include "itask.h"

#define POSSIBLE_QUANTITY ( 1024 / 5 )

class PotentiometerTask : public ITask {

	private:

		GlobalVar_t* gv;

		int sugar_quantity;

	public:

		PotentiometerTask( GlobalVar_t* gv );

		void Exec() override;

};

#endif

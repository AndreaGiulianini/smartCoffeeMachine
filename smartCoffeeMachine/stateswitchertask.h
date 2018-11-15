#ifndef __STATE_SWITCHER_TASK__
#define __STATE_SWITCHER_TASK__

#include "globalvar.h"
#include "itask.h"

class StateSwitcherTask : public ITask {

	private:

		GlobalVar_t* gv;

		bool button_flag;

	public:

		StateSwitcherTask( GlobalVar_t* gv );

		void Exec() override;

};

#endif

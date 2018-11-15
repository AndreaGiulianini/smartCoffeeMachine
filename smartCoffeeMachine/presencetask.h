#ifndef __PRESENCE_TASK__
#define __PRESENCE_TASK__

#include "globalvar.h"
#include "itask.h"

class PresenceTask : public ITask {

	private:

		GlobalVar_t* gv;

	public:

		PresenceTask( GlobalVar_t* gv );

		void Exec() override;

};

#endif

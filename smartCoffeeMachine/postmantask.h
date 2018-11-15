#ifndef __POSTMAN_TASK__
#define __POSTMAN_TASK__

#include "globalvar.h"
#include "itask.h"

class PostmanTask : public ITask {

	private:

		GlobalVar_t* gv;

	public:

		PostmanTask( GlobalVar_t* gv );

		void Exec() override;

};

#endif

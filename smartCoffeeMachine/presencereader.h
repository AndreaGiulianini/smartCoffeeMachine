#ifndef __PRESENCE_READER__
#define __PRESENCE_READER__

#include "globalvar.h"
#include "itask.h"

class PresenceReader : public ITask {

  private:

    GlobalVar_t* gv;

  public:

    PresenceReader( GlobalVar_t* gv );

    void Exec() override;
    
};

#endif

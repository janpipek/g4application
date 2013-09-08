#ifndef RunManager_HH
#define RunManager_HH

#include <G4RunManager.hh>

namespace g4
{
    /**
      * Custom version of G4RunManager that enables us to
      * step in the middle of state transitions.
      *
      * Note: it can be done in another way, from outside
      *   via special callback classes (see manual).
      */
    class RunManager : public G4RunManager
    {
    public:     
        /**
          * Do what is necessary for the application and do standard initialize.
          *
          * This invokes all the builders from plugins.
          * It is called with /run/initialize         
          */
        virtual void Initialize();

        virtual void DoEventLoop(G4int n_event,const char* macroFile=0,G4int n_select=-1);

        virtual void RunTermination();
    };
}

#endif // RunManager_HH

#ifndef RunManager_HH
#define RunManager_HH

#include <G4RunManager.hh>

#include "CompositeEventAction.hh"
#include "CompositeRunAction.hh"
#include "CompositeSteppingAction.hh"
#include "CompositeTrackingAction.hh"

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
        RunManager();

        /**
          * Do what is necessary for the application and do standard initialize.
          *
          * This invokes all the builders from plugins.
          * It is called with /run/initialize         
          */
        virtual void Initialize();

        virtual void DoEventLoop(G4int n_event,const char* macroFile=0,G4int n_select=-1);

        virtual void RunTermination();

        void AddEventAction(G4UserEventAction* action)
        {
            _eventAction->AddSubAction(action);
        }

        void AddRunAction(G4UserRunAction* action)
        {
            _runAction->AddSubAction(action);
        }

        void AddSteppingAction(G4UserSteppingAction* action)
        {
            _steppingAction->AddSubAction(action);
        }

        void AddTrackingAction(G4UserTrackingAction* action)
        {
            _trackingAction->AddSubAction(action);
        }

        void InitializeUserActions();


    private:

        CompositeEventAction* _eventAction;

        CompositeRunAction* _runAction;

        CompositeSteppingAction* _steppingAction;

        CompositeTrackingAction* _trackingAction;
    };
}

#endif // RunManager_HH

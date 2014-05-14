#ifndef RunManager_HH
#define RunManager_HH

#include <G4RunManager.hh>

#include "CompositeEventAction.hh"
#include "CompositeRunAction.hh"
#include "CompositeSteppingAction.hh"
#include "CompositeTrackingAction.hh"

namespace g4
{
    class RunListener;

    /**
      * Class providing geometry, physics and particle generator
      * for the RunManger.
      *
      * In this library, G4Application is the only subclass
      * but it is possible to create other subclasses in applications
      * without G4Application class.
      */
    class RunInitializer
    {
    public:   
        virtual void InitializeGeometry() = 0;
        
        virtual void InitializePhysics() = 0;
        
        virtual void InitializeParticleGenerator() = 0;
    };

    /**
      * @short Custom version of G4RunManager that enables us to
      * step in the middle of state transitions.
      *
      * Note: it can be done in another way, from outside
      *   via special callback classes (see manual).
      *
      * AddXXXAction() methods register user actions
      * inside the composite actions.
      *
      * Run manager catches SIGINT signal and stops the run
      * instead of the whole application. Another interrupt 
      * makes the application really stop.
      */
    class RunManager : public G4RunManager
    {
    public:
        RunManager(RunInitializer& init);

        /**
          * @short Do what is necessary for the application and do standard initialize.
          *
          * This invokes all the builders from plugins.
          * It is called with /run/initialize         
          */
        virtual void Initialize();

        virtual void DoEventLoop(G4int n_event,const char* macroFile=0,G4int n_select=-1);

        virtual void RunTermination();

        void AddAction(G4UserEventAction* action)
        {
            _eventAction->AddSubAction(action);
        }

        void AddAction(G4UserRunAction* action)
        {
            _runAction->AddSubAction(action);
        }

        void AddAction(G4UserSteppingAction* action)
        {
            _steppingAction->AddSubAction(action);
        }

        void AddAction(G4UserTrackingAction* action)
        {
            _trackingAction->AddSubAction(action);
        }

        void InitializeUserActions();

        void AddListener(RunListener* listener);

        void RemoveListener(RunListener* listener);

    private:
        RunInitializer& _initializer;

        CompositeEventAction* _eventAction;

        CompositeRunAction* _runAction;

        CompositeSteppingAction* _steppingAction;

        CompositeTrackingAction* _trackingAction;

        std::vector<RunListener*> _listeners;
    };
}

#endif // RunManager_HH

#ifndef RunManager_HH
#define RunManager_HH

#include <G4RunManager.hh>

class G4UserEventAction;
class G4UserRunAction;
class G4UserSteppingAction;
class G4UserTrackingAction;

namespace g4
{
    class RunObserver;
    class CompositeEventAction;
    class CompositeRunAction;
    class CompositeSteppingAction;
    class CompositeTrackingAction;

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

        virtual ~RunInitializer() { }
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

        void AddAction(G4UserEventAction* action);

        void AddAction(G4UserRunAction* action);

        void AddAction(G4UserSteppingAction* action);

        void AddAction(G4UserTrackingAction* action);

        void InitializeUserActions();

        void AddObserver(RunObserver* observer);

        void RemoveObserver(RunObserver* observer);

    private:
        RunInitializer& _initializer;

        CompositeEventAction* _eventAction;

        CompositeRunAction* _runAction;

        CompositeSteppingAction* _steppingAction;

        CompositeTrackingAction* _trackingAction;

        std::vector<RunObserver*> _observers;
    };
}

#endif // RunManager_HH

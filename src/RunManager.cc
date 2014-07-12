#include "RunManager.hh"

#include <signal.h>
#include <unistd.h> 
#include <algorithm>

#include "CompositeEventAction.hh"
#include "CompositeRunAction.hh"
#include "CompositeSteppingAction.hh"
#include "CompositeTrackingAction.hh"

#include "RunObserver.hh"

// Run a specific member function for all the listeners.
// TODO: Change from macro to member function pointer type
#define OBSERVERS_DO( name ) {\
    for (vector<RunObserver*>::const_iterator it = _observers.begin(); it != _observers.end(); it++) \
    {\
        (*it)->name();\
    }\
}

using namespace std;
using namespace g4;

namespace g4
{   
    void terminate_run(int sig)
    {
        G4RunManager::GetRunManager()->AbortRun();
        (void) signal(SIGINT, SIG_DFL);
        sleep(1);
    }

    void RunManager::RunTermination()
    {
        (void) signal(SIGINT, SIG_DFL);
        G4RunManager::RunTermination();
    }

    RunManager::RunManager(RunInitializer& init)
        : _eventAction(0), _runAction(0), _trackingAction(0),
          _steppingAction(0), _initializer(init)
    { }

    void RunManager::AddObserver(RunObserver* observer)
    {
        if (std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
        {
            _observers.push_back(observer);
        }
    }

    void RunManager::RemoveObserver(RunObserver* observer)
    {
        std::vector<RunObserver*>::iterator needle = std::find(_observers.begin(), _observers.end(), observer);
        if (needle != _observers.end())
        {
            _observers.erase(needle);
        }        
    }   

    void RunManager::Initialize()
    {
        // 1) Physics
        OBSERVERS_DO( OnPhysicsInitializing );
        _initializer.InitializePhysics();
        InitializeUserActions(); // TODO: Move elsewhere?

        OBSERVERS_DO( OnPhysicsInitialized );
        
        // 2) Geometry
        OBSERVERS_DO( OnGeometryInitializing );
        _initializer.InitializeGeometry();
        OBSERVERS_DO( OnGeometryInitialized );
        
        // 3) Particle Generator
        OBSERVERS_DO( OnParticleGeneratorInitializing );
        _initializer.InitializeParticleGenerator();
        OBSERVERS_DO( OnParticleGeneratorInitialized );
        
        G4cout << "Initializing Geant4 run manager." << endl;
        // Initialize Geant4's own run manager
        G4RunManager::Initialize();
        OBSERVERS_DO( OnRunInitialized );
        G4cout << "Run initialized." << endl;
    }

    void RunManager::DoEventLoop(G4int n_event, const char *macroFile, G4int n_select)
    {
        (void) signal(SIGINT, terminate_run);
        G4RunManager::DoEventLoop(n_event, macroFile, n_select);
    }

    void RunManager::InitializeUserActions()
    {
        _eventAction = new CompositeEventAction;
        _runAction = new CompositeRunAction;
        _steppingAction = new CompositeSteppingAction;
        _trackingAction = new CompositeTrackingAction;

        SetUserAction(_eventAction);
        SetUserAction(_runAction);
        SetUserAction(_steppingAction);
        SetUserAction(_trackingAction);
    }

    void RunManager::AddAction(G4UserEventAction* action)
    {
        _eventAction->AddSubAction(action);
    }

    void RunManager::AddAction(G4UserRunAction* action)
    {
        _runAction->AddSubAction(action);
    }

    void RunManager::AddAction(G4UserSteppingAction* action)
    {
        _steppingAction->AddSubAction(action);
    }

    void RunManager::AddAction(G4UserTrackingAction* action)
    {
        _trackingAction->AddSubAction(action);
    }
}

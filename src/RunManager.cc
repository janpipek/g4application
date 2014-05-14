#include "RunManager.hh"

#include <signal.h>
#include <unistd.h> 
#include <algorithm>

#include "RunListener.hh"

// Run a specific member function for all the listeners.
// TODO: Change from macro to member function pointer type
#define LISTENERS_DO( name ) {\
    for (vector<RunListener*>::const_iterator it = _listeners.begin(); it != _listeners.end(); it++) \
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

    void RunManager::AddListener(RunListener* listener)
    {
        if (std::find(_listeners.begin(), _listeners.end(), listener) == _listeners.end())
        {
            _listeners.push_back(listener);
        }
    }

    void RunManager::RemoveListener(RunListener* listener)
    {
        std::vector<RunListener*>::iterator needle = std::find(_listeners.begin(), _listeners.end(), listener);
        if (needle != _listeners.end())
        {
            _listeners.erase(needle);
        }        
    }   

    void RunManager::Initialize()
    {
        // 1) Physics
        LISTENERS_DO( OnPhysicsInitializing );
        _initializer.InitializePhysics();
        InitializeUserActions(); // TODO: Move elsewhere?

        LISTENERS_DO( OnPhysicsInitialized );
        
        // 2) Geometry
        LISTENERS_DO( OnGeometryInitializing );
        _initializer.InitializeGeometry();
        LISTENERS_DO( OnGeometryInitialized );
        
        // 3) Particle Generator
        LISTENERS_DO( OnParticleGeneratorInitializing );
        _initializer.InitializeParticleGenerator();
        LISTENERS_DO( OnParticleGeneratorInitialized );
        
        G4cout << "Initializing Geant4 run manager." << endl;
        // Initialize Geant4's own run manager
        G4RunManager::Initialize();
        LISTENERS_DO( OnRunInitialized );
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
}

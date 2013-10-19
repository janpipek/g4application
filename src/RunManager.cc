#include "RunManager.hh"

#include <signal.h>
#include <unistd.h> 

#include "Plugin.hh"
#include "G4Application.hh"

// Run a specific member function for all the plugins
// TODO: Change from macro to member function pointer type
#define PLUGINS_DO( name ) {\
    for (vector<Plugin*>::const_iterator it = plugins.begin(); it != plugins.end(); it++) \
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

    RunManager::RunManager()
        : _eventAction(0), _runAction(0), _trackingAction(0),
          _steppingAction(0)
    {


    }

    void RunManager::Initialize()
    {
        G4Application* app = G4Application::GetInstance();  
        vector<Plugin*> plugins = app->GetPluginLoader()->GetPlugins();
        
        // 1) Physics
        PLUGINS_DO( OnPhysicsInitializing );
        app->InitializePhysics();
        InitializeUserActions(); // TODO: Move elsewhere?

        PLUGINS_DO( OnPhysicsInitialized );
        
        // 2) Geometry
        PLUGINS_DO( OnGeometryInitializing );
        app->InitializeGeometry();
        PLUGINS_DO( OnGeometryInitialized );
        
        // 3) Particle Generator
        PLUGINS_DO( OnParticleGeneratorInitializing );
        app->InitializeParticleGenerator();
        PLUGINS_DO( OnParticleGeneratorInitialized );
        
        G4cout << "Initializing Geant4 run manager." << endl;
        // Initialize Geant4's own run manager
        G4RunManager::Initialize();
        PLUGINS_DO( OnRunInitialized );
        G4cout << "Run initialized." << endl;
    }

    void RunManager::DoEventLoop(G4int n_event, const char *macroFile, G4int n_select)
    {
        (void) signal(SIGINT, terminate_run);
        G4RunManager::DoEventLoop(n_event, macroFile, n_select);
    }

    void RunManager::RunTermination()
    {
        (void) signal(SIGINT, SIG_DFL);
        G4RunManager::RunTermination();
    }

    void RunManager::InitializeUserActions()
    {
        _eventAction = new CompositeEventAction;
        // _numberingEventAction = new NumberingEventAction;
        // AddEventAction(_numberingEventAction);

        _runAction = new CompositeRunAction;
        _steppingAction = new CompositeSteppingAction;
        _trackingAction = new CompositeTrackingAction;

        SetUserAction(_eventAction);
        SetUserAction(_runAction);
        SetUserAction(_steppingAction);
        SetUserAction(_trackingAction);
    }
}

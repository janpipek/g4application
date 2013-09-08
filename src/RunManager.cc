#include "RunManager.hh"
#include "Plugin.hh"

#include <signal.h>

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

    void RunManager::Initialize()
    {
        G4Application* app = G4Application::GetInstance();  
        vector<Plugin*> plugins = app->GetPluginLoader()->GetPlugins();
        
        // 1) Physics
        PLUGINS_DO( OnPhysicsInitializing );
        app->InitializePhysics();
        app->InitializeUserActions(); // TODO: Move elsewhere?

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
}

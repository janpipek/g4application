#include "G4Application.hh"

#include <cstdlib>
#include <ctime>

#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include <G4UIsession.hh>
#include <G4UIdirectory.hh>

#include "ComponentManager.hh"

#ifdef G4UI_USE_QT
    #include <G4UIQt.hh>
    // #include <QtGui/QMainWindow>
#else
    #include <G4UItcsh.hh>
#endif

using namespace std;
using namespace g4::util;

namespace g4
{
    G4Application::G4Application(int argc, char** argv)
    {
        Initialize(argc, argv);
    }

    G4Application::G4Application()
    {
        // TODO: Change to exception of a lower severity.
        G4cerr << "Warning: G4Application created without argc/argv!" << G4endl;
        Initialize(0, 0);
    }

    void G4Application::Initialize(int argc, char** argv)
    {
        _argc = argc;
        _argv = argv;
        _interactiveSession = 0;
        // _physicsBuilder = 0;
        // _particleGeneratorBuilder = 0;

        _componentManager = new ComponentManager();

        // Initialize directory for UI commands
        _uiDirectory = new G4UIdirectory("/app/");
        _uiDirectory->SetGuidance("G4Application commands");

        _messenger = new ApplicationMessenger();

        // Custom run manager
        _runManager = new RunManager(*_componentManager);

        // Plugin-loading system
        _pluginLoader = new PluginLoader(_componentManager);

        // Visualization
        #ifdef G4VIS_USE
          _visManager = new G4VisExecutive;
          _visManager->Initialize();
        #endif
    }

    void G4Application::PrepareInteractiveMode()
    {
        #ifdef G4UI_USE_QT
            _interactiveSession = new G4UIQt(_argc, _argv); // There are no arguments but nevermind.
        #else
            #ifdef G4UI_USE_TCSH
                _interactiveSession = new G4UIterminal(new G4UItcsh);
            #else
                _interactiveSession = new G4UIterminal();
            #endif
        #endif
    }
    
    G4Application::~G4Application()
    {
        // Visualization
        #ifdef G4VIS_USE
          delete _visManager;
        #endif

        delete _componentManager;
                
        delete _messenger;
        delete _uiDirectory;
        delete _runManager;
        delete _pluginLoader;
    }
    
    void G4Application::CreateInstance(int argc, char **argv)
    {
        if (instanceExists<G4Application>())
        {
            G4Exception("G4Application", "DuplicateInstance", FatalException, "Cannot create second instance of G4Application." );
        }
        new G4Application(argc, argv);
    }
    
    void G4Application::EnterInteractiveMode()
    {
        if (!_interactiveSession)
        {
            PrepareInteractiveMode();
        }
        _interactiveSession->SessionStart();
    }

    void G4Application::PauseExecution()
    {
        G4cout << "Press ENTER to continue..." << endl;
        G4cin.get();
    }
    
    void G4Application::RunUI()
    {
        G4UImanager * UI = G4UImanager::GetUIpointer();
        if (_argc != 1)   // batch mode
        {
            // *** BATCH RUN (even more files)
            // Whatever commands - they are applied HERE
            G4String command = "/control/execute ";
            for (int macro = 1; macro < _argc; macro++)
            {
                G4String fileName = _argv[macro];
                G4cout << "Executing macro file: " << fileName << endl;
                UI->ApplyCommand(command+fileName);
            }
            // G4RunManager::GetRunManager()->RunInitialization();
        }
        else
        {
            G4cout << "No macro specified, entering interactive mode." << endl;
            EnterInteractiveMode();
        }
        G4cout << "Closing application..." << endl;
    }

    void G4Application::GenerateRandomSeed()
    {
        /* initialize random seed: */
        srand ( time(NULL) );
        int seed = rand();

        CLHEP::HepRandom::setTheSeed( seed );
        G4cout << "New random seed has been set: " << seed << G4endl;
    }
}

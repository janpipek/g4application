#include "G4Application.hh"

#include <cstdlib>
#include <ctime>

#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include <G4UIsession.hh>
#include <G4UIdirectory.hh>

#ifdef G4UI_USE_QT
    #include <G4UIQt.hh>
    // #include <QtGui/QMainWindow>
#else
    #include <G4UItcsh.hh>
#endif

using namespace std;

namespace g4
{
    G4Application* G4Application::_instance = 0;

    G4Application::G4Application(int argc, char** argv) :
        _argc(argc), _argv(argv), _interactiveSession(0), _physicsBuilder(0), _particleGeneratorBuilder(0), _eventAction(0), _runAction(0)
    {
        _geometry = new PluggableGeometry();
        
        // Initialize directory for UI commands
        _uiDirectory = new G4UIdirectory("/g4/");
        _uiDirectory->SetGuidance("G4Application commands");

        _messenger = new ApplicationMessenger(this);
        
        _runManager = new RunManager;

        // Plugin-loading system
        _pluginLoader = new PluginLoader(*this);
        
        // Visualization
        #ifdef G4VIS_USE
          _visManager = new G4VisExecutive;
          _visManager->Initialize();
        #endif
          
        #ifdef G4UI_USE_QT
            // _interactiveSession = new G4UIQt(argc, argv);
        #endif      
    }
    
    G4Application::~G4Application()
    {
        // Visualization
        #ifdef G4VIS_USE
          delete _visManager;
        #endif
        
        if (_interactiveSession)
        {
            delete _interactiveSession;         
        }  
        
        delete _messenger;
        delete _uiDirectory;
        delete _runManager;
        delete _pluginLoader; // Unload DLLs => it should be the last thing to delete
    }
    
    void G4Application::InitializeGeometry()
    {
        G4cout << "Initializing detector construction..." << std::endl;
        _runManager->SetUserInitialization(_geometry->GetDetectorConstruction());
        G4cout << "Detector initialized." << std::endl;
    }
    
    void G4Application::InitializePhysics()
    {
        G4cout << "Initializing physics..." << std::endl;
        if (_physicsBuilder)
        {
            _runManager->SetUserInitialization(_physicsBuilder->CreateUserPhysicsList());
        }
        else
        {
            G4Exception("G4Application", "NoPhysList", FatalException, "None of loaded plugins defined user physics list." );
        }
        G4cout << "Physics initialized." << std::endl;
    }

    void G4Application::InitializeParticleGenerator()
    {
        G4cout << "Initializing particle generator..." << std::endl;
        if (_particleGeneratorBuilder)
        {
            _runManager->SetUserAction(_particleGeneratorBuilder->BuildParticleGenerator());
        }
        else
        {
            G4cerr << "Warning: None of the plugins provided a particle generator." << std::endl;
        }
        G4cout << "Particle generator initialized." << std::endl;
    }

    void G4Application::InitializeUserActions()
    {
        _eventAction = new CompositeEventAction;
        _numberingEventAction = new NumberingEventAction;
        AddEventAction(_numberingEventAction);

        _runAction = new CompositeRunAction;
        _steppingAction = new CompositeSteppingAction;

        _runManager->SetUserAction(_eventAction);
        _runManager->SetUserAction(_runAction);
        _runManager->SetUserAction(_steppingAction);
    }

    void G4Application::SetPhysicsBuilder(PhysicsBuilder* physicsBuilder)
    {
        _physicsBuilder = physicsBuilder;
    }
    
    void G4Application::SetParticleGeneratorBuilder(ParticleGeneratorBuilder* generatorBuilder)
    {
        _particleGeneratorBuilder = generatorBuilder;
    }
    
    G4Application* G4Application::GetInstance()
    {
        if (!_instance)
        {
            G4Exception("G4Application", "NoInstance", FatalException, "There is no instance of G4pplication class.");
        }
        return _instance;
    }
    
    void G4Application::CreateInstance(int argc, char **argv)
    {
        if (_instance)
        {
            G4Exception("G4Application", "DuplicateInstance", FatalException, "Cannot create second instance of G4Application." );
        }
        _instance = new G4Application(argc, argv);
    }
    
    void G4Application::EnterInteractiveMode()
    {
        // UI used (in order of preference): Qt, TCSH, default terminal
        #ifdef G4UI_USE_QT
            if (!_interactiveSession)
            {
                _interactiveSession = new G4UIQt(_argc, _argv); // There are no arguments but nevermind.
            }
        #else
            #ifdef G4UI_USE_TCSH
                _interactiveSession = new G4UIterminal(new G4UItcsh);
            #else
                _interactiveSession = new G4UIterminal();
            #endif
        #endif
        _interactiveSession->SessionStart();
        delete _interactiveSession;
        _interactiveSession = 0;
    }
    
    void G4Application::ExitInteractiveMode()
    {
        #ifdef G4UI_USE_QT
            // ((G4UIQt*)_interactiveSession)->getMainWindow()->close();
        #endif
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

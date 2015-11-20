#include "Application.hh"

#include <cstdlib>
#include <ctime>

#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include <G4UIsession.hh>
#include <Randomize.hh>

#ifdef G4VIS_USE
    #include <G4VisExecutive.hh>
#endif

#ifdef G4UI_USE_QT
    #include <G4UIQt.hh>
#else
    #include <G4UItcsh.hh>
#endif

#include "ComponentManager.hh"
#include "ComponentRegistry.hh"
#include "PluginLoader.hh"
#include "ApplicationMessenger.hh"
#include "RunManager.hh"

using namespace std;
using namespace g4::util;

namespace g4
{
    Application::Application(int argc, char** argv) : _interactiveSession(nullptr), _argc(argc), _argv(argv)
    {
        if (!argc)
        {
            G4cerr << "Warning: G4Application created without argc/argv!" << G4endl;
        }
        else if (!argv)
        {
            G4Exception("G4Application", "WrongArgv", FatalException, "argv not set although argc >= 1" );
        }
        G4cout << "Application: Instance created." << G4endl;
        Initialize(argc, argv);
    }

    void Application::Initialize(int argc, char** argv)
    {
        _componentManager = new ComponentManager();
        _componentRegistry = &ComponentRegistry::Instance();

        _messenger = new ApplicationMessenger(this);
        _configurationMessenger = new ConfigurationMessenger();

        // Custom run manager
        _runManager = new RunManager(*_componentManager);

        // Plugin-loading system
        _pluginLoader = new PluginLoader(_componentManager);

        // Visualization
        #ifdef G4VIS_USE
          _visManager = new G4VisExecutive("quiet");
          _visManager->Initialize();
        #endif

        G4Random::setTheEngine(new CLHEP::RanecuEngine);
    }

    void Application::PrepareInteractiveMode()
    {
        if (!_interactiveSession) {
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
    }

    Application::~Application()
    {
        G4cout << "Closing application..." << endl;

        // Visualization
        #ifdef G4VIS_USE
          delete _visManager;
        #endif

        // delete _componentManager;

        // delete _messenger;
        // delete _uiDirectory;
        delete _runManager;
        // delete _pluginLoader;
    }

    Application& Application::CreateInstance(int argc, char **argv)
    {
        if (instanceExists<Application>())
        {
            G4Exception("G4Application", "DuplicateInstance", FatalException, "Cannot create second instance of G4Application." );
        }
        new Application(argc, argv);
        return Instance();
    }

    void Application::EnterInteractiveMode()
    {
        if (!_interactiveSession)
        {
            PrepareInteractiveMode();
        }
        _interactiveSession->SessionStart();
    }

    void Application::PauseExecution()
    {
        G4cout << "Press ENTER to continue..." << endl;
        G4cin.get();
    }

    void Application::ExecuteMacros()
    {
        G4UImanager* ui = G4UImanager::GetUIpointer();
        G4String command = "/control/execute ";

        if (!_macros.size())
        {
            G4cout << "No macro files specified." << G4endl;
        }
        while (_macros.size())   // batch mode
        {
            auto fileName = _macros.front();
            _macros.pop_front();
            G4cout << "Executing macro file: " << fileName << G4endl;
            ui->ApplyCommand(command + fileName);               
        }
    }

    void Application::GenerateRandomSeed()
    {
        /* initialize random seed: */
        srand ( time(NULL) );
        int seed = rand();

        CLHEP::HepRandom::setTheSeed( seed );
        G4cout << "New random seed has been set: " << seed << G4endl;
    }

    void Application::ApplyCommand(const string& command)
    {
        G4UImanager * UI = G4UImanager::GetUIpointer();
        UI->ApplyCommand(command);
    }

    void Application::AddBuiltinComponent(const G4String& name)
    {
        Component* component = _componentRegistry->GetComponent(name);
        if (!component)
        {
            G4ExceptionDescription message;
            message << "Component " << name << " does not exist.";
            G4Exception("Application", "UnknownComponent", FatalException, message);
        }
        _componentManager->AddComponent(name, component);
        G4cout << "Loaded built-in component " << name << "." << G4endl;
    }

    void Application::AddMacro(const G4String& name)
    {
        _macros.push_back(name);
    }
}

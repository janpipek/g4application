#ifndef APPLICATION_HH
#define APPLICATION_HH

#include <deque>
#include <memory>

#include <globals.hh>
#include <G4GenericMessenger.hh>

#include "util/Singleton.hh"
#include "ConfigurationMessenger.hh"
#include "ComponentManager.hh"

#ifdef G4VIS_USE
    class G4VisExecutive;
#endif

class G4UIdirectory;
class G4UIsession;

namespace g4
{
    class ApplicationMessenger;
    class PluginLoader;
    class ComponentManager;
    class ComponentRegistry;
    class RunManager;
    
    /**
      * @short Singleton application object.
      */
    class Application : public util::Singleton<Application>
    {
    public:
        ~Application();

        std::shared_ptr<RunManager> GetRunManager() const { return _runManager; }
        
        std::shared_ptr<PluginLoader> GetPluginLoader() const { return _pluginLoader; }

        std::shared_ptr<ComponentManager> GetComponentManager() const { return _componentManager; }

        /**
          * @short Generate random random seed.
          *
          * This enables multiple program runs with the same macro file
          * to generate different results. Uses system rand() function.
          */
        // TODO: Not used, return this in a way
        void GenerateRandomSeed();

        void ApplyCommand(const std::string& command);

        /**
          * @short Prepare UI Session.
          *
          * It is possible to call this method multiple times.
          * The session will capture output.
          */
        void PrepareInteractiveMode();
            
        /**
          * Enter mode where user can manually type commands
          */
        void EnterInteractiveMode();

        void SetInteractiveModeType(G4String name) { name.toLower(); _interactiveName = name; }

        /**
          * @short Wait for the user to press ENTER.
          */
        void PauseExecution();

        /**
          * @short Run User Interface
          * 
          * If there are command-line parameters, they are treated as macros.
          * Otherwise interactive mode (Qt by default) is entered.
          */
        void ExecuteMacros();

        /**
          * @short Add a macro file name to be executed.
          */
        void AddMacro(const G4String& name);

        void AddBuiltinComponent(G4String name); // TODO: Strange here

        friend class util::Singleton<Application>;

    private:
        Application();

        std::deque<G4String> _macros;
        
        // Visualization Manager
        #ifdef G4VIS_USE
          std::shared_ptr<G4VisExecutive> _visManager;
        #endif
        
        G4UIsession* _interactiveSession;

        G4String _interactiveName;

        G4GenericMessenger _messenger;

        // ApplicationMessenger* _messenger;

        // TODO: Temporary, not wise to have it here.
        ConfigurationMessenger* _configurationMessenger;

        std::shared_ptr<ComponentManager> _componentManager;

        std::shared_ptr<PluginLoader> _pluginLoader;

        std::shared_ptr<RunManager> _runManager;

        ComponentRegistry* _componentRegistry;
    };
}

#endif // APPLICATION_HH

#ifndef APPLICATION_HH
#define APPLICATION_HH

#include "util/Singleton.hh"
#include "ConfigurationMessenger.hh"

#include <globals.hh>
#include <vector>

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
        // TODO: This class is a typical "god object". Refactor.
        static Application& CreateInstance(int argc, char** argv);

        ~Application();

        RunManager* GetRunManager() const { return _runManager; }
        
        PluginLoader* GetPluginLoader() const { return _pluginLoader; }

        ComponentManager* GetComponentManager() const { return _componentManager; }

        /**
          * @short Generate random random seed.
          *
          * This enables multiple program runs with the same macro file
          * to generate different results. Uses system rand() function.
          */
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
        void RunUI();

        /**
          * @short Add a macro file name to be executed.
          */
        void AddMacro(const G4String& name);

        void AddBuiltinComponent(const G4String& name); // TODO: Strange here

        friend class util::Singleton<Application>;

    private:
        Application(int argc = 0, char** argv = nullptr);

        void Initialize(int argc, char **argv);

        std::vector<G4String> _macros;

        int _argc;
        
        char** _argv;
        
        // Visualization Manager
        #ifdef G4VIS_USE
          G4VisExecutive* _visManager;
        #endif
        
        RunManager* _runManager;
        
        G4UIsession* _interactiveSession;
        
        PluginLoader* _pluginLoader;
        
        ApplicationMessenger* _messenger;

        // TODO: Temporary, not wise to have it here.
        ConfigurationMessenger* _configurationMessenger;

        ComponentManager* _componentManager;

        ComponentRegistry* _componentRegistry;
    };
}

#endif // APPLICATION_HH

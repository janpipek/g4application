#ifndef G4APPLICATION_HH
#define G4APPLICATION_HH

#include <G4UIdirectory.hh>
#include <G4VisExecutive.hh>
#include <G4UIsession.hh>

#include "RunManager.hh"
#include "PluginLoader.hh"
#include "ApplicationMessenger.hh"
#include "util/Singleton.hh"

namespace g4
{
    class ApplicationMessenger;
    class PluginLoader;
    class ComponentManager;
    
    /**
      * @short Singleton application object.
      */
    class G4Application : public util::Singleton<G4Application>
    {
    public:     
        // TODO: This class is a typical "god object". Refactor.
        static void CreateInstance(int argc, char** argv);

        ~G4Application();

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

        friend class util::Singleton<G4Application>;   

    private:
        G4Application();

        G4Application(int argc, char** argv);

        void Initialize(int argc, char **argv);

        int _argc;
        
        char** _argv;
        
        // Visualization Manager
        #ifdef G4VIS_USE
          G4VisExecutive* _visManager;
        #endif
        
        RunManager* _runManager;
        
        G4UIdirectory* _uiDirectory;
        
        G4UIsession* _interactiveSession;
        
        PluginLoader* _pluginLoader;
        
        ApplicationMessenger* _messenger;

        ComponentManager* _componentManager;
    };
}

#endif // G4APPLICATION_HH

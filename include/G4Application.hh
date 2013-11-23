#ifndef G4APPLICATION_HH
#define G4APPLICATION_HH

#include <G4UIdirectory.hh>
#include <G4VisExecutive.hh>
#include <G4UIsession.hh>

#include "RunManager.hh"
#include "PluggableGeometry.hh"
#include "ParticleGeneratorBuilder.hh"
#include "PhysicsBuilder.hh"
#include "PluginLoader.hh"
#include "ApplicationMessenger.hh"

namespace g4
{
    class ApplicationMessenger;
    class PluginLoader;
    
    /**
      * Singleton application object.
      */
    class G4Application
    {
    public:     
        // TODO: This class is a typical "god object". Refactor.
        static void CreateInstance(int argc, char** argv);
        
        static G4Application* GetInstance();
                    
        ~G4Application();
        
        PluggableGeometry* GetGeometry() const { return _geometry; }
        
        RunManager* GetRunManager() const { return _runManager; }
        
        PluginLoader* GetPluginLoader() const { return _pluginLoader; }
        
        void SetPhysicsBuilder(PhysicsBuilder*);

        void SetParticleGeneratorBuilder(ParticleGeneratorBuilder*);

        /**
          * @short Generate random random seed.
          *
          * This enables multiple program runs with the same macro file
          * to generate different results. Uses system rand() function.
          */
        void GenerateRandomSeed();
            
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

        void Destroy();
        
        void InitializeGeometry();
        
        void InitializePhysics();
        
        void InitializeParticleGenerator();     

    private:
        // Ensure singleton behaviour
        G4Application(int argc, char** argv);
        G4Application(const G4Application&) {};
        G4Application& operator= (const G4Application&);    
                    
        int _argc;
        
        char** _argv;
        
        // Visualization Manager
        #ifdef G4VIS_USE
          G4VisExecutive* _visManager;
        #endif
          
        static G4Application* _instance;
        
        RunManager* _runManager;
        
        G4UIdirectory* _uiDirectory;
        
        G4UIsession* _interactiveSession;
        
        PhysicsBuilder* _physicsBuilder;
        
        ParticleGeneratorBuilder* _particleGeneratorBuilder;
        
        PluginLoader* _pluginLoader;
        
        ApplicationMessenger* _messenger;
        
        PluggableGeometry* _geometry;
    };
}

#endif // G4APPLICATION_HH
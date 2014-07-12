#ifndef PLUGIN_HH
#define PLUGIN_HH

// Helper macros used when looking for symbols in libraries
#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)

// If present, this function will be called when the plugin is loaded.
#define PLUGIN_MAIN_FUNCTION plugin_main

// Exports main function that creates a single copy of Plugin descendant
#define MAKE_G4_PLUGIN(class_name) \
extern "C" g4::Plugin* PLUGIN_MAIN_FUNCTION()\
{\
    return new class_name;\
}
// end of MAKE_G4_PLUGIN

#include <string>
#include <G4VUserPhysicsList.hh>
#include <G4UIdirectory.hh>

#include "PhysicsBuilder.hh"
#include "GeometryBuilder.hh"
#include "ParticleGeneratorBuilder.hh"
#include "RunObserver.hh"

namespace g4
{
    /**
      * @short Base class for any plugin. The plugin loader gets it from the plugin
      * and communicates with the plugin using this class.
      *
      * You can define following builders:
      *  - PhysicsBuilder 
      *  - GeometryBuilder
      *  - ParticleGeneratorBuilder
      * 
      * It also inherits from @see RunListener that reacts to all state changes
      * initiated by run manager.
      *
      * Apart from that, there is a customizable (empty by default) callback:         
      */
    class Plugin : public RunObserver
    {
    public:
        Plugin() : _uiDirectory(0) { }
        
        virtual ~Plugin() { if (_uiDirectory) delete _uiDirectory; }
        
        /** User-friendly plugin name. */
        virtual const std::string GetName() const = 0;

        /**
          * @short Procedure that is called after loading the plugin.
          */
        virtual void OnLoad() { }
        
        /** @see PhysicsBuilder */
        virtual PhysicsBuilder* GetPhysicsBuilder() { return NULL; }
        
        /** @see GeometryBuilder */
        virtual GeometryBuilder* GetGeometryBuilder() { return NULL; }
        
        /** @see ParticleGeneratorBuilder */
        virtual ParticleGeneratorBuilder* GetParticleGeneratorBuilder() { return NULL; }

    protected:
        void CreateUiDirectory(std::string name)
        {
            _uiDirectory = new G4UIdirectory(name.c_str());
            _uiDirectory->SetGuidance(("Commands for plugin " + GetName()).c_str());
        }

    private:
        G4UIdirectory* _uiDirectory;
    };
}
#endif // PLUGIN_HH

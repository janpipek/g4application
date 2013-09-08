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

#include "G4Application.hh"
#include "PhysicsBuilder.hh"
#include "GeometryBuilder.hh"
#include "ParticleGeneratorBuilder.hh"

namespace g4
{
    class G4Application;

    /**
      * @short Base class for any plugin. The plugin loader gets it from the plugin
      * and communicates with the plugin using this class.
      *
      * You can define following builders:
      *  - PhysicsBuilder 
      *  - GeometryBuilder
      *  - ParticleGeneratorBuilder
      *
      * Apart from that, there are customizable (empty by default) callbacks:         
      *  - OnLoad - when the plugin is loaded
      *  - For each XXX in (Physics, Geometry, ParticleGenerator):
      *  --- OnXXXInitialiazing - before initializing
      *  --- OnXXXInitialized - after initializing
      */
    class Plugin
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
        
        /** 
          * @short Procedure called before geometry is initialized.
          */
        virtual void OnGeometryInitializing() { }
        
        /**
          * @short Procedure called after geometry is initialized.
          */
        virtual void OnGeometryInitialized() { }
        
        /** 
          * @short Procedure called before physics is initialized.
          */
        virtual void OnPhysicsInitializing() { }
        
        /**
          * @short Procedure called after physics is initialized.
          */
        virtual void OnPhysicsInitialized() { }

        /** 
          * @short Procedure that is called before particle generator builder is initialized.
          */
        virtual void OnParticleGeneratorInitializing() { }
        
        /**
          * @short Procedure called immediatelly after particle generator builder is initialized.
          */
        virtual void OnParticleGeneratorInitialized() { }           
        
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

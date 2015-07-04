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
#include <vector>

#include "Component.hh"

namespace g4
{
    /**
      * @short Base class for any plugin. The plugin is a container
      *   of components stored in a DLL.
      */
    class Plugin // , RunObserver
    {
    public:
        Plugin() { }

        virtual const std::vector<std::string>& GetAvailableComponents() const = 0;

        virtual Component* GetComponent(std::string) = 0;
        
        virtual ~Plugin() { }
        
        /** User-friendly plugin name. */
        // virtual const std::string GetName() const = 0;

        /**
          * @short Procedure that is called after loading the plugin.
          */
        virtual void OnLoad() { }
    };
}
#endif // PLUGIN_HH

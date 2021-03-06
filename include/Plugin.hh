#ifndef PLUGIN_HH
#define PLUGIN_HH

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
// #include "RunObserver.hh"

namespace g4
{
    class PluginLoader;

    /**
      * @short Base class for any plugin. The plugin is a container
      *   of components stored in a DLL.
      */
    class Plugin
    {
        friend class PluginLoader;

    public:
        /**
          * @short The list of component names the plugin provides.
          */
        virtual const std::vector<std::string> GetAvailableComponents() const = 0;

        /**
          * @short Create or return and existing component by name.
          * 
          * Note: if there is no such component, the method should return nullptr,
          *   no G4Exceptions, no C++ exceptions.
          */
        virtual Component* GetComponent(const std::string&) = 0;

        virtual ~Plugin() = default;

        /**
          * @short Procedure that is called after loading the plugin.
          */
        virtual void OnLoad() { }

        const std::string& GetName() { return _name; }

    private:
        std::string _name;

    };
}
#endif // PLUGIN_HH

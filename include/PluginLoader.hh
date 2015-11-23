#ifndef PLUGINLOADER_HH
#define PLUGINLOADER_HH

#include <string>
#include <map>

#include <G4GenericMessenger.hh>

#include "Plugin.hh"
#include "util/Verbosity.hh"

namespace g4
{
    class PluginMessenger;
    class Plugin;
    class ComponentManager;

    std::string shortLibraryName(const std::string& name);

    std::string longLibraryName(const std::string& name);
    
    class PluginLoader : public util::VerbosityMixin
    {
    public:
        PluginLoader(ComponentManager* componentManager);
        
        /**
          * @short Load a plugin dynamic library (.so) with full name +name+.
          *
          * It runs plugin's OnLoad() procedure and associates 
          * geometry and generator functions with their counterparts.
          *
          * The name, if not absolute path, should be in $LD_LIBRARY_PATH
          */
        void Open(G4String name);

        /**
         * @brief Load a single component from the plugin.
         *
         * @param pluginName Name of the plugin
         * @param componentName Name of the component
         */
        void Load(G4String pluginName, G4String componentName);

        /**
         * @brief Load all components from the plugin.
         */
        void LoadAll(G4String pluginName);

        /**
         * @brief Write a list of components in the plugin.
         */
        void ListComponents(G4String pluginName);

        /**
          * @short Add a plugin.
          *
          * Such plugin needn't be loaded using Load method and doesn't
          * need to come from an external library at all.
          */
        void AddPlugin(Plugin*);
        
        /**
          * @short Unload all plugins.
          *
          * Note: This has to be done as the last step as other classes
          *   use object from the plugins.
          */
        ~PluginLoader();

    protected:
        Plugin* FindPlugin(const G4String& name);

        void ExecuteLoad(Plugin* plugin, const G4String& componentName);
        
    private:                  
        // PluginMessenger* _messenger;
        G4GenericMessenger _messenger;

        ComponentManager* _componentManager;
                
        std::vector<void*> _libraries;

        std::map<G4String, Plugin*> _plugins;
    };
}

#endif // PLUGINLOADER_HH

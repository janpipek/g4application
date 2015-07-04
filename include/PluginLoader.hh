#ifndef PLUGINLOADER_HH
#define PLUGINLOADER_HH

#include <string>
#include <map>

#include "Plugin.hh"

namespace g4
{
    class PluginMessenger;
    class Plugin;
    class ComponentManager;

    std::string shortLibraryName(const std::string& name);

    std::string longLibraryName(const std::string& name);
    
    class PluginLoader
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
        int Open(std::string name);

        int Load(std::string pluginName, std::string componentName);

        int LoadAll(std::string pluginName);

        /**
          * @short Add a plugin.
          *
          * Such plugin needn't be loaded using Load method and doesn't
          * need to come from an external library at all.
          */
        void AddPlugin(Plugin*);
        
        /**
          * @short Vector of all loaded plugins.
          */
        /*const std::vector<Plugin*>& GetPlugins() const
        {
            return _plugins;
        }*/
        
        /**
          * @short Unload all plugins.
          *
          * Note: This has to be done as the last step as other classes
          *   use object from the plugins.
          */
        ~PluginLoader();

    protected:
        int Load(Plugin* plugin, const std::string& componentName);
        
    private:                  
        PluginMessenger* _messenger;

        ComponentManager* _componentManager;
                
        std::vector<void*> _libraries;

        // std::vector<Plugin*> _plugins;

        std::map<std::string, Plugin*> _plugins;
    };
}

#endif // PLUGINLOADER_HH

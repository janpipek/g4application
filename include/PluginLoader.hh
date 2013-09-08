#ifndef PLUGINLOADER_HH
#define PLUGINLOADER_HH

#include <string>
#include <vector>

#include "PluginMessenger.hh"
#include "Plugin.hh"

namespace g4
{
    class PluginMessenger;
    class Plugin;
    
    class PluginLoader
    {
    public:
        PluginLoader();
        
        /**
          * @short Load a plugin dynamic library (.so) with full name +name+.
          *
          * It runs plugin's OnLoad() procedure and associates 
          * geometry and generator functions with their counterparts.
          *
          * The name, if not absolute path, should be in $LD_LIBRARY_PATH
          */
        int Load(std::string name);
        
        /** 
          * Vector of all loaded plugins.
          */
        const std::vector<Plugin*>& GetPlugins() const
        {
            return _plugins;
        }
        
        /**
          * Unload all plugins.
          *
          * Note: This has to be done as the last step as other classes
          *   use object from the plugins.
          */
        ~PluginLoader();
        
    private:                   
        PluginMessenger* _messenger;
                
        std::vector<void*> _libraries;
        std::vector<Plugin*> _plugins;
    };
}

#endif // PLUGINLOADER_HH

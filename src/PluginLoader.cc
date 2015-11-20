#include "PluginLoader.hh"

#include <dlfcn.h>
#include <iostream>
#include <sys/stat.h>

#include <G4StateManager.hh>

#include "PluginMessenger.hh"
#include "ComponentManager.hh"

using namespace std;

namespace g4
{
    string shortLibraryName(const string& name)
    {
        // TODO: Make platform-independent!
        if ((name.find("lib") == 0) && (name.rfind(".so") == name.length() - 3))
        {
            return name.substr(3, name.length() - 6);
        }
        else
        {
            return name;
        }
    }

    string longLibraryName(const string& name)
    {
        // TODO: Make platform-independent!
        if ((name.find("lib") == 0) && (name.rfind(".so") == name.length() - 3))
        {
            return name;
        }
        else
        {
            return string("lib") + name + ".so";
        }
    }

    typedef Plugin*(*plugin_load_function)();
    
    PluginLoader::PluginLoader(ComponentManager *componentManager) :
        _componentManager(componentManager)
    {
        _messenger = new PluginMessenger(this);
    }
    
    void PluginLoader::Open(std::string name)
    {
        // Check for application state
        G4ApplicationState state = G4StateManager::GetStateManager()->GetCurrentState();
        if (state != G4State_PreInit)
        {
            G4Exception("PluginLoader", "LoadInWrongState", FatalException , "All plugins have to be loaded in PreInit state.");
        }


        const string shortName = shortLibraryName(name);
        const string longName = longLibraryName(name);

        if (GetVerboseLevel() > 0)
        {
            G4cout << "PluginLoader: Loading plugin library `" << shortName << "` from `" << longName << "`." << endl;
        }
        
        // Try to load the file as dynamic library
        void* library = nullptr;
        library = dlopen(longName.c_str(), RTLD_LAZY );


        if (library)
        {
            plugin_load_function PLUGIN_MAIN_FUNCTION = (plugin_load_function) (dlsym(library, QUOTEME(PLUGIN_MAIN_FUNCTION))); 
            if (PLUGIN_MAIN_FUNCTION)
            {
                Plugin* plugin = (*PLUGIN_MAIN_FUNCTION)();
                plugin->_name = shortName;
                plugin->OnLoad();
                _plugins[shortName] = plugin;

                // AddPlugin(plugin);
                _libraries.push_back(library);
                if (GetVerboseLevel() > 0)
                {
                    G4cout << "PluginLoader: Loaded plugin `" << shortName << "`." << endl;
                }
            }
            else
            {
                G4cerr << "dlopen() error: " << dlerror() << endl;
                G4Exception("PluginLoader", "WrongFile" , FatalException, "Plugin method could not be loaded from the library!");
                dlclose(library);
                
            }
        }
        else
        {
            G4cerr << "dlopen() error: " << dlerror() << endl;
            G4Exception("PluginLoader", "CantOpen", FatalException, "Library exists but could not be loaded!");
            
        }
    }

    void PluginLoader::Load(string pluginName, string componentName)
    {
        Plugin* plugin = FindPlugin(pluginName);
        if (!plugin)
        {
            G4Exception("PluginLoader", "CantLoad", FatalException, "No such plugin opened.");
        }
        Load(plugin, componentName);
    }

    void PluginLoader::LoadAll(string pluginName)
    {
        if (GetVerboseLevel() > 0)
        {
            G4cout << "PluginLoader: Loading all components from plugin `" << pluginName << "`..." << G4endl;
        }
        Plugin* plugin = FindPlugin(pluginName);
        if (!plugin)
        {
            G4Exception("PluginLoader", "CantLoad", FatalException, "No such plugin opened.");
        }
        vector<string> componentNames = plugin->GetAvailableComponents();
        for (auto compIt = componentNames.begin(); compIt != componentNames.end(); compIt++)
        {
            string componentName = *compIt;
            Load(plugin, componentName);
        }
        if (GetVerboseLevel() > 0)
        {
            G4cout << "PluginLoader: Loaded all components from plugin `" << pluginName << "`." << G4endl;
        }
    }

    void PluginLoader::ListComponents(string pluginName)
    {
        Plugin* plugin = FindPlugin(pluginName);
        if (!plugin)
        {
            G4Exception("PluginLoader", "CantListComponents", FatalException, "No such plugin opened.");
        }
        G4cout << "------------------------------------------" << G4endl;
        G4cout << "Components of " << pluginName << " plugin:" << G4endl;
        vector<string> componentNames = plugin->GetAvailableComponents();
        for (auto compIt = componentNames.begin(); compIt != componentNames.end(); compIt++)
        {
            string componentName = *compIt;
            G4cout << " * " << componentName << G4endl;
        }
        G4cout << "------------------------------------------" << G4endl;
    }

    Plugin *PluginLoader::FindPlugin(const string &name)
    {
        auto it = _plugins.find(name);
        if (it != _plugins.end())
        {
            Plugin* plugin = it->second;
            return plugin;
        }
        return nullptr;
    }
            
    PluginLoader::~PluginLoader()
    {
        delete _messenger;
        // Destroy all plugin objects
        /* for (vector<Plugin*>::iterator it = _plugins.begin(); it != _plugins.end(); it++)
        {
            // _runManager->RemoveObserver(*it);
            delete (*it);
        }

        */

        // Unload all plugins
        if (GetVerboseLevel() > 0)
        {
            G4cout << "PluginLoader: Destructor called." << G4endl;
            G4cout << "PluginLoader: Unloading " << _libraries.size() << " plugins." << G4endl;
        }
        for (vector<void*>::iterator it = _libraries.begin(); it != _libraries.end(); it++)
        {
            if (*it) dlclose(*it);
        }
        _libraries.clear();
        if (GetVerboseLevel() > 0)
        {
            G4cout << "PluginLoader: Destructor finished." << G4endl;
        }
    }

    void PluginLoader::Load(Plugin *plugin, const string& componentName)
    {
        if (GetVerboseLevel() > 0)
        {
            G4cout << "Plugin Loader: Loading component `" << componentName << "` from plugin `" << plugin->GetName() << "`..." << G4endl;
        }
        Component* component = plugin->GetComponent(componentName);
        G4String name = plugin->GetName() + "/" + componentName;
        if (component)
        {
            _componentManager->AddComponent(name, component);
            G4cout << "Plugin Loader: Loaded component `" << componentName << "` from plugin " << plugin->GetName() << "." << G4endl;
        }
        else
        {
            G4Exception("PluginLoader", "NoSuchComponent", FatalException, "No such component in the plugin.");
        }
    }
}

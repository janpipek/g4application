#include "PluginLoader.hh"

#include <dlfcn.h>
#include <iostream>
#include <sys/stat.h>

#include <G4StateManager.hh>

#include "PluginMessenger.hh"
#include "G4Application.hh"
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
    
    int PluginLoader::Open(std::string name)
    {
        // Check for application state
        G4ApplicationState state = G4StateManager::GetStateManager()->GetCurrentState();
        if (state != G4State_PreInit)
        {
            G4Exception("PluginLoader", "LoadInWrongState", FatalException , "All plugins have to be loaded in PreInit state.");
            return -1;
        }


        const string shortName = shortLibraryName(name);
        const string longName = longLibraryName(name);

        G4cout << "Loading plugin library `" << shortName << "` from " << longName << "." << endl;
        
        // Check whether file exists.
        struct stat fileInfo;
        if (stat(longName.c_str(), &fileInfo)) // Returns 0 if file exists (confusing)
        {
            G4Exception("PluginLoader", "FileNotFound", FatalException  , ("File doesn't exist: `" + longName + "`.").c_str());
            return -1;
        }
        
        // Try to load the file as dynamic library
        void* library = 0;
        library = dlopen(longName.c_str(), RTLD_LAZY );

        if (library)
        {
            plugin_load_function PLUGIN_MAIN_FUNCTION = (plugin_load_function) (dlsym(library, QUOTEME(PLUGIN_MAIN_FUNCTION))); 
            if (PLUGIN_MAIN_FUNCTION)
            {
                Plugin* plugin = (*PLUGIN_MAIN_FUNCTION)();
                plugin->OnLoad();
                _plugins[shortName] = plugin;

                // AddPlugin(plugin);
                _libraries.push_back(library);
                G4cout << "Loaded plugin `" << shortName << "`." << endl;
            }
            else
            {
                G4cerr << "dlopen() error: " << dlerror() << endl;
                G4Exception("PluginLoader", "WrongFile" , FatalException, "Plugin method could not be loaded from the library!");
                dlclose(library);
                return -1;
            }
        }
        else
        {
            G4cerr << "dlopen() error: " << dlerror() << endl;
            G4Exception("PluginLoader", "CantLoad", FatalException, "Library exists but could not be loaded!");
            return -1;
        }
        return 0;
    }

    int PluginLoader::Load(string pluginName, string componentName)
    {
        auto it = _plugins.find(pluginName);
        if (it != _plugins.end())
        {
            Plugin* plugin = it->second;
            Load(plugin, componentName);
        }
        else
        {
            // TODO: Throw or something
        }
    }

    int PluginLoader::LoadAll(string pluginName)
    {
        map<string, Plugin*>::iterator it = _plugins.find(pluginName);
        if (it != _plugins.end()) {
            Plugin* plugin = it->second;
            vector<string> componentNames = plugin->GetAvailableComponents();
            for (auto compIt = componentNames.begin(); compIt != componentNames.end(); compIt++)
            {
                string componentName = *compIt;
                Load(plugin, componentName);
            }
        }
        else
        {
            // TODO: Throw or something
        }
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
        cout << "Unloading " << _libraries.size() << " plugins." << endl;
        */

        // Unload all plugins
        for (vector<void*>::iterator it = _libraries.begin(); it != _libraries.end(); it++)
        {
            if (*it) dlclose(*it);
        }
        _libraries.clear();
    }

    int PluginLoader::Load(Plugin *plugin, const string& componentName)
    {
        Component* component = plugin->GetComponent(componentName);
        if (component)
        {
            _componentManager->AddComponent(component);
            G4cout << "Loaded component `" << componentName << "`." << endl;
        }
        else
        {
            // TODO: Throw or something
        }
    }
}

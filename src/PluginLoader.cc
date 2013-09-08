// #include <cstdlib>
// #include <cstdio>
#include <dlfcn.h>

#include <iostream>
#include <sys/stat.h>

#include <G4StateManager.hh>

#include "PluginLoader.hh"
#include "GeometryBuilder.hh"
#include "PhysicsBuilder.hh"
#include "ParticleGeneratorBuilder.hh"

using namespace std;

namespace g4
{
    typedef Plugin*(*plugin_load_function)();
    
    PluginLoader::PluginLoader(G4Application& application) : _application(application)
    {
        _messenger = new PluginMessenger(this);
        // cout << "Loading plugin system." << endl;
    }
    
    int PluginLoader::Load(std::string name)
    {
        // Check for application state
        G4ApplicationState state = G4StateManager::GetStateManager()->GetCurrentState();
        if (state != G4State_PreInit)
        {
            G4Exception("PluginLoader", "LoadInWrongState", FatalException , "All plugins have to be loaded in PreInit state.");
            return -1;
        }
        
        G4cout << "Loading plugin library `" << name << "`." << endl;
        
        // Check whether file exists.
        struct stat fileInfo;
        if (stat(name.c_str(), &fileInfo)) // Returns 0 if file exists (confusing)
        {
            G4Exception("PluginLoader", "FileNotFound", FatalException  , ("File doesn't exist: `" + name + "`.").c_str());
            return -1;
        }
        
        // Try to load the file as dynamic library
        void* library = 0;
        library = dlopen(name.c_str(), RTLD_LAZY );

        if (library)
        {
            plugin_load_function PLUGIN_MAIN_FUNCTION = (plugin_load_function) (dlsym(library, QUOTEME(PLUGIN_MAIN_FUNCTION))); 
            if (PLUGIN_MAIN_FUNCTION)
            {
                Plugin* plugin = (*PLUGIN_MAIN_FUNCTION)();
                G4cout << "Loaded plugin `" << plugin->GetName() << "`." << endl;
                
                plugin->OnLoad(_application);

                // Geometry from plugin
                GeometryBuilder* geomBuilder = plugin->GetGeometryBuilder();
                if (geomBuilder)
                {
                    _application.GetGeometry()->AddGeometryBuilder(geomBuilder);
                    G4cout << "Using geometry definition from plugin `" << plugin->GetName() << "`." << endl;
                }
                
                // Particle generator from plugin
                ParticleGeneratorBuilder* genBuilder = plugin->GetParticleGeneratorBuilder();
                if (genBuilder)
                {
                    _application.SetParticleGeneratorBuilder(genBuilder);
                    G4cout << "Using particle generator from plugin `" << plugin->GetName() << "`." << endl;
                }
                
                // Physics from plugin
                PhysicsBuilder* physBuilder = plugin->GetPhysicsBuilder();
                if (physBuilder)
                {
                    _application.SetPhysicsBuilder(physBuilder);
                    G4cout << "Using physics from plugin `" << plugin->GetName() << "`." << endl;
                }
                
                _plugins.push_back(plugin);
                _libraries.push_back(library);
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
            
    PluginLoader::~PluginLoader()
    {
        delete _messenger;
        
        cout << "Unloading " << _libraries.size() << " plugins." << endl;
        // Unload all plugins
        for (vector<void*>::iterator it = _libraries.begin(); it != _libraries.end(); it++)
        {
            if (*it) dlclose(*it);
        }
        _libraries.clear();
    }
}

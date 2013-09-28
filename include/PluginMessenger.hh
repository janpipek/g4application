#ifndef PLUGINMESSENGER_HH
#define PLUGINMESSENGER_HH

#include <G4UImessenger.hh>
#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>

#include "PluginLoader.hh"

namespace g4
{
    class PluginLoader;
    
    /**
      * Messenger that enables commands for dealing with plugins.
      *
      * @see PluginLoader
      */
    class PluginMessenger : public G4UImessenger
    {
    public:
        PluginMessenger(PluginLoader* loader);
        
        // override         
        virtual void SetNewValue(G4UIcommand* command, G4String newValue);
                    
        virtual ~PluginMessenger();
        
    private:
        PluginLoader* _loader;
        
        /**
          * Directory /app/plugin/
          */
        G4UIdirectory* _directory;
        
        /**
          * Command /app/plugin/load
          *
          * When given an exact name of the DLL (including extension),
          * it loads it.
          */
        G4UIcmdWithAString* _loadCommand;
    };
}

#endif // PLUGINMESSENGER_HH

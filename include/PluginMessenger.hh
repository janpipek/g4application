#ifndef PLUGINMESSENGER_HH
#define PLUGINMESSENGER_HH

#include <G4UImessenger.hh>

class G4UIcmdWithAString;
class G4UIdirectory;

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
          * Directory /plugin/
          */
        G4UIdirectory* _directory;
        
        /**
          * Command /plugin/open
          *
          * When given an exact name of the DLL (including extension),
          * it opens it.
          */
        G4UIcmdWithAString* _openCommand;

        G4UIcommand* _loadCommand;

        G4UIcmdWithAString* _loadAllCommand;
    };
}

#endif // PLUGINMESSENGER_HH

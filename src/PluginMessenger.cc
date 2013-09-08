#include "PluginMessenger.hh"
#include "PluginLoader.hh"

namespace g4
{
    PluginMessenger::PluginMessenger(PluginLoader* loader)
        : _loader(loader)
    {
        _directory = new G4UIdirectory("/g4/plugin/");
        _directory->SetGuidance("G4Application plugin system commands");
        
        _loadCommand = new G4UIcmdWithAString("/g4/plugin/load", this);
        _loadCommand->SetGuidance("Loads a plugin - fully qualified dynamic library from current directory.");
    }
    
    PluginMessenger::~PluginMessenger()
    {
        delete _loadCommand;
        delete _directory;
    }
    
    void PluginMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
    {
        if (command == _loadCommand)
        {
            _loader->Load(newValue);
        }
    }
}

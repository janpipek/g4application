#include "PluginMessenger.hh"

#include <G4UIdirectory.hh>
#include <G4UIcmdWithAString.hh>
#include <G4Tokenizer.hh>

#include "PluginLoader.hh"

using namespace std;

namespace g4
{
    PluginMessenger::PluginMessenger(PluginLoader* loader)
        : _loader(loader)
    {
        _directory = new G4UIdirectory("/plugin/");
        _directory->SetGuidance("G4Application plugin system commands");
        
        _openCommand = new G4UIcmdWithAString("/plugin/open", this);
        _openCommand->SetGuidance("Open a plugin from current directory.");
        _openCommand->SetParameterName("pluginName", false);
        _openCommand->AvailableForStates(G4State_PreInit);

        _loadAllCommand = new G4UIcmdWithAString("/plugin/loadAll", this);
        _loadAllCommand->SetGuidance("Load all components from a plugin.");
        _loadAllCommand->SetParameterName("pluginName", false);
        _loadAllCommand->AvailableForStates(G4State_PreInit);

        _loadCommand = new G4UIcommand("/plugin/load", this);
        _loadCommand->SetGuidance("Load a component from a plugin.");
        _loadCommand->AvailableForStates(G4State_PreInit);

        G4UIparameter* pluginNameParam = new G4UIparameter("pluginName", 's', false);
        pluginNameParam->SetGuidance("Name of the plugin.");
        _loadCommand->SetParameter(pluginNameParam);

        G4UIparameter* componentNameParam = new G4UIparameter("componentName", 's', false);
        componentNameParam->SetGuidance("Name of the component.");
        _loadCommand->SetParameter(componentNameParam);

        _listComponentsCommand = new G4UIcmdWithAString("/plugin/listComponents", this);
    }

    PluginMessenger::~PluginMessenger()
    {
        delete _openCommand;
        delete _loadCommand;
        delete _loadAllCommand;
        delete _listComponentsCommand;

        delete _directory;
    }
    
    void PluginMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
    {
        if (command == _openCommand)
        {
            _loader->Open(newValue);
        }
        else if (command == _loadAllCommand)
        {
            _loader->LoadAll(newValue);
        }
        else if (command == _loadCommand)
        {
            G4Tokenizer next(newValue);
            G4String pluginName = next();
            G4String componentName = next();
            _loader->Load(pluginName, componentName);
        }
        else if (command == _listComponentsCommand)
        {
            _loader->ListComponents(newValue);
        }
    }
}

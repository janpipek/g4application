#include "ComponentMessenger.hh"

#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAnInteger.hh>

#include "ComponentManager.hh"

using namespace g4;

ComponentMessenger::ComponentMessenger(ComponentManager* manager)
: _manager(manager)
{
    _directory = new G4UIdirectory("/component/");

    _listCommand = new G4UIcmdWithoutParameter("/component/list", this);
    _listCommand->SetGuidance("List loaded components.");
    _listCommand->SetToBeBroadcasted(false);
}

ComponentMessenger::~ComponentMessenger()
{
    delete _listCommand;
    delete _directory;
}

void ComponentMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if (command == _listCommand)
    {
        _manager->ListComponents();
    }
}

#include "ComponentMessenger.hh"

using namespace g4;

ComponentMessenger::ComponentMessenger(ComponentManager* manager)
: _manager(manager)
{

}

ComponentMessenger::~ComponentMessenger()
{

}

void ComponentMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{

}
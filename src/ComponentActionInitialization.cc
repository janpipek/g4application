#include "ComponentActionInitialization.hh"

#include "CompositeEventAction.hh"
#include "CompositeRunAction.hh"
#include "CompositeSteppingAction.hh"
#include "CompositeTrackingAction.hh"

using namespace g4;

void ComponentActionInitialization::Build() const
{
    BuildCompositeAction<CompositeEventAction, G4UserEventAction>(&Component::CreateEventAction);
    BuildCompositeAction<CompositeRunAction, G4UserRunAction>(&Component::CreateRunAction);
    BuildCompositeAction<CompositeSteppingAction, G4UserSteppingAction>(&Component::CreateSteppingAction);
    BuildCompositeAction<CompositeTrackingAction, G4UserTrackingAction>(&Component::CreateTrackingAction);
}

void ComponentActionInitialization::BuildForMaster() const
{
    BuildCompositeAction<CompositeRunAction>(&Component::CreateRunAction);
}

ComponentActionInitialization::ComponentActionInitialization(ComponentManager* componentManager)
{
    _componentManager = componentManager;
}

#include "ApplicationActionInitialization.hh"

#include "CompositeEventAction.hh"
#include "CompositeRunAction.hh"
#include "CompositeSteppingAction.hh"
#include "CompositeTrackingAction.hh"

#include "G4Application.hh"
#include "Component.hh"

using namespace g4;

void ApplicationActionInitialization::Build() const
{
    BuildCompositeAction<CompositeEventAction, G4UserEventAction>(&Component::CreateEventAction);
    BuildCompositeAction<CompositeRunAction, G4UserRunAction>(&Component::CreateRunAction);
    BuildCompositeAction<CompositeSteppingAction, G4UserSteppingAction>(&Component::CreateSteppingAction);
    BuildCompositeAction<CompositeTrackingAction, G4UserTrackingAction>(&Component::CreateTrackingAction);
}

void ApplicationActionInitialization::BuildForMaster() const
{
    BuildCompositeAction<CompositeRunAction>(&Component::CreateRunAction);
}

ApplicationActionInitialization::ApplicationActionInitialization(G4Application* application)
{
    _application = application;
}

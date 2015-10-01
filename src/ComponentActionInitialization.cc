#include "ComponentActionInitialization.hh"

#include <G4VUserPrimaryGeneratorAction.hh>
#include <globals.hh>

#include "CompositeEventAction.hh"
#include "CompositeRunAction.hh"
#include "CompositeSteppingAction.hh"
#include "CompositeTrackingAction.hh"

using namespace g4;

void ComponentActionInitialization::Build() const
{
    G4cout << "Constructing composite action for worker thread..." << G4endl;
    BuildCompositeAction<CompositeEventAction, G4UserEventAction>(&Component::CreateEventAction);
    BuildCompositeAction<CompositeRunAction, G4UserRunAction>(&Component::CreateRunAction);
    BuildCompositeAction<CompositeSteppingAction, G4UserSteppingAction>(&Component::CreateSteppingAction);
    BuildCompositeAction<CompositeTrackingAction, G4UserTrackingAction>(&Component::CreateTrackingAction);

    SetUserAction(GetPrimaryGeneratorAction());
}

void ComponentActionInitialization::BuildForMaster() const
{
    G4cout << "Constructing composite action for master thread..." << G4endl;
    BuildCompositeAction<CompositeRunAction>(&Component::CreateRunAction);
}

G4VUserPrimaryGeneratorAction* ComponentActionInitialization::GetPrimaryGeneratorAction() const
{
    G4VUserPrimaryGeneratorAction* generatorAction = nullptr;
    auto components = _componentManager->GetComponents();
    for (auto it = components.begin(); it != components.end(); it++)
    {
        Component* component = it->second;
        G4VUserPrimaryGeneratorAction* componentAction = component->CreatePrimaryGeneratorAction();
        if (componentAction)
        {
            if (generatorAction)
            {
                G4Exception("ComponentActionInitialization", "MultiplePrimaryGeneratorActions", FatalException, "Multiple component define the primary generator action.");
            }
            else
            {
                generatorAction = componentAction;
            }
        }
    }
    if (!generatorAction)
    {
        G4Exception("ComponentActionInitialization", "NoPrimaryGeneratorActions", FatalException, "No component defines the primary generator action.");
    }
    return generatorAction;
}

ComponentActionInitialization::ComponentActionInitialization(ComponentManager* componentManager)
{
    _componentManager = componentManager;
}

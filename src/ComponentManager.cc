#include "ComponentManager.hh"

#include "ComponentActionInitialization.hh"
#include "CompositeDetectorConstruction.hh"

using namespace g4;

void ComponentManager::AddComponent(Component *component)
{
    // TODO: Check master thread
    // TODO: Check status
    _components.push_back(component);
}

G4VUserActionInitialization* ComponentManager::GetActionInitialization()
{
    return new ComponentActionInitialization(this);
}

G4VUserDetectorConstruction* ComponentManager::GetDetectorConstruction()
{
    return new CompositeDetectorConstruction(this);
}

G4VUserPhysicsList* ComponentManager::GetPhysicsList()
{
    G4VUserPhysicsList* list = nullptr;
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        Component* component = *it;
        G4VUserPhysicsList* componentList = component->CreatePhysicsList();
        if (componentList)
        {
            if (list)
            {
                G4Exception("ComponentManager", "MultiplePhysicsLists", FatalException, "Multiple components define the physics list.");
            }
            else
            {
                list = componentList;
            }
        }
    }
    if (!list)
    {
        G4Exception("ComponentManager", "NoPhysicsLists", FatalException, "No component defines the physics list.");
    }
    return list;
}

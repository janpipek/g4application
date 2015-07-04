#include "ComponentManager.hh"

#include "ComponentActionInitialization.hh"
#include "CompositeDetectorConstruction.hh"

using namespace g4;

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
                // TODO: Exception
            }
            else
            {
                list = componentList;
            }
        }
    }
    if (!list)
    {
        // TODO: Exception
    }
    return list;
}

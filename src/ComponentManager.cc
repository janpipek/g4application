#include "ComponentManager.hh"

#include "ComponentMessenger.hh"
#include "ComponentActionInitialization.hh"
#include "CompositeDetectorConstruction.hh"

using namespace g4;

ComponentManager::ComponentManager()
{
    _messenger = new ComponentMessenger(this);
}

ComponentManager::~ComponentManager()
{
    delete _messenger;
}

void ComponentManager::AddComponent(const G4String& name, Component *component)
{
    component->OnLoad(); // TODO: ???
    if (GetComponent(name))
    {
        G4Exception("ComponentManager", "DuplicitComponentName", FatalException, G4String("A component with the name `" + name + "` already registered."));
    }
    else
    {
        _components[name] = component;
    }
}

Component* ComponentManager::GetComponent(const G4String& name) const
{
    if (_components.find(name) != _components.end())
    {
        return _components.at(name);
    }
    else
    {
        return nullptr;
    }
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
    // for (auto it : _components)
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        Component* component = it->second;
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

void ComponentManager::ListComponents() const
{
    G4cout << G4endl;
    G4cout << "-----------------" << G4endl;
    G4cout << "Loaded components" << G4endl;
    G4cout << "-----------------" << G4endl;
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        G4cout << "* " << it->first << G4endl;
    }
    G4cout << "-----------------" << G4endl;
}

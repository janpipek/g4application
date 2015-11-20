#include "ComponentManager.hh"

#include "ComponentMessenger.hh"
#include "ComponentActionInitialization.hh"
#include "CompositeDetectorConstruction.hh"

using namespace g4;

ComponentManager::ComponentManager() : _initialization(nullptr)
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

void ComponentManager::UnloadComponent(const G4String &name)
{
    Component* component = GetComponent(name);
    if (component)
    {
        G4cout << "Removing component " << name << "..." << G4endl;
        component->Unload();
        delete component;
        G4cout << _components.erase(name) << G4endl;
    }
    else
    {
        // Warning
        G4cout << "Component " << name << " not found." << G4endl;
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

G4VModularPhysicsList* ComponentManager::GetPhysicsList()
{
    G4VModularPhysicsList* list = nullptr;
    // for (auto it : _components)
    for (auto it = _components.begin(); it != _components.end(); it++)
    {
        Component* component = it->second;
        G4VModularPhysicsList* componentList = component->CreatePhysicsList();
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
        // TODO: If you use component manager in an app, this may be a valid condition
        G4Exception("ComponentManager", "NoPhysicsLists", FatalException, "No component defines the physics list.");
    }
    return list;
}

std::vector<G4VUserParallelWorld *> ComponentManager::GetParallelWorlds()
{
    std::vector<G4VUserParallelWorld*> result;
    for (auto key_val : _components)
    {
        Component* component = key_val.second;
        auto parallelWorlds = component->CreateParallelWorlds();
        result.reserve(result.size() + parallelWorlds.size());
        result.insert(result.end(), parallelWorlds.begin(), parallelWorlds.end());
    }
    return result;
}

void ComponentManager::UpdateBeforeRun()
{
    // _initialization->
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

#include "ComponentManager.hh"

#include "ComponentMessenger.hh"
#include "ComponentActionInitialization.hh"
#include "CompositeDetectorConstruction.hh"

using namespace g4;

ComponentManager::ComponentManager()
    : VerbosityMixin(true, "/component/"), _messenger(this, "/component/")
{
    _messenger.DeclareMethod("list", &ComponentManager::ListComponents);
    if (GetVerboseLevel() > 0)
    {
        G4cout << "ComponentManager: Constructor finished." << G4endl;
    }
}

ComponentManager::~ComponentManager()
{
    if (GetVerboseLevel() > 0)
    {
        G4cout << "ComponentManager: Destructor called (and finished)." << G4endl;
    }
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
        if (GetVerboseLevel() > 0)
        {
            G4cout << "ComponentManager: Added component `" << name << "`." << G4endl;
        }
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
    if (GetVerboseLevel() > 0)
    {
        G4cout << "ComponentManager: Creating component action intialization..." << G4endl;
    }
    return new ComponentActionInitialization(this);
    if (GetVerboseLevel() > 0)
    {
        G4cout << "ComponentManager: Created component action initialization." << G4endl;
    }
}

G4VUserDetectorConstruction* ComponentManager::GetDetectorConstruction()
{
    if (GetVerboseLevel() > 0)
    {
        G4cout << "ComponentManager: Creating composite detector construction..." << G4endl;
    }
    return new CompositeDetectorConstruction(this);
    if (GetVerboseLevel() > 0)
    {
        G4cout << "ComponentManager: Created composite detector construction." << G4endl;
    }
}

G4VModularPhysicsList* ComponentManager::GetPhysicsList()
{
    if (GetVerboseLevel() > 0)
    {
        G4cout << "ComponentManager: Searching for physics list among loaded components..." << G4endl;
    }
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
                if (GetVerboseLevel() > 0)
                {
                    G4cout << "ComponentManager: Using physics list from component `" << it->first << "`" << G4endl;
                }
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
    if (GetVerboseLevel() > 0)
    {
        G4cout << "ComponentManager: Creating parallel worlds..." << G4endl;
    }
    for (auto key_val : _components)
    {
        Component* component = key_val.second;
        auto parallelWorlds = component->CreateParallelWorlds();
        if (parallelWorlds.size())
        {
            if (GetVerboseLevel() > 0)
            {
                G4cout << "ComponentManager: Adding " << parallelWorlds.size() << " parallel worlds from component `" << key_val.first << "`..." << G4endl;
            }
            result.reserve(result.size() + parallelWorlds.size());
            result.insert(result.end(), parallelWorlds.begin(), parallelWorlds.end());
        }
    }
    if (GetVerboseLevel() > 0)
    {
        G4cout << "ComponentManager: Total " << result.size() << " parallel worlds created." << G4endl;
    }
    return result;
}

void ComponentManager::ListComponents()
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

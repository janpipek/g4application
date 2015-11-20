#ifndef COMPONENTMANAGER_HH
#define COMPONENTMANAGER_HH

#include <map>

#include <G4String.hh>

#include "RunInitializer.hh"

namespace g4
{
    class Component;
    class ComponentMessenger;

    /**
     * @brief The ComponentManager class
     *
     * Threading: shared
     */
    class ComponentManager : public RunInitializer
    {
    public:
        ComponentManager();

        virtual ~ComponentManager();

        const std::map<G4String, Component*>& GetComponents() const { return _components; }

        void AddComponent(const G4String& name, Component* component);

        Component* GetComponent(const G4String& name) const;

        G4VUserActionInitialization* GetActionInitialization() override;

        G4VUserDetectorConstruction* GetDetectorConstruction() override;

        G4VModularPhysicsList* GetPhysicsList() override;

        std::vector<G4VUserParallelWorld *> GetParallelWorlds() override;

        void ListComponents() const;

        void SetVerboseLevel(G4int vl) { _verboseLevel = vl; }

        G4int GetVerboseLevel() const { return _verboseLevel; }

    private:
        std::map<G4String, Component*> _components;

        ComponentMessenger* _messenger;

        G4int _verboseLevel;
    };
}

#endif // COMPONENTMANAGER_HH


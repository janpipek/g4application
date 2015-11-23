#ifndef COMPONENTMANAGER_HH
#define COMPONENTMANAGER_HH

#include <map>

#include <G4String.hh>
#include <G4GenericMessenger.hh>

#include "RunInitializer.hh"
#include "util/Verbosity.hh"

namespace g4
{
    class Component;

    /**
     * @brief The ComponentManager class
     *
     * Threading: shared
     *
     * UI commands (in /component/ directory)
     *   - /component/verbose
     *   - /component/list
     */
    class ComponentManager : public RunInitializer, public util::VerbosityMixin
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

        void ListComponents();

    private:
        std::map<G4String, Component*> _components;

        G4GenericMessenger _messenger;
    };
}

#endif // COMPONENTMANAGER_HH


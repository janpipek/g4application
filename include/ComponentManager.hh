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

        /**
         * @brief Unload a component.
         *
         * Note: In general, components
         */
        void UnloadComponent(const G4String& name);

        G4VUserActionInitialization* GetActionInitialization() override;

        G4VUserDetectorConstruction* GetDetectorConstruction() override;

        G4VModularPhysicsList* GetPhysicsList() override;

        std::vector<G4VUserParallelWorld *> GetParallelWorlds() override;

        void ListComponents() const;

    private:
        std::map<G4String, Component*> _components;

        ComponentMessenger* _messenger;


    };
}

#endif // COMPONENTMANAGER_HH


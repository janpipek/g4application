#ifndef COMPONENTMANAGER_HH
#define COMPONENTMANAGER_HH

#include <map>

#include <G4String.hh>

#include "RunInitializer.hh"

class G4VUserDetectorConstruction;
class G4VUserActionInitialization;
class G4VUserPhysicsList;

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

        G4VUserPhysicsList* GetPhysicsList() override;

        // std::vector<RunObserver*> GetRunObservers() override;

    private:
        std::map<G4String, Component*> _components;

        ComponentMessenger* _messenger;
    };
}

#endif // COMPONENTMANAGER_HH


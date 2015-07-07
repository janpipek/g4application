#ifndef COMPONENTMANAGER_HH
#define COMPONENTMANAGER_HH

#include <vector>

#include "RunInitializer.hh"

class G4VUserDetectorConstruction;
class G4VUserActionInitialization;
class G4VUserPhysicsList;

namespace g4
{
    class Component;
    // class ComponentMessenger;

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

        std::vector<Component*> GetComponents() const { return _components; }

        void AddComponent(Component* component);

        G4VUserActionInitialization* GetActionInitialization() override;

        G4VUserDetectorConstruction* GetDetectorConstruction() override;

        G4VUserPhysicsList* GetPhysicsList() override;

    private:
        std::vector<Component*> _components;

        // ComponentMessenger* _messenger;
    };
}

#endif // COMPONENTMANAGER_HH


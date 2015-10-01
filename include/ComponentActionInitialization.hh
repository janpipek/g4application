#ifndef COMPONENTACTIONINITIALIZATION_HH
#define COMPONENTACTIONINITIALIZATION_HH

#include <G4VUserActionInitialization.hh>

#include "ComponentManager.hh"
#include "Component.hh"

class G4VUserPrimaryGeneratorAction;

namespace g4
{
    /**
     * @brief User action initialization class for ComponentManager
     */
    class ComponentActionInitialization : public G4VUserActionInitialization
    {
    public:
        // TODO: Integrate into the main class?

        ComponentActionInitialization(ComponentManager* componentManager);

        void Build() const override;

        void BuildForMaster() const override;

    protected:
        template<typename CompositeActionType, typename SubActionType> void BuildCompositeAction(SubActionType* (Component::*createFunc) ()) const
        {
            auto components = _componentManager->GetComponents();
            CompositeActionType* compositeAction = new CompositeActionType();
            for (auto it = components.begin(); it != components.end(); it++)
            {
                Component* component = it->second;
                SubActionType* action = (component->*createFunc)();
                if (action)
                {
                    compositeAction->AddSubAction(action);
                }
            }
            this->SetUserAction(compositeAction);
        }

        G4VUserPrimaryGeneratorAction* GetPrimaryGeneratorAction() const;

    private:
        ComponentManager* _componentManager;
    };
}

#endif // COMPONENTACTIONINITIALIZATION_HH


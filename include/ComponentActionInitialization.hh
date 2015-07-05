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
        ComponentActionInitialization(ComponentManager* componentManager);

        virtual void Build() const override;

        virtual void BuildForMaster() const override;

    protected:
        template<typename CompositeActionType, typename SubActionType> void BuildCompositeAction(SubActionType* (Component::*createFunc) () const) const
        {
            auto components = _componentManager->GetComponents();
            CompositeActionType* compositeAction = new CompositeActionType();
            for (auto it = components.begin(); it != components.end(); it++)
            {
                Component* component = *it;
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


#ifndef APPLICATIONACTIONINITIALIZATION_HH
#define APPLICATIONACTIONINITIALIZATION_HH

#include <G4VUserActionInitialization.hh>

#include "G4Application.hh"
#include "ComponentManager.hh"
#include "Component.hh"

namespace g4
{
    class ApplicationActionInitialization : public G4VUserActionInitialization
    {
    public:
        ApplicationActionInitialization(G4Application* application);

        virtual void Build() const override;

        virtual void BuildForMaster() const override;

    protected:
        template<typename CompositeActionType, typename SubActionType> void BuildCompositeAction(SubActionType* (Component::*createFunc) ()) const
        {
            auto components = _application->GetComponentManager()->GetComponents();
            CompositeActionType* compositeAction = new CompositeActionType();
            for (auto it = components.begin(); it != components.end(); it++)
            {
                Component* component = *it;
                SubActionType* action = (component->*createFunc)();
                compositeAction->AddSubAction(action);
            }
            this->SetUserAction(compositeAction);
        }

    private:
        G4Application* _application;
    };
}

#endif // APPLICATIONACTIONINITIALIZATION_HH


#ifndef COMPOSITERUNACTION_HH
#define COMPOSITERUNACTION_HH

#include <G4UserRunAction.hh>
#include "CompositeAction.hh"

namespace g4
{
    class CompositeRunAction : public CompositeAction<G4UserRunAction>
    {
    public:
        virtual void BeginOfRunAction(const G4Run* aRun)
        {
            Invoke(&G4UserRunAction::BeginOfRunAction, aRun);
        }

        virtual void EndOfRunAction(const G4Run* aRun)
        {
            Invoke(&G4UserRunAction::EndOfRunAction, aRun);
        }
    };
}

#endif // COMPOSITERUNACTION_HH

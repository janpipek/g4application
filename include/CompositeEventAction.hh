#ifndef COMPOSITEEVENTACTION_HH
#define COMPOSITEEVENTACTION_HH

#include <G4UserEventAction.hh>
#include "CompositeAction.hh"

namespace g4
{
    class CompositeEventAction : public CompositeAction<G4UserEventAction>
    {
    public:
        void BeginOfEventAction(const G4Event* anEvent) override
        {
            Invoke(&G4UserEventAction::BeginOfEventAction, anEvent);
        }

        void EndOfEventAction(const G4Event* anEvent) override
        {
            Invoke(&G4UserEventAction::EndOfEventAction, anEvent);
        }
    };
}

#endif // COMPOSITEEVENTACTION_HH

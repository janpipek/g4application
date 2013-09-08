#ifndef COMPOSITEEVENTACTION_HH
#define COMPOSITEEVENTACTION_HH

#include <G4UserEventAction.hh>
#include "CompositeAction.hh"

namespace g4
{
    class CompositeEventAction : public CompositeAction<G4UserEventAction>
    {
    public:
        virtual void BeginOfEventAction(const G4Event* anEvent)
        {
            Invoke(&G4UserEventAction::BeginOfEventAction, anEvent);
        }

        virtual void EndOfEventAction(const G4Event* anEvent)
        {
            Invoke(&G4UserEventAction::EndOfEventAction, anEvent);
        }
    };
}

#endif // COMPOSITEEVENTACTION_HH

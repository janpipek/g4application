#ifndef COMPOSITESTEPPINGACTION_HH
#define COMPOSITESTEPPINGACTION_HH

#include <G4UserSteppingAction.hh>
#include <vector>
#include "CompositeAction.hh"

namespace g4
{
    class CompositeSteppingAction : public CompositeAction<G4UserSteppingAction>
    {
    public:
        void UserSteppingAction(const G4Step* step) override
        {
            Invoke(&G4UserSteppingAction::UserSteppingAction, step);
        }
    };
}

#endif // COMPOSITESTEPPINGACTION_HH

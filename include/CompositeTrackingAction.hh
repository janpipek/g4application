#ifndef COMPOSITETRACKINGACTION_HH
#define COMPOSITETRACKINGACTION_HH

#include <G4UserTrackingAction.hh>
#include <vector>
#include "CompositeAction.hh"

namespace g4
{
    class CompositeTrackingAction : public CompositeAction<G4UserTrackingAction>
    {
    public:
        void PreUserTrackingAction(const G4Track* track) override
        {
            Invoke(&G4UserTrackingAction::PreUserTrackingAction, track);
        }

        void PostUserTrackingAction(const G4Track* track) override
        {
            Invoke(&G4UserTrackingAction::PostUserTrackingAction, track);
        }
    };
}

#endif // COMPOSITETRACKINGACTION_HH

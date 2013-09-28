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
        virtual void PreUserTrackingAction(const G4Track* track)
        {
            Invoke(&G4UserTrackingAction::PreUserTrackingAction, track);
        }

        virtual void PostUserTrackingAction(const G4Track* track)
        {
            Invoke(&G4UserTrackingAction::PostUserTrackingAction, track);
        }
    };
}

#endif // COMPOSITETRACKINGACTION_HH
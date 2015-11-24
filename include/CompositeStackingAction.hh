#ifndef COMPOSITESTACKINGACTION_HH
#define COMPOSITESTACKINGACTION_HH

#include <G4UserStackingAction.hh>

#include "CompositeAction.hh"

namespace g4
{
    class CompositeStackingAction : public CompositeAction<G4UserStackingAction>
    {
    public:
        /**
         * @brief Classify a track.
         *
         * The treatment is follows (like a "chain of command"):
         * - If any of the sub-actions proposes other than urgent classification
         *   it is immediatelly used (FIFO)
         * - If no sub-action proposes other than urgent, this is kept.
         */
        G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack) override
        {
            G4ClassificationOfNewTrack classification = fUrgent;
            for (auto action : _actions)
            {
                classification = action->ClassifyNewTrack(aTrack);
                if (classification != fUrgent)
                {
                    break;
                }
            }
            return classification;
        }
    };
}

#endif // COMPOSITESTACKINGACTION_HH


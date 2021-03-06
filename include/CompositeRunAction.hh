#ifndef COMPOSITERUNACTION_HH
#define COMPOSITERUNACTION_HH

#include <G4UserRunAction.hh>
#include <globals.hh>

#include "macros.hh"
#include "CompositeAction.hh"

namespace g4
{
    class CompositeRunAction : public CompositeAction<G4UserRunAction>
    {
    public:
        /**
         * @brief Possibly generate a run.
         * @return nullptr / G4Run based on the output of stored actions
         *
         * It is important that only one run action creates a run,
         * otherwise G4Exception is thrown.
         *
         * This class also distributes the information about master/non-master
         * thread.
         */
        G4Run* GenerateRun() override
        {
            G4Run* run = nullptr;
            for (auto action : _actions)
            {
                action->SetMaster(IsMaster());
                G4Run* candidate = action->GenerateRun();
                if (candidate)
                {
                    if (run)
                    {
                        G4Exception(EXCEPTION_WHERE, "DuplicateRunCreation", FatalException, "More than one run action defines a custom run.");
                    }
                    else
                    {
                        run = candidate;
                    }
                }
            }
            return run;
        }

        void BeginOfRunAction(const G4Run* aRun) override
        {
            Invoke(&G4UserRunAction::BeginOfRunAction, aRun);
        }

        void EndOfRunAction(const G4Run* aRun) override
        {
            Invoke(&G4UserRunAction::EndOfRunAction, aRun);
        }
    };
}

#endif // COMPOSITERUNACTION_HH

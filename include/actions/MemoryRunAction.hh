#ifndef MEMORYRUNACTION_HH
#define MEMORYRUNACTION_HH

#include "G4UserRunAction.hh"

namespace g4
{
    /**
     * @short Action that prints memory consumption info before and after run.
     *
     * Based on code by David Robert Nadeau
     * (see http://nadeausoftware.com/articles/2012/07/c_c_tip_how_get_process_resident_set_size_physical_memory_use)
     */
    class MemoryRunAction : public G4UserRunAction
    {
    public:
        void BeginOfRunAction(const G4Run *aRun);

        void EndOfRunAction(const G4Run *aRun);
    };
}

#endif // MEMORYRUNACTION_HH

#ifndef MEMORYLOGGING_HH
#define MEMORYLOGGING_HH

#include "Component.hh"

namespace g4
{
    namespace components
    {
        class MemoryLogging : public Component
        {
        public:
            virtual G4UserRunAction* CreateRunAction() override;
        };
    }
}

#endif
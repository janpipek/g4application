#ifndef EVENTNUMBERLOGGING_HH
#define EVENTNUMBERLOGGING_HH

#include "Component.hh"

namespace g4
{
    namespace components
    {
        /**
          * @short Display current event number processed (+ rough speed info).
          *
          * Configuration:
          * - component.EventNumberLogging.frequency : How often (0 = never)
          */
        class EventNumberLogging : public Component
        {
        public:
            virtual G4UserEventAction* CreateEventAction() override;

        protected:
            virtual void OnLoad() override;
        };
    }
}

#endif
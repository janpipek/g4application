#ifndef REFERENCEPHYSICSLIST_HH
#define REFERENCEPHYSICSLIST_HH

#include "Component.hh"

namespace g4
{
    namespace components
    {
        /**
         * @brief Automatic loading of reference physics list.
         *
         * Configuration:
         * - component.ReferencePhysicsList.listName Name of the physics list to be loaded.
         *
         * If the configuration value is not set, no physics list is loaded and its
         * definition is left to other components.
         */
        class ReferencePhysicsList : public Component
        {
        public:
            ReferencePhysicsList();

            virtual G4VUserPhysicsList* CreatePhysicsList();
        };
    }
}

#endif // REFERENCEPHYSICSLIST_HH


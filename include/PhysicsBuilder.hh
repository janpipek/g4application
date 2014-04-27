#ifndef PHYSICSBUILDER_HH
#define PHYSICSBUILDER_HH

#include "G4VUserPhysicsList.hh"

namespace g4
{
    /**
      * @short Plugin physics.
      *
      * If this class is returned from the plugin, it's used to initialize
      * the physics.
      *
      * It is necessary that at least one plugin provides this functionality.
      */
    class PhysicsBuilder
    {
    public:
        virtual G4VUserPhysicsList* CreateUserPhysicsList() = 0;

        virtual ~PhysicsBuilder() { }
    };
}

#endif // PHYSICSBUILDER_HH

#ifndef DEFAULTWORLD_HH
#define DEFAULTWORLD_HH

#include "Component.hh"

namespace g4
{
    namespace components
    {
        /**
          * @short Builder of default world volume.
          *
          * Configuration:
          *   - component.defaultWorld.materialName: name of the world volume material
          *         (the name must be understandable by G4NistManager)
          *   - component.defaultWorld.size_x: world x size in Geant4 units
          *   - component.defaultWorld.size_y: world y size in Geant4 units
          *   - component.defaultWorld.size_z: world z size in Geant4 units
          *
          * The configuration is read once at the time of detector construction.
          * No further changes are taken into account.
          */
        class DefaultWorld : public Component
        {
        public:
            virtual G4VPhysicalVolume *CreateWorld();

            virtual void OnLoad();

        private:
            G4ThreeVector _size;

            G4String _material;
        };
    }
}

#endif // DEFAULTWORLD_HH

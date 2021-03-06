#ifndef COMPOSITEDETECTORCONSTRUCTION_HH
#define COMPOSITEDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

namespace g4
{
    class ComponentManager;

    class CompositeDetectorConstruction : public G4VUserDetectorConstruction
    {
    public:
        CompositeDetectorConstruction(ComponentManager* manager, G4VPhysicalVolume *worldVolume = nullptr);

        G4VPhysicalVolume* Construct() override;

        void ConstructSDandField() override;

    private:
        ComponentManager* _componentManager;

        G4VPhysicalVolume* _worldVolume;
    };
}

#endif // COMPOSITEDETECTORCONSTRUCTION_HH


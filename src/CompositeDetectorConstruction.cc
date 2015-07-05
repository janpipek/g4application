#include "CompositeDetectorConstruction.hh"

#include "ComponentManager.hh"
#include "Component.hh"
#include "G4VPhysicalVolume.hh"

using namespace g4;

CompositeDetectorConstruction::CompositeDetectorConstruction(ComponentManager* manager, G4VPhysicalVolume* worldVolume)
    : _componentManager(manager), _worldVolume(worldVolume)
{

}

G4VPhysicalVolume* CompositeDetectorConstruction::Construct()
{
    auto components = _componentManager->GetComponents();

    // Construct world (just one of the components should have it)
    for (auto it = components.begin(); it != components.end(); it++)
    {
        Component* component = *it;
        G4VPhysicalVolume* componentWorld = component->CreateWorld();
        if (componentWorld)
        {
            if (_worldVolume)
            {
                // TODO: Error
            }
            else
            {
                _worldVolume = componentWorld;
            }
        }
    }

    // Construct the geometry of components
    for (auto it = components.begin(); it != components.end(); it++)
    {
        Component* component = *it;
        component->BuildGeometry(_worldVolume->GetLogicalVolume());
    }
}

#include "CompositeDetectorConstruction.hh"

#include <G4VPhysicalVolume.hh>

#include "ComponentManager.hh"
#include "Component.hh"

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
        Component* component = it->second;
        G4VPhysicalVolume* componentWorld = component->CreateWorld();
        if (componentWorld)
        {
            if (_worldVolume)
            {
                G4Exception("CompositeDetectorConstruction", "MultipleWorldVolumes", FatalException, "Multiple components define the world volume.");
            }
            else
            {
                _worldVolume = componentWorld;
            }
        }
    }
    if (!_worldVolume)
    {
        G4Exception("CompositeDetectorConstruction", "NoWorldVolume", FatalException, "No world volume defined in any of the components.");
    }

    // Construct the geometry of components
    for (auto it = components.begin(); it != components.end(); it++)
    {
        Component* component = it->second;
        component->BuildGeometry(_worldVolume->GetLogicalVolume());
    }
    return _worldVolume;
}

void CompositeDetectorConstruction::ConstructSDandField()
{
    auto components = _componentManager->GetComponents();
    // Construct the geometry of components
    for (auto it = components.begin(); it != components.end(); it++)
    {
        Component* component = it->second;
        component->ConstructSDandField();
    }
}

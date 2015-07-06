#include "components/DefaultWorld.hh"

#include <G4Box.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4VisAttributes.hh>

#include "Configuration.hh"

using namespace g4::components;
using namespace std;
using namespace CLHEP;

G4VPhysicalVolume *DefaultWorld::CreateWorld()
{
    // Read configuration
    G4double x = Configuration::Get<double>("component.defaultWorld.size_x");
    G4double y = Configuration::Get<double>("component.defaultWorld.size_y");
    G4double z = Configuration::Get<double>("component.defaultWorld.size_z");
    _size = G4ThreeVector(x, y, z);

    const G4String _materialName = Configuration::Get<string>("component.defaultWorld.materialName");
    G4Material* material = G4NistManager::Instance()->FindOrBuildMaterial(_materialName);

    // 1 - solid
    G4Box* worldBox = new G4Box("worldBox", x / 2, y / 2, z / 2);

    // 2 - logical volume
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, material, "worldLog");

    // 3 - physical volume
    G4PVPlacement* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "worldPhys", 0, false, 0);
    worldLog->SetVisAttributes (G4VisAttributes::Invisible);
    return worldPhys;
}

void DefaultWorld::OnLoad()
{
    Configuration::SetDefaultValue("component.defaultWorld.materialName", "G4_AIR");
    Configuration::SetDefaultValue("component.defaultWorld.size_x", 2.5 * m);
    Configuration::SetDefaultValue("component.defaultWorld.size_y", 2.5 * m);
    Configuration::SetDefaultValue("component.defaultWorld.size_z", 2.5 * m);
}

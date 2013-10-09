#include "ExampleGeometryBuilder.hh"

// Geant4 includes
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

using namespace std;

void ExampleGeometryBuilder::BuildGeometry(G4LogicalVolume* volume)
{
    G4cout << "Building geometry (one box) from the examplePlugin." << endl;
    double size = 100. * mm;
    G4Box* box = new G4Box("centralBox", size, size, size);

    G4Material* water = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
    G4LogicalVolume* boxLog = new G4LogicalVolume(box, water, "boxLog");

    new G4PVPlacement( 0, G4ThreeVector(0., 0., 0.), boxLog, "boxPhys", volume, false, 0);
}

#include "ExamplePlugin.hh"

#include <G4PVPlacement.hh>
#include <G4LogicalVolume.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4VisAttributes.hh>

#include "ExampleEventAction.hh"
#include "ExamplePhysicsList.hh"
#include "ExampleParticleGenerator.hh"

MAKE_G4_PLUGIN( ExamplePlugin )

using namespace g4;
using namespace std;
using namespace CLHEP;

ExamplePlugin::ExamplePlugin()
{
}

ExamplePlugin::~ExamplePlugin()
{
}

/* void ExamplePlugin::OnRunInitialized()
{
    G4cout << "ExamplePlugin::OnRunInitialized: adding event action..." << endl;
    _eventAction = new ExampleEventAction();
    // G4Application::Instance()->GetRunManager()->AddAction(_eventAction);
}*/

void ExamplePlugin::BuildGeometry(G4LogicalVolume *logVolume)
{
    G4cout << "Building geometry (one box) from the examplePlugin." << G4endl;
    double size = 100. * mm;
    G4Box* box = new G4Box("centralBox", size, size, size);

    G4Material* water = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
    G4LogicalVolume* boxLog = new G4LogicalVolume(box, water, "boxLog");

    new G4PVPlacement( 0, G4ThreeVector(0., 0., 0.), boxLog, "boxPhys", logVolume, false, 0);
}

G4VUserPrimaryGeneratorAction *ExamplePlugin::CreatePrimaryGeneratorAction()
{
    G4cout << "Creating particle generator action from the examplePlugin." << G4endl;
    return new ExampleParticleGenerator();
}

G4UserEventAction *ExamplePlugin::CreateEventAction()
{
    G4cout << "Creating event action from the examplePlugin." << G4endl;
    return new ExampleEventAction();
}

G4VUserPhysicsList *ExamplePlugin::CreatePhysicsList()
{
    G4cout << "Creating physics list from the examplePlugin." << G4endl;
    return new ExamplePhysicsList();
}

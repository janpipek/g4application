#include "ParallelPlugin.hh"

#include <Component.hh>   // g4App
#include <G4VUserParallelWorld.hh>
#include <G4NistManager.hh>
#include <G4Material.hh>
#include <G4Box.hh>
#include <G4SystemOfUnits.hh>
#include <G4PVPlacement.hh>
#include <G4VisAttributes.hh>

MAKE_G4_PLUGIN( ParallelPlugin )

using namespace g4;
using namespace std;

class ParWorld1 : public G4VUserParallelWorld
{
public:
    ParWorld1() : G4VUserParallelWorld("parworld1") { }

    virtual void Construct()
    {
        auto nist = G4NistManager::Instance();
        auto water = nist->FindOrBuildMaterial("G4_WATER");

        G4VPhysicalVolume* ghostWorld = GetWorld();
        G4LogicalVolume* worldLogical = ghostWorld->GetLogicalVolume();

        G4VSolid* paraBox = new G4Box("paraBox",5.0*cm,5.0*cm,5.0*cm);
        G4LogicalVolume* paraBoxLogical = new G4LogicalVolume(paraBox,water,"paraBox");

        G4VisAttributes* blue = new G4VisAttributes(G4Colour(0. ,0. ,1., 1.0));
        blue->SetVisibility(true);
        blue->SetForceSolid(true);
        paraBoxLogical->SetVisAttributes(blue);

        new G4PVPlacement(0,G4ThreeVector(-10.0*cm,0.,0.),paraBoxLogical,"paraBox",worldLogical,false,0);
    }
};

class Parallel1 : public Component
{
public:
    virtual std::vector<G4VUserParallelWorld *> CreateParallelWorlds()
    {
        return { new ParWorld1() };
    }
};

class ParWorld2 : public G4VUserParallelWorld
{
public:
    ParWorld2() : G4VUserParallelWorld("parworld2") { }

    virtual void Construct()
    {
        G4Element* carbon = G4NistManager::Instance()->FindOrBuildElement("C");
        G4Element* hydrogen = G4NistManager::Instance()->FindOrBuildElement("H");
        G4Element* oxygen = G4NistManager::Instance()->FindOrBuildElement("O");

        auto polyester = new G4Material("polyester", 1.35 * g/cm3, 3);
        polyester->AddElement(hydrogen, 4.2 * perCent);
        polyester->AddElement(carbon, 62.5 * perCent);
        polyester->AddElement(oxygen, 33.3 * perCent);

        G4VPhysicalVolume* ghostWorld = GetWorld();
        G4LogicalVolume* worldLogical = ghostWorld->GetLogicalVolume();

        G4VSolid* paraBox = new G4Box("paraBox", 5.0*cm, 5.0*cm, 5.0*cm);
        G4LogicalVolume* paraBoxLogical = new G4LogicalVolume(paraBox, polyester, "paraBox");

        G4VisAttributes* red = new G4VisAttributes(G4Colour(1. ,0. ,0., 1.0));
        red->SetVisibility(true);
        red->SetForceSolid(true);
        paraBoxLogical->SetVisAttributes(red);

        new G4PVPlacement(0,G4ThreeVector(10.0*cm,0.,0.), paraBoxLogical, "paraBox", worldLogical, false, 0);
    }
};

class Parallel2 : public Component
{
public:
    virtual std::vector<G4VUserParallelWorld *> CreateParallelWorlds()
    {
        return { new ParWorld2() };
    }
};

Component* ParallelPlugin::GetComponent(const string& name)
{
    if (name == "parallel1")
    {
        return new Parallel1();
    }
    else if (name == "parallel2")
    {
        return new Parallel2();
    }
    return nullptr;
}

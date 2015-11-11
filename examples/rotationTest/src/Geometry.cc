#include "Geometry.hh"

#include <G4Box.hh>
#include <G4NistManager.hh>
// #include <G4Colour.hh>
#include <G4VisAttributes.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>

using namespace g4;
using namespace std;

Geometry::Geometry()
	: _position({90 * cm, 0, 0}), _matrix()
{
	_matrix.rotateY(90.0 * deg);
}

void Geometry::BuildGeometry(G4LogicalVolume* world)
{
	// Solids
	G4Box* motherBox = new G4Box("mother", 100 * cm, 20 * cm, 10 * cm);
	G4Box* daughterBox = new G4Box("daughter", 10 * cm, 2 * cm, 1 * cm);
	G4Box* dotBox = new G4Box("dot", 0.5 * cm, 0.5 * cm, 0.5 * cm);

	// Materials
	G4NistManager* nist = G4NistManager::Instance();
	G4Material* kapton = nist->FindOrBuildMaterial("G4_KAPTON"); 
	G4Material* air = nist->FindOrBuildMaterial("G4_AIR"); 

	// Logical volumes
	G4LogicalVolume* mother = new G4LogicalVolume(motherBox, kapton, "mother");
	G4LogicalVolume* daughter = new G4LogicalVolume(daughterBox, air, "daughter");
	G4LogicalVolume* dot = new G4LogicalVolume(dotBox, air, "dot");

	// Physical volumes
	new G4PVPlacement(nullptr, {}, mother, "mother", world, false, 0);
	new G4PVPlacement(nullptr, { 9.5 * cm, 1.5 * cm, 0.5 * cm}, dot, "dot", daughter, false, 0);
	CreatePhysicalVolume(daughter, mother);	

	// Visualize
    G4VisAttributes* blue = new G4VisAttributes(G4Colour(0. ,0. ,1., 0.4));
    blue->SetVisibility(true);
    blue->SetForceWireframe(true);
    daughter->SetVisAttributes(blue);

    G4VisAttributes* wire = new G4VisAttributes(G4Colour(1. ,0. ,0., 0.4));
    wire->SetVisibility(true);
    wire->SetForceWireframe(true);
    mother->SetVisAttributes(wire);    

	G4VisAttributes* white = new G4VisAttributes(G4Colour(1. ,1. ,1., 0.4));
    white->SetVisibility(true);
    white->SetForceSolid(true);
    dot->SetVisAttributes(white);    
}

G4VPhysicalVolume* ActiveGeometry::CreatePhysicalVolume(G4LogicalVolume* daughter, G4LogicalVolume* mother)
{
	return new G4PVPlacement(
		G4Transform3D(
			_matrix,
			_position
		),
		daughter, "daughter", mother, false, 0
	);
}

G4VPhysicalVolume* PassiveGeometry::CreatePhysicalVolume(G4LogicalVolume* daughter, G4LogicalVolume* mother)
{
	return new G4PVPlacement(
		&_matrix,
		_position,
		daughter, "daughter", mother, false, 0
	);
}
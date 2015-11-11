#ifndef GEOMETRY_HH
#define GEOMETRY_HH

#include "Component.hh"

class Geometry : public g4::Component
{
public:
	Geometry();

	virtual void BuildGeometry(G4LogicalVolume* logVolume) override;

private:
	virtual G4VPhysicalVolume* CreatePhysicalVolume(G4LogicalVolume* daughter, G4LogicalVolume* mother) = 0;

protected:
	G4ThreeVector _position;

	G4RotationMatrix _matrix;
};

class ActiveGeometry : public Geometry
{
private:
	G4VPhysicalVolume* CreatePhysicalVolume(G4LogicalVolume* daughter, G4LogicalVolume* mother) override;
};

class PassiveGeometry : public Geometry
{
private:
	G4VPhysicalVolume* CreatePhysicalVolume(G4LogicalVolume* daughter, G4LogicalVolume* mother) override;
};

#endif
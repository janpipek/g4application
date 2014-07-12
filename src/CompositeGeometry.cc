#include "CompositeGeometry.hh"

#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4VisAttributes.hh>
#include <G4LogicalVolume.hh>

#include "GeometryBuilder.hh"

using namespace std;

namespace g4
{
    CompositeGeometry::CompositeGeometry() :
        _detectorConstruction(0), _worldLog(0), _worldPhys(0)
    {       
    }
    
    CompositeGeometry::~CompositeGeometry()
    {
        // Remove all builders
        for (vector<GeometryBuilder*>::iterator it = _builders.begin(); it != _builders.end(); it++)
        {
            delete *it;
        }
    }

    void CompositeGeometry::SetWorldVolume(G4VPhysicalVolume* volume)
    {
        if (_worldPhys)
        {
            throw "World volume already defined.";
        }
        _worldPhys = volume;
    }
    
    G4VUserDetectorConstruction* CompositeGeometry::GetDetectorConstruction()
    {
        if (!_detectorConstruction)
        {
            _detectorConstruction = new CompositeGeometry::CompositeGeometryDetectorConstruction(this);
        }
        return _detectorConstruction;
    }
    
    G4VPhysicalVolume* CompositeGeometry::CompositeGeometryDetectorConstruction::Construct()
    {
        if (!_parent->_worldPhys)
        {
            CreateWorld();
        }
        if (!_parent->_worldLog)
        {
            _parent->_worldLog = _parent->_worldPhys->GetLogicalVolume();
        }
        // Call all builders
        for (vector<GeometryBuilder*>::const_iterator it = _parent->_builders.begin(); it != _parent->_builders.end(); it++)
        {
            (*it)->BuildGeometry(_parent->_worldLog);
        }
        return _parent->_worldPhys;
    }
    
    CompositeGeometry::CompositeGeometryDetectorConstruction::CompositeGeometryDetectorConstruction(CompositeGeometry * parent)
        : _parent(parent)
    {
    }
    
    void CompositeGeometry::CompositeGeometryDetectorConstruction::CreateWorld()
    {
        // 1 - solid
        G4double length = 2.5 * m;
        G4Box* worldBox = new G4Box("worldBox", length, length, length);
        
        // 2 - logical volume
        G4Material* air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
        _parent->_worldLog = new G4LogicalVolume(worldBox, air, "worldLog");
        
        // 3 - physical volume
        _parent->_worldPhys = new G4PVPlacement(0, G4ThreeVector(), _parent->_worldLog, "worldPhys", 0, false, 0);
        _parent->_worldLog->SetVisAttributes (G4VisAttributes::Invisible);
    }
}
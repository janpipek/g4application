#include "GeometryBuilder.hh"
#include "G4Application.hh"

#include <G4LogicalVolume.hh>

namespace g4
{
    void GeometryBuilder::GeometryChanged()
    {
        G4Application::Instance()->GetRunManager()->GeometryHasBeenModified();
    }   
}

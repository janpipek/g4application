#include "GeometryBuilder.hh"
#include "G4Application.hh"

namespace g4
{
    void GeometryBuilder::GeometryChanged()
    {
        G4Application::GetInstance()->GetRunManager()->GeometryHasBeenModified();
    }   
}

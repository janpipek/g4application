#include "ExamplePhysicsList.hh"

ExamplePhysicsList::ExamplePhysicsList()
{
    RegisterPhysics(new G4EmLivermorePhysics());
}

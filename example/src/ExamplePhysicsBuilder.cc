#include "ExamplePhysicsBuilder.hh"

#include "G4VModularPhysicsList.hh"
#include "G4EmLivermorePhysics.hh"

class ExamplePhysics : public G4VModularPhysicsList
{
public:
    ExamplePhysics()
    {
        RegisterPhysics(new G4EmLivermorePhysics());
    }
};

ExamplePhysicsBuilder::ExamplePhysicsBuilder() :
    _physicsList(0)
{
}

ExamplePhysicsBuilder::~ExamplePhysicsBuilder()
{
    if (_physicsList)
    {
        delete _physicsList;
    }
}

G4VUserPhysicsList* ExamplePhysicsBuilder::CreateUserPhysicsList()
{
    if (!_physicsList)
    {
        _physicsList = new ExamplePhysics();
    }
    return _physicsList;
}

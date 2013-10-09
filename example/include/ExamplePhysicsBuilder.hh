#ifndef EXAMPLEPHYSICSBUILDER_HH
#define EXAMPLEPHYSICSBUILDER_HH

#include "PhysicsBuilder.hh"

class ExamplePhysicsBuilder : public g4::PhysicsBuilder
{
public:
    ExamplePhysicsBuilder();

    ~ExamplePhysicsBuilder();

    virtual G4VUserPhysicsList* CreateUserPhysicsList();

private:
    G4VUserPhysicsList* _physicsList;
};
#endif

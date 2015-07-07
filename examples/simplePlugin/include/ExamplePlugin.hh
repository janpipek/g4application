#ifndef EXAMPLEPLUGIN_HH
#define EXAMPLEPLUGIN_HH

// G4Application includes
#include "SingleComponentPlugin.hh"

// Plugin includes
#include "ExampleParticleGenerator.hh"

class ExamplePhysics;

class ExamplePlugin : public g4::SingleComponentPlugin
{
public:
    ExamplePlugin();

    ~ExamplePlugin();

public:
    virtual void BuildGeometry(G4LogicalVolume *logVolume);

    virtual G4VUserPrimaryGeneratorAction* CreatePrimaryGeneratorAction();

    virtual G4UserEventAction* CreateEventAction();

    virtual G4VUserPhysicsList* CreatePhysicsList();
};

#endif // EXAMPLEPLUGIN_HH

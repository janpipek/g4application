#ifndef EXAMPLEPLUGIN_HH
#define EXAMPLEPLUGIN_HH

// G4Application includes
#include "Plugin.hh"
#include "Component.hh"

// Plugin includes
#include "ExampleParticleGenerator.hh"

class ExamplePhysics;

class ExamplePlugin : public g4::Plugin, g4::Component
{
public:
    ExamplePlugin();

    ~ExamplePlugin();

public:
    virtual const std::vector<std::string> GetAvailableComponents() const;

    virtual g4::Component* GetComponent(const std::string& name);

public:
    virtual void BuildGeometry(G4LogicalVolume *logVolume);

    virtual G4VPhysicalVolume *CreateWorld();

    virtual G4VUserPrimaryGeneratorAction* CreatePrimaryGeneratorAction() const;

    virtual G4UserEventAction* CreateEventAction() const;

    virtual G4VUserPhysicsList* CreatePhysicsList() const;
};

#endif // EXAMPLEPLUGIN_HH

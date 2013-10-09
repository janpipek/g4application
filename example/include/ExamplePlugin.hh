#ifndef EXAMPLEPLUGIN_HH
#define EXAMPLEPLUGIN_HH

// G4Application includes
#include "Plugin.hh"
#include "GeometryBuilder.hh"
#include "PhysicsBuilder.hh"

// Plugin includes
#include "ExamplePhysicsBuilder.hh"
#include "ExampleGeometryBuilder.hh"
#include "ExampleParticleGeneratorBuilder.hh"
#include "ExampleEventAction.hh"

class ExamplePlugin : public g4::Plugin
{
public:
    ExamplePlugin();

    ~ExamplePlugin();
    
    virtual const std::string GetName() const { return "Example Plugin"; }
    
    virtual g4::GeometryBuilder* GetGeometryBuilder() { return _geometryBuilder; }

    virtual g4::PhysicsBuilder* GetPhysicsBuilder() { return _physicsBuilder; }

    virtual g4::ParticleGeneratorBuilder* GetParticleGeneratorBuilder() { return _particleGeneratorBuilder; }

    void OnRunInitialized();
    
private:
    ExampleGeometryBuilder* _geometryBuilder;

    ExamplePhysicsBuilder* _physicsBuilder;

    ExampleParticleGeneratorBuilder* _particleGeneratorBuilder;

    ExampleEventAction* _eventAction;
};

#endif // EXAMPLEPLUGIN_HH

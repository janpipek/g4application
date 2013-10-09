#include "ExamplePlugin.hh"

MAKE_G4_PLUGIN( ExamplePlugin )

ExamplePlugin::ExamplePlugin()
{
    _geometryBuilder = new ExampleGeometryBuilder();
    _particleGeneratorBuilder = new ExampleParticleGeneratorBuilder();
    _physicsBuilder = new ExamplePhysicsBuilder();
}

ExamplePlugin::~ExamplePlugin()
{
    delete _geometryBuilder;
    delete _particleGeneratorBuilder;
    delete _physicsBuilder;
}

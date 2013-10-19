#include "ExamplePlugin.hh"

#include "G4Application.hh"

MAKE_G4_PLUGIN( ExamplePlugin )

using namespace g4;
using namespace std;

ExamplePlugin::ExamplePlugin() :
    _eventAction(0)
{
    _geometryBuilder = new ExampleGeometryBuilder();
    _particleGeneratorBuilder = new ExampleParticleGeneratorBuilder();
    _physicsBuilder = new ExamplePhysicsBuilder();
}

ExamplePlugin::~ExamplePlugin()
{
    delete _eventAction;
    delete _geometryBuilder;
    delete _particleGeneratorBuilder;
    delete _physicsBuilder;
}

void ExamplePlugin::OnRunInitialized()
{
    G4cout << "ExamplePlugin::OnRunInitialized: adding event action..." << endl;
    _eventAction = new ExampleEventAction();
    G4Application::GetInstance()->GetRunManager()->AddEventAction(_eventAction);
}

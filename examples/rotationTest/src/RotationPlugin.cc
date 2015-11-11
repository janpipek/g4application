#include "RotationPlugin.hh"

#include <Component.hh>   // g4App
#include "Geometry.hh"

MAKE_G4_PLUGIN( RotationPlugin )

using namespace g4;
using namespace std;

Component* RotationPlugin::GetComponent(const string& name)
{
	if (name == "active") {
		return new ActiveGeometry();
	} else if (name == "passive") {
		return new PassiveGeometry();
	}
	return nullptr;
}

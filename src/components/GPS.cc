#include "components/GPS.hh"

#include <G4GeneralParticleSource.hh>
#include <G4VUserPrimaryGeneratorAction.hh>

using namespace g4::components;

class GPSGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    GPSGeneratorAction(G4GeneralParticleSource* gps)
    {
        _gps = gps;
    }

    virtual void GeneratePrimaries(G4Event *anEvent) override
    {
        _gps->GeneratePrimaryVertex(anEvent);
    }

private:
    G4GeneralParticleSource* _gps;
};

GPS::GPS() : _gps(nullptr)
{
}

GPS::~GPS()
{
    delete _gps;
}

G4VUserPrimaryGeneratorAction *GPS::CreatePrimaryGeneratorAction()
{
    if (!_gps)
    {
        _gps = new G4GeneralParticleSource();
    }
    return new GPSGeneratorAction(_gps);
}


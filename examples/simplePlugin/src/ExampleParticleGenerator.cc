#include "ExampleParticleGenerator.hh"

#include <G4ParticleGun.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTable.hh>

using namespace g4;
using namespace std;
using namespace CLHEP;

ExampleParticleGenerator::ExampleParticleGenerator()
    : _gun(0)
{
    Configuration::SetDefaultValue("generator.energy", 6.0 * MeV);
    _gun = new G4ParticleGun();
    ApplyEnergyChange();
    G4ParticleDefinition* gamma = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    _gun->SetParticleDefinition(gamma);
    _gun->SetParticlePosition(G4ThreeVector(0.0, 0.0, -1.0 * m));
    _gun->SetParticleMomentumDirection(G4ParticleMomentum(0.0, 0.0, 1.0));
}

ExampleParticleGenerator::~ExampleParticleGenerator()
{
    delete _gun;
}

void ExampleParticleGenerator::GeneratePrimaries(G4Event *event)
{
    _gun->GeneratePrimaryVertex(event);
}

void ExampleParticleGenerator::ConfigurationChanged(const string &key)
{
    if (key == "generator.energy")
    {
        ApplyEnergyChange();
    }
}

void ExampleParticleGenerator::ApplyEnergyChange()
{
    _energy = Configuration::Get<double>("generator.energy");
    G4cout << "Generator energy changed to " << _energy << "." << endl;
    if (_gun)
    {
        _gun->SetParticleEnergy(_energy);
    }
}

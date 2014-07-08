#include "ExampleParticleGeneratorBuilder.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "Configuration.hh"

using namespace g4;
using namespace std;

class ExampleParticleGenerator : public G4VUserPrimaryGeneratorAction, ConfigurationObserver
{
public:
    ExampleParticleGenerator()
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

    ~ExampleParticleGenerator()
    {
        delete _gun;
    }

    void GeneratePrimaries(G4Event* event)
    {
        _gun->GeneratePrimaryVertex(event);
    }

protected:
    void ConfigurationChanged(const string &key)
    {
        if (key == "generator.energy")
        {
            ApplyEnergyChange();
        }
    }

private:
    G4ParticleGun* _gun;

    double _energy;

    void ApplyEnergyChange()
    {
        _energy = Configuration::GetValue<double>("generator.energy");
        G4cout << "Generator energy changed to " << _energy << "." << endl;
        if (_gun)
        {
            _gun->SetParticleEnergy(_energy);
        }
    }
};

ExampleParticleGeneratorBuilder::~ExampleParticleGeneratorBuilder()
{
    if (_generator)
    {
        delete _generator;
    }
}

G4VUserPrimaryGeneratorAction* ExampleParticleGeneratorBuilder::BuildParticleGenerator()
{
    if (!_generator)
    {
        _generator = new ExampleParticleGenerator();
    }
    return _generator;
}

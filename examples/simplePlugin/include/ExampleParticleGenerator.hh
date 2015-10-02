#ifndef EXAMPLEPARTICLEGENERATOR_HH
#define EXAMPLEPARTICLEGENERATOR_HH

#include <G4VUserPrimaryGeneratorAction.hh>

#include "Configuration.hh"

class G4ParticleGun;

class ExampleParticleGenerator : public G4VUserPrimaryGeneratorAction, g4::ConfigurationObserver
{
public:
    ExampleParticleGenerator();

    ~ExampleParticleGenerator();

    void GeneratePrimaries(G4Event* event);

protected:
    void ConfigurationChanged(const std::string &key);

private:
    G4ParticleGun* _gun;

    double _energy;

    void ApplyEnergyChange();
};
#endif

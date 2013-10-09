#ifndef EXAMPLEPARTICLEGENERATORBUILDER_HH
#define EXAMPLEPARTICLEGENERATORBUILDER_HH

#include "ParticleGeneratorBuilder.hh"

class ExampleParticleGeneratorBuilder : public g4::ParticleGeneratorBuilder
{
public:
    ExampleParticleGeneratorBuilder() : _generator(0) { }

    ~ExampleParticleGeneratorBuilder();

    G4VUserPrimaryGeneratorAction* BuildParticleGenerator();

private:
    G4VUserPrimaryGeneratorAction* _generator;
};
#endif

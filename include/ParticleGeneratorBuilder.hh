#ifndef PARTICLEGENERATORBUILDER_HH
#define PARTICLEGENERATORBUILDER_HH

#include <G4VUserPrimaryGeneratorAction.hh>

namespace g4
{
    /**
      * Class that builds customized G4VUserPrimaryGeneratorAction upon request.
      *
      * To be used (mostly in plugins).
      *
      * Note: It is important, that the builder instantiates
      *   generator action only after requested. Don't do
      *   this in the constructor!
      */
    class ParticleGeneratorBuilder
    {
    public:
        virtual G4VUserPrimaryGeneratorAction* BuildParticleGenerator() = 0;
    };
}

#endif // PARTICLEGENERATORBUILDER_HH

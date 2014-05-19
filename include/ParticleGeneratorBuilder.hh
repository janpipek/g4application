#ifndef PARTICLEGENERATORBUILDER_HH
#define PARTICLEGENERATORBUILDER_HH

class G4VUserPrimaryGeneratorAction;

namespace g4
{
    /**
      * @short Class that builds customized G4VUserPrimaryGeneratorAction upon request.
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

        virtual ~ParticleGeneratorBuilder() { }
    };
}

#endif // PARTICLEGENERATORBUILDER_HH

#ifndef RUNINITIALIZER_HH
#define RUNINITIALIZER_HH

#include <vector>

class G4VUserActionInitialization;
class G4VUserDetectorConstruction;
class G4VModularPhysicsList;
class G4VUserParallelWorld;

namespace g4
{
    class RunObserver;

    /**
      * Class providing geometry, physics and particle generator
      * for the RunManager.
      *
      * In this library, G4Application is the only subclass
      * but it is possible to create other subclasses in applications
      * without G4Application class.
      */
    class RunInitializer
    {
    public:
        virtual G4VUserActionInitialization* GetActionInitialization() = 0;

        virtual G4VUserDetectorConstruction* GetDetectorConstruction() = 0;

        virtual G4VModularPhysicsList* GetPhysicsList() = 0;

        virtual std::vector<G4VUserParallelWorld*> GetParallelWorlds() = 0;

        virtual void UpdateBeforeRun() { }

        // virtual std::vector<RunObserver*> GetRunObservers() { return {}; }

        virtual ~RunInitializer() = default;
    };
}

#endif // RUNINITIALIZER_HH


#ifndef RUNINITIALIZER_HH
#define RUNINITIALIZER_HH

class G4VUserActionInitialization;
class G4VUserDetectorConstruction;
class G4VUserPhysicsList;

namespace g4
{
    /**
      * Class providing geometry, physics and particle generator
      * for the RunManger.
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

        virtual G4VUserPhysicsList* GetPhysicsList() = 0;

        // virtual std::vector<RunObserver*> GetRunObservers() { return {}; }

        virtual ~RunInitializer() = default;
    };
}

#endif // RUNINITIALIZER_HH


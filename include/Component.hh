#ifndef COMPONENT_HH
#define COMPONENT_HH

#include <G4LogicalVolume.hh>

class G4VUserPrimaryGeneratorAction;
class G4UserEventAction;
class G4UserRunAction;
class G4UserStackingAction;
class G4UserSteppingAction;
class G4UserTrackingAction;
class G4VUserPhysicsList;
class G4VPhysicalVolume;

namespace g4
{
    class GeometryBuilder;
    class ComponentManager;

    /**
     * @brief A component for the G4Application architecture.
     *
     * Instances of this class are shared. Ideally, they have no state, otherwise
     * careful thread-safety is necessary.
     *
     * The components may be created at different stages of application
     * run. Therefore, useful initialization code can be put
     * into `OnLoad` method.
     */
    class Component
    {
    public:
        virtual ~Component() { }

        /**
          * @short Create part of the geometry and insert it into
          * provided G4LogicalVolume
          *
          * @param logVolume In most cases, this is the world volume (in most cases)
          */
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wunused-parameter"
        virtual void BuildGeometry(G4LogicalVolume* logVolume) { }
        #pragma GCC diagnostic pop

        virtual G4VPhysicalVolume* CreateWorld() { return nullptr; }

        virtual void ConstructSDandField() { }

        virtual G4VUserPrimaryGeneratorAction* CreatePrimaryGeneratorAction() { return nullptr; }

        virtual G4UserEventAction* CreateEventAction() { return nullptr; }

        virtual G4UserRunAction* CreateRunAction() { return nullptr; }

        virtual G4UserStackingAction* CreateStackingAction() { return nullptr; }

        virtual G4UserSteppingAction* CreateSteppingAction() { return nullptr; }

        virtual G4UserTrackingAction* CreateTrackingAction() { return nullptr; }

        virtual G4VUserPhysicsList* CreatePhysicsList() { return nullptr; }

    protected:
        friend class ComponentManager;

        virtual void OnLoad() { }
    };
}

#endif // COMPONENT_HH

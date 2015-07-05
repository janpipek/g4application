#ifndef COMPONENT_HH
#define COMPONENT_HH

// #include "G4RunManager.hh"

class G4VUserPrimaryGeneratorAction;
class G4UserEventAction;
class G4UserRunAction;
class G4UserStackingAction;
class G4UserSteppingAction;
class G4UserTrackingAction;
class G4VUserPhysicsList;
class G4VPhysicalVolume;
class G4LogicalVolume;

namespace g4
{
    class GeometryBuilder;

    /**
     * @brief A component for the G4Application architecture.
     *
     * Instances of this class are shared. Ideally, they have no state, otherwise
     * careful thread-safety is necessary.
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
        virtual void BuildGeometry(G4LogicalVolume* logVolume) { }

        virtual G4VPhysicalVolume* CreateWorld() { return nullptr; }

        virtual G4VUserPrimaryGeneratorAction* CreatePrimaryGeneratorAction() const { return nullptr; }

        virtual G4UserEventAction* CreateEventAction() const { return nullptr; }

        virtual G4UserRunAction* CreateRunAction() const { return nullptr; }

        virtual G4UserStackingAction* CreateStackingAction() const { return nullptr; }

        virtual G4UserSteppingAction* CreateSteppingAction() const { return nullptr; }

        virtual G4UserTrackingAction* CreateTrackingAction() const { return nullptr; }

        virtual G4VUserPhysicsList* CreatePhysicsList() const { return nullptr; }

    /* protected:
        void GeometryHasBeenModified() { G4RunManager::GetRunManager()->GeometryHasBeenModified(); }*/
    };
}

#endif // COMPONENT_HH


#ifndef COMPONENT_HH
#define COMPONENT_HH

class G4VUserPrimaryGeneratorAction;
class G4UserEventAction;
class G4UserRunAction;
class G4UserStackingAction;
class G4UserSteppingAction;
class G4UserTrackingAction;
class G4VUserPhysicsList;

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

        virtual GeometryBuilder* CreateGeometryBuilder() const { return nullptr; }

        virtual G4VUserPrimaryGeneratorAction* CreatePrimaryGeneratorAction() const { return nullptr; }

        virtual G4UserEventAction* CreateEventAction() const { return nullptr; }

        virtual G4UserRunAction* CreateRunAction() const { return nullptr; }

        virtual G4UserStackingAction* CreateStackingAction() const { return nullptr; }

        virtual G4UserSteppingAction* CreateSteppingAction() const { return nullptr; }

        virtual G4UserTrackingAction* CreateTrackingAction() const { return nullptr; }

        virtual G4VUserPhysicsList* CreatePhysicsList() const { return nullptr; }
    };
}

#endif // COMPONENT_HH


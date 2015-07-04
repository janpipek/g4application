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

    class Component
    {
    public:
        virtual ~Component() { }

        virtual GeometryBuilder* CreateGeometryBuilder() { return nullptr; }

        virtual G4VUserPrimaryGeneratorAction* CreatePrimaryGeneratorAction() { return nullptr; }

        virtual G4UserEventAction* CreateEventAction() { return nullptr; }

        virtual G4UserRunAction* CreateRunAction() { return nullptr; }

        virtual G4UserStackingAction* CreateStackingAction() { return nullptr; }

        virtual G4UserSteppingAction* CreateSteppingAction() { return nullptr; }

        virtual G4UserTrackingAction* CreateTrackingAction() { return nullptr; }

        virtual G4VUserPhysicsList* CreatePhysicsList() { return nullptr; }
    };
}

#endif // COMPONENT_HH


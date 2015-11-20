#ifndef COMPONENT_HH
#define COMPONENT_HH

#include <vector>

#include <G4LogicalVolume.hh>

class G4VUserPrimaryGeneratorAction;
class G4UserEventAction;
class G4UserRunAction;
class G4UserStackingAction;
class G4UserSteppingAction;
class G4UserTrackingAction;
class G4VModularPhysicsList;
class G4VPhysicalVolume;
class G4VUserParallelWorld;

namespace g4
{
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
        virtual ~Component() = default;

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wunused-parameter"
        /**
          * @short Create part of the geometry and insert it into
          * provided G4LogicalVolume
          *
          * @param logVolume In most cases, this is the world volume.
          */
        virtual void BuildGeometry(G4LogicalVolume* logVolume) { }
        #pragma GCC diagnostic pop

        /**
          * @short Build the world geometry.
          *
          * Note: Only one of the components can create the world volume;
          *   otherwise, an exception is thrown.
          *
          * Note2: There is a built-in component called "DefaultWorld",
          *   that creates the default world (with a few defaults and
          *   configuration values.)
          */
        virtual G4VPhysicalVolume* CreateWorld() { return nullptr; }

        virtual std::vector<G4VUserParallelWorld*> CreateParallelWorlds() { return {}; }

        virtual void ConstructSDandField() { }

        virtual G4VUserPrimaryGeneratorAction* CreatePrimaryGeneratorAction() { return nullptr; }

        virtual G4UserEventAction* CreateEventAction() { return nullptr; }

        virtual G4UserRunAction* CreateRunAction() { return nullptr; }

        virtual G4UserStackingAction* CreateStackingAction() { return nullptr; }

        virtual G4UserSteppingAction* CreateSteppingAction() { return nullptr; }

        virtual G4UserTrackingAction* CreateTrackingAction() { return nullptr; }

        virtual G4VModularPhysicsList* CreatePhysicsList() { return nullptr; }

    protected:
        friend class ComponentManager;

        /**
         * @short Method called by ComponentManager when adding the component.
         *
         * This enables to separate calling constructor and initialization.
         */
        virtual void OnLoad() { }

        /**
         * @short Method called by ComponentManager when removal is requested.
         *
         * By default, this is not possible (G4Exception). Override only if you
         * know what you are doing.
         */
        virtual void Unload()
        {
            G4Exception("Component::Unload()", "Unloading forbidden", FatalException, "It is not possible to unload this component.");
        }
    };
}

#endif // COMPONENT_HH

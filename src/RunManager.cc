#include "RunManager.hh"

#include <signal.h>
#include <unistd.h>
#include <algorithm>

#include <G4VUserParallelWorld.hh>
#include <G4VModularPhysicsList.hh>
#include <G4VUserParallelWorld.hh>
#include <G4ParallelWorldPhysics.hh>
#include <G4VUserDetectorConstruction.hh>

#include "CompositeEventAction.hh"
#include "CompositeRunAction.hh"
#include "CompositeSteppingAction.hh"
#include "CompositeTrackingAction.hh"

#include "RunObserver.hh"
#include "RunInitializer.hh"

// Run a specific member function for all the listeners.
// TODO: Change from macro to member function pointer type
#define OBSERVERS_DO( name ) {\
    for (vector<RunObserver*>::const_iterator it = _observers.begin(); it != _observers.end(); it++) \
    {\
        (*it)->name();\
    }\
}

using namespace std;
using namespace g4;

namespace g4
{
    RunManager::RunManager(std::shared_ptr<RunInitializer> init)
        : _initializer(init)
    { }

    RunManager::~RunManager()
    {
        if (verboseLevel > 0) { G4cout << "RunManager: destructor called." << endl; }
        OBSERVERS_DO( OnDestructorCalled );
    }

    void RunManager::AddObserver(RunObserver* observer)
    {
        if (std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
        {
            _observers.push_back(observer);
        }
    }

    void RunManager::RemoveObserver(RunObserver* observer)
    {
        std::vector<RunObserver*>::iterator needle = std::find(_observers.begin(), _observers.end(), observer);
        if (needle != _observers.end())
        {
            _observers.erase(needle);
        }
    }

    void RunManager::Initialize()
    {
        // 1) Physics
        if (verboseLevel > 1) { G4cout << "RunManager: Physics initializing..." << G4endl; }
        OBSERVERS_DO( OnPhysicsInitializing );
        auto physList = _initializer->GetPhysicsList();
        this->SetUserInitialization(physList);
        OBSERVERS_DO( OnPhysicsInitialized );
        if (verboseLevel > 1) { G4cout << "RunManager: Physics initialized." << G4endl; }

        // 2a) Geometry
        if (verboseLevel > 1) { G4cout << "RunManager: Geometry initializing..." << G4endl; }
        OBSERVERS_DO( OnGeometryInitializing );
        auto detectorConstruction = _initializer->GetDetectorConstruction();
        this->SetUserInitialization(detectorConstruction);

        // 2b) Parallel worlds
        auto parallelWorlds = _initializer->GetParallelWorlds();
        if (parallelWorlds.size())
        {
            for (G4VUserParallelWorld* world : parallelWorlds)
            {
                detectorConstruction->RegisterParallelWorld(world);
                auto parallelPhysics = new G4ParallelWorldPhysics(world->GetName(), true);
                // This btw. registers the parallel world as mass layered geometry
                physList->RegisterPhysics(parallelPhysics);
            }
            // TODO: Circumvent "All materials have to be defined in the detectorconstruction" ???
            //   GeometryHasBeenModified();
        }

        OBSERVERS_DO( OnGeometryInitialized );
        if (verboseLevel > 1) { G4cout << "RunManager: Geometry initialized." << G4endl; }

        // 3) Actions
        if (verboseLevel > 1) { G4cout << "RunManager: Actions initializing..." << G4endl; }
        this->SetUserInitialization(_initializer->GetActionInitialization());
        if (verboseLevel > 1) { G4cout << "RunManager: Actions initialized." << G4endl; }

        if (verboseLevel > 0) { G4cout << "RunManager: Initializing Geant4 run manager..." << endl; }

        // Initialize Geant4's own run manager
        RunManagerBaseClass::Initialize();
        OBSERVERS_DO( OnRunInitialized );
        G4cout << "Run initialized." << endl;
    }
}

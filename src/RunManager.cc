#include "RunManager.hh"

#include <signal.h>
#include <unistd.h>
#include <algorithm>

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
    RunManager::RunManager(RunInitializer& init)
        : _initializer(init)
    { }

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
        OBSERVERS_DO( OnPhysicsInitializing );
        this->SetUserInitialization(_initializer.GetPhysicsList());
        OBSERVERS_DO( OnPhysicsInitialized );

        // 2) Geometry
        OBSERVERS_DO( OnGeometryInitializing );
        this->SetUserInitialization(_initializer.GetDetectorConstruction());
        OBSERVERS_DO( OnGeometryInitialized );

        // 3) Actions
        this->SetUserInitialization(_initializer.GetActionInitialization());


        G4cout << "Initializing Geant4 run manager." << endl;
        // Initialize Geant4's own run manager
        RunManagerBaseClass::Initialize();
        OBSERVERS_DO( OnRunInitialized );
        G4cout << "Run initialized." << endl;
    }
}

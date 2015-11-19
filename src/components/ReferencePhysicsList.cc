#include "components/ReferencePhysicsList.hh"

#include <G4VModularPhysicsList.hh>
#include <G4PhysListFactory.hh>
// #include <G4ios.hh>

#include "Configuration.hh"


using namespace g4::components;
using namespace g4;
using namespace std;

ReferencePhysicsList::ReferencePhysicsList()
{

}

G4VModularPhysicsList* ReferencePhysicsList::CreatePhysicsList()
{
    if (Configuration::HasKey("component.ReferencePhysicsList.listName"))
    {
        G4String listName = Configuration::Get<string>("component.ReferencePhysicsList.listName");
        G4PhysListFactory factory;
        if (factory.IsReferencePhysList(listName))
        {
            auto list = factory.GetReferencePhysList(listName);
            G4cout << "ReferencePhysicsList: loaded list " << listName << "." << G4endl;
            return list;
        }
        else
        {
            vector<G4String> availableLists = factory.AvailablePhysLists();
            G4cerr << "Unknown physics list: " << listName << G4endl;
            G4cerr << "  Candidates: " << listName << G4endl;
            for (auto it = availableLists.begin() ; it != availableLists.end(); it++)
            {
                G4cerr << "  * " << *it << G4endl;
            }
            G4ExceptionDescription message;
            message << "Unknown physics list: " << listName;
            G4Exception("ReferencePhysicsList", "UnknownReferencePhysicsList", FatalException, message);
        }
    }
    else
    {
        // TODO: if some verbosity...
        G4cout << "ReferencePhysicsList: no list specified." << G4endl;
        G4cout << "  Set component.ReferencePhysicsList.listName configuration value to change it." << G4endl;
    }
    return nullptr;
}

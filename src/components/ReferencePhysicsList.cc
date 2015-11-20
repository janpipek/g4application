#include "components/ReferencePhysicsList.hh"

#include <G4VModularPhysicsList.hh>
#include <G4PhysListFactory.hh>
#include <G4HadronicProcessStore.hh>

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

        // Make physics as quiet as possible
        factory.SetVerbose(0);
        G4HadronicProcessStore::Instance()->SetVerbose(0);

        
        auto list = factory.GetReferencePhysList(listName);
        if (!list)
        {
            G4cerr << "Unknown physics list: " << listName << G4endl;
            G4cerr << "  Available general: " << G4endl;
            for (auto name : factory.AvailablePhysLists())
            {
                G4cerr << "  * " << name << G4endl;
            }
            G4cerr << G4endl;
            G4cerr << "  Available EM:" << G4endl;
            for (auto name : factory.AvailablePhysListsEM())
            {
                G4cerr << "  * " << name << G4endl;
            }            
            G4ExceptionDescription message;
            message << "Unknown physics list: " << listName;
            G4Exception("ReferencePhysicsList", "UnknownReferencePhysicsList", FatalException, message);
        }
        
        G4cout << "ReferencePhysicsList: loaded list " << listName << "." << G4endl;
        list->SetVerboseLevel(0);
        return list;
    }
    else
    {
        // TODO: if some verbosity...
        G4cout << "ReferencePhysicsList: no list specified." << G4endl;
        G4cout << "  Set component.ReferencePhysicsList.listName configuration value to change it." << G4endl;
    }
    return nullptr;
}

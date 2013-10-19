#ifndef EXAMPLEEVENTACTION_HH
#define EXAMPLEEVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

class ExampleEventAction : public G4UserEventAction
{
public:
    void BeginOfEventAction(const G4Event *anEvent)
    {
        G4cout << "ExampleEventAction: Start of event " << anEvent->GetEventID() << std::endl;
    }

    void EndOfEventAction(const G4Event *anEvent)
    {
        G4cout << "ExampleEventAction: End of event " << anEvent->GetEventID() << std::endl;
    }
};

#endif // EXAMPLEEVENTACTION_HH

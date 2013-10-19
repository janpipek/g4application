#ifndef HTTPEVENTACTION_HH
#define HTTPEVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "ServerState.hh"

namespace http
{
    class HttpEventAction : public G4UserEventAction
    {
    public:
        HttpEventAction(ServerState* state)
            : _state(state)
        { }

        virtual void BeginOfEventAction(const G4Event* anEvent)
        {
            _state->SetEventNumber(anEvent->GetEventID());
        }

    private:
        ServerState* _state;
    };
}

#endif

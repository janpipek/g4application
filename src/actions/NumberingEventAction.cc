#include <G4Event.hh>

#include "actions/NumberingEventAction.hh"

using namespace std;

namespace g4
{
    NumberingEventAction::NumberingEventAction()
    {
        Configuration::SetDefaultValue(LOGGING_FREQUENCY_KEY, 1000);
        _loggingFrequency = Configuration::Get<int>(LOGGING_FREQUENCY_KEY);
    }

    void NumberingEventAction::ConfigurationChanged(const std::string &key)
    {
        if (key == LOGGING_FREQUENCY_KEY)
        {
            _loggingFrequency = Configuration::Get<int>(LOGGING_FREQUENCY_KEY);
        }
    }

    void NumberingEventAction::EndOfEventAction(const G4Event* anEvent)
    {
        if (_loggingFrequency > 0)
        {
            int eventId = anEvent->GetEventID();
            if ( eventId % _loggingFrequency == 0) // Log each n-th event
            {
                G4cout << "Event #" << anEvent->GetEventID();
                if ( eventId != 0)
                {
                    G4double timeElapsed = float( clock () - _lastTime ) /  CLOCKS_PER_SEC;
                    // G4double timeElapsed = _timer.elapsed().wall / 1.e9;
                    G4cout << " ( " << (_loggingFrequency / timeElapsed ) << " events/s )";
                }
                G4cout << G4endl;
                _lastTime = clock();
            }
        }
    }
}

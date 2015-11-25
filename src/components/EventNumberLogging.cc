#include "components/EventNumberLogging.hh"

#include <ctime>
#include <G4UserEventAction.hh>
#include <G4Event.hh>

#include "Configuration.hh"

#define LOGGING_FREQUENCY_KEY "component.EventNumberLogging.frequency"

using namespace std;
using namespace g4;
using namespace g4::components;

class NumberingEventAction : public G4UserEventAction, public ConfigurationObserver
{
public:
    virtual void EndOfEventAction(const G4Event* anEvent)
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

    NumberingEventAction()
    {
        _loggingFrequency = Configuration::Get<int>(LOGGING_FREQUENCY_KEY);
    }

    virtual void ConfigurationChanged(const G4String& key)
    {
        if (key == LOGGING_FREQUENCY_KEY)
        {
            _loggingFrequency = Configuration::Get<int>(LOGGING_FREQUENCY_KEY);
        }
    }

private:
    int _loggingFrequency;

    // Timer used for measuring time between events
    // boost::timer::cpu_timer _timer;

    std::clock_t _lastTime;
};

G4UserEventAction* EventNumberLogging::CreateEventAction() 
{
    return new NumberingEventAction();
}

void EventNumberLogging::OnLoad()
{
    Configuration::SetDefaultValue(LOGGING_FREQUENCY_KEY, 1000);
}

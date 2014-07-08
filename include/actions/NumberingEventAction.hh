#ifndef NUMBERINGEVENTACTION_HH
#define NUMBERINGEVENTACTION_HH

#include <G4UserEventAction.hh>
#include <ctime>

#include "Configuration.hh"

#define LOGGING_FREQUENCY_KEY "app.logEvents"

namespace g4
{
    /**
      * @short Event action that after each event (or N events), it writes how many events
      * have been calculated (and approximate speed).
      *
      * Configuration value LOGGING_FREQUENCY_KEY (0 for no logging).
      */
    class NumberingEventAction : public G4UserEventAction, public ConfigurationObserver
    {
    public:
        virtual void EndOfEventAction(const G4Event* anEvent);

        NumberingEventAction();

        virtual ~NumberingEventAction() { }

        virtual void ConfigurationChanged(const std::string& key);

    private:
        int _loggingFrequency;

        // Timer used for measuring time between events
        // boost::timer::cpu_timer _timer;

        std::clock_t _lastTime;
    };
}

#endif // NUMBERINGEVENTACTION_HH

#ifndef NUMBERINGEVENTACTION_HH
#define NUMBERINGEVENTACTION_HH

#include <G4UserEventAction.hh>
#include <ctime>

#include "Configuration.hh"

namespace g4
{
    /**
      * Event action that is automatically included in the application.
      *
      * It does following things:
      *  - after each event (or N events), it writes how many events have been calculated
      *    ( macro command /g4/logEvents N )
      */
    class NumberingEventAction : public G4UserEventAction, public ConfigurationListener
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

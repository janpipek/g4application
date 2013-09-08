#ifndef NUMBERINGEVENTACTION_HH
#define NUMBERINGEVENTACTION_HH

#include <G4UserEventAction.hh>
#include <ctime>

#include "ApplicationConfiguration.hh"

namespace g4
{
    /**
      * Event action that is automatically included in the application.
      *
      * It does following things:
      *  - after each event (or N events), it writes how many events have been calculated
      *    ( macro command /g4/logEvents N )
      */
    class NumberingEventAction : public G4UserEventAction, public ApplicationConfigurationListener
    {
    public:
        virtual void EndOfEventAction(const G4Event* anEvent);

        NumberingEventAction();

        virtual ~NumberingEventAction() { }

        virtual void ApplicationConfigurationChanged(const std::string& key);

    private:
        int _loggingFrequency;

        // Timer used for measuring time between events
        // boost::timer::cpu_timer _timer;

        std::clock_t _lastTime;
    };
}

#endif // NUMBERINGEVENTACTION_HH

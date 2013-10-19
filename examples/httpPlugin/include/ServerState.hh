#ifndef SERVERSTATE_HH
#define SERVERSTATE_HH

#include <pthread.h>
#include <map>

#include "Configuration.hh"

namespace http
{
    class ServerState : public g4::ConfigurationListener
    {
    public:
        ServerState();

        int GetEventNumber() const;

        void SetEventNumber(int);

        std::map<std::string, g4::ConfigurationValue> GetConfiguration() const;

    private:
        int _eventNumber;

        mutable pthread_mutex_t _stateMutex;

        std::map<std::string, g4::ConfigurationValue> _configuration;

        // ConfigurationListener interface
    protected:
        void ConfigurationChanged(const string &key);
    };
}

#endif // SERVERSTATE_HH

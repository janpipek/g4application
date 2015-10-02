#ifndef SERVERSTATE_HH
#define SERVERSTATE_HH

#include <pthread.h>    // TODO: Change to thread API?
#include <map>
#include <string>

#include "Configuration.hh"

namespace http
{
    /**
     * @short Application state to be displayed in the HTTP server.
     *
     * Copies of configuration and event number are kept
     * so that no race conditions occur when accessing them.
     */
    class ServerState : public g4::ConfigurationObserver
    {
    public:
        ServerState();

        int GetEventNumber() const;

        void SetEventNumber(int);

        /**
         * @short A copy of application configuration.
         *
         * It is automatically updated via the ConfigurationListener interface.
         */
        std::map<std::string, g4::ConfigurationValue> GetConfiguration() const;

    private:
        int _eventNumber;

        mutable pthread_mutex_t _stateMutex;

        std::map<std::string, g4::ConfigurationValue> _configuration;

    protected:
        // Automatically store all configuration changes.
        void ConfigurationChanged(const std::string &key);
    };
}

#endif // SERVERSTATE_HH

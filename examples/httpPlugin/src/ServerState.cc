#include "ServerState.hh"

using namespace g4;
using namespace std;

namespace http
{
    ServerState::ServerState()
        : _stateMutex(PTHREAD_MUTEX_INITIALIZER)
    {
        _configuration = Configuration::GetItems();
    }

    int ServerState::GetEventNumber() const
    {
        pthread_mutex_lock(&_stateMutex);
        int eventNumber = _eventNumber;
        pthread_mutex_unlock(&_stateMutex);
        return eventNumber;
    }

    void ServerState::SetEventNumber(int number)
    {
        pthread_mutex_lock(&_stateMutex);
        _eventNumber = number;
        pthread_mutex_unlock(&_stateMutex);
    }

    std::map<string, g4::ConfigurationValue> ServerState::GetConfiguration() const
    {
        pthread_mutex_lock(&_stateMutex);
        std::map<string, g4::ConfigurationValue> result = _configuration;
        pthread_mutex_unlock(&_stateMutex);
        return result;
    }

    void ServerState::ConfigurationChanged(const string &key)
    {
        pthread_mutex_lock(&_stateMutex);
        _configuration[key] = Configuration::Get(key);
        pthread_mutex_unlock(&_stateMutex);
    }
}

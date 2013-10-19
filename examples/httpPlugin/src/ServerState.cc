#include "ServerState.hh"

namespace http
{
    ServerState::ServerState()
        : _stateMutex(PTHREAD_MUTEX_INITIALIZER)
    {

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
}

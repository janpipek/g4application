#ifndef SERVERSTATE_HH
#define SERVERSTATE_HH

#include <pthread.h>

namespace http
{
    class ServerState
    {
    public:
        ServerState();

        int GetEventNumber() const;

        void SetEventNumber(int);

    private:
        int _eventNumber;

        mutable pthread_mutex_t _stateMutex;
    };
}

#endif // SERVERSTATE_HH

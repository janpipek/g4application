#ifndef HTTPSERVER_HH
#define HTTPSERVER_HH

#include <pthread.h>

#include "ServerState.hh"

namespace WPP
{
    class Server;
}

namespace http
{
    void startServer(void* arg);

    class HttpServer
    {
    public:
        ServerState* GetState() { return _state; }

        static HttpServer* GetInstance();

        void Start();

        void Stop();

        friend void startServer(void* arg);

    private:
        HttpServer();

        static HttpServer* _instance;

        WPP::Server* _wppServer;

        int _portNumber;

        pthread_t _wppServerThread;

        ServerState* _state;
    };
}

#endif

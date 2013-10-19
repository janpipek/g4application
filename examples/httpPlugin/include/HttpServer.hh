#ifndef HTTPSERVER_HH
#define HTTPSERVER_HH

#include <pthread.h>

#include "ServerState.hh"
#include "Configuration.hh"

namespace WPP
{
    class Server;
}

namespace http
{
    void startServer(void* arg);

    class HttpServer : public g4::ConfigurationListener
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

    protected:
        void ConfigurationChanged(const string &key);
    };
}

#endif

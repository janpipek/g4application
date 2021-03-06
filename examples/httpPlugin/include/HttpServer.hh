#ifndef HTTPSERVER_HH
#define HTTPSERVER_HH

#include <pthread.h>
#include <string>

#include "ServerState.hh"
#include "Configuration.hh"

namespace WPP
{
    // Forward declaration of the class from web++
    class Server;
}

namespace http
{
    // Function that starts the server and is called from a new thread
    void startServer(void* arg);

    class HttpServer : public g4::ConfigurationObserver
    {
    public:
        ServerState* GetState() { return _state; }

        static HttpServer* GetInstance();

        void Start();

        void Stop();

        bool IsRunning();

        friend void startServer(void* arg);

    private:
        HttpServer();

        static HttpServer* _instance;

        WPP::Server* _wppServer;

        int _portNumber;

        pthread_t _wppServerThread;

        ServerState* _state;

    protected:
        void ConfigurationChanged(const std::string &key);
    };
}

#endif

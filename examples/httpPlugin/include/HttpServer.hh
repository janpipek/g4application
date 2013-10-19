#ifndef HTTPSERVER_HH
#define HTTPSERVER_HH

#include <pthread.h>

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
        HttpServer();       

        ~HttpServer();

        void Start();

        void Stop();

        friend void startServer(void* arg);

    private:
        WPP::Server* _wppServer;

        int _portNumber;

        pthread_t _wppServerThread;
    };
}

#endif

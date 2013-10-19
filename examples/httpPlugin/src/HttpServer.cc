#include "HttpServer.hh"

#include <sstream>
#include <globals.hh>

#include "web++.hpp"

using namespace WPP;
using namespace std;

namespace http 
{
    HttpServer::HttpServer() 
        : _wppServer(0), _portNumber(7070)
    {

    }

    HttpServer::~HttpServer()
    {
        Stop();
    }

    void startServer(void* arg)
    {
        G4cout << "Web thread started" << G4endl;
        HttpServer* caller = (HttpServer*)arg;
        caller->_wppServer->start(caller->_portNumber);
    }

    void webEventNumber(Request* req, Response* res)
    {
        stringstream ss;
        res->body << 4;
    }

    void HttpServer::Start()
    {
        if (_wppServer)
        {
            throw "HTTP server already started.";
        }
        _wppServer = new Server();
        _wppServer->get("/eventNumber", &webEventNumber);

        // Start in a new thread
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        pthread_create(&_wppServerThread, &attr, (void* (*)(void*))startServer, (void*)this);
    }

    void HttpServer::Stop()
    {
        if (_wppServer)
        {
            pthread_cancel(_wppServerThread);
            pthread_join(_wppServerThread, NULL);
            delete _wppServer;
            _wppServer = 0;
        }   
    }
}

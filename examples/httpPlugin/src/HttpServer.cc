#include "HttpServer.hh"

#include <sstream>
#include <globals.hh>

#include "web++.hpp"

using namespace WPP;
using namespace std;
using namespace g4;

namespace http 
{
    HttpServer* HttpServer::_instance = NULL;

    HttpServer::HttpServer()
        : _wppServer(0), _portNumber(7070), _state(new ServerState)
    {

    }

    void startServer(void* arg)
    {
        G4cout << "Web thread started" << G4endl;
        HttpServer* caller = (HttpServer*)arg;
        caller->_wppServer->start(caller->_portNumber);
    }

    HttpServer*HttpServer::GetInstance()
    {
        if (!_instance)
        {
            _instance = new HttpServer;
        }
        return _instance;
    }

    ServerState* state = HttpServer::GetInstance()->GetState();

    namespace www
    {

        void eventNumber(Request* req, Response* res)
        {
            res->body << state->GetEventNumber();
        }

        void index(Request* req, Response* res)
        {
            res->body << "<a href=eventNumber>Event number</a><br/>";
            res->body << "<a href=configuration>Actual configuration</a><br/>";
        }

        void configuration(Request* req, Response* res)
        {
            res->type = "application/json";
            res->body << "{\n";
            std::map<string, g4::ConfigurationValue> conf = state->GetConfiguration();
            int count = conf.size();
            for (std::map<string, g4::ConfigurationValue>::iterator it = conf.begin(); it != conf.end(); it++)
            {
                res->body << "    \"";
                res->body << it->first;
                res->body << "\" : ";
                ConfigurationValue value = it->second;
                if (value.which() == 2) // is string;
                {
                    res->body << "\"" << value << "\"";
                }
                else
                {
                    res->body << value;
                }
                if (--count)
                {
                    res->body << ",";
                }
                res->body << "\n";
            }
            res->body << "}\n";
        }
    }

    void HttpServer::Start()
    {
        if (_wppServer)
        {
            throw "HTTP server already started.";
        }
        _wppServer = new Server();
        _wppServer->get("/", &www::index);
        _wppServer->get("/configuration", &www::configuration);
        _wppServer->get("/eventNumber", &www::eventNumber);

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

    void HttpServer::ConfigurationChanged(const string &key)
    {
        if (key == "http.port")
        {
            if (_wppServer)
            {
                throw "Cannot specify port for running server.";
            }
            _portNumber = Configuration::GetValue<int>("http.port");
        }
    }
}

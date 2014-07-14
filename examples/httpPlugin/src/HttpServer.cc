#include "HttpServer.hh"

#include <sstream>
#include <globals.hh>
#include <G4ScoringManager.hh>

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
        G4cout << "Web thread started." << G4endl;
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

    // Namespace with all request-handling methods.
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
            res->body << "<a href=scoring>List of scoring meshes</a><br/>";
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

        void scoring(Request* req, Response* res)
        {
            G4ScoringManager* scoring = G4ScoringManager::GetScoringManager();
            size_t meshCount = scoring->GetNumberOfMesh();
            res->body << "[\n";
            for (size_t i = 0; i < meshCount; i++) {
                G4VScoringMesh* mesh = scoring->GetMesh(i);
                res->body << "  {\n";
                res->body << "    \"shape\" : \"";
                switch(mesh->GetShape())
                {
                case boxMesh:
                    res->body << "box";
                    break;
                case cylinderMesh:
                    res->body << "cylinder";
                    break;
                case sphereMesh:
                    res->body << "sphere";
                    break;
                }
                res->body << "\",\n";
                G4ThreeVector size = mesh->GetSize();
                res->body << "    \"size\" : ["
                          << size.x() << ", "
                          << size.y() << ", "
                          << size.z() << "]\n";
                res->body << "  }\n";
            }
            res->body << "]\n";
        }
    }

    void HttpServer::Start()
    {
        if (_wppServer)
        {
            throw "HTTP server already started.";
        }
        _wppServer = new Server();

        // Define all possible URLs
        _wppServer->get("/", &www::index);
        _wppServer->get("/configuration", &www::configuration);
        _wppServer->get("/eventNumber", &www::eventNumber);
        _wppServer->get("/scoring", &www::scoring);

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
            _portNumber = Configuration::Get<int>("http.port");
        }
    }
}

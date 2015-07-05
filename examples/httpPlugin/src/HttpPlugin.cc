#include "HttpPlugin.hh"

#include <G4AutoLock.hh>

using namespace g4;

namespace http
{
    /* void HttpPlugin::OnRunInitialized()
    {
        _server->Start();
        _action = new HttpEventAction(_server->GetState());
        G4Application::Instance()->GetRunManager()->AddAction(_action);
    }*/

    HttpPlugin::HttpPlugin()
        : _action(0)
    {
        _mutex = G4MUTEX_INITIALIZER;
        G4MUTEXLOCK(&_mutex);
        _server = HttpServer::GetInstance();
        G4MUTEXUNLOCK(&_mutex);
    }

    HttpPlugin::~HttpPlugin()
    {
        G4MUTEXLOCK(&_mutex);
        if (_server)
        {
            if (_server->IsRunning())
            {
                _server->Stop();
            }
            delete _server;
        }
        _server = nullptr;
        G4MUTEXUNLOCK(&_mutex);
    }

    G4UserEventAction *HttpPlugin::CreateEventAction()
    {
        G4MUTEXLOCK(&_mutex);
        // G4AutoLock(&_mutex);
        if (!_server->IsRunning())
        {
            _server->Start();
        }
        G4MUTEXUNLOCK(&_mutex);
        return new HttpEventAction(_server->GetState());
    }
}

MAKE_G4_PLUGIN( http::HttpPlugin)

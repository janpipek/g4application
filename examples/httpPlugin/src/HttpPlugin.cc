#include "HttpPlugin.hh"

#include "G4Application.hh"

using namespace g4;

namespace http
{
    void HttpPlugin::OnLoad() 
    {

    }

    void HttpPlugin::OnRunInitialized()
    {
        _server->Start();
        _action = new HttpEventAction(_server->GetState());
        G4Application::GetInstance()->GetRunManager()->AddAction(_action);
    }

    HttpPlugin::HttpPlugin()
        : _action(0)
    {
        _server = HttpServer::GetInstance();
    }

    HttpPlugin::~HttpPlugin()
    {
        _server->Stop();
    }
}

MAKE_G4_PLUGIN( http::HttpPlugin)

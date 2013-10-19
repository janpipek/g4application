#include "HttpPlugin.hh"

namespace http
{
    void HttpPlugin::OnLoad() 
    {
        G4cout << "OnLoad" << G4endl;
        _server->Start();
    }

    HttpPlugin::HttpPlugin()
        : _server(new HttpServer)
    {

    }

    HttpPlugin::~HttpPlugin()
    {
        delete _server;
    }
}

MAKE_G4_PLUGIN( http::HttpPlugin)

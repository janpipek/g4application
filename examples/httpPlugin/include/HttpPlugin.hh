#ifndef HTTPPLUGIN_HH
#define HTTPPLUGIN_HH

#include <string>

#include "Plugin.hh"

#include "HttpServer.hh"
#include "ServerState.hh"
#include "HttpEventAction.hh"

namespace http 
{
    class HttpPlugin : public g4::Plugin 
    {
    public:
        virtual const std::string GetName() const { return "HTTP Plugin";}

        HttpPlugin();

        ~HttpPlugin();

        void OnLoad();

        void OnRunInitialized();

    private:
        HttpServer* _server;

        HttpEventAction* _action;
    };
}

#endif // HTTPPLUGIN_HH

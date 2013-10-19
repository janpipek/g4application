#ifndef HTTPPLUGIN_HH
#define HTTPPLUGIN_HH

#include <string>

#include "Plugin.hh"
#include "HttpServer.hh"

namespace http 
{
    class HttpPlugin : public g4::Plugin 
    {
    public:
        virtual const std::string GetName() const { return "HTTP Plugin";}

        HttpPlugin();

        ~HttpPlugin();

        void OnLoad();

    private:
        HttpServer* _server;
    };
}

#endif // HTTPPLUGIN_HH

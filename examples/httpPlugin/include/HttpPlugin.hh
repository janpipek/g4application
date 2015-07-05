#ifndef HTTPPLUGIN_HH
#define HTTPPLUGIN_HH

#include <string>
#include <G4Threading.hh>

#include "SingleComponentPlugin.hh"

#include "HttpServer.hh"
#include "ServerState.hh"
#include "HttpEventAction.hh"

namespace http 
{
    class HttpPlugin : public g4::SingleComponentPlugin
    {
    public:
        HttpPlugin();

        ~HttpPlugin();

        virtual G4UserEventAction* CreateEventAction() override;

        // void OnRunInitialized();

    private:
        HttpServer* _server;

        HttpEventAction* _action;

        G4Mutex _mutex;
    };
}

#endif // HTTPPLUGIN_HH

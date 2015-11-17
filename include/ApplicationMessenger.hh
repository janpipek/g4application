#ifndef APPLICATIONMESSENGER_HH
#define APPLICATIONMESSENGER_HH

#include <G4UImessenger.hh>
#include <sstream>

class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithoutParameter;

namespace g4
{
    class Application;

    /**
     * @brief Main UI messenger for the application.
     *
     * It provides following commands:
     *  - /app/generateRandomSeed
     *  - /app/pause
     *  - /app/addComponent
     */
    class ApplicationMessenger : public G4UImessenger
    {
        // TODO: Move a few commands into ConfigurationMessenger
    public:
        ApplicationMessenger(Application* application);
        
        virtual ~ApplicationMessenger();
        
        // override         
        void SetNewValue(G4UIcommand* command, G4String newValue) override;
        
    private:
        G4UIdirectory* _uiDirectory;

        G4UIcmdWithAnInteger* _waitCommand;

        G4UIcmdWithoutParameter* _generateRandomSeedCommand;

        G4UIcmdWithAString* _addComponentCommand;

        G4UIcmdWithoutParameter* _pauseCommand;

        Application* _application;
    };

}

#endif // APPLICATIONMESSENGER_HH

#ifndef COMPONENTMESSENGER_HH
#define COMPONENTMESSENGER_HH

#include <G4UImessenger.hh>

class G4UIcmdWithoutParameter;

namespace g4
{
    class ComponentManager;

    class ComponentMessenger : public G4UImessenger
    {
    public:
        ComponentMessenger(ComponentManager* manager);

        virtual ~ComponentMessenger();

        void SetNewValue(G4UIcommand* command, G4String newValue) override;

    private:
        ComponentManager* _manager;

        G4UIdirectory* _directory;

        G4UIcommand* _listCommand;

        G4UIcommand* _unloadCommand;

        G4UIcommand* _translateCommand;

        G4UIcommand* _rotateCommand;
    };
}

#endif

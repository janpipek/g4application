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

        G4UIcmdWithoutParameter* _listCommand;
    };
}

#endif

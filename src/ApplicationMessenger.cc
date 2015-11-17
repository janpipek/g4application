#include "ApplicationMessenger.hh"

#include <iostream>
#include <limits>
#include <unistd.h>

#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithoutParameter.hh>

#include "Application.hh"
#include "Configuration.hh"

using namespace std;

namespace g4
{
    ApplicationMessenger::ApplicationMessenger(Application *application)
        : _application(application)
    {
        // Initialize directory for UI commands
        _uiDirectory = new G4UIdirectory("/app/");
        _uiDirectory->SetGuidance("G4Application commands");

        _waitCommand = new G4UIcmdWithAnInteger("/app/wait", this);
        _waitCommand->SetGuidance("Wait");
        _waitCommand->SetGuidance("0 - wait for a key press");
        _waitCommand->SetGuidance(">0 - wait for a specified interval in seconds");

        _generateRandomSeedCommand = new G4UIcmdWithoutParameter("/app/generateRandomSeed", this);
        _generateRandomSeedCommand->SetGuidance("Generate a really random random seed.");

        _pauseCommand = new G4UIcmdWithoutParameter("/app/pause", this);
        _pauseCommand->SetGuidance("Pause and wait for user input.");

        _addComponentCommand = new G4UIcmdWithAString("/app/addComponent", this);
        _addComponentCommand->SetGuidance("Add one of the integrated components.");
    }
    
    void ApplicationMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
    {
        if (command == _waitCommand)
        {
            int seconds = _waitCommand->GetNewIntValue(newValue);
            if (seconds)
            {
                std::cout << "Sleeping for " << seconds << " seconds." << endl;
                sleep(seconds);
            }
            else
            {
                std::cout << "Press ENTER to continue...";
                std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
            }
        }
        else if (command == _generateRandomSeedCommand)
        {
            _application->GenerateRandomSeed();
        }
        else if (command == _pauseCommand)
        {
            _application->PauseExecution();
        }
        else if (command == _addComponentCommand)
        {
            _application->AddBuiltinComponent(newValue);
        }
    }
    
    ApplicationMessenger::~ApplicationMessenger()
    {
        delete _waitCommand;
        delete _generateRandomSeedCommand;

        delete _pauseCommand;
        delete _addComponentCommand;

        delete _uiDirectory;
    }
}

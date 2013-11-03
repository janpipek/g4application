#include "ApplicationMessenger.hh"

#include <iostream>
#include <limits>
#include <unistd.h>
#include <boost/xpressive/xpressive.hpp>

#include "G4Application.hh"
#include "Configuration.hh"

// Actions to add
#include "actions/NumberingEventAction.hh"

using namespace boost::xpressive;
using namespace std;

namespace g4
{
    // Forward declaration of functions for value retrieval from parameter string
    template <typename ValueType> const ValueType parseValue(const std::string& valueString);
    template <> const std::string parseValue<std::string>(const std::string& valueString);

    // String defining the
    // template <typename ValueType> const char* getParameterType<valueType>();

    // Implementation of UIcmdConfiguration
    template<typename ValueType> UIcmdConfiguration<ValueType>::UIcmdConfiguration(const char *theCommandPath, G4UImessenger *theMessenger)
        : G4UIcommand(theCommandPath, theMessenger)
    {
        SetParameter(new G4UIparameter("key", 's', false));
        // SetParameter(new G4UIParameter("value", 's', false));
    }

    template<typename ValueType> const std::string UIcmdConfiguration<ValueType>::GetKey(const std::string& paramString) const
    {
        sregex keyRegex = sregex::compile("^\\s*([a-zA-Z0-9\\._]+)\\s+");
        smatch what;
        if (regex_search(paramString, what, keyRegex))
        {
            return what[1];
        }
        else
        {
            throw "Cannot parse configuration key.";
        }
    }

    template<typename ValueType> const ValueType UIcmdConfiguration<ValueType>::GetValue(const std::string& paramString) const
    {
        sregex keyAndValueRegex = sregex::compile("^\\s*([a-zA-Z0-9\\._]+)\\s+(.*)");
        smatch what;
        if (regex_search(paramString, what, keyAndValueRegex))
        {
        return parseValue<ValueType>(what[2]);
        }
        else
        {
            throw "Cannot parse configuration value.";
        }
    }

    // Implementation of value-reading methods
    template <typename ValueType> const ValueType parseValue(const std::string& valueString)
    {
        ValueType result;
        std::stringstream(valueString) >> result;
        return result;
    }

    template <> inline const std::string parseValue<std::string>(const std::string& valueString)
    {
        return valueString;
    }

    ApplicationMessenger::ApplicationMessenger()
    {
        _waitCommand = new G4UIcmdWithAnInteger("/app/wait", this);
        _waitCommand->SetGuidance("Wait");
        _waitCommand->SetGuidance("0 - wait for a key press");
        _waitCommand->SetGuidance(">0 - wait for a specified interval in seconds");
        
        _interactiveCommand = new G4UIcmdWithoutParameter("/app/interactive", this);
        _interactiveCommand->SetGuidance("Enter interactive mode");

        _generateRandomSeedCommand = new G4UIcmdWithoutParameter("/app/generateRandomSeed", this);
        _generateRandomSeedCommand->SetGuidance("Generate a really random random seed.");

        _setIntCommand = new UIcmdConfiguration<int>("/app/setInt", this);
        _setIntCommand->SetGuidance("Set an integer configuration value.");

        _setDoubleCommand = new UIcmdConfiguration<double>("/app/setDouble", this);
        _setDoubleCommand->SetGuidance("Set a double configuration value.");

        _setStringCommand = new UIcmdConfiguration<string>("/app/setString", this);
        _setStringCommand->SetGuidance("Set a string configuration value.");

        _printConfigurationCommand = new G4UIcmdWithoutParameter("/app/printConfiguration", this);
        _printConfigurationCommand->SetGuidance("Print application configuration.");

        _pauseCommand = new G4UIcmdWithoutParameter("/app/pause", this);
        _pauseCommand->SetGuidance("Pause and wait for user input.");

        _addActionCommand = new G4UIcmdWithAString("/app/addAction", this);
        _addActionCommand->SetGuidance("Add one of the integrated actions.");
    }

    template <typename ValueType> void ApplicationMessenger::applyConfigurationCommand(const UIcmdConfiguration<ValueType>* command, const string& newValue)
    {
        try
        {
            string key = command->GetKey(newValue);
            ValueType value = command->GetValue(newValue);
            Configuration::SetValue(key, value);
        }
        catch(const char* exception)
        {
            G4Exception("ApplicationMessenger", "app.configuration", FatalErrorInArgument, exception);
        }
    }
    
    void ApplicationMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
    {
        G4Application* application = G4Application::GetInstance();
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
        else if (command == _interactiveCommand)
        {
            application->EnterInteractiveMode();
        }
        else if (command == _generateRandomSeedCommand)
        {
            application->GenerateRandomSeed();
        }
        else if (command == _setDoubleCommand)
        {
            applyConfigurationCommand(_setDoubleCommand, newValue);
        }
        else if (command == _setIntCommand)
        {
            applyConfigurationCommand(_setIntCommand, newValue);
        }
        else if (command == _setStringCommand)
        {
            applyConfigurationCommand(_setStringCommand, newValue);
        }
        else if (command == _printConfigurationCommand)
        {
            Configuration::Print(G4cout);
        }
        else if (command = _pauseCommand)
        {
            application->PauseExecution();
        }
        else if (command = _addActionCommand)
        {
            if (newValue == "NumberingEventAction")
            {
                application->GetRunManager()->AddAction(new NumberingEventAction);
            }
            else
            {
                throw "Unknown action to add: " + newValue;
            }
        }
    }
    
    ApplicationMessenger::~ApplicationMessenger()
    {
        delete _waitCommand;
        delete _interactiveCommand;
        delete _generateRandomSeedCommand;

        delete _setIntCommand;
        delete _setDoubleCommand;
        delete _setStringCommand;
        delete _printConfigurationCommand;
        delete _pauseCommand;
        delete _addActionCommand;
    }
}

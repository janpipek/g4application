#include "ConfigurationMessenger.hh"

#include <boost/xpressive/xpressive.hpp>

#include <G4UIcmdWithoutParameter.hh>

#include "Configuration.hh"

using namespace g4;
using namespace std;
using namespace boost::xpressive;

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

ConfigurationMessenger::ConfigurationMessenger()
{
    _uiDirectory = new G4UIdirectory("/conf/");

    _setIntCommand = new UIcmdConfiguration<int>("/conf/setInt", this);
    _setIntCommand->SetGuidance("Set an integer configuration value.");

    _setDoubleCommand = new UIcmdConfiguration<double>("/conf/setDouble", this);
    _setDoubleCommand->SetGuidance("Set a double configuration value.");

    _setStringCommand = new UIcmdConfiguration<string>("/conf/setString", this);
    _setStringCommand->SetGuidance("Set a string configuration value.");

    _printConfigurationCommand = new G4UIcmdWithoutParameter("/conf/print", this);
    _printConfigurationCommand->SetGuidance("Print application configuration.");
}

ConfigurationMessenger::~ConfigurationMessenger()
{
    delete _setIntCommand;
    delete _setDoubleCommand;
    delete _setStringCommand;
    delete _printConfigurationCommand;
}

template <typename ValueType> void applyConfigurationCommand(const UIcmdConfiguration<ValueType>* command, const string& newValue)
{
    try
    {
        string key = command->GetKey(newValue);
        ValueType value = command->GetValue(newValue);
        Configuration::Set(key, value);
    }
    catch(const char* exception)
    {
        G4Exception("ApplicationMessenger", "app.configuration", FatalErrorInArgument, exception);
    }
}

void ConfigurationMessenger::SetNewValue(G4UIcommand *command, G4String newValue)
{
    if (command == _setDoubleCommand)
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
}

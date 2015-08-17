#ifndef CONFIGURATIONMESSENGER_HH
#define CONFIGURATIONMESSENGER_HH

#include <string>

#include <G4UImessenger.hh>
#include <G4UIcommand.hh>

class G4UIcmdWithoutParameter;

namespace g4
{
    /**
     * @brief UI command for configuration (string + value type).
     *
     * First argument is a string key.
     * Second is a value of a specified type.
     *
     * Used to update the Configuration object.
     */
    template <typename ValueType> class UIcmdConfiguration : public G4UIcommand
    {
    public:
        // Forward declarations (see end of file)
        UIcmdConfiguration(const char* theCommandPath, G4UImessenger *theMessenger);

        const std::string GetKey(const std::string& paramString) const;

        const ValueType GetValue(const std::string& paramString) const;
    };

    /**
     * @brief The ConfigurationMessenger class
     *
     * Commands:
     *  - /conf/setInt
     *  - /conf/setDouble
     *  - /conf/setString
     *  - /conf/print
     */
    class ConfigurationMessenger : public G4UImessenger
    {
    public:
        ConfigurationMessenger();

        ~ConfigurationMessenger();

        void SetNewValue(G4UIcommand* command, G4String newValue) override;

    private:
        G4UIdirectory* _uiDirectory;

        UIcmdConfiguration<std::string>* _setStringCommand;

        UIcmdConfiguration<int>* _setIntCommand;

        UIcmdConfiguration<double>* _setDoubleCommand;

        G4UIcmdWithoutParameter* _printConfigurationCommand;
    };
}

#endif // CONFIGURATIONMESSENGER_HH


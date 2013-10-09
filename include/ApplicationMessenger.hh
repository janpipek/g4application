#ifndef APPLICATIONMESSENGER_HH
#define APPLICATIONMESSENGER_HH

#include <G4UImessenger.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcommand.hh>
#include <sstream>

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
     * @brief Main UI messenger for the application.
     *
     * It provides following commands:
     *  - /app/generateRandomSeed
     *  - /app/interactive
     *  - /app/logEvents
     *  - /app/setInt
     *  - /app/setDouble
     *  - /app/setString
     *  - /app/printConfiguration
     *  - /app/pause
     */
	class ApplicationMessenger : public G4UImessenger
	{
	public:
		ApplicationMessenger();
		
		virtual ~ApplicationMessenger();
		
		// override			
		virtual void SetNewValue(G4UIcommand* command, G4String newValue);
		
	private:
        template <typename ValueType> void applyConfigurationCommand(const UIcmdConfiguration<ValueType>* command, const std::string& newValue);

		G4UIcmdWithAnInteger* _waitCommand;
		
		G4UIcmdWithoutParameter* _interactiveCommand;

        G4UIcmdWithAnInteger* _logEventsCommand;

        G4UIcmdWithoutParameter* _generateRandomSeedCommand;

        UIcmdConfiguration<std::string>* _setStringCommand;

        UIcmdConfiguration<int>* _setIntCommand;

        UIcmdConfiguration<double>* _setDoubleCommand;

        G4UIcmdWithoutParameter* _printConfigurationCommand;

        G4UIcmdWithoutParameter* _pauseCommand;
    };

}

#endif // APPLICATIONMESSENGER_HH

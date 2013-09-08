#ifndef APPLICATIONMESSENGER_HH
#define APPLICATIONMESSENGER_HH

#include <G4UImessenger.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcommand.hh>
#include <sstream>

#include "G4Application.hh"

namespace g4
{
	class G4Application;

    /**
     * @brief UI command for configuration (string + value type).
     *
     * First argument is a string key.
     * Second is a value of a specified type.
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
     *  - /g4/generateRandomSeed
     *  - /g4/interactive
     *  - /g4/logEvents
     *  - /g4/setInt
     *  - /g4/setDouble
     *  - /g4/setString
     *  - /g4/printConfiguration
     */
	class ApplicationMessenger : public G4UImessenger
	{
	public:
		ApplicationMessenger(G4Application* application);
		
		virtual ~ApplicationMessenger();
		
		// override			
		virtual void SetNewValue(G4UIcommand* command, G4String newValue);
		
	private:
        template <typename ValueType> void applyConfigurationCommand(const UIcmdConfiguration<ValueType>* command, const std::string& newValue);

        G4Application* _application; // G4Application is a singleton...

		G4UIcmdWithAnInteger* _waitCommand;
		
		G4UIcmdWithoutParameter* _interactiveCommand;

        G4UIcmdWithAnInteger* _logEventsCommand;

        G4UIcmdWithoutParameter* _generateRandomSeedCommand;

        UIcmdConfiguration<std::string>* _setStringCommand;

        UIcmdConfiguration<int>* _setIntCommand;

        UIcmdConfiguration<double>* _setDoubleCommand;

        G4UIcmdWithoutParameter* _printConfigurationCommand;
    };

}

#endif // APPLICATIONMESSENGER_HH

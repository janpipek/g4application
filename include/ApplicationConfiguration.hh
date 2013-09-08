#ifndef APPLICATIONCONFIGURATION_HH
#define APPLICATIONCONFIGURATION_HH

#include <boost/variant.hpp>

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

namespace g4
{
    /**
     * @short Adaptable type used in our configuration system
     *
     * Covers three basic reasonable types for paramaters.
     */
    typedef boost::variant<int, double, std::string> ConfigurationValue;

    class ApplicationConfigurationListener;

    /**
     * @brief General application configuration class with listeners.
     *
     * It is implemented as a dictionary (map) of string => string/int/double.
     */
    class ApplicationConfiguration
    {     
    public:
        friend class ApplicationConfigurationListener;

        /**
         * @brief Casting of value to the required template parameter.
         *
         * Guarded by boost exception.
         */
        template<typename ValueType> static const ValueType& GetValue(const std::string& key)// const
        {
            try
            {
                return boost::get<ValueType>(_entries[key]);
            }
            catch (const boost::bad_get&)
            {
                std::cerr << "Invalid value stored in configuration key \"" << key << "\": " << _entries[key] << std::endl;
                throw;
            }
        }

        static void SetValue(const std::string& key, const ConfigurationValue& value);

        static bool HasKey(const std::string& key);

        /**
         * @brief Set value, but only if not present.
         *
         * This allows classes that use configuration, to provide meaningful values
         * when these are not set from outside.
         */
        static void SetDefaultValue(const std::string& key, const ConfigurationValue& value);

        /**
         * @brief Print the configuration in a human-readable form.
         */
        static void Print(std::ostream& stream);

    private:
        static std::map<std::string, ConfigurationValue> _entries;

        static std::vector<ApplicationConfigurationListener*> _listeners;

        static void AddListener(ApplicationConfigurationListener* listener);

        static void RemoveListener(ApplicationConfigurationListener* listener);

        static void NotifyListeners(const std::string& key);

    };

    /**
     * @brief Abstract base class for the application configuration listener.
     *
     * Note that it is automatically registered.
     * You have to provide your implementation for ApplicationConfigurationChanged.
     */
    class ApplicationConfigurationListener
    {
    protected:
        friend class ApplicationConfiguration;

        ApplicationConfigurationListener();

        virtual ~ApplicationConfigurationListener();

        /**
         * @brief Abstract method responding to each change of any configuration value.
         * @param key Key of the value that was changed.
         *
         * Respond to all keys you are interested in and do nothing for others.
         */
        virtual void ApplicationConfigurationChanged(const std::string& key) = 0;
    };
}

#endif // APPLICATIONCONFIGURATION_HH

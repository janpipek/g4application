#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

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
     * Covers three basic reasonable types for paramaters:
     * - int, double & string  
     */
    typedef boost::variant<int, double, std::string> ConfigurationValue;

    class ConfigurationListener;

    /**
     * @brief General application configuration class (static class).
     *
     * It holds a dictionary of values (string/int/double as boost::variant). Keys are strings.
     * Note that the client has to know of which type the value is.
     * 
     * Instances of classes inheriting from ApplicationConfigurationListener are 
     * automatically registered as listeners of configuration changes.
     */
    class Configuration
    {     
    public:
        friend class ConfigurationListener;

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

        static ConfigurationValue& GetValue(const std::string& key)
        {
            return _entries[key];
        }

        static std::map<std::string, ConfigurationValue> GetItems();

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

        static std::vector<ConfigurationListener*> _listeners;

        static void AddListener(ConfigurationListener* listener);

        static void RemoveListener(ConfigurationListener* listener);

        static void NotifyListeners(const std::string& key);

    };

    /**
     * @brief Abstract base class for the application configuration listener.
     *
     * Note that it is automatically registered.
     * You have to provide your implementation for ConfigurationChanged.
     */
    class ConfigurationListener
    {
    protected:
        friend class Configuration;

        ConfigurationListener();

        virtual ~ConfigurationListener();

        /**
         * @brief Abstract method responding to each change of any configuration value.
         * @param key Key of the value that was changed.
         *
         * Respond to all keys you are interested in and do nothing for others.
         */
        virtual void ConfigurationChanged(const std::string& key) = 0;
    };
}

#endif // CONFIGURATION_HH
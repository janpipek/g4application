#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <boost/variant.hpp>

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>

namespace g4
{
    /**
     * @short Adaptable type used in our configuration system
     *
     * Covers three basic reasonable types for parameters:
     * - int, double & string (bool treated as integer)
     */
    typedef boost::variant<int, double, std::string> ConfigurationValue;

    /**
      * @short Get configuration value as desired type.
      *
      * Below, two specializations allow automatic treatment
      * of ints as doubles and doubles as ints.
      */
    template<typename ValueType> ValueType getValue(const ConfigurationValue& value)
    {
        return boost::get<ValueType>(value);
    }

    class ConfigurationObserver;

    /**
     * @short General application configuration class (static class).
     *
     * It holds a dictionary of values (string/int/double as boost::variant). Keys are strings.
     * Note that the client has to know of which type the value is. On the other hand,
     * it is possible to use doubles as ints (if there is no fractional part) and ints as doubles.
     * 
     * Instances of classes inheriting from ConfigurationObserver are
     * automatically registered as listeners of configuration changes.
     */
    class Configuration
    {     
    public:
        friend class ConfigurationObserver;

        /**
         * @short Get a stored key with casting.
         *
         * Guarded by boost exception.
         */
        template<typename ValueType> static ValueType Get(const std::string& key)// const
        {
            try
            {
                return getValue<ValueType>(_entries[key]);
            }
            catch (const boost::bad_get&)
            {
                std::cerr << "Invalid value stored in configuration key \"" << key << "\": " << _entries[key] << std::endl;
                throw;
            }
        }

        /**
          * @short Get a stored key with casting and fallback value.
          *
          * @param fallback This value is returned if the key is not found.
          */
        template<typename ValueType> static ValueType Get(const std::string& key, const ValueType& fallback)
        {
            if (HasKey(key)) 
            {
                return Get<ValueType>(key);
            }
            else
            {
                return fallback;
            }
        }

        /**
          * @short Get a stored string with casting and fallback value.
          *
          * Included to enable C string literals. 
          */
        static std::string Get(const std::string& key, const char* fallback)
        {
            return Get<std::string>(key, fallback);
        }

        /**
         * @short Get a stored value without casting.
         */
        static ConfigurationValue& Get(const std::string& key)
        {
            return _entries[key];
        }

        /**
         * @short Get the underlying map object.
         */
        static std::map<std::string, ConfigurationValue> GetItems();

        /**
         * @short Set value.
         *
         * @param observerToIgnore - if set, this observer is not
         *    notified of the change. Useful when some object
         *    updates several values and it would get confused.
         *
         * The listeners get notified only if there really is a change.
         */
        static void Set(const std::string& key, const ConfigurationValue& value, ConfigurationObserver* observerToIgnore = 0);

        /**
         * @short Whether there is a configuration value of a given name.
         */
        static bool HasKey(const std::string& key);

        /**
         * @short Set value, but only if not present.
         *
         * This allows classes that use configuration, to provide meaningful values
         * when these are not set from outside.
         */
        static void SetDefaultValue(const std::string& key, const ConfigurationValue& value);

        /**
         * @short Print the configuration in a human-readable form.
         */
        static void Print(std::ostream& stream);

    private:
        static std::map<std::string, ConfigurationValue> _entries;

        static std::vector<ConfigurationObserver*> _observers;

        static void AddObserver(ConfigurationObserver* observer);

        static void RemoveObserver(ConfigurationObserver* observer);

        static void NotifyObservers(const std::string& key, ConfigurationObserver *observerToIgnore);

    };

    template<> double getValue<double>(const ConfigurationValue& value);
    template<> int getValue<int>(const ConfigurationValue& value);
    template<> bool getValue<bool>(const ConfigurationValue& value);

    /**
     * @short Abstract base class for the application configuration observer.
     *
     * Note that it is automatically registered in constructor and deregistered in destructor.
     * You have to provide your implementation for ConfigurationChanged.
     */
    class ConfigurationObserver
    {
    protected:
        friend class Configuration;

        ConfigurationObserver();

        virtual ~ConfigurationObserver();

        /**
         * @short Abstract method responding to each change of any configuration value.
         * @param key Key of the value that was changed.
         *
         * Respond to all keys you are interested in and do nothing for others.
         */
        virtual void ConfigurationChanged(const std::string& key) = 0;
    };
}

#endif // CONFIGURATION_HH

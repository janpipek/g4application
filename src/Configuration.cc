#include "Configuration.hh"

#include <algorithm>
#include <iostream>
#include <limits>
#include <mutex>

using namespace std;

namespace g4
{
    std::map<std::string, ConfigurationValue> Configuration::_entries;

    std::vector<ConfigurationObserver*> Configuration::_observers;

    std::mutex observerMutex;

    ConfigurationObserver::ConfigurationObserver()
    {
        Configuration::AddObserver(this);
    }

    ConfigurationObserver::~ConfigurationObserver()
    {
        Configuration::RemoveObserver(this);
    }

    void Configuration::AddObserver(ConfigurationObserver *observer)
    {
        observerMutex.lock();
        if (std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
        {
            _observers.push_back(observer);
        }
        observerMutex.unlock();
    }

    void Configuration::RemoveObserver(ConfigurationObserver *observer)
    {
        observerMutex.lock();
        std::vector<ConfigurationObserver*>::iterator needle = std::find(_observers.begin(), _observers.end(), observer);
        if (needle != _observers.end())
        {
            _observers.erase(needle);
        }
        observerMutex.unlock();
    }

    void Configuration::NotifyObservers(const std::string &key, ConfigurationObserver* observerToIgnore = 0)
    {
        for (auto it = _observers.begin(); it != _observers.end(); it++)
        {
            if (*it == observerToIgnore) continue;
            (*it)->ConfigurationChanged(key);
        }
    }

    void Configuration::Set(const std::string &key, const ConfigurationValue &value, ConfigurationObserver* observerToIgnore)
    {
        // TODO: enable only in main thread? Or add mutex?
        ConfigurationValue oldValue = _entries[key];
        if (!(oldValue == value))
        {
            _entries[key] = value;
            NotifyObservers(key, observerToIgnore);
        }
    }

    bool Configuration::HasKey(const std::string &key)
    {
        return _entries.count(key);
    }

    void Configuration::SetDefaultValue(const std::string &key, const ConfigurationValue &value)
    {
        if (!HasKey(key))
        {
            Set(key, value);
        }
    }

    void Configuration::Print(ostream& stream)
    {
        stream << "-------------" << endl;
        stream << "Configuration" << endl;
        stream << "-------------" << endl;
        for (auto it = _entries.begin(); it != _entries.end(); it++)
        {
            stream << it->first;
            stream << " : ";
            stream << it->second;
            stream << endl;
        }
        stream << "-------------" << endl;
    }

    std::map<std::string, ConfigurationValue> Configuration::GetItems()
    {
        return _entries;
    }

    template<> const double getValue<double>(const ConfigurationValue& value)
    {
        if (value.which() == 0)
        {
            return boost::get<int>(value);
        }
        else
        {
            return boost::get<double>(value);
        }
    }

    template<> const int getValue<int>(const ConfigurationValue& value)
    {
        if (value.which() == 1)
        {
            double val = boost::get<double>(value);
            if ((double)(int)val != val)
            {
                boost::get<int>(value); // Raises exception
            }
            return val;
        }
        else
        {
            return boost::get<int>(value);
        }
    }

    template<> const bool getValue<bool>(const ConfigurationValue& value)
    {
        return !!getValue<int>(value);
    }
}

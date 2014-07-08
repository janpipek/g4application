#include "Configuration.hh"

#include <algorithm>
#include <iostream>

using namespace std;

namespace g4
{
    std::map<std::string, ConfigurationValue> Configuration::_entries;

    std::vector<ConfigurationObserver*> Configuration::_observers;

    template<> const double Configuration::GetValue<double>(const std::string& key)
    {
        ConfigurationValue& val = GetValue(key);
        if (val.which() == 0)
        {
            return boost::get<int>(val);
        }
        else
        {
            return boost::get<double>(val);
        }
    }    

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
        if (std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
        {
            _observers.push_back(observer);
        }
    }

    void Configuration::RemoveObserver(ConfigurationObserver *observer)
    {
        std::vector<ConfigurationObserver*>::iterator needle = std::find(_observers.begin(), _observers.end(), observer);
        if (needle != _observers.end())
        {
            _observers.erase(needle);
        }
    }

    void Configuration::NotifyObservers(const std::string &key)
    {
        for (auto it = _observers.begin(); it != _observers.end(); it++)
        {
            (*it)->ConfigurationChanged(key);
        }
    }

    void Configuration::SetValue(const std::string &key, const ConfigurationValue &value)
    {
        ConfigurationValue oldValue = _entries[key];
        if (!(oldValue == value))
        {
            _entries[key] = value;
            NotifyObservers(key);
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
            SetValue(key, value);
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
}

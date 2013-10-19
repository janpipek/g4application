#include "Configuration.hh"

#include <algorithm>
#include <iostream>

using namespace std;

namespace g4
{
    std::map<std::string, ConfigurationValue> Configuration::_entries;

    std::vector<ConfigurationListener*> Configuration::_listeners;

    ConfigurationListener::ConfigurationListener()
    {
        Configuration::AddListener(this);
    }

    ConfigurationListener::~ConfigurationListener()
    {
        Configuration::RemoveListener(this);
    }

    void Configuration::AddListener(ConfigurationListener *listener)
    {
        if (std::find(_listeners.begin(), _listeners.end(), listener) == _listeners.end())
        {
            _listeners.push_back(listener);
        }
    }

    void Configuration::RemoveListener(ConfigurationListener *listener)
    {
        std::vector<ConfigurationListener*>::iterator needle = std::find(_listeners.begin(), _listeners.end(), listener);
        if (needle != _listeners.end())
        {
            _listeners.erase(needle);
        }
    }

    void Configuration::NotifyListeners(const std::string &key)
    {
        for (auto it = _listeners.begin(); it != _listeners.end(); it++)
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
            NotifyListeners(key);
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

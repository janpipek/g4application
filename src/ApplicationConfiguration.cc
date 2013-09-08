#include "ApplicationConfiguration.hh"

#include <algorithm>
#include <iostream>

using namespace std;

namespace g4
{
    std::map<std::string, ConfigurationValue> ApplicationConfiguration::_entries;

    std::vector<ApplicationConfigurationListener*> ApplicationConfiguration::_listeners;

    ApplicationConfigurationListener::ApplicationConfigurationListener()
    {
        ApplicationConfiguration::AddListener(this);
    }

    ApplicationConfigurationListener::~ApplicationConfigurationListener()
    {
        ApplicationConfiguration::RemoveListener(this);
    }

    void ApplicationConfiguration::AddListener(ApplicationConfigurationListener *listener)
    {
        if (std::find(_listeners.begin(), _listeners.end(), listener) == _listeners.end())
        {
            _listeners.push_back(listener);
        }
    }

    void ApplicationConfiguration::RemoveListener(ApplicationConfigurationListener *listener)
    {
        std::vector<ApplicationConfigurationListener*>::iterator needle = std::find(_listeners.begin(), _listeners.end(), listener);
        if (needle != _listeners.end())
        {
            _listeners.erase(needle);
        }
    }

    void ApplicationConfiguration::NotifyListeners(const std::string &key)
    {
        for (auto it = _listeners.begin(); it != _listeners.end(); it++)
        {
            (*it)->ApplicationConfigurationChanged(key);
        }
    }

    void ApplicationConfiguration::SetValue(const std::string &key, const ConfigurationValue &value)
    {
        // cout << "Configuration: " << key << " = " << value << endl;
        ConfigurationValue oldValue = _entries[key];
        if (!(oldValue == value))
        {
            _entries[key] = value;
            NotifyListeners(key);
        }
    }

    bool ApplicationConfiguration::HasKey(const std::string &key)
    {
        return _entries.count(key);
    }

    void ApplicationConfiguration::SetDefaultValue(const std::string &key, const ConfigurationValue &value)
    {
        if (!HasKey(key))
        {
            SetValue(key, value);
        }
    }

    void ApplicationConfiguration::Print(ostream& stream)
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
}

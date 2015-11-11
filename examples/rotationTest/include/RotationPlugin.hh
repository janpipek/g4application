#ifndef ROTATIONPLUGIN_HH
#define ROTATIONPLUGIN_HH

#include "Plugin.hh"

class RotationPlugin : public g4::Plugin
{
public:
    const std::vector<std::string> GetAvailableComponents() const override
    {
    	return { "active", "passive" };
    }

    g4::Component* GetComponent(const std::string& name) override;	
};

#endif
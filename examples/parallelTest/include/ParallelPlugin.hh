#ifndef PARALLELPLUGIN_HH
#define PARALLELPLUGIN_HH

#include "Plugin.hh"

class ParallelPlugin : public g4::Plugin
{
public:
    const std::vector<std::string> GetAvailableComponents() const override
    {
        return { "parallel1", "parallel2" };
    }

    g4::Component* GetComponent(const std::string& name) override;  
};

#endif
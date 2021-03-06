#include "ComponentRegistry.hh"

#include "components/DefaultWorld.hh"
#include "components/MemoryLogging.hh"
#include "components/EventNumberLogging.hh"
#include "components/ReferencePhysicsList.hh"
#include "components/GPS.hh"

using namespace std;
using namespace g4;
using namespace g4::components;

template<typename ComponentType> Component* Creator()
{
    return new ComponentType();
}

ComponentRegistry::ComponentRegistry()
{
    _creators["DefaultWorld"] = Creator<DefaultWorld>;
    _creators["MemoryLogging"] = Creator<MemoryLogging>;
    _creators["EventNumberLogging"] = Creator<EventNumberLogging>;
    _creators["ReferencePhysicsList"] = Creator<ReferencePhysicsList>;
    _creators["GPS"] = Creator<GPS>;
}

const std::vector<std::string> ComponentRegistry::GetAvailableComponents() const
{
    vector<string> res;
    for (auto it = _creators.begin(); it != _creators.end(); it++)
    {
        res.push_back(it->first);
    }
    return res;
}

Component* ComponentRegistry::GetComponent(const std::string& name)
{
    auto it = _creators.find(name);
    if (it != _creators.end())
    {
        componentCreator creator = it->second;
        return creator();
    }
    return nullptr;
}

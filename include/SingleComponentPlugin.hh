#ifndef SINGLECOMPONENTPLUGIN_HH
#define SINGLECOMPONENTPLUGIN_HH

#include "Plugin.hh"
#include "Component.hh"

namespace g4
{
    /**
     * @brief Simple plugin with a single component.
     *
     * The class merges the functionality of the component inside the plugin class itself.
     * The self-component is called "default".
     */
    class SingleComponentPlugin : public Plugin, public Component
    {
    public:
        virtual const std::vector<std::string> GetAvailableComponents() const override;

        virtual Component* GetComponent(const std::string& name) override;
    };
}

#endif // SINGLECOMPONENTPLUGIN_HH


#ifndef COMPONENTREGISTRY_HH
#define COMPONENTREGISTRY_HH

#include <map>
#include <string>
#include <vector>

#include "util/Singleton.hh"
#include "Component.hh"

namespace g4
{
    namespace components
    {
        /**
          * @short A register of built-in components.
          */
        class ComponentRegistry : public g4::util::Singleton<ComponentRegistry>
        {
        // TODO: Rename class?
        public:
            friend class Singleton<ComponentRegistry>;

            virtual const std::vector<std::string> GetAvailableComponents() const;

            virtual Component* GetComponent(const std::string&);

        private:
            ComponentRegistry();

            typedef Component* (*componentCreator)();

            std::map<std::string, componentCreator> _creators;
        };
    }
}

#endif

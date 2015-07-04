#ifndef COMPONENTMANAGER_HH
#define COMPONENTMANAGER_HH

#include <vector>

namespace g4
{
    class Component;

    class ComponentManager
    {
    public:
        std::vector<Component*> GetComponents() const { return _components; }

        void AddComponent(Component* component) { _components.push_back(component); }

    private:
        std::vector<Component*> _components;
    };
}

#endif // COMPONENTMANAGER_HH


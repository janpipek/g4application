#ifndef COMPOSITEACTION_HH
#define COMPOSITEACTION_HH

#include <iostream>

namespace g4
{
    template<typename ActionType> class CompositeAction : public ActionType
    {
    public:
        CompositeAction() : _actions() { }

        void AddSubAction(ActionType* action)
        {
            _actions.push_back(action);
        }

        void RemoveSubAction(ActionType* action)
        {
            // TODO: Implement
        }

    protected:
        template<typename ArgType> void Invoke(void (ActionType::*func)(ArgType), ArgType arg)
        {
            // All sub-actions
            for (typename std::vector<ActionType*>::iterator it = _actions.begin(); it != _actions.end(); it++)
            {
                ActionType& action = **it;

                // Weird syntax for calling pointed-to-member-function
                // According to http://www.parashift.com/c++-faq/macro-for-ptr-to-memfn.html
                ((action).*(func))(arg);
            }
        }

        std::vector<ActionType*> _actions;
    };
}

#endif // COMPOSITEACTION_HH

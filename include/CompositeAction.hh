#ifndef COMPOSITEACTION_HH
#define COMPOSITEACTION_HH

#include <iostream>
#include <list>
#include <algorithm>

namespace g4
{
    /**
      * Composite action.
      *
      * In Geant4, you can typically add only one user action of each type.
      * If you combine multiple libraries together, each of which wants to 
      * define such action, a conflict arises.
      *
      * This class can be easily used on its own (as is).
      */
    template<typename ActionType> class CompositeAction : public ActionType
    {
    public:
        CompositeAction() : _actions() { }

        /**
         * @short Add action.
         * 
         * If already present, nothing happens.
         */
        void AddSubAction(ActionType* action)
        {
            if (find(_actions.begin(), _actions.end(), action) == _actions.end())
            {
                _actions.push_back(action);
            }
        }

        /**
         * @short Remove action.
         */
        void RemoveSubAction(ActionType* action)
        {
            // Erases just one (first) copy of the action.
            typename std::list<ActionType*>::iterator it = find(_actions.begin(), _actions.end(), action);
            if (it != _actions.end()) 
            {
                _actions.erase(it);
            }
        }

    protected:
        /**
          * @short Call a member method on all actions.
          */
        template<typename ArgType> void Invoke(void (ActionType::*func)(ArgType), ArgType arg)
        {
            // All sub-actions
            for (typename std::list<ActionType*>::iterator it = _actions.begin(); it != _actions.end(); it++)
            {
                ActionType& action = **it;

                // Weird syntax for calling pointed-to-member-function
                // According to http://www.parashift.com/c++-faq/macro-for-ptr-to-memfn.html
                ((action).*(func))(arg);
            }
        }


    private:
        std::list<ActionType*> _actions;
    };
}

#endif // COMPOSITEACTION_HH

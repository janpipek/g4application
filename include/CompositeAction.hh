#ifndef COMPOSITEACTION_HH
#define COMPOSITEACTION_HH

#include <list>
#include <algorithm>

namespace g4
{
    /**
      * @short Composite action.
      *
      * In Geant4, you can typically add only one user action of each type.
      * If you combine multiple libraries together, each of which wants to 
      * define such action, a conflict arises.
      *
      * All user action classes are given an implementation but for stacking action
      * that has a return value for one of its methods and thus cannot be 
      * used multiple times.
      *
      * This class can be easily used on its own (as is). In fact, it only 
      * specifies the compositeness and any class with virtual void one-parametric
      * methods can be composed (as ActionType).
      */
    template<typename ActionType> class CompositeAction : public ActionType
    {
    public:
        CompositeAction() : _actions() { }

        // TODO: Destructor???

        /**
         * @short Add action.
         * 
         * If already present, nothing happens.
         */
        void AddSubAction(ActionType* action)
        {
            if (!action)
            {
                G4Exception("CompositeAction", "AddNullSubAction", FatalException, "Cannot add null subaction.");
            }
            if (find(_actions.begin(), _actions.end(), action) == _actions.end())
            {
                _actions.push_back(action);
            }
        }

        /**
         * @short Remove action.
         *
         * If trying to remove action that is not present, nothing happens.
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
          * @short Call a member method on all actions (with argument).
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

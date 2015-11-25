#ifndef OBSERVER_HH
#define OBSERVER_HH

/**
  * @short A pair of Observer<->Publisher templates based
  * on the Observer design pattern.
  *
  * Note: Both objects involved in the relationship must not be copied (enforced)
  *    (Maybe, a clever gymnastics with pointers could solve this)
  */

#include <vector>
#include <memory>
#include <algorithm>

namespace g4
{
    namespace util
    {
        // Exported classes
        template<typename T> class Publisher;
        template<typename T> class Observer;

        /**
          * @short A generic observer.
          *
          * This class needn't be inherited publicly.
          * You have to implement the Update method.
          *
          * It automatically keeps a list of publishers it has subscribed to
          * and automatically deregisters itself in the destructor
          * (the class is safe from this point of view).
          *
          * These objects are not copyable because the relationships are stored
          * as pointers.
          *
          * @see Publisher
          */
        template<typename T> class Observer
        {
        public:
            virtual ~Observer()
            {
                while(!_publishers.empty())
                {
                    _publishers[0]->RemoveObserver(this);
                }
            }

            Observer() = default;

            Observer& operator=(const Observer<T>&) = delete;

            Observer(const T&) = delete;

        protected:
            /**
              * @short Method called by the publisher after change.
              */
            virtual void Update(T&) = 0;

        private:
            friend class Publisher<T>;

            using stored_pointer_type = Publisher<T>*;

            void RemovePublisher(stored_pointer_type publisher)
            {
                // No checking of existence needed (called from publisher)
                auto needle = std::find(_publishers.begin(), _publishers.end(), publisher);
                _publishers.erase(needle);
            }

            void AddPublisher(stored_pointer_type publisher)
            {
                // No checking for duplicity neeeded (called from publisher)
                _publishers.push_back(publisher);
            }

            std::vector<stored_pointer_type> _publishers;
        };

        /**
          * @short A generic publisher.
          *
          * It automatically deregisters all observers in the destructor
          * (so the class is safe to delete this from this point of view).
          *
          * This class has to be inherited publicly with the template
          * parameter idential to the class being defined.
          *
          * On the other hand, implementation does not require any step,
          * just call Update() when necessary.
          *
          * @see Observer
          *
          * @code
          *     class SomePublisher : public Publisher<SomePublisher> { };
          *     class SomeObserver : public Observer<SomePublisher> {
          *         virtual void Update(SomePublisher&) { ... }
          *     }
          *
          *     SomePublisher sp;
          *     sp->AddObserver(new SomeObserver());
          * @endcode
          */
        template<typename T> class Publisher
        {
        private:
            using stored_pointer_type = Observer<T>*;

        public:
            friend class Observer<T>;

            Publisher() = default;

            Publisher& operator=(const Publisher<T>&) = delete;

            Publisher(const T&) = delete;

            /**
              * @short Add an observer.
              *
              * Multiple additions
              */
            void AddObserver(stored_pointer_type observer)
            {
                if (std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
                {
                    _observers.push_back(observer);
                    observer->AddPublisher(this);
                }
            }

            /**
              * @short Remove an observer.
              *
              * Non-existent
              */
            void RemoveObserver(stored_pointer_type observer)
            {
                auto needle = std::find(_observers.begin(), _observers.end(), observer);
                if (needle != _observers.end())
                {

                    _observers.erase(needle);
                    observer->RemovePublisher(this);
                }
            }

            virtual ~Publisher()
            {
                while(!_observers.empty())
                {
                    RemoveObserver(_observers[0]);
                }
            }

        protected:
            /**
              * @short Call Update() on all observers.
              */
            void Update()
            {
                T* emitAs = dynamic_cast<T*>(this);
                for (auto it = _observers.begin(); it != _observers.end(); it++)
                {
                    (*it)->Update(*emitAs);
                }
            }

        private:
            std::vector<stored_pointer_type> _observers;
        };
    }
}

#endif // OBSERVER_HH

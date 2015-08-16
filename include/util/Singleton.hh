#ifndef SINGLETON_HH
#define SINGLETON_HH

#include <stdexcept>
#include <cstdlib>
#include <mutex>

namespace g4
{
    namespace util
    {
        template<typename T> bool instanceExists();

        /**
          * @short A simple, non-thread-safe singleton template.
          *
          * You have to inherit it with the class being declared as parameter.
          *
          * The creation is protected at runtime level (just one instance),
          * compile-time protection can be achieved by having a private
          * constructor in the class and making the template friend.
          *
          * The instance is automatically destroyed when the program ends.
          *
          * Inspiration: http://www.codeproject.com/Articles/4750/Singleton-Pattern-A-review-and-analysis-of-existin
          *
          * According to Alexandrescu's terminology (see Modern C++ Design), this is a create-new,
          * phoenix, non-thread-safe singleton.
          *
          * TODO: Check this thread-safety after the change.
          *
          * @code
          *   class AClass : public Singleton<AClass> { };
          *   AClass::Instance().DoSomething();
          *
          *   class AnotherClass : public Singleton<AnotherClass> {
          *   private:
          *     AnotherClass() { }
          *     friend class Singleton<AnotherClass>;
          *   }
          * @endcode
          */
        template<typename T> class Singleton
        {
        public:
            /**
              * @short Get reference to the valid instance.
              */
            static T& Instance()
            {
                if (!_instance)
                {
                    #ifdef G4MULTITHREADED
                    _mutex.lock();
                    #endif
                    if (!_instance)
                    {
                        _instance = new T();
                    }
                    #ifdef G4MULTITHREADED
                    _mutex.unlock();
                    #endif
                }
                return *_instance;
            }

            friend bool instanceExists<T>();

        protected:
            Singleton()
            {
                if (_instance)
                {
                    throw std::runtime_error("Attempt to create multiple instances of the singleton class.");
                }
                _instance = static_cast<T*>(this);
                // atexit(Singleton<T>::Destroy);
            }

            virtual ~Singleton()
            {
                _instance = 0; // enables further re-creation
            }

        private:
            Singleton(const Singleton&);
            Singleton& operator= (const Singleton&);

            static T* _instance;

            static void Destroy()   // TODO: Reconsider using it
            {
                delete _instance;
            }

            #ifdef G4MULTITHREADED
            static std::mutex _mutex;
            #endif
        };

        template<typename T> T* Singleton<T>::_instance = 0;

        #ifdef G4MULTITHREADED
        template<typename T> std::mutex Singleton<T>::_mutex;
        #endif

        /**
          * @short Is an instance of singleton class T already created?
          *
          * Defined outside the class not to spoil the class namespace.
          */
        template<typename T> bool instanceExists()
        {
            return T::_instance != 0;
        }
    }
}

#endif // SINGLETON_HH

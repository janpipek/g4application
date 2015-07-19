#ifndef THREADLOCAL_HH
#define THREADLOCAL_HH

#include <G4Threading.hh>

#include <map>
#include <mutex>

namespace g4
{
    namespace util
    {
       /**
         * A proxy for thread-local variables.
         *
         * When compiled without multithreading support,
         * this class just stores the pointer.
         *
         * In any case, if value is not defined, Get()
         * returns nullptr;
         *
         * Note: std::map is thread-safe as long as you don't
         *   manipulate the same element in different threads.
         *   This will not happen, as id is thread-unique.
         *
         * Note2: Geant4 assigns the same thread number
         *   to multiple different runs. You have to deal
         *   with it somehow.
         *
         * Note3: If destructor is called from outside,
         *   you also may have a problem.
         */
        template<typename T> class ThreadLocal
        {
        public:
            #ifndef G4MULTITHREADED
                ThreadLocal() : _value(nullptr) { }
            #endif

            void Set(T* item)
            {
                #ifdef G4MULTITHREADED
                    int id = G4Threading::G4GetThreadId();
                    _mutex.lock();
                    _storage[id] = item;
                    _mutex.unlock();
                #else
                    _value = item;
                #endif
            }

            T* Get()
            {
                #ifdef G4MULTITHREADED
                    int id = G4Threading::G4GetThreadId();
                    _mutex.lock();
                    T* res = _storage[id];
                    _mutex.unlock();
                    return res;  // nullptr if not present
                #else
                    return _value;
                #endif
            }

            void Unset()
            {
                Set(nullptr);
            }

            // TODO: Some sort of clearing the _storage?

        private:
            #ifdef G4MULTITHREADED
                std::map<int, T*> _storage;

                std::mutex _mutex;
            #else
                T* _value;
            #endif


        };
    }
}

#endif // THREADLOCAL_HH

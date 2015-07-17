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
            void Set(T* item)
            {
                int id = G4Threading::G4GetThreadId();
                _mutex.lock();
                _storage[id] = item;
                _mutex.unlock();
            }

            T* Get()
            {
                int id = G4Threading::G4GetThreadId();
                _mutex.lock();
                T* res = _storage[id];
                _mutex.unlock();
                return res;  // nullptr if not present
            }

            void Unset()
            {
                Set(nullptr);
            }

            // TODO: Some sort of clearing the _storage?

        private:
            std::map<int, T*> _storage;

            std::mutex _mutex;
        };
    }
}

#endif // THREADLOCAL_HH

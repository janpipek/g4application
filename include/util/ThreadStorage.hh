#ifndef THREADSTORAGE_HH
#define THREADSTORAGE_HH

#include <G4Threading.hh>

#include <map>

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
         */
        template<typename T> class ThreadLocal
        {
        public:
            Set(T* item)
            {
                int id = G4Threading::G4GetThreadId();
                _storage[id] = item;
            }

            T* Get() const
            {
                int id = G4Threading::G4GetThreadId();
                return _storage[id];
            }

            // TODO: Some sort of clearing the _storage?

        private:
            std::map<int, T*> _storage;
        };
    }
}

#endif // THREADSTORAGE_HH

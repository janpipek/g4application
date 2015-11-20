#ifndef VERBOSITY_HH
#define VERBOSITY_HH

#include <G4Types.hh>

namespace g4
{
    namespace util
    {
        class VerbosityMixin
        {
        public:
            VerbosityMixin() : _verboseLevel(0) { }

            virtual ~VerbosityMixin() = default;

            void SetVerboseLevel(G4int vl) { _verboseLevel = vl; }

            G4int GetVerboseLevel() const { return _verboseLevel; }

        private:
            G4int _verboseLevel;
        };
    }
}
#endif

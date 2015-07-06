#ifndef THROWINGEXCEPTIONHANDLER_HH
#define THROWINGEXCEPTIONHANDLER_HH

#include <G4VExceptionHandler.hh>
#include <stdexcept>

namespace g4
{
    namespace util
    {
        class Geant4Exception : public std::exception
        {
        public:
            Geant4Exception(const char *originOfException, const char *exceptionCode, G4ExceptionSeverity excSeverity, const char *theDescription);

            std::string origin;

            std::string code;

            G4ExceptionSeverity severity;

            std::string description;
        };

        class ThrowingExceptionHandler : public G4VExceptionHandler
        {
        public:
            ThrowingExceptionHandler(bool alsoWarnings = false) : _alsoWarning(alsoWarnings) { }

            virtual G4bool Notify(const char *originOfException, const char *exceptionCode, G4ExceptionSeverity severity, const char *description)
            {
                if ((severity != JustWarning) || _alsoWarning)
                {
                    throw Geant4Exception(originOfException, exceptionCode, severity, description);
                }
            }
        private:
            bool _alsoWarning;
        };
    }
}

#endif // THROWINGEXCEPTIONHANDLER_HH


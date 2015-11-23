#ifndef THROWINGEXCEPTIONHANDLER_HH
#define THROWINGEXCEPTIONHANDLER_HH

#include <G4VExceptionHandler.hh>
#include <stdexcept>

namespace g4
{
    namespace util
    {
        /**
         * @brief G4Exception turned into a class.
         */
        class Geant4Exception : public std::exception
        {
        public:
            Geant4Exception(const char *originOfException, const char *exceptionCode, G4ExceptionSeverity excSeverity, const char *theDescription);

            std::string origin;

            std::string code;

            G4ExceptionSeverity severity;

            std::string description;
        };

        /**
         * @brief Exception handler that throws C++ exceptions.
         *
         * By default, Geant4 writes G4Exceptions to console. This
         * handler enables to throw proper exceptions.
         */
        class ThrowingExceptionHandler : public G4VExceptionHandler
        {
        public:
            ThrowingExceptionHandler(bool alsoWarnings = false) : _alsoWarning(alsoWarnings) { }

            virtual ~ThrowingExceptionHandler();

            virtual G4bool Notify(const char *originOfException, const char *exceptionCode, G4ExceptionSeverity severity, const char *description) override
            {
                if ((severity != JustWarning) || _alsoWarning)
                {
                    throw Geant4Exception(originOfException, exceptionCode, severity, description);
                }
                return false;
            }
        private:
            bool _alsoWarning;
        };
    }
}

#endif // THROWINGEXCEPTIONHANDLER_HH

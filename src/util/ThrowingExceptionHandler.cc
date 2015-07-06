#include "util/ThrowingExceptionHandler.hh"

using namespace g4::util;

Geant4Exception::Geant4Exception(const char *originOfException, const char *exceptionCode, G4ExceptionSeverity excSeverity, const char *theDescription)
    : origin(originOfException), code(exceptionCode), severity(excSeverity), description(theDescription)
{

}

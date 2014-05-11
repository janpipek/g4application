#ifndef UICMDWITHNINTEGERS_HH
#define UICMDWITHNINTEGERS_HH

#include <G4UIcommand.hh>

#include <vector>

namespace g4
{
    /**
      * @short Geant4 UI command that accepts exactly N integers.
      *
      * Note: It could for sure be implemented as a template but this is not necessary.
      */
    class UIcmdWithNIntegers : public G4UIcommand
    {
    public:
        UIcmdWithNIntegers(const char* theCommandPath, G4int nOfIntegers, G4UImessenger *theMessenger);

        std::vector<int> GetNewIntVectorValue(const char* paramString) const;

    private:
        int _nOfIntegers;
    };
}
#endif // UICMDWITHNINTEGERS_HH

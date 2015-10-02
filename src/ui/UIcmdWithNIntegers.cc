#include "ui/UIcmdWithNIntegers.hh"

#include <sstream>

namespace g4
{
    UIcmdWithNIntegers::UIcmdWithNIntegers(const char* theCommandPath, G4int nOfIntegers, G4UImessenger *theMessenger)
        : G4UIcommand(theCommandPath, theMessenger), _nOfIntegers(nOfIntegers)
    {
        for (int i = 0; i < nOfIntegers; i++)
        {
            G4UIparameter* param = new G4UIparameter('i');
            SetParameter(param);
        }
    }

    std::vector<int> UIcmdWithNIntegers::GetNewIntVectorValue(const char *paramString) const
    {
        // TODO: Change to G4Tokenizer
        std::istringstream stream(paramString);
        std::vector<int> result;
        for (int i = 0; i < _nOfIntegers; i++)
        {
            int val;
            stream >> val;
            result.push_back(val);
        }
        return result;
    }
}


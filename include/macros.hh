#ifndef MACROS_HH
#define MACROS_HH

#include <G4String.hh>

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)

namespace
{
    /**
     * @brief Shorten __PRETTY_FUNCTION__ macro output.
     *
     * void g4::RunManager::AddObserver(RunObserver* observer) => RunManager::AddObserver
     */
    inline G4String shorten_pretty_function(const G4String& fname)
    {
        G4String result = fname.substr(fname.find(" ") + 1);
        if (result.substr(0, 4) == "g4::")
        {
            result = result.substr(4);
        }
        size_t pos = result.rfind('(');
        if (pos != std::string::npos)
        {
            result = result.substr(0, pos);
        }
        return result;
    }
}

// Use this when calling G4Exception :-)
#define FILE_NAME_(fname) ((fname).substr((fname).rfind("/") + 1))
#define FILE_NAME (FILE_NAME_(G4String(__FILE__)))
#define FUNCTION_NAME (shorten_pretty_function(__PRETTY_FUNCTION__))
#define EXCEPTION_WHERE ((FUNCTION_NAME + " in " + FILE_NAME + ":" + QUOTEME(__LINE__)).c_str())

#endif // MACROS_HH


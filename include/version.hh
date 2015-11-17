#ifndef G4_VERSION_HH
#define G4_VERSION_HH

#include <boost/version.hpp>
#include <G4Version.hh>

#ifdef G4UI_USE_QT
    #include <QtGlobal>
#endif

inline void printVersionInfo()
{
    std::cout << "g4 app, version 0.0.0" << std::endl;
    std::cout << "Built: " << __DATE__ << " " << __TIME__ << std::endl;
    std::cout << "Compiled with: " << std::endl;
    std::cout << "- Geant4: " << G4Version << " " << G4Date << std::endl;
    #ifdef __GNUC__
        std::cout << "- gcc: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << std::endl;
    #endif
    #ifdef G4UI_USE_QT
        std::cout << "- Qt: " << qVersion() << std::endl;
    #endif
    std::cout << "- Boost: "     
      << BOOST_VERSION / 100000     << "."  // major version
      << BOOST_VERSION / 100 % 1000 << "."  // minor version
      << BOOST_VERSION % 100                // patch level
      << std::endl;
}

#endif
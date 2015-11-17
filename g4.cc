#include <exception>
#include <iostream>

#include <G4Version.hh>
#include <globals.hh>
#include <boost/version.hpp>

#include "Application.hh"
#include "optionparser.h"

#ifdef G4UI_USE_QT
    #include <QtGlobal>
#endif

using namespace g4;
using namespace std;

enum optionIndex { UNKNOWN, INTERACTIVE, HELP, VERSION };

void printVersionInfo()
{
    cout << "g4 app, version 0.0.0" << endl;
    cout << "Compiled with: " << endl;
    cout << "- Geant4: " << G4Version << " " << G4Date << endl;
    #ifdef __GNUC__
        cout << "- gcc: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << endl;
    #endif
    #ifdef G4UI_USE_QT
        cout << "- Qt: " << qVersion() << endl;
    #endif
    cout << "- Boost: "     
      << BOOST_VERSION / 100000     << "."  // major version
      << BOOST_VERSION / 100 % 1000 << "."  // minor version
      << BOOST_VERSION % 100                // patch level
      << endl;
}

const option::Descriptor usage[] =
{
    {UNKNOWN, 0, "", "", option::Arg::None, "Usage: g4 [options] <macro1> <macro2> ...\n\nOptions:"},
    {HELP, 0, "h", "help", option::Arg::None,               "  --help           Print usage and exit."},
    {VERSION, 0, "V", "version", option::Arg::None,         "  --version        Print version info and exit."},
    {INTERACTIVE, 0, "i", "interactive", option::Arg::None, "  --interactive    Start interactive mode."},
    {0,0,0,0,0,0}
};

/**
  * @short Simple main function.
  */
int main(int argc, char** argv)
{
    argc -= (argc>0); argv += (argc>0);
    option::Stats  stats(usage, argc, argv);
    option::Option options[stats.options_max], buffer[stats.buffer_max];
    option::Parser parse(usage, argc, argv, options, buffer);

    if (parse.error()) return 1;

    if (options[HELP] || argc == 0) {
        option::printUsage(std::cout, usage);
        return 0;
    }

    if (options[VERSION]) {
        printVersionInfo();
        return 0;
    }

    Application& app = Application::CreateInstance(argc, argv);

    // Load all macros from command line
    for (int i = 0; i < parse.nonOptionsCount(); ++i)
    {
        app.AddMacro(parse.nonOption(i));
    }

    app.RunUI();

    if (options[INTERACTIVE])
    {
        app.EnterInteractiveMode();
    }

    G4cout << "Application exiting normally..." << G4endl;
}


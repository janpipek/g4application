#include <exception>
#include <iostream>

#include <globals.hh>

#include "Application.hh"
#include "optionparser.h"
#include "version.hh"

using namespace g4;
using namespace std;

enum optionIndex { UNKNOWN, INTERACTIVE, HELP, VERSION };


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

    if (options[INTERACTIVE])
    {
        app.PrepareInteractiveMode();
    }

    app.ExecuteMacros();

    if (options[INTERACTIVE])
    {
        app.EnterInteractiveMode();
    }

    G4cout << "Application exiting normally..." << G4endl;
}


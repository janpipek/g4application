#include <exception>
#include <iostream>

#include <globals.hh>

#include "Application.hh"
#include "optionparser.h"
#include "version.hh"

using namespace g4;
using namespace std;
using namespace option;

enum optionIndex { UNKNOWN, INTERACTIVE, HELP, VERSION };


const option::Descriptor usage[] =
{
    {UNKNOWN, 0, "", "", option::Arg::None, "Usage: g4 [options] <macro1> <macro2> ...\n\nOptions:"},
    {HELP, 0, "h", "help", option::Arg::None,               "-h,  --help          Print usage and exit."},
    {VERSION, 0, "V", "version", option::Arg::None,         "-v, --version        Print version info and exit."},
    {INTERACTIVE, 0, "i", "interactive", option::Arg::Optional, "-i, --interactive    Start interactive mode [optional parameter: qt*/tcsh]."},
    {0,0,0,0,0,0}
};

/**
  * @short Simple main function.
  *
  * Most of the code deals with argument processing.
  */
int main(int argc, char** argv)
{
    argc -= (argc>0); argv += (argc>0);
    Stats  stats(usage, argc, argv);
    Option* options = new Option[stats.options_max];
    Option* buffer = new Option[stats.buffer_max];
    Parser parse(usage, argc, argv, options, buffer);

    if (parse.error()) return 1;

    if (options[HELP] || options[UNKNOWN] || argc == 0) {
        option::printUsage(std::cout, usage);
        return 0;
    }

    if (options[VERSION]) {
        printVersionInfo();
        return 0;
    }

    Application& app = Application::Instance();

    // Load all macros from command line
    for (int i = 0; i < parse.nonOptionsCount(); ++i)
    {
        app.AddMacro(parse.nonOption(i));
    }

    if (options[INTERACTIVE])
    {
        if (options[INTERACTIVE].arg)
        {
            G4String name = options[INTERACTIVE].arg;
            app.SetInteractiveModeType(name);
        }
        app.PrepareInteractiveMode();
    }

    app.ExecuteMacros();

    if (options[INTERACTIVE])
    {
        app.EnterInteractiveMode();
    }

    G4cout << "Application exiting normally..." << G4endl;

    delete[] options;
    delete[] buffer;

    delete &app;
}

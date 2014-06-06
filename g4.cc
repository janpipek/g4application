#include <exception>

#include "globals.hh"

#include "G4Application.hh"

#ifdef __GNUC__
    // #include <cstdio>
    #include <execinfo.h>
    #include <stdlib.h>
    #include <unistd.h>

    void handleException()
    {
        void *array[10];
        size_t size;

        // get void*'s for all entries on the stack
        size = backtrace(array, 10);

        // print out all the frames to stderr
        // fprintf(stderr, "Error: signal %d:\n", sig);
        backtrace_symbols_fd(array, size, STDERR_FILENO);
        exit(-1);
    }
#else
    void handleException()
    {
        exit(-1);
    }
#endif

using namespace g4;
using namespace std;

/**
  * @short Simple main function.
  *
  * It only initializes and runs application and
  * prints out all exceptions.
  */
int main(int argc, char** argv)
{
    try
    {
        // Run the application
        G4Application::CreateInstance(argc, argv);
        G4Application::GetInstance()->RunUI();
    }
    catch (const exception& exc)
    {
        G4cerr << "Exception thrown: " << exc.what() << endl;
        handleException();
    }
    catch (const string& exc)
    {
        G4cerr << "Exception thrown: " << exc << endl;
        handleException();
    }
    catch (const char* exc)
    {
        G4cerr << "Exception thrown: " << exc << endl;
        handleException();
    }
}


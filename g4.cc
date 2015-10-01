#include <exception>

#include "globals.hh"

#include "Application.hh"

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
    /*try
    {*/
        // Run the application
        Application::CreateInstance(argc, argv);
        Application::Instance().RunUI();
    /*}
    catch (const exception& exc)
    {
        G4cerr << "Exception thrown: " << exc.what() << endl;
        exit(-1);
    }
    catch (const string& exc)
    {
        G4cerr << "Exception thrown: " << exc << endl;
        exit(-1);
    }
    catch (const char* exc)
    {
        G4cerr << "Exception thrown: " << exc << endl;
        exit(-1);
    }*/
    G4cout << "Application exiting normally..." << G4endl;
}


#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Application.hh"
#include "util/ThrowingExceptionHandler.hh"

using namespace g4;
using namespace g4::util;
using namespace std;

ThrowingExceptionHandler* excHandler = nullptr;

TEST_CASE( "It is possible to run the application", "[run][app]" ) {

    // G4Application
    Application* app = &Application::Instance();

    if (!excHandler)
    {
        excHandler = new ThrowingExceptionHandler();
    }

    SECTION("No duplicate instances") {
        REQUIRE_THROWS(Application::CreateInstance(0, nullptr));
    }

    SECTION("Proper class initialization") {
        REQUIRE(app->GetComponentManager() != nullptr);
        REQUIRE(app->GetPluginLoader() != nullptr);
        REQUIRE(app->GetRunManager() != nullptr);
    }
}

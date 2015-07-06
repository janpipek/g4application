#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Application.hh"

using namespace g4;
using namespace std;

TEST_CASE( "It is possible to run the application", "[run]" ) {
    Application::CreateInstance(0, nullptr);

    SECTION("No duplicate instances") {
        REQUIRE_THROWS(Application::CreateInstance(0, nullptr));
    }
}

# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(B1)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# g4Application required
# G4APP_PATH
if(DEFINED ENV{G4APP_PATH})
    message(STATUS "Using install location: $ENV{G4APP_PATH}" )
    set(CMAKE_INSTALL_PREFIX $ENV{G4APP_PATH})
else()
    message(STATUS "Using default install location.")
    set(CMAKE_INSTALL_PREFIX "../../build/")
endif()

if(DEFINED ENV{G4APP_SOURCE_PATH})
    set(G4APP_SOURCE_PATH $ENV{G4APP_SOURCE_PATH})
else()
    message(FATAL_ERROR "Please, set G4APP_SOURCE_PATH environment variable.")
endif()
set(CMAKE_MODULE_PATH "${G4APP_SOURCE_PATH}/cmake/" ${CMAKE_MODULE_PATH})
find_package(G4Application REQUIRED)
include_directories(${G4Application_INCLUDE_DIR} include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_library(parallelTest SHARED ${sources} ${headers})

target_link_libraries(parallelTest ${Geant4_LIBRARIES} ${G4Application_LIBRARY})

install(TARGETS parallelTest DESTINATION .)

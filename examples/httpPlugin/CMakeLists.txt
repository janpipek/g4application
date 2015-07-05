cmake_minimum_required(VERSION 2.8)

project(httpPlugin)

# G4APP_PATH 
if(DEFINED ENV{G4APP_PATH})
    message(STATUS "Using install location: $ENV{G4APP_PATH}" )
    set(CMAKE_INSTALL_PREFIX $ENV{G4APP_PATH})
else()
    message(STATUS "Using default install location.")
    set(CMAKE_INSTALL_PREFIX "../../build/")
endif()

# Use the FindG4Application.cmake file
set(CMAKE_MODULE_PATH "../../cmake/" ${CMAKE_MODULE_PATH})

# Set the necessary variable for FindG4Application.cmake file
set(G4APP_SOURCE_PATH "../../")

# Find the application library & Geant4
find_package(G4Application REQUIRED)
find_package(Geant4 REQUIRED)
find_package(Geant4 COMPONENTS qt)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

include_directories(${G4Application_INCLUDE_DIR} include)
add_library(httpPlugin SHARED ${sources} ${headers})

target_link_libraries(httpPlugin ${Geant4_LIBRARIES} ${G4Application_LIBRARY})

install(TARGETS httpPlugin DESTINATION .)



 



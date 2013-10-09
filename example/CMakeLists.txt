cmake_minimum_required(VERSION 2.8)

project(examplePlugin)

set(CMAKE_INSTALL_PREFIX "../build/")

# Use the FindG4Application.cmake file
set(CMAKE_MODULE_PATH "../cmake/" ${CMAKE_MODULE_PATH})

# Set the necessary variable for FindG4Application.cmake file
set(G4APPLICATION_DIR "..")

# Find the application library & Geant4
find_package(G4Application REQUIRED)
find_package(Geant4 REQUIRED qt)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

include_directories(${G4Application_INCLUDE_DIR} include)
add_library(examplePlugin SHARED ${sources} ${headers})

target_link_libraries(examplePlugin ${Geant4_LIBRARIES} ${G4Application_LIBRARY})

install(TARGETS examplePlugin DESTINATION bin)



 



cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(g4Application)

# G4APP_PATH (-D or env.variable)
if(DEFINED ENV{G4APP_PATH})
    set(G4APP_PATH $ENV{G4APP_PATH})
endif()

if (DEFINED G4APP_PATH)
    message(STATUS "Using install location: ${G4APP_PATH}" )
    set(CMAKE_INSTALL_PREFIX ${G4APP_PATH})
else()
    message(STATUS "Using default install location.")
    set(CMAKE_INSTALL_PREFIX build)
endif()

find_package(Boost 1.49 COMPONENTS system filesystem REQUIRED)
find_package(Geant4 REQUIRED)
find_package(Geant4 COMPONENTS qt)

include(${Geant4_USE_FILE})

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(g4 g4.cc ${headers})
add_library(g4Application SHARED ${sources} ${headers})

add_dependencies(g4 g4Application)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

target_link_libraries(g4 g4Application ${Geant4_LIBRARIES} dl ${Boost_LIBRARIES})

install(TARGETS g4 DESTINATION .)
install(TARGETS g4Application DESTINATION .)

include_directories(include)

set(CMAKE_CXX_FLAGS "-std=c++0x")

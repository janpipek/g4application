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

set(CMAKE_MODULE_PATH "cmake/" ${CMAKE_MODULE_PATH})

# Boost requirements
find_package(Boost 1.49 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

# Geant4 requirements
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
# find_package(Geant4 REQUIRED)
# find_package(Geant4 COMPONENTS qt)
include(${Geant4_USE_FILE})

file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/lib/json/jsoncpp.cpp)
file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/include/*.hh ${PROJECT_SOURCE_DIR}/lib/json/json/*.h)

add_library(g4Application SHARED ${sources} ${headers})
add_executable(g4 g4.cc ${headers})

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib/json)
set(CMAKE_CXX_FLAGS "-std=c++0x")

add_dependencies(g4 g4Application)

target_link_libraries(g4Application ${Geant4_LIBRARIES} dl ${Boost_LIBRARIES})
target_link_libraries(g4 g4Application)

install(TARGETS g4 DESTINATION .)
install(TARGETS g4Application DESTINATION .)

# Tests
add_executable(testRun "test/run.cc" ${headers})
add_dependencies(testRun g4Application)
target_link_libraries(testRun g4Application ${Geant4_LIBRARIES} dl ${Boost_LIBRARIES})

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(g4App)

find_package(Boost 1.49 COMPONENTS system filesystem REQUIRED)
find_package(Geant4 REQUIRED qt)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(g4 g4.cc ${headers})
add_library(g4App SHARED ${sources} ${headers})

add_dependencies(g4 g4App)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

target_link_libraries(g4 g4App ${Geant4_LIBRARIES} dl ${Boost_LIBRARIES})

install(TARGETS g4 DESTINATION bin)
install(TARGETS g4App DESTINATION bin)

include_directories(include)

set(CMAKE_CXX_FLAGS "-std=c++0x")
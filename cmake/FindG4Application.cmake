# This is an example cmake that defines two important variables:
# - G4Application_INCLUDE_DIR: what you have specify as include path (-I)
# - G4Application_LIBRARY: where are the libraries for the target (-L)
#
# It requires you to set the G4APP_SOURCE_PATH to point to the 
#   g4Application root directory (either as cmake variable or
#   environment variable.)

if (DEFINED ENV{G4APP_SOURCE_PATH} )
    set(G4APP_SOURCE_PATH $ENV{G4APP_SOURCE_PATH})
endif()

if (DEFINED G4APP_SOURCE_PATH)
    message(STATUS "Using g4Application from ${G4APP_SOURCE_PATH}.")
    find_path(G4Application_INCLUDE_DIR "Plugin.hh" HINTS "${G4APP_SOURCE_PATH}/include")
    find_library(G4Application_LIBRARY g4Application HINTS ${G4APP_SOURCE_PATH} $ENV{G4APP_PATH})   
else()
    message(ERROR " Please set G4APP_SOURCE_PATH variable.")
endif()
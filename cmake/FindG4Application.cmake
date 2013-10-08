# This is an example cmake that defines two important variables:
# - G4Application_INCLUDE_DIR: what you have specify as include path
# - G4Application_LIBRARY: what you have to libraries for the target
#
# It requires you to set the G4APPLICATION_DIR to point to the 
#   g4Application root directory.
if (NOT G4APPLICATION_DIR )
    message(send_error "Please set G4APPLICATION_DIR variable.")
else()
    message(STATUS "Using g4Application from ${G4APPLICATION_DIR}.")
    find_path(G4Application_INCLUDE_DIR "Plugin.hh" HINTS "${G4APPLICATION_DIR}/include")
    find_library(G4Application_LIBRARY g4Application HINTS ${G4APPLICATION_DIR})
endif()
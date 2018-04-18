# $Id$
#
# ------------------------------------------------------------------------------
# The configuration file for CMake build for Virtual Geometry Model
# Copyright (C) 2012, Ivana Hrivnacova
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# ------------------------------------------------------------------------------

# The CMake build for Virtual Geometry Model is a result of a merge 
# of the CMake configuration files kindly provided 
# by Florian Uhlig, GSI and Pere Mato, CERN.

# - Try to find Geant4 instalation
# This module sets up Geant4 information: 
# - either from Geant4 CMake configuration file (Geant4Config.cmake), if available
# - or it defines:
# GEANT4_FOUND          If Geant4 is found
# GEANT4_INCLUDE_DIR    PATH to the include directory
# GEANT4_LIBRARIES      Most common libraries
# GEANT4_LIBRARY_DIR    PATH to the library directory 

message(STATUS "Looking for GEANT4 ...")

# First search for Geant4Config.cmake on the path defined via user setting 
# Geant4_DIR

if(EXISTS ${Geant4_DIR}/Geant4Config.cmake)
  include(${Geant4_DIR}/Geant4Config.cmake)
  set(GEANT4_INCLUDE_DIR ${Geant4_INCLUDE_DIRS})
  message(STATUS "Found Geant4 CMake configuration in ${Geant4_DIR}")
  return()
endif()

# If Geant4_DIR was not set search for geant4-config executable on system path
# to get Geant4 installation directory 

find_program(GEANT4_CONFIG_EXECUTABLE geant4-config PATHS
  ${GEANT4_DIR}/bin
  )

if(GEANT4_CONFIG_EXECUTABLE)
  execute_process(
    COMMAND ${GEANT4_CONFIG_EXECUTABLE} --prefix 
    OUTPUT_VARIABLE G4PREFIX 
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  execute_process(
    COMMAND ${GEANT4_CONFIG_EXECUTABLE} --version 
    OUTPUT_VARIABLE GEANT4_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  if(EXISTS ${G4PREFIX}/lib/Geant4-${GEANT4_VERSION}/Geant4Config.cmake)
    set(Geant4_DIR ${G4PREFIX}/lib/Geant4-${GEANT4_VERSION})
    include(${Geant4_DIR}/Geant4Config.cmake)
    set(GEANT4_INCLUDE_DIR ${Geant4_INCLUDE_DIRS})
    message(STATUS "Found Geant4 CMake configuration in ${Geant4_DIR}")
    return()
  endif()

  if(EXISTS ${G4PREFIX}/lib64/Geant4-${GEANT4_VERSION}/Geant4Config.cmake)
    set(Geant4_DIR ${G4PREFIX}/lib64/Geant4-${GEANT4_VERSION})
    include(${Geant4_DIR}/Geant4Config.cmake)
    set(GEANT4_INCLUDE_DIR ${Geant4_INCLUDE_DIRS})
    message(STATUS "Found Geant4 CMake configuration in ${Geant4_DIR}")
    return()
  endif()

endif()

# If search for geant4-config failed try to use directly user paths if set
# or environment variables 
#
if (NOT GEANT4_FOUND)
  find_path(GEANT4_INCLUDE_DIR NAMES globals.hh PATHS
    ${GEANT4_INC_DIR}
    ${GEANT4_DIR}/include
    $ENV{G4INSTALL}/include
    $ENV{G4INCLUDE}
  )
  find_path(GEANT4_LIBRARY_DIR NAMES libname.map PATHS
    ${GEANT4_LIB_DIR}
    ${GEANT4_DIR}/lib/${GEANT4_SYSTEM}
    $ENV{G4INSTALL}/lib/$ENV{G4SYSTEM}
    $ENV{G4LIB}
  )
  if (GEANT4_INCLUDE_DIR AND GEANT4_LIBRARY_DIR)
    execute_process(
      COMMAND ${GEANT4_LIBRARY_DIR}/liblist -m ${GEANT4_LIBRARY_DIR}                  
      INPUT_FILE ${GEANT4_LIBRARY_DIR}/libname.map 
      OUTPUT_VARIABLE GEANT4_LIBRARIES
      OUTPUT_STRIP_TRAILING_WHITESPACE
      TIMEOUT 2)
  endif()
  set(GEANT4_LIBRARIES "-L${GEANT4_LIBRARY_DIR} ${GEANT4_LIBRARIES} -lexpat -lz")
endif()      

if (GEANT4_INCLUDE_DIR AND GEANT4_LIBRARY_DIR AND GEANT4_LIBRARIES)
  set (GEANT4_FOUND TRUE)
endif()  

if(GEANT4_FOUND) 
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${GEANT4_LIBRARY_DIR})
  if (NOT GEANT4_FIND_QUIETLY)
    if (G4PREFIX)
      message(STATUS "Found GEANT4 ${GEANT4_VERSION} in ${G4PREFIX}")
    else()  
      message(STATUS "Found GEANT4 includes in ${GEANT4_INCLUDE_DIR}")
      message(STATUS "Found GEANT4 libraries in ${GEANT4_LIBRARY_DIR}")
      #message(STATUS "Found GEANT4 libraries ${GEANT4_LIBRARIES}")
    endif()  
  endif (NOT GEANT4_FIND_QUIETLY)  
else()
  if (Geant4_FIND_REQUIRED)
    message(FATAL_ERROR "Geant4 required, but not found")
  endif (Geant4_FIND_REQUIRED)   
endif()

# Make variables changeble to the advanced user
mark_as_advanced(GEANT4_INCLUDE_DIR GEANT4_LIBRARY_DIR GEANT4_LIBRARIES)



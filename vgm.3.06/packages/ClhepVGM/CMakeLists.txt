# $Id: CMakeLists.txt 709 2012-03-01 14:33:26Z ihrivnac $
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

#---ClhepVGM -------------------------------------------------------------------
      
#---Include directories---------------------------------------------------------
include_directories(
  ${CLHEP_INCLUDE_DIR}
  ${VGM_SOURCE_DIR}/packages/VGM/include 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#---Add Library-----------------------------------------------------------------
file(GLOB sources source/*.cxx)
add_library(ClhepVGM ${sources})
target_link_libraries(ClhepVGM ${Geant4_LIBRARIES})

#----Installation---------------------------------------------------------------
install(DIRECTORY include/ DESTINATION include  PATTERN ".svn" EXCLUDE)
install(TARGETS ClhepVGM DESTINATION lib)

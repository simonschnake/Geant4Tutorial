# $Id: CMakeLists.txt 708 2012-02-29 17:19:48Z ihrivnac $
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

#---vgm_test -------------------------------------------------------------------

message(STATUS "Configuring vgm_test")  

# Create executables "vgm_test"

#----------------------------------------------------------------------------
# Includes
#
include_directories(
   ${CLHEP_INCLUDE_DIR} 
   ${ROOT_INCLUDE_DIR} 
   ${GEANT4_INCLUDE_DIR} 
   ${VGM_SOURCE_DIR}/packages/VGM/include
   ${VGM_SOURCE_DIR}/packages/ClhepVGM/include
   ${VGM_SOURCE_DIR}/packages/BaseVGM/include 
   ${VGM_SOURCE_DIR}/packages/XmlVGM/include
   ${VGM_SOURCE_DIR}/packages/RootGM/include
   ${VGM_SOURCE_DIR}/packages/Geant4GM/include
   ${VGM_SOURCE_DIR}/test/include
)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources src/*.cc)
file(GLOB headers include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(vgm_test vgm_test.cc ${sources} ${headers})
target_link_libraries(vgm_test ${ROOT_LIBRARIES} ${CLHEP_LIBRARIES} ${XERCES_LIBRARIES} ${GEANT4_LIBRARIES} Geant4GM RootGM BaseVGM ClhepVGM XmlVGM)

#----------------------------------------------------------------------------
# Copy all test scripts and macros to the build directory.
#

# macros
file(GLOB macros macro/*.mac)
foreach(_macropath ${macros})
  get_filename_component(_macro ${_macropath} NAME)
  # message(STATUS "Macro in list ${_macro}")
  configure_file(
    ${PROJECT_SOURCE_DIR}/test/macro/${_macro}
    ${PROJECT_BINARY_DIR}/test/macro/${_macro}
    COPYONLY
  )
endforeach()

# scripts
set(VGM_TEST_SCRIPTS
  test1_suite.sh
  test2_suite.sh
  test3_suite.sh
  test_suite.sh)

foreach(_script ${VGM_TEST_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/test/${_script}
    ${PROJECT_BINARY_DIR}/test/${_script}
    COPYONLY
    )
endforeach()

#----Installation-----------------------------------------------------------------
install(TARGETS vgm_test DESTINATION bin)

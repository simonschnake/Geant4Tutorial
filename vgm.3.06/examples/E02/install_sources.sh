#!/bin/sh
# $Id: install_sources.sh 707 2012-02-29 17:03:07Z ihrivnac $

# -----------------------------------------------------------------------
# The script for environment setting for the Virtual Geometry Model example
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

#
# Script for installation of sources for E02 examples

SOURCE_DIR=`dirname $0`

# Find sources
echo "... Installing E02 sources in ${SOURCE_DIR}"
if [ ! "`which geant4-config 2> /dev/null`" = "" ]; then
  DIR="`geant4-config --prefix`"/share/Geant4-"`geant4-config --version`"/examples/novice/N03
else
  DIR=${G4INSTALL}/examples/novice/N03
fi
if [ ! -d ${DIR} ]; then 
  echo "... Example source not found in Geant4 installation"
  exit 1
fi    

# Copy sources
#
cp -r ${DIR} ${SOURCE_DIR}
cp ${SOURCE_DIR}/N03Example.root ${SOURCE_DIR}/N03
cp ${SOURCE_DIR}/GNUmakefile ${SOURCE_DIR}/N03
cp ${SOURCE_DIR}/DetectorConstruction.cc ${SOURCE_DIR}/N03/src
#cp ExN03PrimaryGeneratorAction.cc N03/src
#cp ExN03SteppingAction.cc N03/src
#rm N03/include/ExN03DetectorMessenger.hh
#rm N03/src/ExN03DetectorMessenger.cc

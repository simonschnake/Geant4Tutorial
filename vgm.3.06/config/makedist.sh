#!/bin/sh
# $Id: makedist.sh 543 2007-05-23 08:49:24Z ivana $

# -----------------------------------------------------------------------
# The source distribution script for the Virtual Geometry Model
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

#
# Script to produce the source distribution of VGM.
# Should be run from the VGM istallation parent directory.
# The distributed files list is saved in makedist.log.
# 
# Usage:  makedist.sh  vgm_installation
#
# By I.Hrivnacova, 20/08/2004

# Input parameters
if [ $# != 1 ]; then
  echo "Usage:  makedist.sh  vgm_installation"
  exit 1
fi  

SOURCE=$1
TARFILE=$SOURCE."tar.gz"
TAR="tar czvf"

mv $SOURCE/include $SOURCE/include.exl
EXCLUDE1="--exclude CVS --exclude include.exl --exclude bin --exclude lib --exclude tmp "
EXCLUDE2="--exclude log --exclude log_ref/xml --exclude log_ref/gdml --exclude test/xml --exclude test/gdml "
EXCLUDE3="--exclude N03 --exclude rootgeom"
rm -f $TARFILE.gz

$TAR $TARFILE $EXCLUDE1 $EXCLUDE2 $EXCLUDE3 $SOURCE > makedist.log
mv $SOURCE/include.exl $SOURCE/include

exit 0

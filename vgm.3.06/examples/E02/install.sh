#!/bin/sh
# $Id: install.sh 672 2010-12-21 16:17:37Z ihrivnac $

# -----------------------------------------------------------------------
# The script for installation for the Virtual Geometry Model examples
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

#
# Script for installation for E02 examples

CURDIR=`pwd`

# E02
#
echo "... Installing E02"
./install_sources.sh
. ./env_setup.sh
cd N03
gmake
echo "... Installing E02 finished"

cd $CURDIR

# $Id: GNUmakefile 544 2007-05-23 10:39:11Z ivana $

# -----------------------------------------------------------------------
# The makefile for a package of the Virtual Geometry Model
# Copyright (C) 2007, Ivana Hrivnacova               
# All rights reserved. 
#           
# For the licensing terms see vgm/LICENSE.
# Contact: ivana@ipno.in2p3.fr
# -----------------------------------------------------------------------

# Based on Geant4 makefiles
# (GNUmakefile for particles library.  Gabriele Cosmo, 4/4/97 )

name := RootGM

# Added for reading INTYLIBS (needed on MacOS)
include $(VGM_INSTALL)/config/architecture.gmk
include $(VGM_INSTALL)/config/root.gmk

SUBDIRS = common materials solids volumes
SUBLIBS = RootGM_common RootGM_materials RootGM_solids RootGM_volumes 

ifndef VGM_INSTALL
  VGM_INSTALL = ../..
endif

include $(VGM_INSTALL)/config/globlib.gmk

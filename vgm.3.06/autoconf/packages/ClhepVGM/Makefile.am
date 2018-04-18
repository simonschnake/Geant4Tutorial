# $Id: Makefile.am 698 2011-12-09 13:38:04Z ihrivnac $

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

INCLUDES = ${CLHEP_INCLUDE} ${GEANT4_INCLUDE} \
         -I../../../packages/VGM/include \
         -I../../../packages/ClhepVGM/include 

clhepvgmsrc=../../../packages/ClhepVGM/source

lib_LTLIBRARIES = libClhepVGM.la

libClhepVGM_la_SOURCES =                        \
	$(clhepvgmsrc)/Units.cxx \
	$(clhepvgmsrc)/transform.cxx

clhepvgminc=../../../packages/ClhepVGM/include/ClhepVGM
clhepvgmincdir = $(includedir)/ClhepVGM
clhepvgminc_HEADERS = \
	$(clhepvgminc)/Units.h \
	$(clhepvgminc)/transform.h


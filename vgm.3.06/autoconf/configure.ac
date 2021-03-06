# $Id: configure.ac 698 2011-12-09 13:38:04Z ihrivnac $

# This file is part of the Autoconf build mechanism for the
# Virtual Geometry Model
# Copyright (C) 2007, Brett Viren
# All rights reserved.
# 
# For the licensing terms see vgm/LICENSE.
# Contact: bv@bnl.gov

# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(vgm-autoconf, 0.2, bv@bnl.gov)
AM_INIT_AUTOMAKE(vgm-autoconf, 0.2)
## ^
## |
## +-> note: until these autoconf macros cause "make dist" to tar up
##     vgm proper instead of just the autoconf area, don't use 
##     VGM version strings here.


AC_CONFIG_SRCDIR([Makefile.am])
AM_CONFIG_HEADER(config.h)
#AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Let's be strict.
AX_CFLAGS_GCC_OPTION([-pedantic],CXXFLAGS)
AX_CFLAGS_GCC_OPTION([-ansi],CXXFLAGS)
# Well, not so strict that we can't use ROOT
AX_CFLAGS_GCC_OPTION([-Wno-long-long],CXXFLAGS)

# This should be from acmacros/vgm_build.m4 *not* acmacros/vgm.m4.
# This is set in acinclude.m4.
VGM_SETUP

CLHEP_SETUP

if test x$VGM_ENABLE_GEANT4GM = xyes ; then
GEANT4_SETUP
EXPAT_SETUP
XERCESC_SETUP
fi

if test x$VGM_ENABLE_ROOTGM = xyes ; then
ROOT_SETUP
fi


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([sqrt])

AC_CONFIG_FILES([Makefile
                 packages/Makefile
                 packages/VGM/Makefile
                 packages/ClhepVGM/Makefile
                 packages/BaseVGM/Makefile
                 packages/RootGM/Makefile
                 packages/Geant4GM/Makefile
                 packages/XmlVGM/Makefile
                 test/Makefile
                ])
AC_OUTPUT

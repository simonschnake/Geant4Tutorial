// $Id: ITrd.h 634 2008-11-20 13:28:44Z ihrivnac $

// -----------------------------------------------------------------------
// The VGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup VGM_solids
///
/// \class VGM::ITrd
/// 
/// The VGM interface to trd solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_TRD_H
#define VGM_I_TRD_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

  class ITrd : public virtual ISolid
  {
    public:
      virtual ~ITrd() {}

      // methods
      
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

		      /// Return the half-length along x at the surface positioned 
		      /// at -hz in mm
      virtual double XHalfLengthMinusZ() const = 0;
		      ///
		      /// Return the half-length along x at the surface positioned 
		      /// at +hz in mm
      virtual double XHalfLengthPlusZ() const = 0;
		      ///
		      /// Return the half-length along y at the surface positioned 
		      /// at -hz in mm
      virtual double YHalfLengthMinusZ() const = 0;
		      ///
		      /// Return thehalf-length along y at the surface positioned 
		      /// at +hz in mm
      virtual double YHalfLengthPlusZ() const = 0;
		      ///
		      /// Return the half-length along the z axis in mm
      virtual double ZHalfLength() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}

std::ostream& operator << (std::ostream& out, const VGM::ITrd& trd);

#endif //VGM_I_TRD_H

// $Id: ITorus.h 634 2008-11-20 13:28:44Z ihrivnac $

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
/// \class VGM::ITorus
/// 
/// The VGM interface to torus solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_TORUS_H
#define VGM_I_TORUS_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

  class ITorus : public virtual ISolid
  {
    public:
      virtual ~ITorus() {}

      // methods
      
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;
 
		      ///
		      /// Return the inside radius of the torus in mm
      virtual double InnerRadius() const = 0;
		      ///
		      /// Return the outside radius of the torus in mm
      virtual double OuterRadius() const = 0;
		      ///
		      /// Return the axial (swept) radius of the torus in mm
      virtual double AxialRadius() const = 0;
		      ///
		      /// Return the starting phi angle of the segment in deg
		      /// (with 0 being the +x axis)
      virtual double StartPhi() const = 0;
		      ///
		      /// Return the opening phi angle of the segment in deg
      virtual double DeltaPhi() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };

}

std::ostream& operator << (std::ostream& out, const VGM::ITorus& torus);

#endif //VGM_I_TORUS_H

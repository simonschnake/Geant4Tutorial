// $Id: ITrap.h 634 2008-11-20 13:28:44Z ihrivnac $

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
/// \class VGM::ITrap
/// 
/// The VGM interface to trap solids.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef VGM_I_TRAP_H
#define VGM_I_TRAP_H

#include "VGM/solids/ISolid.h"

#include <iostream>

namespace VGM {

  class ITrap : public virtual ISolid
  {
    public:
      virtual ~ITrap() {}

      // methods
      
      virtual SolidType   Type() const = 0;
      virtual std::string Name() const = 0;

		      ///
		      /// Return the half-length along the z axis in mm
      virtual double ZHalfLength() const = 0;
		      ///
		      /// Return the polar angle of the line joining the centres
		      /// of the faces at -hz and +hz in deg
      virtual double Theta() const = 0;
		      ///
		      /// Return the azimuthal angle of the line joining the centres
 		      /// of the faces at -hz and +hz in deg
      virtual double Phi() const = 0;
		      ///
		      /// Return the half-length along y of the face at -hz in mm
      virtual double YHalfLengthMinusZ() const = 0;
		      ///
		      /// Return the half-length along x of the side at -hy 
		      /// of the face at -hz in mm
      virtual double XHalfLengthMinusZMinusY() const = 0;
		      ///
		      /// Return the half-length along x of the side at +hy
		      /// of the face at +hz in mm
      virtual double XHalfLengthMinusZPlusY() const = 0;
		      ///
		      /// Return the angle with respect to the y axis from the 
		      /// centre of the side at -hy to the centre at +hy
		      /// of the face at -hz
      virtual double AlphaMinusZ() const = 0;
		      ///
		      /// Return the half-length along y of the face at +hz in m
      virtual double YHalfLengthPlusZ() const = 0;
		      ///
		      /// Return the half-length along x of the side at -hy 
		      /// of the face at +hz in m
      virtual double XHalfLengthPlusZMinusY() const = 0;
		      ///
		      /// Return the half-length along x of the side at +hy
		      /// of the face at +hz in m
      virtual double XHalfLengthPlusZPlusY() const = 0;
		      ///
		      /// Return the angle with respect to the y axis from the 
		      /// centre of the side at -hy to the centre at +hy
		      /// of the face at +hz
      virtual double AlphaPlusZ() const = 0;

      // streaming
      virtual std::ostream& Put(std::ostream& out) const = 0;
  };
  
}  

std::ostream& operator << (std::ostream& out, const VGM::ITrap& trap);

#endif //VGM_I_TRAP_H

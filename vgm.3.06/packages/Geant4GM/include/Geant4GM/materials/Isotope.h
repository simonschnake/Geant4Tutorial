// $Id: Isotope.h 634 2008-11-20 13:28:44Z ihrivnac $

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup Geant4GM_materials
//
/// \class Geant4GM::Isotope
///
/// VGM implementation for Geant4 Isotope.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_ISOTOPE_H
#define GEANT4_GM_ISOTOPE_H

#include "VGM/materials/IIsotope.h"

#include <string>

class G4Isotope;

namespace Geant4GM {

  class Isotope : public virtual VGM::IIsotope
  {
    public:
      Isotope(const std::string& name, int z, int n, double a); 
      Isotope(G4Isotope* Isotope);		
      virtual ~Isotope();
    
      // methods
      virtual std::string Name() const;

      virtual int     Z() const;     
      virtual int     N() const;     
      virtual double  A() const;     

    protected:  
      Isotope();
      Isotope(const Isotope& rhs);
    
    private:
      G4Isotope*  fIsotope;  
  };

}

#endif //GEANT4_GM_ISOTOPE_H

// $Id: Medium.h 685 2010-12-22 11:50:33Z ihrivnac $

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
/// \class Geant4GM::Medium
///
/// The VGM implementation of interface to tracking medium.
/// As there is no equivalent object in Geant4, the tracking medium
/// parameters are store in data members of this class.
///
/// \author Ivana Hrivnacova; IPN Orsay

#ifndef GEANT4_GM_MEDIUM_H
#define GEANT4_GM_MEDIUM_H

#include "BaseVGM/materials/VMedium.h"

#include "globals.hh"

#include <string>

class G4Material;

namespace Geant4GM {

  class Medium : public BaseVGM::VMedium
  {
    public:
      Medium(const std::string& name, 
             int mediumId,
             VGM::IMaterial* material,
             int nofParameters, double* parameters);
      virtual ~Medium();
    
      // methods
      virtual std::string Name() const;

      virtual int     Id() const;
      virtual double  Parameter(int i) const;

    protected:  
      Medium();
      Medium(const Medium& rhs); 
    
    private:
      void CheckIndex(int iel) const;

      // data members
      static  const int fgkParamSize;  
          
      G4String     fName;
      G4Material * fMaterial;
      G4int        fId;
      G4double*    fParameters;
  };

}

#endif //GEANT4_GM_MEDIUM_H

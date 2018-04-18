// $Id: Placement.cxx 634 2008-11-20 13:28:44Z ihrivnac $

// -----------------------------------------------------------------------
// The Geant4GM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

//
// Class Placement
// -------------------
// VGM implementation for Geant4 positions of volumes.
//
// Author: Ivana Hrivnacova; IPN Orsay

#include "VGM/common/Axis.h"
#include "VGM/solids/ICons.h"
#include "VGM/solids/IPolycone.h"
#include "VGM/solids/IPolyhedra.h"
#include "VGM/solids/ITubs.h"
#include "VGM/volumes/IVolume.h"

#include "ClhepVGM/transform.h"
#include "ClhepVGM/Units.h"

#include "Geant4GM/volumes/Placement.h"
#include "Geant4GM/volumes/VolumeMap.h"
#include "Geant4GM/volumes/PlacementMap.h"

#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PVDivision.hh"
#include "G4VDivisionParameterisation.hh"
#include "G4ReflectionFactory.hh"

//_____________________________________________________________________________
Geant4GM::Placement::Placement(      
                         VGM::IVolume* volume, VGM::IVolume* motherVolume,
                         G4VPhysicalVolume* pv)
  : VGM::IPlacement(),
    BaseVGM::VPlacement(volume, motherVolume),
    fPhysicalVolume(pv)       
{
/// Standard constructor to define a multiple placement via G4 object

  // Register physical volume in the map
  Geant4GM::PlacementMap::Instance()->AddPlacement(this, fPhysicalVolume); 
}

//_____________________________________________________________________________
Geant4GM::Placement::Placement() 
  : VGM::IPlacement(),
    BaseVGM::VPlacement() 
{
/// Protected default constructor
}

//_____________________________________________________________________________
Geant4GM::Placement::Placement(const Placement& rhs) 
  : VGM::IPlacement(rhs),
    BaseVGM::VPlacement(rhs) 
{
/// Protected copy constructor
}

//_____________________________________________________________________________
Geant4GM::Placement::~Placement() {
//
}

//
// static public functions
//

//_____________________________________________________________________________
EAxis 
Geant4GM::Placement::GetAxis(VGM::Axis axis)
{
  switch (axis) {
    case VGM::kXAxis:    return kXAxis;    break;
    case VGM::kYAxis:    return kYAxis;    break;
    case VGM::kZAxis:    return kZAxis;    break;
    case VGM::kRho:      return kRho;      break;
    case VGM::kRadial3D: return kRadial3D; break;
    case VGM::kPhi:      return kPhi;      break;
    case VGM::kUnknownAxis: return kUndefined; break;
    default:                return kUndefined; break;
  }  
}    

//_____________________________________________________________________________
VGM::Axis 
Geant4GM::Placement::GetAxis(EAxis axis)
{
  switch (axis) {
    case kXAxis:     return VGM::kXAxis;    break;
    case kYAxis:     return VGM::kYAxis;    break;
    case kZAxis:     return VGM::kZAxis;    break;
    case kRho:       return VGM::kRho;      break;
    case kRadial3D:  return VGM::kRadial3D; break;
    case kPhi:       return VGM::kPhi;      break;
    case kUndefined: return VGM::kUnknownAxis; break;
    default:         return VGM::kUnknownAxis; break;
  }  
}    

//
// public functions
//

//_____________________________________________________________________________
VGM::PlacementType 
Geant4GM::Placement::Type() const
{
  // TO DO: add check for general parameterised volume
         // return VGM::kUnknownPlacement;
         // not yet supported
  
  if (fPhysicalVolume->IsParameterised() || fPhysicalVolume->IsReplicated())  
    return VGM::kMultiplePlacement;
  
  return VGM::kSimplePlacement;
}

//_____________________________________________________________________________
std::string   Geant4GM::Placement::Name() const
{
//
  return fPhysicalVolume->GetName();
}  

//_____________________________________________________________________________
int Geant4GM::Placement::CopyNo() const
{
//
  return fPhysicalVolume->GetCopyNo();
}  

//_____________________________________________________________________________
VGM::Transform 
Geant4GM::Placement::Transformation() const
{
//
  return  ClhepVGM::Transform(*fPhysicalVolume->GetObjectRotation(),
                               fPhysicalVolume->GetObjectTranslation());
  
}  
    
//_____________________________________________________________________________
bool Geant4GM::Placement::MultiplePlacementData(
                                VGM::Axis&  axis,
                                int&     nofItems,
                                double&  width,
                                double&  offset) const
{
  // Fill data only if multiple placement
  if (Type() != VGM::kMultiplePlacement) return false;
    
  // Different get functions for PVReplica and PVDivisions
  //
  EAxis g4Axis;
  if (dynamic_cast<G4PVReplica*>(fPhysicalVolume)) {
    bool consuming;
  
    G4double offset0;
    fPhysicalVolume->GetReplicationData(
                       g4Axis, nofItems, width, offset0, consuming);

    // Different meaning of offset in R/Phi division
    // for replica than for division:
    // the offset includes start value (rmin, sphi)

    G4double xlo = 0.;
    VGM::ISolid* solid = Volume()->Solid();
    
    if (g4Axis == kRho) {
 	if (solid->Type() == VGM::kTubs)
	   xlo = dynamic_cast<VGM::ITubs*>(solid)->InnerRadius();
    }	   
	 
    if (g4Axis == kPhi) {
         // Different meaning of offset in R/Phi division
         // for replica than for division:
	 // the offset includes start value (rmin, sphi)
	 
 	if (solid->Type() == VGM::kCons)
	   xlo = dynamic_cast<VGM::ICons*>(solid)->StartPhi();
 
 	if (solid->Type() == VGM::kTubs)
	   xlo = dynamic_cast<VGM::ITubs*>(solid)->StartPhi();

 	if (solid->Type() == VGM::kPolycone)
	   xlo = dynamic_cast<VGM::IPolycone*>(solid)->StartPhi();
	
 	if (solid->Type() == VGM::kPolyhedra)
	   xlo = dynamic_cast<VGM::IPolyhedra*>(solid)->StartPhi();
    }
    
    offset = offset0 - xlo;		       
  }
  else if (dynamic_cast<G4PVDivision*>(fPhysicalVolume)) {
    G4VDivisionParameterisation* param
      = dynamic_cast<G4VDivisionParameterisation*>(
          fPhysicalVolume->GetParameterisation());
	  
    if (!param) {
      std::cerr << "    Geant4GM::Placement::MultiplePlacementData: " << std::endl; 
      std::cerr << "    Incorrect parameterisation type for G4PVDivision" 
                 << std::endl; 
      std::cerr << "    (G4VDivisionParameterisation type was expected.)"  
                << std::endl; 
      std::cerr << "*** Error: Aborting execution  ***" << std::endl; 
      exit(1);
    }
    
    g4Axis = param->GetAxis();
    nofItems = param->GetNoDiv();
    width =  param->GetWidth();
    offset = param->GetOffset();
  }  

  axis = GetAxis(g4Axis);

  // Convert units
  offset *= ClhepVGM::Units::AxisUnit(axis);
  width  *= ClhepVGM::Units::AxisUnit(axis);

  return true;
}


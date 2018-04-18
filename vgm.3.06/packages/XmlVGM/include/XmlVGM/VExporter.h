// $Id: VExporter.h 634 2008-11-20 13:28:44Z ihrivnac $

// -----------------------------------------------------------------------
// The XmlVGM package of the Virtual Geometry Model
// Copyright (C) 2007, Ivana Hrivnacova               
// All rights reserved. 
//           
// For the licensing terms see vgm/LICENSE.
// Contact: ivana@ipno.in2p3.fr
// -----------------------------------------------------------------------

/// \ingroup XmlVGM
//
/// \class XmlVGM::VExporter
///
/// Class for generation of geometry data files in XML,
/// the XML format is independent from the geometry object model. 
/// It has one abstract method for processing the volume tree
/// that has to be provided by derived classes.
///
/// \author I. Hrivnacova, 19.1.2004

#ifndef XML_VGM_V_EXPORTER_H
#define XML_VGM_V_EXPORTER_H

#include "XmlVGM/Maps.h"

#include <fstream>
#include <string>
#include <set>
#include <map>

namespace VGM {
  class IElement;
  class IMaterial;
  class ISolid;
  class IFactory;
  class IVolume;
}

namespace XmlVGM {

  typedef std::vector<double> ThreeVector;

  class IWriter;
  
  class VExporter
  {
    public:
      typedef std::set <std::string, 
                        std::less<std::string> >  StringSet; 

    public:
      VExporter(const VGM::IFactory* factory,
                IWriter* writer);
      // --> protected
      // VExporter();
      // VExporter(const VExporter& right);
      virtual ~VExporter();
 
      // methods
      void GenerateXMLGeometry();
      void GenerateXMLGeometry(const std::string& volumeName);

      // set methods
      void SetFileName(const std::string& fileName);
      void SetDebug(int debug);
      void SetNumWidth(int width);
      void SetNumPrecision(int precision);

      // get methods
      std::string FileName() const;
      int  Debug() const;

    protected:
      VExporter();
      VExporter(const VExporter& right);

      // operators
      VExporter& operator=(const VExporter& /*right*/);

      // abstract methods
      // specific to XML definition
      //
                  /// Generate XML geometry file for the geometry tree 
                  /// starting from the specified VGM volume
     virtual void GenerateGeometry(VGM::IVolume* volume) = 0;

      // methods
      //
      void GeneratePositions(VGM::IVolume* volume);
      void GenerateRotations(VGM::IVolume* volume);
      void GenerateScale();
      void GenerateMaterials(VGM::IVolume* volume);
      void GenerateMedia(VGM::IVolume* volume);
      void GenerateSolids(VGM::IVolume* volume);

      void ClearVolumeNames();
      
      // static data members
      static const std::string fgkUndefinedFileName; //default value of file name
                                     
      // data members
      //
      const VGM::IFactory*  fFactory; // VGM factory 
      IWriter*       fWriter;         // interface to XML writer 
      std::string    fFileName;       // output file name
      StringSet      fVolumeNames;    // set of volume names
      int            fDebug;          // debug level
      Maps           fMaps; // maps between XML elements and their names

    private:
      // methods
      //
      void ProcessPositions(VGM::IVolume* volume); 
      void ProcessPositionsInBoolean(VGM::ISolid* solid); 
      void ProcessPositionsInTessellated(VGM::ISolid* solid); 

      void ProcessRotations(VGM::IVolume* volume); 
      void ProcessRotationsInBoolean(VGM::ISolid* solid); 

      void ProcessMaterials(VGM::IVolume* volume); 
      void ProcessMedia(VGM::IVolume* volume); 
      void ProcessSolids(VGM::IVolume* volume); 
  };
}

// inline methods

inline void XmlVGM::VExporter::SetFileName(const std::string& fileName)
{ /// Set the XML file name
  fFileName = fileName; }

inline void XmlVGM::VExporter::SetDebug(int debug)
{ /// Set the debug level
  fDebug = debug; }

inline std::string XmlVGM::VExporter::FileName() const
{ /// Return the XML file name
  return fFileName; }

inline int XmlVGM::VExporter::Debug() const
{ /// Return the debug level
  return fDebug; }

#endif //XML_VGM_V_EXPORTER_H


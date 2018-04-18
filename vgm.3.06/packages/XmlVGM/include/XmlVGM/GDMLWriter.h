// $Id: GDMLWriter.h 693 2011-01-11 14:41:39Z ihrivnac $

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
/// \class XmlVGM::GDMLWriter
///
/// The implementation of the interface for the XML writer that
/// writes VGM geometry objects to XML defined by GDML scheme.
///
/// \author I. Hrivnacova, 31.03.2004 

#ifndef XML_VGM_GDML_WRITER_H
#define XML_VGM_GDML_WRITER_H

#include "XmlVGM/IWriter.h"

#include <fstream>
#include <vector>
#include <set>

namespace VGM {
  class ISolid;
  class IBooleanSolid;
  class IArb8;
  class IBox;
  class IBox;
  class ICons;
  class ICtubs;
  class IEllipsoid;
  class IEllipticalTube;
  class IExtrudedSolid;
  class IHype;
  class IPara;
  class IParaboloid;
  class IPolycone;
  class IPolyhedra;
  class ISphere;
  class ITessellatedSolid;
  class ITorus;
  class ITrap;
  class ITrd;
  class ITubs;
  class IMaterial;
  class IElement;
  class IVolume;
  class IPlacement;
}  

namespace XmlVGM {

  class Maps;

  class GDMLWriter : public virtual IWriter
  {
    public:
      GDMLWriter(const std::string& unitName = "unit1", 
                 const std::string& version = "1.0"); 
      virtual ~GDMLWriter();

      // methods

      // XML elements 
      //
      virtual void OpenFile(std::string filePath);
      virtual void OpenDocument();
      virtual void OpenSection(const std::string& topVolume);
      virtual void OpenPositions(); 
      virtual void OpenRotations();       
      virtual void OpenMaterials();
      virtual void OpenMedia() {} 
      virtual void OpenSolids(); 
      virtual void OpenStructure(); 
      virtual void OpenComposition(const std::string& name,
                                   const std::string& materialName);

      virtual void CloseFile();
      virtual void CloseDocument();
      virtual void CloseSection(const std::string& topVolume);
      virtual void ClosePositions();
      virtual void CloseRotations();
      virtual void CloseMaterials();
      virtual void CloseMedia() {}
      virtual void CloseSolids();
      virtual void CloseStructure();
      virtual void CloseComposition();

      // Geometry elements
      //
      virtual void WriteIsotope(const VGM::IIsotope* isotope);

      virtual void WriteElement(const VGM::IElement* element); 
      
      virtual void WriteMaterial(const VGM::IMaterial* material); 

      virtual void WriteMedium(const VGM::IMedium* /*medium*/) {} 
      virtual void WriteMedium(const VGM::IMaterial* /*material*/) {} 
      
      virtual void WriteSolid(
                            std::string lvName, 
                            const VGM::ISolid* solid, 
                            std::string /*mediumName*/);
			     
      virtual void WritePosition(
                            const std::string& name, 
                            const VGM::Transform& transform); 
			    
      virtual void WriteRotation(
                            const std::string& name, 
                            const VGM::Transform& transform); 

      virtual void WriteScale(
                            const std::string& name); 

      virtual void WritePlacement(
                            const VGM::IPlacement& placement); 

      // Formatting utilities
      //
      virtual void WriteEmptyLine();
      virtual void IncreaseIndention();
      virtual void DecreaseIndention();
      
      // Units
      //
      virtual double LengthUnit() const;
      virtual double AngleUnit() const;
      virtual double AtomicWeightUnit() const;
      virtual double MassDensityUnit() const;
      virtual double TemperatureUnit() const;
      virtual double PressureUnit() const;

      // Set methods
      //
      virtual void SetMaps(Maps* maps);
      virtual void SetNumWidth(int width);
      virtual void SetNumPrecision(int precision);

      // Get methods
      //
      virtual double GetNumWidth() const;
      virtual double GetNumPrecision() const;

    protected:
       GDMLWriter(const GDMLWriter& rhs); 

    private:
      // types
      //
      typedef std::set <std::string, std::less<std::string> > StringSet; 

      // Utility methods
      //
      double UpdateAngle(double angle) const;
      void RegisterName(const std::string& name, bool warning = true);
    
      // Writing solids
      //
      void WriteBooleanSolid(
                     std::string name, const VGM::IBooleanSolid* solid);  
      void WriteBox (std::string lvName, 
                     double hx, double hy, double hz);
      void WriteArb8(std::string name, const VGM::IArb8* arb8);  
      void WriteBox (std::string name, const VGM::IBox*  box);  
      void WriteCons(std::string name, const VGM::ICons* cons); 
      void WriteCtubs(std::string name, const VGM::ICtubs* ctubs); 
      void WriteEllipsoid(std::string name, 
                     const VGM::IEllipsoid* ellipsoid); 
      void WriteEllipticalTube(std::string name, 
                     const VGM::IEllipticalTube* eltu); 
      void WriteExtrudedSolid(std::string name, 
                     const VGM::IExtrudedSolid* extruded); 
      void WriteHype(std::string name, const VGM::IHype* hype); 
      void WritePara(std::string name, const VGM::IPara* para); 
      void WriteParaboloid(std::string name, const VGM::IParaboloid* paraboloid); 
      void WritePolycone(std::string name, const VGM::IPolycone* polycone); 
      void WritePolyhedra(std::string name, const VGM::IPolyhedra* polyhedra); 
      void WriteSphere(std::string name, const VGM::ISphere* sphere); 
      void WriteTessellatedSolid(std::string name, 
                     const VGM::ITessellatedSolid* tessellated); 
      void WriteTorus(std::string name, const VGM::ITorus* torus); 
      void WriteTrap(std::string name, const VGM::ITrap* trap); 
      void WriteTrd (std::string name, const VGM::ITrd*  trd);  
      void WriteTubs(std::string name, const VGM::ITubs* tubs); 
      void WriteNotSupportedSolid(std::string name); 
  
      // Writing placements
      //
      virtual void WriteSimplePlacement(
                            const std::string& lvName, 
			    const std::string& positionRef,
			    const std::string& rotationRef,
                            bool isReflection);
			     
      virtual void WriteMultiplePlacement(
                            const std::string& lvName,
                            VGM::Axis axis, int nofReplicas, 
			    double width, double offset);			       

      // static data members
      //
      static const int          fgkDefaultNumWidth;     //default output numbers width
      static const int          fgkDefaultNumPrecision; //default output numbers precision 
      static const std::string  fgkSolidNameExtension;  //solid names extension 
      static const std::string  fgkIsotopeNameExtension;//isotope names extension 
      static const std::string  fgkElementNameExtension;//element names extension 
      static const char         fgkCharReplacement;     //replacement for ' ' in names 
      static const std::string  fgkNotAllowedChars;     //not allowed characters in XML
      static const std::string  fgkNotAllowedChars1;    //not allowed first characters
                                                        //in XML names
      static const double       fgkSTPTemperature; /// STP temperature                                                        
      static const double       fgkSTPPressure;    /// STP pressure   
      static const double       fgkCarTolerance;   /// length tolerance                                                     
      static const double       fgkAngTolerance;   /// angle tolerance                                                     

      // data members
      //
      std::ofstream      fOutFile;          //output file
      std::string        fUnitName;         //unit name
      std::string        fVersion;          //geometry version
      const std::string  fkBasicIndention;  //basic indention 
      std::string        fIndention;        //indention string
      int                fNW;               //output numbers width
      int                fNP;               //output numbers precision 
      StringSet          fGDMLNames;        //names in GDML 
      Maps*              fMaps;             //name maps
      bool               fFullLengths;      //full lengths in solids
  };

}

inline double XmlVGM::GDMLWriter::LengthUnit() const
{ return 10.; }    // cm

inline double XmlVGM::GDMLWriter::AngleUnit() const
{ return  1.; }    // deg

inline double XmlVGM::GDMLWriter::AtomicWeightUnit() const
{ return  1.; }   // g/mole

inline double XmlVGM::GDMLWriter::MassDensityUnit() const
{ return  1.; }   // g/cm3
 
inline double XmlVGM::GDMLWriter::TemperatureUnit() const
{ return  1.; }   // kelvin

inline double XmlVGM::GDMLWriter::PressureUnit() const
{ return  1./101325.0; }   // pascal 

inline void XmlVGM::GDMLWriter::SetMaps(Maps* maps)
{ /// Set the name maps
  fMaps = maps; }

inline void XmlVGM::GDMLWriter::SetNumWidth(int width)
{ fNW = width; }

inline void XmlVGM::GDMLWriter::SetNumPrecision(int precision)
{ fNP = precision; }

inline double XmlVGM::GDMLWriter::GetNumWidth() const
{ return fNW; }

inline double XmlVGM::GDMLWriter::GetNumPrecision() const
{ return fNP; }

#endif //XML_VGM_GDML_WRITER_H


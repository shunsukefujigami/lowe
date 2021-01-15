#ifndef HITINFO_HH
#define HITINFO_HH
// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// WCSim library
#include "WCSimRootGeom.hh"
#include "WCSimRootEvent.hh"

class hitinfo
{
public:
  hitinfo()
  {
  }
  virtual ~hitinfo()
  {
  }
  hitinfo& operator=(const hitinfo& info)
  {
    hittime = info.HitTime();
    pmtposition = info.Get3Position();
    pmtdirection = info.Get3Orientation();
    WCradius = info.GetWCradius();
    WClength = info.GetWClength();

    return *this;
  }
  
  void Sethit(WCSimRootCherenkovDigiHit* h,WCSimRootGeom* wcsimrootgeom)
  {
    int tubeId = h->GetTubeId();
    hittime = h->GetT();
    WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId-1);
    pmtposition.setX(pmt.GetPosition(0));
    pmtposition.setY(pmt.GetPosition(1));
    pmtposition.setZ(pmt.GetPosition(2));
    pmtdirection.setX(pmt.GetOrientation(0));
    pmtdirection.setY(pmt.GetOrientation(1));
    pmtdirection.setZ(pmt.GetOrientation(2));
    WCradius = wcsimrootgeom->GetWCCylRadius();
    WClength = wcsimrootgeom->GetWCCylLength();
    
  }
  CLHEP::Hep3Vector Get3Position() const
  {
    return pmtposition;
  }
  CLHEP::Hep3Vector Get3Orientation() const
  {
    return pmtdirection;
  }
  double HitTime() const
  {
    return hittime;
  }
  double GetWCradius() const 
  {
    return WCradius;
  }
  double GetWClength() const 
  {
    return WClength;
  }
  
  
private:
  double hittime;
  CLHEP::Hep3Vector pmtposition;
  CLHEP::Hep3Vector pmtdirection;
  double WCradius;
  double WClength;
};

#endif

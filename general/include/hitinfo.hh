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
  void Sethit(WCSimRootCherenkovDigiHit* h,WCSimRootGeom* wcsimrootgeom)
  {
    hit = h;
    int tubeId = hit->GetTubeId();
    pmt = wcsimrootgeom->GetPMT(tubeId-1);
    WCradius = wcsimrootgeom->GetWCCylRadius();
    WClength = wcsimrootgeom->GetWCCylLength();
    
  }
  double GetPosition(int i)
  {
    return pmt.GetPosition(i);
  }
  CLHEP::Hep3Vector Get3Position()
  {
    double pmtX = GetPosition(0);
    double pmtY = GetPosition(1);
    double pmtZ = GetPosition(2);
    CLHEP::Hep3Vector vector(pmtX,pmtY,pmtZ);
    return vector;
  }
  double GetOrientation(int i)
  {
    return pmt.GetOrientation(i);
  }
  CLHEP::Hep3Vector Get3Orientation()
  {
    double orientX = GetOrientation(0);
    double orientY = GetOrientation(1);
    double orientZ = GetOrientation(2);
    CLHEP::Hep3Vector vector(orientX,orientY,orientZ);
    return vector;
  }
  double HitTime()
  {
    return hit->GetT();
  }
  double GetWCradius()
  {
    return WCradius;
  }
  double GetWClength()
  {
    return WClength;
  }
  
  
private:
  WCSimRootCherenkovDigiHit* hit;
  WCSimRootPMT pmt;
  double WCradius;
  double WClength;
};

#endif

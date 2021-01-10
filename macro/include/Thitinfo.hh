#ifndef THITINFO_HH
#define THITINFO_HH
// ROOT library
#include <TObject.h>
#include <TVector3.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

class Thitinfo : public TObject
{
public:
  Thitinfo();
  virtual ~Thitinfo()
  {
  }
  void Sethit(WCSimRootCherenkovDigiHit* hit,WCSimRootGeom* wcsimrootgeom)
  {
    hittime = hit->GetT();
    int tubeId = hit->GetTubeId();
    pmt = wcsimrootgeom->GetPMT(tubeId-1);
    WCradius = wcsimrootgeom->GetWCCylRadius();
    WClength = wcsimrootgeom->GetWCCylLength();
  }
  double GetPosition(int i)
  {
    return pmt.GetPosition(i);
  }
  TVector3 Get3Position()
  {
    double pmtX = GetPosition(0);
    double pmtY = GetPosition(1);
    double pmtZ = GetPosition(2);
    TVector3 vector(pmtX,pmtY,pmtZ);
    return vector;
  }
  double GetOrientation(int i)
  {
    return pmt.GetOrientation(i);
  }
  TVector3 Get3Orientation()
  {
    double orientX = GetOrientation(0);
    double orientY = GetOrientation(1);
    double orientZ = GetOrientation(2);
    TVector3 vector(orientX,orientY,orientZ);
    return vector;
  }
  double HitTime()
  {
    return hittime;
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
  WCSimRootPMT pmt;
  double WCradius;
  double WClength;
  double hittime;
public:
  ClassDef(Thitinfo,1)
};

#endif

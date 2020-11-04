// ROOT library
#include <TVector3.h>

// WCSim library
#include "WCSimRootGeom.hh"

double theta_i_func(WCSimRootPMT pmt,TVector3 hminusv){
  double orientX = pmt.GetOrientation(0);
  double orientY = pmt.GetOrientation(1);
  double orientZ = pmt.GetOrientation(2);
  TVector3 orientation(orientX,orientY,orientZ);
  return orientation.Angle(-hminusv);
}

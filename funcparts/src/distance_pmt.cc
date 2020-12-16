#include <memory>
#include <math.h>
#include <TVector3.h>
#include "WCSimRootGeom.hh"
#include "runoption.hh"

double distance_position_pmt(TVector3 position ,TVector3 pmtposition){
  double d1 = sqrt((pmtposition-position)*(pmtposition-position));
 return d1;
}

double distance_retro_pmt(TVector3 position,TVector3 pmtposition,std::shared_ptr<runoption> option){
 double positionX = position.X();
 double positionY = position.Y();
 double positionZ = position.Z();
 double pmtX = pmtposition.X();
 double pmtY = pmtposition.Y();
 double pmtZ = pmtposition.Z();
 double WCradius = option->wcsimrootgeom->GetWCCylRadius();
 double WClength = option->wcsimrootgeom->GetWCCylLength();
 double half_WClength = WClength/2.;
  double a = (pmtX-positionX)*(pmtX-positionX)+(pmtY-positionY)*(pmtY-positionY);
  double b = positionX*(positionX-pmtX)+positionY*(positionY-pmtY);
  double c = positionX*positionX+positionY*positionY-WCradius*WCradius;
  double t;
  if(a != 0){
    t = (b-sqrt(b*b-a*c))/a;
  }
  else{
    t = -c/(2*b);
  }
  double z = positionZ + (pmtZ - positionZ)*t;
  if(-half_WClength < z && half_WClength > z){

}
  else if(z > half_WClength){
    t = (half_WClength - positionX)/(pmtZ-position[0]);
    z = half_WClength;
  }
  else{
    t = (-half_WClength - positionX)/(pmtZ-positionX);
    z = - half_WClength;
  }
  double x = positionX + (pmtX-positionX)*t;
  double y = positionY + (pmtY-positionY)*t;
  double d2 = sqrt((pmtX-x)*(pmtX-x)+(pmtY-y)*(pmtY-y)+(pmtZ-z)*(pmtZ-z));
  return d2;
}

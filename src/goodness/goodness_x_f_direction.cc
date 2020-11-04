// c++ STL
#include <memory>
#include <cmath>
// ROOT library
#include <TLorentzVector.h>
#include <TVector3.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self-introduced library
#include "runoption.hh"
double goodness_x_f_direction_noretro(TLorentzVector vector,double costheta,double phi,std::shared_ptr<runoption> option)
{
  int ncherenkovdigihits = option->wcsimroottrigger->GetNcherenkovdigihits();
  double g_x_f = 0;
  double sintheta = std::sqrt(1-costheta*costheta);
  double x = sintheta*std::cos(phi);
  double y = sintheta*std::sin(phi);
  double z = costheta;
  TVector3 dvec(x,y,z);
  for( int k = 0 ;k < ncherenkovdigihits ; ++k ){
    WCSimRootCherenkovDigiHit* hit =(WCSimRootCherenkovDigiHit*)((option->wcsimroottrigger->GetCherenkovDigiHits())->At(k));
    double time = hit->GetT();
    int tubeId = hit->GetTubeId();
    WCSimRootPMT pmt = option->wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    TVector3 pmt_position(pmtX,pmtY,pmtZ);
    TVector3 hminusv = pmt_position - vector.Vect();
    double theta_dir_i = dvec.Angle(hminusv);
    g_x_f += (option->ogfunc_noretro)(vector,pmt_position,time,option) * (option->f_dirfunc_noretro)(std::cos(theta_dir_i),option);
  }
  return g_x_f;
}

double goodness_x_f_direction_onretro(TLorentzVector vector,double costheta,double phi,std::shared_ptr<runoption> option)
{
  int ncherenkovdigihits = option->wcsimroottrigger->GetNcherenkovdigihits();
  double g_x_f = 0;
  double sintheta = std::sqrt(1-costheta*costheta);
  double x = sintheta*std::cos(phi);
  double y = sintheta*std::sin(phi);
  double z = costheta;
  TVector3 dvec(x,y,z);
  for( int k = 0 ;k < ncherenkovdigihits ; ++k ){
    WCSimRootCherenkovDigiHit* hit =(WCSimRootCherenkovDigiHit*)((option->wcsimroottrigger->GetCherenkovDigiHits())->At(k));
    double time = hit->GetT();
    int tubeId = hit->GetTubeId();
    WCSimRootPMT pmt = option->wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    TVector3 pmt_position(pmtX,pmtY,pmtZ);
    TVector3 hminusv = pmt_position - vector.Vect();
    double theta_dir_i = dvec.Angle(hminusv);
    g_x_f += (option->ogfunc_onretro)(vector,pmt_position,time,option) * (option->f_dirfunc_onretro)(std::cos(theta_dir_i),option);
  }
  return g_x_f;
}

double goodness_x_f_direction_sum(TLorentzVector vector,double costheta,double phi,std::shared_ptr<runoption> option){
  return goodness_x_f_direction_noretro(vector,costheta,phi,option) + goodness_x_f_direction_onretro(vector,costheta,phi,option);
}

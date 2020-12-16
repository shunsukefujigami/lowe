// c++ STL
#include <memory>
#include <iostream>

// ROOT library
#include <TLorentzVector.h>
#include <TVector3.h>

// WCSim library
#include "WCSimRootEvent.hh"

// self-introduced library
#include "runoption.hh"
#include "theta_i_func.hh"
#include "distance_pmt.hh"
#include "tof.hh"
#include "constants.hh"

double likelihood_direction_noretro(TLorentzVector fitted4Vector,double costheta,double phi,std::shared_ptr<runoption> option){
  int ncherenkovdigihits = option->wcsimroottrigger->GetNcherenkovdigihits();
  double likelihood = 0.;
  double sintheta = std::sqrt(1-costheta*costheta);
  double x = sintheta*std::cos(phi);
  double y = sintheta*std::sin(phi);
  double z = costheta;
  TVector3 dvec(x,y,z);
  for( int k = 0;k < ncherenkovdigihits;++k){
    WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((option->wcsimroottrigger->GetCherenkovDigiHits())->At(k));
    double time = hit->GetT();
    int tubeId = hit->GetTubeId();
    WCSimRootPMT pmt = option->wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    TVector3 pmt_position(pmtX,pmtY,pmtZ); 
    TVector3 hminusv = pmt_position - fitted4Vector.Vect();
    double theta_dir_i = dvec.Angle(hminusv);
    double theta_i = theta_i_func(pmt,hminusv);
    if(costheta == 0. && phi == 0.){
      std::cout << "theta_dir_i : " << theta_dir_i*180./PI << " , theta_i :" << theta_i*180./PI << std::endl;
    }
    double d1 = distance_position_pmt(fitted4Vector.Vect(),pmt_position);
    double toferror = tof(time-option->offset,d1) - fitted4Vector.T();
    if(toferror > -20. && toferror < 20.){
      likelihood += (std::log((option->f_dirfunc_noretro)(std::cos(theta_dir_i))) * std::cos(theta_i)/((option->afunc)()));
    }
  }
 return likelihood;
}

double likelihood_direction_onretro(TLorentzVector fitted4Vector,double costheta,double phi,std::shared_ptr<runoption> option){
  int ncherenkovdigihits = option->wcsimroottrigger->GetNcherenkovdigihits();
  double likelihood = 0.;
  double sintheta = std::sqrt(1-costheta*costheta);
  double x = sintheta*std::cos(phi);
  double y = sintheta*std::sin(phi);
  double z = costheta;
  TVector3 dvec(x,y,z);
  for( int k = 0;k < ncherenkovdigihits;++k){
    WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((option->wcsimroottrigger->GetCherenkovDigiHits())->At(k));
    double time = hit->GetT();
    int tubeId = hit->GetTubeId();
    WCSimRootPMT pmt = option->wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    TVector3 pmt_position(pmtX,pmtY,pmtZ); 
    TVector3 hminusv = pmt_position - fitted4Vector.Vect();
    double theta_dir_i = dvec.Angle(hminusv);
    double theta_i = theta_i_func(pmt,hminusv);
   if(costheta == 0. && phi == 0.)
     std::cout << "theta_dir_i : " << theta_dir_i*180./PI << " , theta_i :" << theta_i*180./PI << std::endl;
    double d1 = distance_position_pmt(fitted4Vector.Vect(),pmt_position);
    double d2 = distance_retro_pmt(fitted4Vector.Vect(),pmt_position,option);
    double toferror = tof(time-option->offset,2*d2-d1) - fitted4Vector.T();
    if(toferror > -20. && toferror < 20.){
      likelihood += (std::log((option->f_dirfunc_onretro)(std::cos(theta_dir_i))) * std::cos(theta_i)/((option->afunc)()));
    }
  }
 return likelihood;
}

double likelihood_direction_sum(TLorentzVector fitted4Vector,double costheta,double phi,std::shared_ptr<runoption> option){
  return ( likelihood_direction_noretro(fitted4Vector,costheta,phi,option) + likelihood_direction_onretro(fitted4Vector,costheta,phi,option));
}


// c++ STL
#include <memory>

// ROOT library
#include <TVector3.h>
#include <TLorentzVector.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "runoption.hh"
#include "distance_pmt.hh"
#include "tof.hh"

int numberofhit_noretro(TLorentzVector fitted4Vector,std::shared_ptr<runoption> option){
  int N = 0;
  int ncherenkovdigihits = option->wcsimroottrigger->GetNcherenkovdigihits();
  for(int k = 0;k < ncherenkovdigihits;k++){
    WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((option->wcsimroottrigger->GetCherenkovDigiHits())->At(k));
    double time = hit->GetT();
    int tubeId = hit->GetTubeId();
    WCSimRootPMT pmt = option->wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    TVector3 pmt_position(pmtX,pmtY,pmtZ);
    double d1 = distance_position_pmt(fitted4Vector.Vect(),pmt_position);
    double toferror = tof(time-option->offset,d1) - fitted4Vector.T();
    if(toferror > -20. && toferror < 20.)
      N++;
  }
  return N;
}

int numberofhit_onretro(TLorentzVector fitted4Vector,std::shared_ptr<runoption> option){
  int N = 0;
  int ncherenkovdigihits = option->wcsimroottrigger->GetNcherenkovdigihits();
  for(int k = 0;k < ncherenkovdigihits;k++){
    WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)((option->wcsimroottrigger->GetCherenkovDigiHits())->At(k));
    double time = hit->GetT();
    int tubeId = hit->GetTubeId();
    WCSimRootPMT pmt = option->wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    TVector3 pmt_position(pmtX,pmtY,pmtZ);
    double d1 = distance_position_pmt(fitted4Vector.Vect(),pmt_position);
    double d2 = distance_retro_pmt(fitted4Vector.Vect(),pmt_position,option);
    double toferror = tof(time-option->offset,2*d2-d1) - fitted4Vector.T();
    if(toferror > -20. && toferror < 20.)
      N++;
  }
  return N;
}

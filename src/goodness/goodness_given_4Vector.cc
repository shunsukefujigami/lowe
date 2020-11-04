// C++ STL
#include <memory>

// ROOT library
#include <TSystem.h>
#include <TLorentzVector.h>
#include <TVector3.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "runoption.hh"

double goodness_given_4Vector(TLorentzVector vector,std::shared_ptr<runoption> option){
  int ncherenkovdigihits = option->wcsimroottrigger->GetNcherenkovdigihits();
  double goodness = 0.;
  for( int k = 0 ;k < ncherenkovdigihits ; ++k ){
    WCSimRootCherenkovDigiHit* hit =(WCSimRootCherenkovDigiHit*)((option->wcsimroottrigger->GetCherenkovDigiHits())->At(k));
    double time = hit->GetT();
    int tubeId = hit->GetTubeId();
    WCSimRootPMT pmt = option->wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    TVector3 pmt_position(pmtX,pmtY,pmtZ);
    auto ogfunc = option->ogfunc;
    goodness += ogfunc(vector,pmt_position,time,option);
  }
  return goodness;
}


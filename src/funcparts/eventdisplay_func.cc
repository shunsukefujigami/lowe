// c++ STL
#include <memory>
#include <cmath>
#include <vector>

// ROOT library
#include <TH2D.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "constants.hh"

void eventdisplay_plot(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom){
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  double WCradius = wcsimrootgeom->GetWCCylRadius();
  double WClength = wcsimrootgeom->GetWCCylLength();
  for(int k=0;k<ncherenkovdigihits;++k){
    //    std::unique_ptr<WCSimRootCherenkovDigiHit> hit {(WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k))};
    const WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
    int tubeId = hit->GetTubeId();
    WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    double pmtS = -WCradius*std::atan2(pmtY,pmtX);
    if((pmt.GetCylLoc()) == 0){
      h_hit->Fill(-pmtY,-(pmtX)+WClength/2+WCradius);
    }
    else if((pmt.GetCylLoc()) == 1){
      h_hit->Fill(pmtS,pmtZ);
    }
    else{
      h_hit->Fill(-pmtY,pmtX-WClength/2-WCradius);
    }
  }
}

void eventdisplay_plot_dir(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,std::vector<int>* vhitdirorref){
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  double WCradius = wcsimrootgeom->GetWCCylRadius();
  double WClength = wcsimrootgeom->GetWCCylLength();
  for(int k=0;k<ncherenkovdigihits;++k){
    if(vhitdirorref->at(k) == 0){
      const WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      int tubeId = hit->GetTubeId();
      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId-1);
      double pmtX = pmt.GetPosition(0);
      double pmtY = pmt.GetPosition(1);
      double pmtZ = pmt.GetPosition(2);
      double pmtS = -WCradius*std::atan2(pmtY,pmtX);
      if((pmt.GetCylLoc()) == 0){
	h_hit->Fill(-pmtY,-(pmtX)+WClength/2+WCradius);
      }
      else if((pmt.GetCylLoc()) == 1){
	h_hit->Fill(pmtS,pmtZ);
      }
      else{
	h_hit->Fill(-pmtY,pmtX-WClength/2-WCradius);
      }
    }
  }
}

void eventdisplay_plot_ref(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,std::vector<int>* vhitdirorref){
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  double WCradius = wcsimrootgeom->GetWCCylRadius();
  double WClength = wcsimrootgeom->GetWCCylLength();
  for(int k=0;k<ncherenkovdigihits;++k){
    if(vhitdirorref->at(k) == 1){
      const WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      int tubeId = hit->GetTubeId();
      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId-1);
      double pmtX = pmt.GetPosition(0);
      double pmtY = pmt.GetPosition(1);
      double pmtZ = pmt.GetPosition(2);
      double pmtS = -WCradius*std::atan2(pmtY,pmtX);
      if((pmt.GetCylLoc()) == 0){
	h_hit->Fill(-pmtY,-(pmtX)+WClength/2+WCradius);
      }
      else if((pmt.GetCylLoc()) == 1){
	h_hit->Fill(pmtS,pmtZ);
      }
      else{
	h_hit->Fill(-pmtY,pmtX-WClength/2-WCradius);
      }
    }
  }
}

void eventdisplay_plot_dir_restrict(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,std::vector<int>* vhitdirorref,std::vector<double>* vhitgoodness){
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  double WCradius = wcsimrootgeom->GetWCCylRadius();
  double WClength = wcsimrootgeom->GetWCCylLength();
  for(int k=0;k<ncherenkovdigihits;++k){
    if((vhitdirorref->at(k) == 0) && (vhitgoodness->at(k) > 1./e)){
      const WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      int tubeId = hit->GetTubeId();
      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId-1);
      double pmtX = pmt.GetPosition(0);
      double pmtY = pmt.GetPosition(1);
      double pmtZ = pmt.GetPosition(2);
      double pmtS = -WCradius*std::atan2(pmtY,pmtX);
      if((pmt.GetCylLoc()) == 0){
	h_hit->Fill(-pmtY,-(pmtX)+WClength/2+WCradius);
      }
      else if((pmt.GetCylLoc()) == 1){
	h_hit->Fill(pmtS,pmtZ);
      }
      else{
	h_hit->Fill(-pmtY,pmtX-WClength/2-WCradius);
      }
    }
  }
}

void eventdisplay_plot_ref_restrict(TH2D* h_hit,WCSimRootTrigger* wcsimroottrigger,WCSimRootGeom* wcsimrootgeom,std::vector<int>* vhitdirorref,std::vector<double>* vhitgoodness){
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  double WCradius = wcsimrootgeom->GetWCCylRadius();
  double WClength = wcsimrootgeom->GetWCCylLength();
  for(int k=0;k<ncherenkovdigihits;++k){
    if((vhitdirorref->at(k) == 1) && (vhitgoodness->at(k) > 1./e)){
      const WCSimRootCherenkovDigiHit* hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      int tubeId = hit->GetTubeId();
      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId-1);
      double pmtX = pmt.GetPosition(0);
      double pmtY = pmt.GetPosition(1);
      double pmtZ = pmt.GetPosition(2);
      double pmtS = -WCradius*std::atan2(pmtY,pmtX);
      if((pmt.GetCylLoc()) == 0){
	h_hit->Fill(-pmtY,-(pmtX)+WClength/2+WCradius);
      }
      else if((pmt.GetCylLoc()) == 1){
	h_hit->Fill(pmtS,pmtZ);
      }
      else{
	h_hit->Fill(-pmtY,pmtX-WClength/2-WCradius);
      }
    }
  }
}

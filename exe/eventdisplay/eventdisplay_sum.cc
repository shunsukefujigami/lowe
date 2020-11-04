// c++ STL
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TArc.h>
#include <TPave.h>
#include <TCanvas.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduce library
#include "config.hh"
#include "eventdisplay_func.hh"
#include "constants.hh"


int main(){
  Config_eventdisplay_sum config;
  TFile* fin_g = new TFile(config.infile_goodness);
  TTree* tin_g = (TTree*)fin_g->Get(config.intree);
  TFile* fin_d = new TFile(config.infile_data);
  TTree* wcsimT = (TTree*)fin_d->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  TTree* wcsimGeoT = (TTree*)fin_d->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  double WCradius = wcsimrootgeom->GetWCCylRadius();
  double WClength = wcsimrootgeom->GetWCCylLength();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  std::vector<double> v_max_x;
  double max_x;
  tin_g->SetBranchAddress("max_x",&max_x);
  const int N = tin_g->GetEntries();
  for( int ientry = 0;ientry < N;++ientry){
    tin_g->GetEntry(ientry);
    v_max_x.push_back(max_x);
  }
  std::vector<bool> vb_max_x(v_max_x.size(),false);
  std::transform(v_max_x.begin(),v_max_x.end(),vb_max_x.begin(),[&v_max_x](double max_x){ return max_x == -1500. ;});
  TH2D* h_hit = new TH2D("hit","event display sum(hit);;",200,-PI*WCradius,PI*WCradius,200,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  int i = 0;
  for(auto vb_iter = vb_max_x.begin();vb_iter != vb_max_x.end();vb_iter++,i++){
    std::cout << i << std::endl;
    wcsimT->GetEntry(i);
    std::cout << i << std::endl;
    WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    if(*vb_iter){
      eventdisplay_plot(h_hit,wcsimroottrigger,wcsimrootgeom);
    }
  }
  std::unique_ptr<TArc> a1 { new TArc(0.,WCradius+WClength/2.,WCradius)};
  std::unique_ptr<TArc> a2 { new TArc(0.,-WCradius-WClength/2.,WCradius)};
  std::unique_ptr<TPave> p1 { new TPave(-PI*WCradius,-WClength/2.,PI*WCradius,WClength/2.)};
  a1->SetFillStyle(0);
  a2->SetFillStyle(0);
  p1->SetFillStyle(0);
  std::unique_ptr<TCanvas> c1 { new TCanvas("c1","c1")};
  h_hit->Draw("colz");
  a1->Draw("same");
  a2->Draw("same");
  p1->Draw("same");
  std::cout << config.outfile << std::endl;
  c1->SaveAs(config.outfile);
}

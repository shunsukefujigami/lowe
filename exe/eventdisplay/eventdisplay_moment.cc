// c++ STL
#include <vector>
#include <iostream>
#include <memory>

// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TArc.h>
#include <TPave.h>
#include <TCanvas.h>

// WCSim libarary
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"


// self-introduced libarary
#include "config.hh"
#include "eventdisplay_func.hh"
#include "constants.hh"

int main(){
  Config_eventdisplay_moment config;
  TFile* fin_g = new TFile(config.infile_goodness);
  TTree* tin_g = (TTree*)fin_g->Get(config.intree_goodness);
  std::vector<int>* vhitdirorref = 0;
  TBranch* bv = 0;
  tin_g->SetBranchAddress("vhitdirorref",&vhitdirorref,&bv);
  std::vector<double>* vhitgoodness = 0;
  TBranch* bvg = 0;
  tin_g->SetBranchAddress("vhitgoodness",&vhitgoodness,&bvg);
  tin_g->GetEntry(config.n_event);
  TFile* fin_d = new TFile(config.infile_data);
  TTree* wcsimGeoT = (TTree*)fin_d->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  TTree* wcsimT = (TTree*)fin_d->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetEntry(config.n_event);
  WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
  double R = wcsimrootgeom->GetWCCylRadius();
  double L = wcsimrootgeom->GetWCCylLength();
  TH2D* h_hit = new TH2D("h_hit","event display(hit);;",config.xbin,-PI*R,PI*R,config.ybin,-L/2-2*R,L/2+2*R);
  TH2D* h_hit_restrict = new TH2D("h_hit_restruct","event display(hit);;",config.xbin,-PI*R,PI*R,config.ybin,-L/2-2*R,L/2+2*R);
  eventdisplay_plot_dir(h_hit,wcsimroottrigger,wcsimrootgeom,vhitdirorref);
  eventdisplay_plot_dir(h_hit,wcsimroottrigger,wcsimrootgeom,vhitdirorref);
  eventdisplay_plot_ref(h_hit,wcsimroottrigger,wcsimrootgeom,vhitdirorref);
  eventdisplay_plot_dir_restrict(h_hit_restrict,wcsimroottrigger,wcsimrootgeom,vhitdirorref,vhitgoodness);
  eventdisplay_plot_dir_restrict(h_hit_restrict,wcsimroottrigger,wcsimrootgeom,vhitdirorref,vhitgoodness);
  eventdisplay_plot_ref_restrict(h_hit_restrict,wcsimroottrigger,wcsimrootgeom,vhitdirorref,vhitgoodness);
  std::unique_ptr<TArc> a1 { new TArc(0.,R+L/2.,R)};
  std::unique_ptr<TArc> a2 { new TArc(0.,-R-L/2.,R)};
  std::unique_ptr<TPave> p1 { new TPave(-PI*R,-L/2.,PI*R,L/2.)};
  a1->SetFillStyle(0);
  a2->SetFillStyle(0);
  p1->SetFillStyle(0);
  std::unique_ptr<TCanvas> c1 { new TCanvas("c1","c1")};
  h_hit->SetStats(0);
  h_hit->Draw("colz");
  a1->Draw("same");
  a2->Draw("same");
  p1->Draw("same");
  c1->Print(config.outfile);
  h_hit_restrict->SetStats(0);
  h_hit_restrict->Draw("colz");
  a1->Draw("same");
  a2->Draw("same");
  p1->Draw("same");
  c1->Print(config.outfile_restrict);

}

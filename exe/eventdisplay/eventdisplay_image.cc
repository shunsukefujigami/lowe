// c++ STL
#include <memory>
#include <iostream>

// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TArc.h>
#include <TPave.h>
#include <TCanvas.h>
#include <TH2D.h>

// WCSim library
#include "WCSimRootGeom.hh"

// self-introduced library
#include "config.hh"
#include "constants.hh"

int main(){
  Config_eventdisplay_image config;
  std::unique_ptr<TFile> fin { new TFile(config.infile)};
  TH2D* hin = (TH2D*)fin->Get(config.inhist);
  std::unique_ptr<TFile> fingeom { new TFile(config.infile_geom)};
  TTree* wcsimGeoT = (TTree*)fingeom->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  double R = wcsimrootgeom->GetWCCylRadius();
  double L = wcsimrootgeom->GetWCCylLength();
  std::cout << "R = " << R << std::endl;
  std::cout << "L = " << L << std::endl;
  std::unique_ptr<TArc> a1 { new TArc(0.,R+L/2.,R)};
  std::unique_ptr<TArc> a2 { new TArc(0.,-R-L/2.,R)};
  std::unique_ptr<TPave> p1 { new TPave(-PI*R,-L/2.,PI*R,L/2.)};
  a1->SetFillStyle(0);
  a2->SetFillStyle(0);
  p1->SetFillStyle(0);
  std::unique_ptr<TCanvas> c1 { new TCanvas("c1","c1")};
  hin->Draw("colz");
  a1->Draw("same");
  a2->Draw("same");
  p1->Draw("same");
  c1->SaveAs(config.outfile);
  delete wcsimrootgeom;
}

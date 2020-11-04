// c++ STL
#include <memory>
#include <cmath>

// ROOT library
#include <TVector3.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>

// WCSim library
#include "WCSimRootGeom.hh"

// self-introduced library
#include "distance_pmt.hh"
#include "config.hh"
#include "constants.hh"
#include "runoption.hh"


int main(){
  Config_distance_image config;
  std::unique_ptr<TH1D> hxnoretro { new TH1D("hxnoretro","distance_noretro;x(cm);distance(cm)",10000,-1500.,1500) };
  std::unique_ptr<TH1D> hynoretro { new TH1D("hynoretro","distance_noretro;y(cm);distance(cm)",10000,-1500.,1500) };
  std::unique_ptr<TH1D> hznoretro { new TH1D("hznoretro","distance_noretro;z(cm);distance(cm)",10000,-1500.,1500) };
  std::unique_ptr<TH1D> hxonretro { new TH1D("hxonretro","distance_onretro;x(cm);distance(cm)",10000,-1500.,1500) };
  std::unique_ptr<TH1D> hyonretro { new TH1D("hyonretro","distance_onretro;y(cm);distance(cm)",10000,-1500.,1500) };
  std::unique_ptr<TH1D> hzonretro { new TH1D("hzonretro","distance_onretro;z(cm);distance(cm)",10000,-1500.,1500) };
  double x_fixed = 0.;
  double y_fixed = 0.;
  double z_fixed = 0.;
  std::unique_ptr<TFile> file { new TFile("/home/fujigami/retro/lowe/data/wcsim_no_retro_electron_5MeV_10000event.root") };
  TTree* wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  std::shared_ptr<runoption> option {new runoption(wcsimrootgeom)};
  double R = wcsimrootgeom->GetWCCylRadius();
  double pmt_z_noretro = R*std::tan(std::acos(1./n_water));
  double pmt_z_onretro = -pmt_z_noretro;
  TVector3 pmt_noretro(R,0,pmt_z_noretro);
  TVector3 pmt_onretro(-R,0,pmt_z_onretro);
  for(double x=-1500.;x < 1500.;x += 1.){
    TVector3 position(x,y_fixed,z_fixed);
    double donretro = 2*distance_retro_pmt(position,pmt_onretro,option) - distance_position_pmt(position,pmt_onretro);
    double dnoretro = distance_position_pmt(position,pmt_noretro);
    hxonretro->Fill(x,donretro);
    hxnoretro->Fill(x,dnoretro);
  }
  for(double y=-1500.;y < 1500.;y += 1.){
    TVector3 position(x_fixed,y,z_fixed);
    double donretro = 2*distance_retro_pmt(position,pmt_onretro,option) - distance_position_pmt(position,pmt_onretro);
    double dnoretro = distance_position_pmt(position,pmt_noretro);
    hyonretro->Fill(y,donretro);
    hynoretro->Fill(y,dnoretro);
  }
  for(double z=-1500.;z < 1500.;z += 1.){
    TVector3 position(x_fixed,y_fixed,z);
    double donretro = 2*distance_retro_pmt(position,pmt_onretro,option) - distance_position_pmt(position,pmt_onretro);
    double dnoretro = distance_position_pmt(position,pmt_noretro);
    hzonretro->Fill(z,donretro);
    hznoretro->Fill(z,dnoretro);
  }
  std::unique_ptr<TCanvas> c1 { new TCanvas("c1","c1")};
  hxonretro->Draw();
  c1->SaveAs(config.outfile_x_onretro);
  hyonretro->Draw();
  c1->SaveAs(config.outfile_y_onretro);
  hzonretro->Draw();
  c1->SaveAs(config.outfile_z_onretro);
  hxnoretro->Draw();
  c1->SaveAs(config.outfile_x_noretro);
  hynoretro->Draw();
  c1->SaveAs(config.outfile_y_noretro);
  hznoretro->Draw();
  c1->SaveAs(config.outfile_z_noretro);
  delete wcsimrootgeom;
}

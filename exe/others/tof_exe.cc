#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <vector>
#include <TVector3.h>
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
#include "constants.hh"
#include "distance_pmt.hh"
#include "tof.hh"
#include "config.hh"
int main()
{
  std::cout << "0" << std::endl;
  Config_tof_exe config;
  std::cout << "1" << std::endl;
  std::cout << "0" << std::endl;
  char* infile = config.infile;
  std::cout << infile << std::endl;
  TFile*file = new TFile(infile);
  TTree* wcsimT =(TTree*)file->Get("wcsimT");
  WCSimRootEvent *wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  TTree *wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
  WCSimRootGeom * wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  std::cout << config.outfile << std::endl;
  TFile *fout = new TFile(config.outfile,"RECREATE");
  TTree *tree = new TTree(config.outtree,"title");
  int ncherenkovdigihits;
  std::vector<double> tof_nretro;
  std::vector<double> tof_retro;
  std::vector<double> time;
  std::vector<double> pmtX;
  std::vector<double> pmtY;
  std::vector<double> pmtZ;
  std::vector<double> d1;
  std::vector<double> d2;
  tree->Branch("ncherenkovdigihits",&ncherenkovdigihits);
  tree->Branch("time",&time);
  tree->Branch("tof_nretro",&tof_nretro);
  tree->Branch("tof_retro",&tof_retro);
  tree->Branch("pmtX",&pmtX);
  tree->Branch("pmtY",&pmtY);
  tree->Branch("pmtZ",&pmtZ);
  tree->Branch("d1",&d1);
  tree->Branch("d2",&d2);
  double position[3] = {0.,0.,0.};
  int n_event = wcsimT->GetEntries();
  for(int i = 0;i<n_event;++i){
    wcsimT->GetEntry(i);
    WCSimRootTrigger *wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
    std::shared_ptr<runoption> option { new runoption(wcsimrootgeom,wcsimroottrigger)};
    for(int j = 0;j<ncherenkovdigihits;++j){
      WCSimRootCherenkovDigiHit *hit =(WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(j));
      time.push_back(hit->GetT());
      int tubeId = hit->GetTubeId();
      WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId-1);
      pmtX.push_back(pmt.GetPosition(0));
      pmtY.push_back(pmt.GetPosition(1));
      pmtZ.push_back(pmt.GetPosition(2));
      TVector3 pmtposition(pmt.GetPosition(0),pmt.GetPosition(1),pmt.GetPosition(2));
      d1.push_back(distance_position_pmt(position,pmtposition));
      tof_nretro.push_back(tof(time[j],d1[j])-option->offset);
      d2.push_back(distance_retro_pmt(position,pmtposition,option));
      tof_retro.push_back(tof(time[j],2*d2[j]-d1[j])-option->offset);
    }
    tree->Fill();
    for(int k = 0;k<ncherenkovdigihits;++k){
      tof_nretro.pop_back();
      tof_retro.pop_back();
      time.pop_back();
      pmtX.pop_back();
      pmtY.pop_back();
      pmtZ.pop_back();
      d2.pop_back();
      d1.pop_back();
    }
    std::cout<<i<<":"<<ncherenkovdigihits<<std::endl;
  }
  fout->Write();
  fout->Close();
}

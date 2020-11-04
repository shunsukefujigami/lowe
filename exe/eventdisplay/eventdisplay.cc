// c++ STL
#include <cmath>
#include <iostream>
#include <memory>

// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TH2.h>
#include <TVector3.h>
#include <TLorentzVector.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "constants.hh"
#include "config.hh"
#include "distance_pmt.hh"
#include "tof.hh"
#include "runoption.hh"
#include "goodness_given_4Vector.hh"

void eventdisplay(int n_event,char *input_file_name,char *output_file_name,int xbin,int ybin,TVector3 trueposition,char* ogfuncname){
  TFile*file = new TFile(input_file_name);
  TTree* wcsimT =(TTree*)file->Get("wcsimT");
  WCSimRootEvent *wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  TTree *wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
  WCSimRootGeom * wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  TFile *fout = new TFile(output_file_name,"RECREATE");
  double WCradius = wcsimrootgeom->GetWCCylRadius();
  double WClength = wcsimrootgeom->GetWCCylLength();
  TH2D* h_hit = new TH2D("hit","event display(hit);;",xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  TH2D* h_charge = new TH2D("charge","event display(charge);;",xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  TH2D* h_charge_restrict1 = new TH2D("charge_restrict1","event display(charge restrict);;",xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  TH2D* h_charge_restrict2 = new TH2D("charge_restrict2","event display(charge restrict);;",xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  TH2D *h_time = new TH2D("htime","event display(time);;",xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  wcsimT->GetEntry(n_event);
  TH2D *h_all = new TH2D("all","event display(all);;",xbin,-PI*WCradius,PI*WCradius,ybin,-WClength/2-2*WCradius,WClength/2+2*WCradius);
  int NumPMT = wcsimrootgeom->GetWCNumPMT();
  for(int i = 0;i<NumPMT;++i){
    WCSimRootPMT pmt = wcsimrootgeom->GetPMT(i);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    double pmtS = -WCradius*atan2(pmtY,pmtX);
    if((pmt.GetCylLoc()) == 0){
      h_all->Fill(-pmtY,-(pmtX)+WClength/2+WCradius);
         }
    else if((pmt.GetCylLoc()) == 1){
      h_all->Fill(pmtS,pmtZ);
    }
    else{
      h_all->Fill(-pmtY,pmtX-WClength/2-WCradius);
    }
  }
  WCSimRootTrigger *wcsimroottrigger = wcsimrootevent->GetTrigger(0);
  std::shared_ptr<runoption> option {new runoption(wcsimrootgeom,wcsimroottrigger)};
  std::string s_ogfuncname = ogfuncname;
  std::cout << s_ogfuncname << std::endl;
  option->ogfunc = (option->ogfuncmap).at(s_ogfuncname);
  option->sigma = 5.;
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  double goodness = 0;
  double timevertex;
  for(double t = -200.;t < 0.;t++){
    TLorentzVector vector = TLorentzVector(trueposition,t);
    double goodness_tmp = goodness_given_4Vector(vector,option);
    if(goodness < goodness_tmp){
      timevertex = t;
      goodness = goodness_tmp;
    }
  }
  for(int k=0;k<ncherenkovdigihits;++k){
    WCSimRootCherenkovDigiHit *hit =(WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
    double time = hit->GetT();
    double charge = hit->GetQ();
    int tubeId = hit->GetTubeId();
    WCSimRootPMT pmt = wcsimrootgeom->GetPMT(tubeId-1);
    double pmtX = pmt.GetPosition(0);
    double pmtY = pmt.GetPosition(1);
    double pmtZ = pmt.GetPosition(2);
    TVector3 pmtposition = TVector3(pmtX,pmtY,pmtZ);
    double pmtS = -WCradius*atan2(pmtY,pmtX);
    double d1 = distance_position_pmt(trueposition,pmtposition);
    double tof_nretro = tof(time-timevertex-option->offset,d1);
    bool bnretro;
    if(tof_nretro < 50. && tof_nretro > -50.)
      bnretro = true;
    else
      bnretro = false;
    double d2 = distance_retro_pmt(trueposition,pmtposition,option);
    double tof_retro = tof(time-timevertex-option->offset,2*d2-d1);
    bool bretro;
    if(tof_retro < 50. && tof_retro > -50.)
      bretro = true;
    else
      bretro =false;
    if((pmt.GetCylLoc()) == 0){
      h_hit->Fill(-pmtY,-(pmtX)+WClength/2+WCradius);
      h_charge->Fill(-pmtY,-(pmtX)+WClength/2+WCradius,charge);
      if(bnretro)
	h_charge_restrict1->Fill(-pmtY,-(pmtX)+WClength/2+WCradius,charge);
      if(bretro)
	h_charge_restrict2->Fill(-pmtY,-(pmtX)+WClength/2+WCradius,charge);
      h_time->Fill(-pmtY,-(pmtX)+WClength/2+WCradius,time);
    }
    else if((pmt.GetCylLoc()) == 1){
      h_hit->Fill(pmtS,pmtZ);
      h_charge->Fill(pmtS,pmtZ,charge);
      if(bnretro)
	h_charge_restrict1->Fill(pmtS,pmtZ,charge);
      if(bretro)
	h_charge_restrict2->Fill(pmtS,pmtZ,charge);
      h_time->Fill(pmtS,pmtZ,time);
    }
    else{
      h_hit->Fill(-pmtY,pmtX-WClength/2-WCradius);
      h_charge->Fill(-pmtY,pmtX-WClength/2-WCradius,charge);
      if(bnretro)
	h_charge_restrict1->Fill(-pmtY,pmtX-WClength/2-WCradius,charge);
      if(bretro)
	h_charge_restrict2->Fill(-pmtY,pmtX-WClength/2-WCradius,charge);
      h_time->Fill(-pmtY,pmtX-WClength/2-WCradius,time);
    }
  }
  fout->Write();
  fout->Close();
}

int main(int argc,char *argv[])
{
  if(argc != 1 ){
    std::cout<<"err : number of variable is wrong.\n";
  }
  else{
    Config_eventdisplay config;
    eventdisplay(config.nevents,config.infile,config.outfile,config.xbin,config.ybin,config.trueposition,config.ogfuncname);
  }
  return 0;
}

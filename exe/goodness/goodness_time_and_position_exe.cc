// c++ STL
#include <vector>
#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <memory>

// ROOT library
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>

// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "goodness_data.hh"
#include "CSearch_range.hh"
#include "runoption.hh"
#include "WCGoodness_calculate.hh"
#include "goodness_given_4Vector.hh"
#include "config.hh"

void goodness_time_and_position_exe(int n_event,char* infile,char* outfile,char* outtree,CSearch_range range,double sigma,int first_event,int n_event_part,char* gfuncname,char* ogfuncname){
  TFile* file = new TFile(infile);
  TTree* wcsimT =(TTree*)file->Get("wcsimT");
  WCSimRootEvent *wcsimrootevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  TTree *wcsimGeoT =(TTree*)file->Get("wcsimGeoT");
  WCSimRootGeom* wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  TFile *fout = new TFile(outfile,"RECREATE");
  TTree *tree = new TTree(outtree,"title");
  int ncherenkovdigihits;
  double max_goodness;
  double max_goodness_noretro;
  double max_goodness_onretro;
  double max_x;
  double max_y;
  double max_z;
  double max_t;
  tree->Branch("ncherenkovdigihits",&ncherenkovdigihits);
  tree->Branch("max_goodness",&max_goodness);
  tree->Branch("max_goodness_noretro",&max_goodness_noretro);
  tree->Branch("max_goodness_onretro",&max_goodness_onretro);
  tree->Branch("max_x",&max_x);
  tree->Branch("max_y",&max_y);
  tree->Branch("max_z",&max_z);
  tree->Branch("max_t",&max_t);
  std::cout << "numx:" << range.GetXNum() << std::endl;
  std::cout << "numy:" << range.GetYNum() << std::endl;
  std::cout << "numz:" << range.GetZNum() << std::endl;
  std::cout << "numt:" << range.GetTNum() << std::endl;
  for(int i = first_event;i<first_event + n_event_part;++i){
    wcsimT->GetEntry(i);
    WCSimRootTrigger *wcsimroottrigger = wcsimrootevent->GetTrigger(0);
    std::shared_ptr<runoption> option { new runoption(wcsimrootgeom,wcsimroottrigger) };
    std::string s_gfuncname = gfuncname;
    option->gfunc = (option->gfuncmap).at(s_gfuncname);
    std::string s_ogfuncname = ogfuncname;
    option->ogfunc = (option->ogfuncmap).at(s_ogfuncname);
    option->sigma = sigma;
    ncherenkovdigihits = option->wcsimroottrigger->GetNcherenkovdigihits();
    goodness_data data = WCGoodness_calculate(range,option);
    max_goodness = data.Getgoodness();
    option->ogfunc = (option->ogfuncmap).at("no_retro");
    max_goodness_noretro = option->gfunc(data.Get4Vector(),option);
    option->ogfunc = (option->ogfuncmap).at("on_retro");
    max_goodness_onretro = option->gfunc(data.Get4Vector(),option);
    option->ogfunc = (option->ogfuncmap).at(s_ogfuncname);
    max_x = data.GetX();
    max_y = data.GetY();
    max_z = data.GetZ();
    max_t = data.GetT();
    tree->Fill();
    std::cout << "max_goodness:" << max_goodness << std::endl;
    std::cout << "max_goodness_noretro:" << max_goodness_noretro << std::endl;
    std::cout << "max_goodness_onretro:" << max_goodness_onretro << std::endl;
    std::cout << "max_x max_y max_z max_t : " << max_x << max_y << max_z << max_t << std::endl;
  }
  fout->Write();
  fout->Close();
  //  delete tree;
  //  delete fout;
  //  delete wcsimrootevent;
  //  delete wcsimrootgeom;
  //  delete file;
}

int main(int argc,char *argv[]){
  try{
    Config_goodness config;
    if(argc != 4){
      std::cout<<"err:number of variable is wrong.\n";
      return -1;
    }
    else{
      char* outfile = argv[1];
      int first_event = atoi(argv[2]);
      int n_event_part = atoi(argv[3]);
      goodness_time_and_position_exe(config.nevents,config.infile,outfile,config.outtree,config.range,config.sigma,first_event,n_event_part,config.gfuncname,config.ogfuncname);
    }
  }
  catch(std::string name){
    std::cerr << "err in " << name << std::endl;
  }  
  return 0;
}

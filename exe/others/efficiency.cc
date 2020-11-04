// c++ STL
#include <cstring>
#include <sstream>
#include <memory>
#include <vector>
#include <iostream>

// ROOT library
#include <TH1D.h>
#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>

// WCSim library
#include <WCSimRootEvent.hh>

// self-introduced library
#include "config.hh"

void fillefficiency(TH1D* h_noretro,TH1D* h_onretro,Config_efficiency config,double energy){
  std::stringstream ssinfile_onretro;
  ssinfile_onretro << config.infilehead_onretro << energy << config.infiletail;
  TFile* f_onretro = new TFile( ssinfile_onretro.str().c_str());
  TTree* wcsimT_onretro = (TTree*)f_onretro->Get("wcsimT");
  std::stringstream ssinfile_noretro;
  ssinfile_noretro << config.infilehead_noretro << energy << config.infiletail;
  TFile* f_noretro = new TFile( ssinfile_noretro.str().c_str());
  TTree* wcsimT_noretro = (TTree*)f_noretro->Get("wcsimT");
  WCSimRootEvent* wcsimrootevent_onretro = new WCSimRootEvent();
  WCSimRootEvent* wcsimrootevent_noretro = new WCSimRootEvent();
  wcsimT_onretro->SetBranchAddress("wcsimrootevent",&wcsimrootevent_onretro);
  wcsimT_noretro->SetBranchAddress("wcsimrootevent",&wcsimrootevent_noretro);
  int ntrigger_onretro = 0;
  int ntrigger_noretro = 0;
  int Nevent = wcsimT_onretro->GetEntries();
  for(int i = 0;i<Nevent;i++){
    wcsimT_onretro->GetEntry(i);
    wcsimT_noretro->GetEntry(i);
    WCSimRootTrigger* wcsimroottrigger_onretro = wcsimrootevent_onretro->GetTrigger(0);
    WCSimRootTrigger* wcsimroottrigger_noretro = wcsimrootevent_noretro->GetTrigger(0);
    if(wcsimroottrigger_onretro->GetNcherenkovdigihits() != 0){
      ntrigger_onretro++;
    }
    if(wcsimroottrigger_noretro->GetNcherenkovdigihits() != 0){
      ntrigger_noretro++;
    }
  }
  double eff_onretro = (double)ntrigger_onretro/(double)Nevent;
  double eff_noretro = (double)ntrigger_noretro/(double)Nevent;
  std::cout << "energy=" << energy << "MeV,eff_onretro=" << eff_onretro << ",eff_noretro=" << eff_noretro << std::endl;
  h_onretro->Fill(energy,eff_onretro);
  h_noretro->Fill(energy,eff_noretro);
  delete wcsimrootevent_noretro;
  delete wcsimrootevent_onretro;
  delete f_onretro;
  delete f_noretro;
}
int main(){
  Config_efficiency config;
  double emin = config.emin;
  double ewidth = config.ewidth;
  int e_num = config.e_num;
  double emax = config.emax;
  TH1D* h_noretro = new TH1D("h_noretro","trigger efficiency;energy(MeV);effciency",e_num,emin-ewidth/2,emax+ewidth/2);
  TH1D* h_onretro = new TH1D("h_onretro","trigger efficiency;energy(MeV);effciency",e_num,emin-ewidth/2,emax+ewidth/2);
  double energy = emin;
  for(int i = 0; i < e_num ; i++, energy += ewidth)
    {
      /*      std::stringstream ssinfile_onretro;
      ssinfile_onretro << config.infilehead_onretro << energy << config.infiletail;
      std::unique_ptr<TFile> f_onretro { new TFile( ssinfile_onretro.str().c_str())};
      TTree* wcsimT_onretro = (TTree*)f_onretro->Get("wcsimT");
      std::stringstream ssinfile_noretro;
      ssinfile_noretro << config.infilehead_noretro << energy << config.infiletail;
      std::unique_ptr<TFile> f_noretro { new TFile( ssinfile_noretro.str().c_str())};
      TTree* wcsimT_noretro = (TTree*)f_noretro->Get("wcsimT");
      WCSimRootEvent* wcsimrootevent_onretro = new WCSimRootEvent();
      WCSimRootEvent* wcsimrootevent_noretro = new WCSimRootEvent();
      wcsimT_onretro->SetBranchAddress("wcsimrootevent",&wcsimrootevent_onretro);
      wcsimT_noretro->SetBranchAddress("wcsimrootevent",&wcsimrootevent_noretro);
      WCSimRootTrigger* wcsimroottrigger_onretro = wcsimrootevent_onretro->GetTrigger(0);
      WCSimRootTrigger* wcsimroottrigger_noretro = wcsimrootevent_noretro->GetTrigger(0);
      int ntrigger_onretro = 0;
      int ntrigger_noretro = 0;
      int Nevent = wcsimT_onretro->GetEntries();
      for(int i = 0;i<Nevent;i++){
	if(wcsimroottrigger_onretro->GetNcherenkovdigihits() != 0){
	  ntrigger_onretro++;
	}
	if(wcsimroottrigger_noretro->GetNcherenkovdigihits() != 0){
	  ntrigger_noretro++;
	}
      }
      double eff_onretro = (double)ntrigger_onretro/(double)Nevent;
      double eff_noretro = (double)ntrigger_noretro/(double)Nevent;
      h_onretro->Fill(energy,eff_onretro);
      h_noretro->Fill(energy,eff_noretro);*/
      fillefficiency(h_noretro,h_onretro,config,energy);
    }
  TCanvas* c1 = new TCanvas("c1","c1");
  h_onretro->SetLineColor(4);
  h_onretro->GetYaxis()->SetRangeUser(0.,1.1);
  h_onretro->SetStats(0);
  h_noretro->SetLineColor(2);
  h_noretro->SetStats(0);
  h_onretro->Draw();
  h_noretro->Draw("same");
  c1->SaveAs(config.outfile);
  return 0;
}

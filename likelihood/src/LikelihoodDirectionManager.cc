// c++ STL
#include <iostream>
// geant4 library
#include <CLHEP/Vector/LorentzVector.h>

// self-introduced library
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionRun.hh"
#include "LikelihoodDirectionEventManager.hh"
#include "LikelihoodDirectionEvent.hh"

LikelihoodDirectionManager* LikelihoodDirectionManager::flikelihooddirectionmanager = 0;

LikelihoodDirectionManager::LikelihoodDirectionManager(const char* infiledata,const char* infilegoodness)
  :RunManager()
{
  if(flikelihooddirectionmanager)
    {
      std::cout << "Error! LikelihoodDirectionManager constructed twice." << std::endl;
      throw "LikelihoodDirectionManager::LikelihoodDirectionManager";
    }
  flikelihooddirectionmanager = this;
  dfile = new TFile(infiledata);
  wcsimT = (TTree*)dfile->Get("wcsimT");
  wcsimGeoT = (TTree*)dfile->Get("wcsimGeoT");
  wcsimrootevent = new WCSimRootEvent();
  wcsimrootgeom = new WCSimRootGeom();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  gfile = new TFile(infilegoodness);
  goodnessT = (TTree*)gfile->Get("goodnessT");
  goodnessdata = new goodness_data();
  goodnessT->SetBranchAddress("goodnessdata",&goodnessdata);
  optionT = (TTree*)gfile->Get("optionT");
  optionT->GetEntry(0);
  Nevents = goodnessT->GetEntries();
  run = new VRun();
  run->SetnumberOfEvent(Nevents);
  eventmanager = new LikelihoodDirectionEventManager();
  std::cout << "input file data is below" << std::endl;
  dfile->Print();
  gfile->Print();
  std::cout << Nevents << "event exist" << std::endl;
}


LikelihoodDirectionManager::~LikelihoodDirectionManager()
{
  if(dfile)
    delete dfile;
  if(wcsimrootevent)
    delete wcsimrootevent;
  if(wcsimrootgeom)
    delete wcsimrootgeom;
  if(gfile)
    delete gfile;
  if(goodnessdata)
    delete goodnessdata;
  if(run)
    delete run;
  if(eventmanager)
    delete eventmanager;
}

void LikelihoodDirectionManager::SetParameters()
{
  eventmanager->SetParameters();
}

void LikelihoodDirectionManager::ProcessOneEvent(int i_event)
{
  wcsimT->GetEntry(i_event);
  goodnessT->GetEntry(i_event);
  currentevent = new LikelihoodDirectionEvent(i_event);
  double x = goodnessdata->GetX();
  double y = goodnessdata->GetY();
  double z = goodnessdata->GetZ();
  double t = goodnessdata->GetT();
  CLHEP::HepLorentzVector fitted4vector;
  fitted4vector.set(x,y,z,t);
  (dynamic_cast<LikelihoodDirectionEvent*>(currentevent))->Setfitted4Vector(fitted4vector);
  eventmanager->ProcessOneEvent(currentevent);
  delete currentevent;
}

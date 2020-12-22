// c++ STL
#include <iostream>
// geant4 library
#include <CLHEP/Vector/LorentzVector.h>

// self-introduced library
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionRun.hh"
#include "LikelihoodDirectionEventManager.hh"
#include "LikelihoodDirectionEvent.hh"


LikelihoodDirectionManager::LikelihoodDirectionManager(const char* infiledata,const char* infilegoodness)
  :ProcessManager()
{
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
}

void LikelihoodDirectionManager::ProcessOneEvent(int i)
{
  wcsimT->GetEntry(i);
  goodnessT->GetEntry(i);
  double x = goodnessdata->GetX();
  double y = goodnessdata->GetY();
  double z = goodnessdata->GetZ();
  double t = goodnessdata->GetT();
  CLHEP::HepLorentzVector fitted4vector;
  fitted4vector.set(x,y,z,t);
  currentprocess->Setfitted4Vector(fitted4vector);
  nextmanager->ProcessOne(currentprocess);
}

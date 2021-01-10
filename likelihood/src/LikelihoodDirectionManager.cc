// c++ STL
#include <iostream>
// geant4 library
#include <CLHEP/Vector/LorentzVector.h>

// self-introduced library
#include "LikelihoodDirectionManager.hh"


LikelihoodDirectionManager::LikelihoodDirectionManager(const char* infilegoodness)
  :ProcessManager()
{
  gfile = new TFile(infilegoodness);
  goodnessT = (TTree*)gfile->Get("goodnessT");
  MyString* infiledataname = (MyString*)gfile->Get("infilename");
  reconstructdata = new TReconstructdata();
  goodnessT->SetBranchAddress("reconstructdata",&reconstructdata);
  optionT = (TTree*)gfile->Get("optionT");
  optionT->GetEntry(0);
  Nevents = goodnessT->GetEntries();
  dfile = new TFile(infiledataname->Getstring().c_str());
  wcsimT = (TTree*)dfile->Get("wcsimT");
  wcsimGeoT = (TTree*)dfile->Get("wcsimGeoT");
  wcsimrootevent = new WCSimRootEvent();
  wcsimrootgeom = new WCSimRootGeom();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
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
  if(reconstructdata)
    delete reconstructdata;
}

void LikelihoodDirectionManager::ProcessOneEvent(int i)
{
  wcsimT->GetEntry(i);
  goodnessT->GetEntry(i);
  double x = reconstructdata->Get4Vector().X();
  double y = reconstructdata->Get4Vector().Y();
  double z = reconstructdata->Get4Vector().Z();
  double t = reconstructdata->Get4Vector().T();
  CLHEP::HepLorentzVector fitted4vector;
  fitted4vector.set(x,y,z,t);
  currentprocess->Setfitted4Vector(fitted4vector);
  nextmanager->ProcessOne(currentprocess);
}

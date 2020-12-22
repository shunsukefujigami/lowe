#ifndef LIKELIHOODDIRECTIONMANAGER_HH
#define LIKELIHOODDIRECTIONMANAGER_HH

// ROOT libarary
#include <TFile.h>
#include <TTree.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "goodness_data.hh"
#include "LikelihoodDirectionRunAction.hh"
#include "LikelihoodDirectionRun.hh"
#include "LikelihoodDirectionEventManager.hh"
#include "LikelihoodDirectionEvent.hh"
#include "ProcessManager.hh"

class LikelihoodDirectionManager : public ProcessManager
{
public:
  LikelihoodDirectionManager() = delete;
  LikelihoodDirectionManager(const char* infiledata,const char* infilegoodness);
  virtual ~LikelihoodDirectionManager();
  void ProcessOneEvent(int i);
  WCSimRootEvent* GetWCSimRootEvent()
  {
    return wcsimrootevent;
  }
  WCSimRootGeom* GetWCSimRootGeom()
  {
    return wcsimrootgeom;
  }
private:
  TFile* dfile = nullptr;
  TTree* wcsimT = nullptr;
  TTree* wcsimGeoT = nullptr;
  WCSimRootEvent* wcsimrootevent = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
  TFile* gfile = nullptr;
  TTree* goodnessT = nullptr;
  TTree* optionT = nullptr;
  goodness_data* goodnessdata = nullptr;
  int Nevents;
};

#endif

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
#include "LikelihoodDirectionParameters.hh"
#include "LikelihoodDirectionRunAction.hh"
#include "LikelihoodDirectionRun.hh"
#include "LikelihoodDirectionEventManager.hh"
#include "LikelihoodDirectionEvent.hh"
#include "RunManager.hh"

class LikelihoodDirectionManager : public RunManager
{
public:
  static LikelihoodDirectionManager* GetLikelihoodDirectionManager(){ return flikelihooddirectionmanager;}
private:
  static LikelihoodDirectionManager* flikelihooddirectionmanager;
public:
  LikelihoodDirectionManager() = delete;
  LikelihoodDirectionManager(const char* infiledata,const char* infilegoodness);
  virtual ~LikelihoodDirectionManager();
  void SetParameters();
  void ProcessOneEvent(int i_event);
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
};

#endif

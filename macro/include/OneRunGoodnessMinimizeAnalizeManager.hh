#ifndef ONERUNGOODNESSMINIMIZEANALIZEMANAGER_HH
#define ONERUNGOODNESSMINIMIZEANALIZEMANAGER_HH

// c++ STL
#include <vector>
// ROOT library
#include <TObject.h>
#include <TTree.h>
#include <TFile.h>
// self
#include "TReconstructdata.hh"
#include "TOption_minimize.hh"
#include "OneGoodnessMinimizeParameters.hh"

class OneRunGoodnessMinimizeAnalizeManager : public TObject
{
public:
  OneRunGoodnessMinimizeAnalizeManager();
  OneRunGoodnessMinimizeAnalizeManager(const char* goodnessminimizefile);
  void Setgoodnessminimizefile(const char* goodnessminimizefile);
  virtual ~OneRunGoodnessMinimizeAnalizeManager();
  void GetEntry(int i);
  int Getevent()
  {
    return neventgoodnessminimize;
  }
  OneGoodnessMinimizeParameters* GetGoodnessMinimizeParameters()
  {
    return onegoodnessminimizeparameters;
  }
private:
  TFile* gfile = nullptr;
  TTree* goodnessminimizeT = nullptr;
  TTree* gmoptionT = nullptr;
  TReconstructdata_minimize* data = nullptr;
  TOption_minimize* option = nullptr;
  int neventgoodnessminimize;
  OneGoodnessMinimizeParameters* onegoodnessminimizeparameters;
public:
  ClassDef(OneRunGoodnessMinimizeAnalizeManager,1)
};

#endif
  

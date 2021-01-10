#ifndef ANALIZEMANAGER_HH
#define ANALIZEMANAGER_HH

// ROOT library
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TF1.h>
#include <TH2D.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"

// self-introduced library
#include "goodness_data.hh"
#include "CSearch_range.hh"
#include "likelihood_direction_data.hh"
#include "AngleRange.hh"
#include "TReconstructdata.hh"
#include "OneRunDataAnalizeManager.hh"
#include "OneRunGoodnessAnalizeManager.hh"
#include "OneRunLikelihoodAnalizeManager.hh"
#include "BiasError.hh"

class OneRunAnalizeManager : public TObject
{
public:
  OneRunAnalizeManager();
  OneRunAnalizeManager(const char* datafile,const char* mode);
  void Setdatafile(const char* datafile);
  void SetGoodnessfile(const char* goodnessfile);
  void SetLikelihoodfile(const char* likelihoodfile);
  virtual ~OneRunAnalizeManager();
  OneRunDataAnalizeManager* Getdatamanager()
  {
    return datamanager;
  }
  OneRunGoodnessAnalizeManager* Getgoodnessmanager()
  {
    return goodnessmanager;
  }
  OneRunLikelihoodAnalizeManager* Getlikelihoodmanager()
  {
    return likelihoodmanager;
  }
  
  TH2D GetTH2DEvent(int n,int xnum,double xmin,double xmax,int ynum,double ymin,double ymax,const char* xvar,const char* yvar);
  TH2D GetTH2DHit(int n,int xnum,double xmin,double xmax,int ynum,double ymin,double ymax,const char* xvar,const char* yvar);
  TH1D GetTH1DEvent(int n,int num,double min,double max,const char* var);
  TH1D GetTH1DHit(int n,int num,double min,double max,const char* var);
  BiasError GetXBiasErrorbygoodness();
  BiasError GetYBiasErrorbygoodness();
  BiasError GetZBiasErrorbygoodness();
  double angleerror1sigma();
private:
  OneRunDataAnalizeManager* datamanager = nullptr;
  OneRunGoodnessAnalizeManager* goodnessmanager = nullptr;
  OneRunLikelihoodAnalizeManager* likelihoodmanager = nullptr;
  double GetVariableEvent(const char* valname,int i);
  double GetVariableHit(const char* valname,int ievent,int jhit);
public:
  ClassDef(OneRunAnalizeManager,1)
};


#endif

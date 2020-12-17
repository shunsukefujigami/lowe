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

class OneRunAnalizeManager : public TObject
{
public:
  OneRunAnalizeManager();
  OneRunAnalizeManager(TFile* datafile);
  OneRunAnalizeManager(TFile* datafile,TFile* goodnessfile,int filenumber = 0);
  OneRunAnalizeManager(TFile* datafile,TFile* goodnessfile,TFile* likelihoodfile,int filenumber = 0);
  void Setdatafile(TFile* datafile);
  void SetGoodnessfile(TFile* goodnessfile,int filenumber = 0);
  void SetLikelihoodfile(TFile* likelihoodfile,int filenumber = 0);
  virtual ~OneRunAnalizeManager();
  TH1D* GetXHist(const char* name="",const char* title="");
  TH1D* GetYHist(const char* name="",const char* title="");
  TH1D* GetZHist(const char* name="",const char* title="");
  TH1D* GetTHist(const char* name="",const char* title="");
  TH1D* GetCosThetaHist()
  {
    return costhetahist;
  }
  TH1D* GetPhiHist()
  {
    return phihist;
  }
  TH1D* GetDeltaAngleHist()
  {
    return deltaanglehist;
  }
  
  
  void FitByGaussianAll();
  TF1* Getfgaussianx()
  {
    return fgaussianx;
  }
  TF1* Getfgaussiany()
  {
    return fgaussiany;
  }
  TF1* Getfgaussianz()
  {
    return fgaussianz;
  }
  TH2D* GetTH2D();
  void FillTH2D(const char* name,const char*title,int n,int xnum,double xmin,double xmax,int ynum,double ymin,double ymax,const char* xvar,const char* yvar);
  double GetEfficiency();
  WCSimRootEvent* GetWCSimRootEvent()
  {
    return wcsimrootevent;
  }
  
private:
  void Setdatafile();
  TFile* dfile = nullptr;
  TFile* gfile = nullptr;
  TFile* lfile = nullptr;
  TTree* wcsimT = nullptr;
  TTree* wcsimGeoT = nullptr;
  TTree* goodnessT = nullptr;
  TTree* optionT = nullptr;
  TTree* likelihoodT = nullptr;
  TTree* loptionT = nullptr;
  goodness_data* gdata = nullptr;
  CSearch_range* range = nullptr;
  WCSimRootEvent* wcsimrootevent = nullptr;
  WCSimRootGeom* wcsimrootgeom = nullptr;
  l_dir_data* ldata = nullptr;
  AngleRange* arange = nullptr;
  TH1D* xhist = nullptr;
  TH1D* yhist = nullptr;
  TH1D* zhist = nullptr;
  TH1D* thist = nullptr;
  TF1* fgaussianx = nullptr;
  TF1* fgaussiany = nullptr;
  TF1* fgaussianz = nullptr;
  TH2D* th2d = nullptr;
  TH1D* costhetahist = nullptr;
  TH1D* phihist = nullptr;
  TH1D* deltaanglehist = nullptr;
  TF1* fgaussiancostheta = nullptr;
  TF1* fgaussianphi = nullptr;
  int neventdata;
  int neventgoodness;
  int neventlikelihood;
  double GetVariable(const char* valname);
  std::string s_fgaussianx;
  std::string s_fgaussiany;
  std::string s_fgaussianz;
  std::vector<int> vncherenkovdigihits;
public:
  ClassDef(OneRunAnalizeManager,1)
};

#endif

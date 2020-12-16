// c++ STL
#include <cstring>
#include <sstream>
// ROOT library
#include <TH2D.h>
// self-introduced library
#include "OneRunAnalizeManager.hh"
#include "CSearch_range.hh"

OneRunAnalizeManager::OneRunAnalizeManager()
{
}

OneRunAnalizeManager::OneRunAnalizeManager(TFile* datafile)
{
  dfile = datafile;
  wcsimT = (TTree*)dfile->Get("wcsimT");
  wcsimGeoT = (TTree*)dfile->Get("wcsimGeoT");
  wcsimrootevent = new WCSimRootEvent();
  wcsimrootgeom = new WCSimRootGeom();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);
  for(int i = 0;i < wcsimT->GetEntries();i++)
    {
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      vncherenkovdigihits.push_back(wcsimroottrigger->GetNcherenkovdigihits());
      
    }
  
  
}

OneRunAnalizeManager::OneRunAnalizeManager(TFile* datafile,TFile* goodnessfile,int number)
{
  if(dfile)
    {
      std::cout << "dfile is already exist!" << std::endl;
    }
  
  dfile = datafile;
  wcsimT = (TTree*)dfile->Get("wcsimT");
  wcsimGeoT = (TTree*)dfile->Get("wcsimGeoT");
  wcsimrootevent = new WCSimRootEvent();
  wcsimrootgeom = new WCSimRootGeom();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootevent);
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEntry(0);

  wcsimGeoT->GetEntry(0);
  for(int i = 0;i < wcsimT->GetEntries();i++)
    {
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      vncherenkovdigihits.push_back(wcsimroottrigger->GetNcherenkovdigihits());
      
    }
  
  gfile = goodnessfile;
  goodnessT = (TTree*)gfile->Get("goodnessT");
  gdata = new goodness_data();
  goodnessT->SetBranchAddress("goodnessdata",&gdata);
  nevent = goodnessT->GetEntries();
  optionT = (TTree*)gfile->Get("optionT");
  range = new CSearch_range();
  optionT->SetBranchAddress("csearchrange",&range);
  optionT->GetEntry(0);
  std::ostringstream oss;
  oss << number;
  std::string s_number = oss.str();
  std::string s_xhist = "xhist" + s_number;
  std::string s_yhist = "yhist" + s_number;
  std::string s_zhist = "zhist" + s_number;
  std::string s_thist = "thist" + s_number;
  xhist = new TH1D(s_xhist.c_str(),"",range->GetXNum(),range->GetXmin()-range->GetXwidth()/2.,range->GetXmax()+range->GetXwidth()/2.);
  yhist = new TH1D(s_yhist.c_str(),"",range->GetYNum(),range->GetYmin()-range->GetYwidth()/2.,range->GetYmax()+range->GetYwidth()/2.);
  zhist = new TH1D(s_zhist.c_str(),"",range->GetZNum(),range->GetZmin()-range->GetZwidth()/2.,range->GetZmax()+range->GetZwidth()/2.);
  thist = new TH1D(s_thist.c_str(),"",range->GetTNum(),range->GetTmin()-range->GetTwidth()/2.,range->GetTmax()+range->GetTwidth()/2.);
  for(int i = 0; i < nevent; i++)
    {
      if(vncherenkovdigihits[i] != 0)
	{
	  goodnessT->GetEntry(i);
	  xhist->Fill(gdata->GetX());
	  yhist->Fill(gdata->GetY());
	  zhist->Fill(gdata->GetZ());
	  thist->Fill(gdata->GetT());
	}
      
    }
  s_fgaussianx = "fgaussianx" + s_number;
  s_fgaussiany = "fgaussiany" + s_number;
  s_fgaussianz = "fgaussianz" + s_number;
  fgaussianx = new TF1(s_fgaussianx.c_str(),"[0]*exp(-0.5*pow((x-[1])/[2],2))",xhist->GetXaxis()->GetXmin(),xhist->GetXaxis()->GetXmax());
  fgaussiany = new TF1(s_fgaussiany.c_str(),"[0]*exp(-0.5*pow((x-[1])/[2],2))",yhist->GetXaxis()->GetXmin(),yhist->GetXaxis()->GetXmax());
  fgaussianz = new TF1(s_fgaussianz.c_str(),"[0]*exp(-0.5*pow((x-[1])/[2],2))",zhist->GetXaxis()->GetXmin(),zhist->GetXaxis()->GetXmax());
  wcsimT->GetEntry(0);
  WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
  fgaussianx->SetParameters(nevent/10.,wcsimroottrigger->GetVtx(0),100.);
  fgaussiany->SetParameters(nevent/10.,wcsimroottrigger->GetVtx(1),100.);
  fgaussianz->SetParameters(nevent/10.,wcsimroottrigger->GetVtx(2),100.);
}

void OneRunAnalizeManager::SetGoodnessfile(TFile* goodnessfile,int number)
{
    gfile = goodnessfile;
  goodnessT = (TTree*)gfile->Get("goodnessT");
  gdata = new goodness_data();
  goodnessT->SetBranchAddress("goodnessdata",&gdata);
  nevent = goodnessT->GetEntries();
  optionT = (TTree*)gfile->Get("optionT");
  range = new CSearch_range();
  optionT->SetBranchAddress("csearchrange",&range);
  optionT->GetEntry(0);
  std::ostringstream oss;
  oss << number;
  std::string s_number = oss.str();
  std::string s_xhist = "xhist" + s_number;
  std::string s_yhist = "yhist" + s_number;
  std::string s_zhist = "zhist" + s_number;
  std::string s_thist = "thist" + s_number;
  xhist = new TH1D(s_xhist.c_str(),"",range->GetXNum(),range->GetXmin()-range->GetXwidth()/2.,range->GetXmax()+range->GetXwidth()/2.);
  yhist = new TH1D(s_yhist.c_str(),"",range->GetYNum(),range->GetYmin()-range->GetYwidth()/2.,range->GetYmax()+range->GetYwidth()/2.);
  zhist = new TH1D(s_zhist.c_str(),"",range->GetZNum(),range->GetZmin()-range->GetZwidth()/2.,range->GetZmax()+range->GetZwidth()/2.);
  thist = new TH1D(s_thist.c_str(),"",range->GetTNum(),range->GetTmin()-range->GetTwidth()/2.,range->GetTmax()+range->GetTwidth()/2.);
  for(int i = 0; i < nevent; i++)
    {
      if(vncherenkovdigihits[i] != 0)
	{
	  goodnessT->GetEntry(i);
	  xhist->Fill(gdata->GetX());
	  yhist->Fill(gdata->GetY());
	  zhist->Fill(gdata->GetZ());
	  thist->Fill(gdata->GetT());
	}
      
    }
  s_fgaussianx = "fgaussianx" + s_number;
  s_fgaussiany = "fgaussiany" + s_number;
  s_fgaussianz = "fgaussianz" + s_number;
  fgaussianx = new TF1(s_fgaussianx.c_str(),"[0]*exp(-0.5*pow((x-[1])/[2],2))",xhist->GetXaxis()->GetXmin(),xhist->GetXaxis()->GetXmax());
  fgaussiany = new TF1(s_fgaussiany.c_str(),"[0]*exp(-0.5*pow((x-[1])/[2],2))",yhist->GetXaxis()->GetXmin(),yhist->GetXaxis()->GetXmax());
  fgaussianz = new TF1(s_fgaussianz.c_str(),"[0]*exp(-0.5*pow((x-[1])/[2],2))",zhist->GetXaxis()->GetXmin(),zhist->GetXaxis()->GetXmax());
  WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
  fgaussianx->SetParameters(nevent/10.,wcsimroottrigger->GetVtx(0),100.);
  fgaussiany->SetParameters(nevent/10.,wcsimroottrigger->GetVtx(1),100.);
  fgaussianz->SetParameters(nevent/10.,wcsimroottrigger->GetVtx(2),100.);
}


OneRunAnalizeManager::~OneRunAnalizeManager()
{
  delete wcsimrootevent;
  delete wcsimrootgeom;
  if(gdata)
    delete gdata;
  if(range)
    delete range;
  if(xhist)
    delete xhist;
  if(yhist)
    delete yhist;
  if(zhist)
    delete zhist;
  if(thist)
    delete thist;
  if(th2d)
    delete th2d;
}


TH1D* OneRunAnalizeManager::GetXHist(const char* name,const char* title)
{
  xhist->SetName(name);
  xhist->SetTitle(title);
  return xhist;
}

TH1D* OneRunAnalizeManager::GetYHist(const char* name,const char* title)
{
  yhist->SetName(name);
  yhist->SetTitle(title);
  return yhist;
}

TH1D* OneRunAnalizeManager::GetZHist(const char* name,const char* title)
{
  zhist->SetName(name);
  zhist->SetTitle(title);
  return zhist;
}

TH1D* OneRunAnalizeManager::GetTHist(const char* name,const char* title)
{
  thist->SetName(name);
  thist->SetTitle(title);
  return thist;
}

void OneRunAnalizeManager::FitByGaussianAll()
{
  
  xhist->Fit(s_fgaussianx.c_str());
  yhist->Fit(s_fgaussiany.c_str());
  zhist->Fit(s_fgaussianz.c_str());
}

void OneRunAnalizeManager::FillTH2D(const char* name,const char* title,int n,int xnum,double xmin,double xmax,int ynum,double ymin,double ymax,const char* xvar,const char* yvar)
{
  
  if(th2d)
    {
      delete th2d;
    }
  th2d = new TH2D(name,title,xnum,xmin,xmax,ynum,ymin,ymax);
  for(int i = 0;i < n;i++)
    {
      wcsimT->GetEntry(i);
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      goodnessT->GetEntry(i);
      int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
      if(ncherenkovdigihits != 0)
	{
	  double xval = GetVariable(xvar);
	  double yval = GetVariable(yvar);
	  th2d->Fill(xval,yval);
	}
    }
}

TH2D* OneRunAnalizeManager::GetTH2D()
{
  return th2d;
}


double OneRunAnalizeManager::GetVariable(const char* valname)
{
  std::string s_valname = valname;
  if(s_valname == "gdata->GetT()")
    {
      return gdata->GetT();
    }
  if(s_valname == "wcsimroottrigger->GetTriggerTime()")
    {
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      return wcsimroottrigger->GetTriggerTime();
    }
  if(s_valname == "gdata->GetX()")
    {
      return gdata->GetX();
    }
  if(s_valname == "gdata->GetY()")
    {
      return gdata->GetY();
    }
  if(s_valname == "gdata->GetZ()")
    {
      return gdata->GetZ();
    }
  if(s_valname == "gdata->Getgoodness()")
    {
      return gdata->Getgoodness();
    }
  if(s_valname == "wcsimroottrigger->GetNcherenkovdigihits()")
    {
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      return (double)wcsimroottrigger->GetNcherenkovdigihits();
    }
  if(s_valname == "wcsimroottrigger->GetVtx(0)")
    {
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      return wcsimroottrigger->GetVtx(0);
    }
  if(s_valname == "wcsimroottrigger->GetVtx(1)")
    {
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      return wcsimroottrigger->GetVtx(1);
    }
  if(s_valname == "wcsimroottrigger->GetVtx(2)")
    {
      WCSimRootTrigger* wcsimroottrigger = wcsimrootevent->GetTrigger(0);
      return wcsimroottrigger->GetVtx(2);
    }
  std::cout << "invalid valname!" << std::endl;
  throw "OneRunAnalizeManager::GetVariable(const char* valname)";;
}

double OneRunAnalizeManager::GetEfficiency()
{
  int ntrigger = 0;
  int Nevent = wcsimT->GetEntries();
  for(int i = 0; i < Nevent; i++)
    {
      if(vncherenkovdigihits[i] != 0)
	{
	  ntrigger++;
	}
    }
  double efficiency = (double)ntrigger/(double)Nevent;
  return efficiency;
}

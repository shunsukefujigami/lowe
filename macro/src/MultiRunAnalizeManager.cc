// c++ STL
#include <iostream>

// self-introduced libarary
#include "MultiRunAnalizeManager.hh"
#include "OneRunAnalizeManager.hh"
#include "FileList.hh"

ClassImp(MultiRunAnalizeManager)

MultiRunAnalizeManager::MultiRunAnalizeManager()
{
}

MultiRunAnalizeManager::MultiRunAnalizeManager(FileList* datafilelist,FileList* goodnessfilelist,int NRun_in)
  :TClonesArray("OneRunAnalizeManager",NRun_in)
{
  int NRundata = datafilelist->GetEntries();
  int NRungoodness = goodnessfilelist->GetEntries();
  if((NRundata != NRungoodness)||(NRundata != NRun_in))
    {
      std::cout << "Number of data is no matching!" << std::endl;
      throw "MultiRunAnalizeManager::MultiRunAnalizeManager(FileList* datafilelist,FileList* goodnessfilelist)";
    }
  NRun = NRun_in;
  for(int i = 0;i < NRundata;i++)
    {
      new((*this)[i]) OneRunAnalizeManager((TFile*)datafilelist->At(i),(TFile*)goodnessfilelist->At(i),i);
    }
}

MultiRunAnalizeManager::MultiRunAnalizeManager(FileList*datafilelist,int NRun_in)
  :TClonesArray("OneRunAnalizeManager",NRun_in)
{
  int NRundata = datafilelist->GetEntries();
  if(NRundata != NRun_in)
    {
      std::cout << "Number of data is no matching!" << std::endl;
      throw "MultiRunAnalizeManager::MultiRunAnalizeManager(FileList* datafilelist)";
    }
  NRun = NRun_in;
  for(int i = 0;i < NRundata;i++)
    {
      new((*this)[i]) OneRunAnalizeManager((TFile*)datafilelist->At(i));
    }
}

void MultiRunAnalizeManager::SetGoodnessfile(FileList* goodnessfilelist)
{
  int NRungoodness = goodnessfilelist->GetEntries();
  if(NRun != NRungoodness)
    {
      std::cout << "Number of data is no matching!" << std::endl;
      throw "MultiRunAnalizeManager::SetGoodnessfile(FileList* goodnessfilelist)";
    }
  for(int i = 0; i < NRun;i++)
    {
      ((OneRunAnalizeManager*)At(i))->SetGoodnessfile((TFile*)goodnessfilelist->At(i),i);
    }
}

  
MultiRunAnalizeManager::~MultiRunAnalizeManager()
{
  if(efficiency)
    {
      delete efficiency;
    }
}

void MultiRunAnalizeManager::Fillefficiency(double xmin,double xmax,double xwidth)
{
  if(efficiency)
    {
      delete efficiency;
    }
  
  efficiency = new TH1D("","",NRun,xmin-xwidth/2.,xmax+xwidth/2.);
  for(int i = 0; i < NRun ; i++)
    {
      double eff = ((OneRunAnalizeManager*)At(i))->GetEfficiency();
      efficiency->Fill(xmin + i * xwidth,eff);
    }
}

void MultiRunAnalizeManager::Fillerrorandbiasgaussian(double xmin,double xmax,double xwidth)
{
  if(xerror)
    {
      delete xerror;
    }
  if(yerror)
    {
      delete yerror;
    }
  if(zerror)
    {
      delete zerror;
    }
  if(xbias)
    {
      delete xbias;
    }
  if(ybias)
    {
      delete ybias;
    }
  if(zbias)
    {
      delete zbias;
    }
 xerror = new TH1D("","",NRun,xmin-xwidth/2.,xmax+xwidth/2.);
 yerror = new TH1D("","",NRun,xmin-xwidth/2.,xmax+xwidth/2.);
 zerror = new TH1D("","",NRun,xmin-xwidth/2.,xmax+xwidth/2.);
 xbias = new TH1D("","",NRun,xmin-xwidth/2.,xmax+xwidth/2.);
 ybias = new TH1D("","",NRun,xmin-xwidth/2.,xmax+xwidth/2.);
 zbias = new TH1D("","",NRun,xmin-xwidth/2.,xmax+xwidth/2.);
  for(int i = 0;i < NRun;i++)
    {
      OneRunAnalizeManager* oram = (OneRunAnalizeManager*)At(i);
      oram->FitByGaussianAll();
      double xerr = oram->Getfgaussianx()->GetParameter(2);
      double yerr = oram->Getfgaussiany()->GetParameter(2);
      double zerr = oram->Getfgaussianz()->GetParameter(2);
      double xerrerr = oram->Getfgaussianx()->GetParError(2);
      double yerrerr = oram->Getfgaussiany()->GetParError(2);
      double zerrerr = oram->Getfgaussianz()->GetParError(2);
      WCSimRootTrigger* wcsimroottrigger = oram->GetWCSimRootEvent()->GetTrigger(0);
      double xbi = oram->Getfgaussianx()->GetParameter(1) - wcsimroottrigger->GetVtx(0);
      double ybi = oram->Getfgaussiany()->GetParameter(1) - wcsimroottrigger->GetVtx(1);
      double zbi = oram->Getfgaussianz()->GetParameter(1) - wcsimroottrigger->GetVtx(2);
      double xbierr = oram->Getfgaussianx()->GetParError(1);
      double ybierr = oram->Getfgaussiany()->GetParError(1);
      double zbierr = oram->Getfgaussianz()->GetParError(1);
      double bin = xmin + i * xwidth;
      xerror->Fill(bin,xerr);
      yerror->Fill(bin,yerr);
      zerror->Fill(bin,zerr);
      xerror->SetBinError(i+1,xerrerr);
      yerror->SetBinError(i+1,yerrerr);
      zerror->SetBinError(i+1,zerrerr);
      xbias->Fill(bin,xbi);
      ybias->Fill(bin,ybi);
      zbias->Fill(bin,zbi);
      xbias->SetBinError(i+1,xbierr);
      ybias->SetBinError(i+1,ybierr);
      zbias->SetBinError(i+1,zbierr);
    }
}


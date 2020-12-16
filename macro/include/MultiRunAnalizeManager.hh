#ifndef MULTIRUNANALIZEMANAGER_HH
#define MULTIRUNANALIZEMANAGER_HH
// c++ STL
#include <vector>
// ROOT library
#include <TClonesArray.h>
#include <TH1D.h>
// self-introduced library
#include "FileList.hh"

class MultiRunAnalizeManager : public TClonesArray
{
public:
  MultiRunAnalizeManager();
  MultiRunAnalizeManager(FileList* datafilelist,FileList* goodnessfilelist,int NRun_in);
  MultiRunAnalizeManager(FileList*datafilelist,int NRun_in);

  void SetGoodnessfile(FileList* goodnessfilelist);
  
  virtual ~MultiRunAnalizeManager();
  int GetNRun()
  {
    return NRun;
  }
  void Fillefficiency(double xmin,double xmax,double xwidth);
  TH1D* Getefficiency()
  {
    return efficiency;
  }
  void Fillerrorandbiasgaussian(double xmin,double xmax,double xwidth);
  TH1D* Getxerror()
  {
    return xerror;
  }
  TH1D* Getyerror()
  {
    return yerror;
  }
  TH1D* Getzerror()
  {
    return zerror;
  }
  TH1D* Getxbias()
  {
    return xbias;
  }
  TH1D* Getybias()
  {
    return ybias;
  }
  TH1D* Getzbias()
  {
    return zbias;
  }
  
private:
  int NRun;
  TH1D* efficiency = nullptr;
  TH1D* xerror = nullptr;
  TH1D* yerror = nullptr;
  TH1D* zerror = nullptr;
  TH1D* xbias = nullptr;
  TH1D* ybias = nullptr;
  TH1D* zbias = nullptr;
public:
  ClassDef(MultiRunAnalizeManager,1)
};

#endif

#ifndef MULTIRUNANALIZEMANAGER_HH
#define MULTIRUNANALIZEMANAGER_HH
// c++ STL
#include <vector>
#include <cstring>
// ROOT library
#include <TClonesArray.h>
#include <TH1D.h>
// self-introduced library
#include "OneDataParameters.hh"
#include "OneGoodnessParameters.hh"
#include "OneLikelihoodParameters.hh"
#include "OneRunAnalizeManager.hh"

class MultiRunAnalizeManager : public TObject
{
public:
  MultiRunAnalizeManager();
  void SetBasefile(const char* file);
  void SetComparefile(std::vector<std::string> vexclusionname);
  void SetAllfile();
  void PrintAllfile();
  void PrintComparefile();
  virtual ~MultiRunAnalizeManager();
  TH1D GetTH1D(int num,double min,double max,const char* xvar,const char* yvar,bool berror=false,const char* errorval="");
  double GetVariable(const char* var,OneRunAnalizeManager& oram);
  OneDataParameters basefileparameters;
  OneGoodnessParameters basegoodnessparameters;
  OneLikelihoodParameters baselikelihoodparameters;
  std::vector<OneDataParameters> vdataparameters;
  std::vector<OneGoodnessParameters> vgoodnessparameters;
  std::vector<OneLikelihoodParameters> vlikelihoodparameters;
  std::vector<OneRunAnalizeManager> vrunanalizemanager;
private:
  std::string sbasefile;
  int mode; // datamode 0;goodnessmode 1;likelihoodmode 2
public:
  ClassDef(MultiRunAnalizeManager,1)
};

#endif

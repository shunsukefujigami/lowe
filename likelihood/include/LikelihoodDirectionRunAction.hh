#ifndef LIKELIHOODDIRECTIONRUNACTION_HH
#define LIKELIHOODDIRECTIONRUNACTION_HH
// c++ STL
#include <memory>
// ROOT library
#include <TFile.h>
#include <TTree.h>

// self-introduced library
#include "AngleRange.hh"
#include "VAction.hh"
#include "TReconstructdata.hh"
#include "MyString.hh"

class LikelihoodDirectionRunAction : public VAction
{
public:
  LikelihoodDirectionRunAction(const char* outfile_in,const char* infilegoodness_in);
  virtual ~LikelihoodDirectionRunAction()
  {
  }
  void BeginOfAction(std::shared_ptr<Process> process);
  void EndOfAction(std::shared_ptr<Process> process);
  TReconstructdata* GetLikelihoodDirectiondata()
  {
    return data;
  }
  TTree* GetTTree()
  {
    return likelihoodtree;
  }
  void SetAngleRange(AngleRange rangein)
  {
    this->rangein = rangein;
  }
  
private:
  const char* outfile;
  const char* cinfilegoodness;
  MyString* infiledata = nullptr;
  MyString* infilegoodness = nullptr;
  TFile* file = nullptr;
  TTree* likelihoodtree = nullptr;
  TTree* optiontree = nullptr;
  TReconstructdata* data = nullptr;
  AngleRange* range = nullptr;
  AngleRange rangein;
};

#endif

#ifndef LIKELIHOODDIRECTIONRUNACTION_HH
#define LIKELIHOODDIRECTIONRUNACTION_HH
// ROOT library
#include <TFile.h>
#include <TTree.h>

// self-introduced library
#include "AngleRange.hh"
#include "VRunAction.hh"
#include "likelihood_direction_data.hh"

class LikelihoodDirectionRunAction : public VRunAction
{
public:
  LikelihoodDirectionRunAction(const char* outfile_in);
  virtual ~LikelihoodDirectionRunAction()
  {
  }
  void BeginOfRunAction(VRun* run);
  void EndOfRunAction(VRun* run);
  l_dir_data* GetLikelihoodDirectiondata()
  {
    return data;
  }
  TTree* GetTTree()
  {
    return likelihoodtree;
  }
  
private:
  const char* outfile;
  TFile* file = nullptr;
  TTree* likelihoodtree = nullptr;
  TTree* optiontree = nullptr;
  l_dir_data* data = nullptr;
  AngleRange* range = nullptr;
};

#endif

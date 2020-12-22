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
#include "likelihood_direction_data.hh"

class LikelihoodDirectionRunAction : public VAction
{
public:
  LikelihoodDirectionRunAction(const char* outfile_in);
  virtual ~LikelihoodDirectionRunAction()
  {
  }
  void BeginOfRunAction(std::shared_ptr<Process> process);
  void EndOfRunAction(std::shared_ptr<Process> process);
  l_dir_data* GetLikelihoodDirectiondata()
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
  TFile* file = nullptr;
  TTree* likelihoodtree = nullptr;
  TTree* optiontree = nullptr;
  l_dir_data* data = nullptr;
  AngleRange* range = nullptr;
  AngleRange rangein;
};

#endif

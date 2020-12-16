#ifndef GOODNESSRUNACTION_HH
#define GOODNESSRUNACTION_HH

// ROOT library
#include <TTree.h>
// self-introduced library
#include "goodness_data.hh"
#include "CSearch_range.hh"

class GoodnessRunAction
{
public:
  GoodnessRunAction(const char* outfile_in);
  virtual ~GoodnessRunAction(){};
public:
  void BeginOfRunAction();
  void EndOfRunAction();
  const char* Getoutfile(){return outfile;}
  goodness_data* GetgoodnessData(){ return data;}
  TTree* GetTTree(){ return goodnesstree;}
private:
  const char* outfile;
  TFile* file = nullptr;
  TTree* goodnesstree = nullptr;
  TTree* optiontree = nullptr;
  goodness_data* data = nullptr;
  CSearch_range* range = nullptr;
};

#endif

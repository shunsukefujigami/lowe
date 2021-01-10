#ifndef GOODNESSRUNACTION_HH
#define GOODNESSRUNACTION_HH

// ROOT library
#include <TTree.h>
// self-introduced library
#include "TReconstructdata.hh"
#include "CSearch_range.hh"
#include "MyString.hh"

class GoodnessRunAction
{
public:
  GoodnessRunAction(const char* outfile_in,const char* infile_in);
  virtual ~GoodnessRunAction(){};
public:
  void BeginOfRunAction();
  void EndOfRunAction();
  const char* Getoutfile(){return outfile;}
  TReconstructdata* GetReconstructdata(){ return data;}
  TTree* GetTTree(){ return goodnesstree;}
private:
  const char* outfile;
  const char* cinfile;
  MyString* infile = nullptr;
  TFile* file = nullptr;
  TTree* goodnesstree = nullptr;
  TTree* optiontree = nullptr;
  TReconstructdata* data = nullptr;
  CSearch_range* range = nullptr;
};

#endif

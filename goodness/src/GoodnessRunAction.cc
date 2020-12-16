// c++ STL
#include <iostream>
// ROOT library
#include <TFile.h>
// self-introduced library
#include "GoodnessRunAction.hh"
#include "CSearch_range.hh"
#include "GoodnessManager.hh"

GoodnessRunAction::GoodnessRunAction(const char* outfile_in)
  :outfile(outfile_in)
{
}

  

void GoodnessRunAction::BeginOfRunAction(){
  file = new TFile(outfile,"recreate","Goodness ROOT File");
  
  goodnesstree = new TTree("goodnessT","GoodnessData Tree");
  optiontree = new TTree("optionT","GoodnessOption Tree");
  data = new goodness_data();
  goodnesstree->Branch("goodnessdata",&data);
  CSearch_range* rangein = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetSearch_range();
  range = new CSearch_range();
  optiontree->Branch("csearchrange",&range);
  range->Setrange(*rangein);
  optiontree->Fill();
}

void GoodnessRunAction::EndOfRunAction(){
  std::cout << "End of RunAction" << std::endl;
  file->Write();
  file->Close();
  delete data;
  delete range;
}

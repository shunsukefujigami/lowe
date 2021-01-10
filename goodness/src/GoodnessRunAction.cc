// c++ STL
#include <iostream>
// ROOT library
#include <TFile.h>
// self-introduced library
#include "GoodnessRunAction.hh"
#include "CSearch_range.hh"
#include "GoodnessManager.hh"

GoodnessRunAction::GoodnessRunAction(const char* outfile_in,const char* infile_in)
  :outfile(outfile_in),cinfile(infile_in)
{
}

  

void GoodnessRunAction::BeginOfRunAction(){
  file = new TFile(outfile,"recreate","Goodness ROOT File");
  infile = new MyString();
  std::string sinfile = cinfile;
  infile->Setstring(sinfile);
  infile->SetName("infilename");
  goodnesstree = new TTree("goodnessT","GoodnessData Tree");
  optiontree = new TTree("optionT","GoodnessOption Tree");
  data = new TReconstructdata();
  goodnesstree->Branch("reconstructdata",&data);
  CSearch_range* rangein = GoodnessManager::GetGoodnessManager()->GetGoodnessParameters()->GetSearch_range();
  range = new CSearch_range();
  optiontree->Branch("csearchrange",&range);
  range->Setrange(*rangein);
  optiontree->Fill();
}

void GoodnessRunAction::EndOfRunAction(){
  std::cout << "End of RunAction" << std::endl;
  file->cd();
  infile->Write();
  file->Write();
  file->Close();
  delete data;
  delete range;
  delete infile;
}

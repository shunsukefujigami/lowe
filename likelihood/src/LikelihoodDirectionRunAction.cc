#include <iostream>
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionRunAction.hh"

LikelihoodDirectionRunAction::LikelihoodDirectionRunAction(const char* outfile_in)
  :outfile(outfile_in)
{
}


void LikelihoodDirectionRunAction::BeginOfRunAction(std::shared_ptr<Process>)
{
  file = new TFile(outfile,"recreate","Likelihood ROOT File");
  likelihoodtree = new TTree("likelihoodT","LikelihoodData Tree");
  optiontree = new TTree("loptionT","LikelihoodOption Tree");
  data = new l_dir_data();
  likelihoodtree->Branch("likelihooddata",&data);
  range = new AngleRange();
  optiontree->Branch("anglerange",&range);
  range->Setrange(rangein);
  optiontree->Fill();
}
void LikelihoodDirectionRunAction::EndOfRunAction(std::shared_ptr<Process>)
{
  std::cout << "End of RunAction" << std::endl;
  file->Write();
  file->Close();
  delete data;
  delete range;
}


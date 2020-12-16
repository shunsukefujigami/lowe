#include <iostream>
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionRunAction.hh"

LikelihoodDirectionRunAction::LikelihoodDirectionRunAction(const char* outfile_in)
  :outfile(outfile_in)
{
}


void LikelihoodDirectionRunAction::BeginOfRunAction(VRun*)
{
  file = new TFile(outfile,"recreate","Likelihood ROOT File");
  likelihoodtree = new TTree("likelihoodT","LikelihoodData Tree");
  optiontree = new TTree("loptionT","LikelihoodOption Tree");
  data = new l_dir_data();
  likelihoodtree->Branch("likelihooddata",&data);
  AngleRange rangein = (dynamic_cast<LikelihoodDirectionParameters*>(LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetParameters()))->GetAngleRange();
  range = new AngleRange();
  optiontree->Branch("anglerange",&range);
  range->Setrange(rangein);
  optiontree->Fill();
}
void LikelihoodDirectionRunAction::EndOfRunAction(VRun*)
{
  std::cout << "End of RunAction" << std::endl;
  file->Write();
  file->Close();
  delete data;
  delete range;
}


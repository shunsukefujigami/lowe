#include <iostream>
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionRunAction.hh"

LikelihoodDirectionRunAction::LikelihoodDirectionRunAction(const char* outfile_in,const char* infilegoodness_in)
  :outfile(outfile_in),cinfilegoodness(infilegoodness_in)
{
}


void LikelihoodDirectionRunAction::BeginOfAction(std::shared_ptr<Process>)
{
  TFile* fgoodness = new TFile(cinfilegoodness);
  MyString* infiledataname = (MyString*)fgoodness->Get("infilename");
  std::string sinfiledata = infiledataname->Getstring();
  delete fgoodness;
  file = new TFile(outfile,"recreate","Likelihood ROOT File");
  infiledata = new MyString();
  infilegoodness = new MyString();
  std::string sinfilegoodness = cinfilegoodness;
  infiledata->Setstring(sinfiledata);
  infiledata->SetName("infiledataname");
  infilegoodness->Setstring(sinfilegoodness);
  infilegoodness->SetName("infilegoodnessname");
  likelihoodtree = new TTree("likelihoodT","LikelihoodData Tree");
  optiontree = new TTree("loptionT","LikelihoodOption Tree");
  data = new TReconstructdata();
  likelihoodtree->Branch("reconstructdatalikelihood",&data);
  range = new AngleRange();
  optiontree->Branch("anglerange",&range);
  range->Setrange(rangein);
  optiontree->Fill();
}
void LikelihoodDirectionRunAction::EndOfAction(std::shared_ptr<Process>)
{
  std::cout << "End of RunAction" << std::endl;
  file->cd();
  infiledata->Write();
  infilegoodness->Write();
  file->Write();
  file->Close();
  delete data;
  delete range;
}


#include "LikelihoodDirectionEvent.hh"
#include "LikelihoodDirectionEventAction.hh"
#include <CLHEP/Vector/ThreeVector.h>

void LikelihoodDirectionEventAction::EndOfEventAction(std::shared_ptr<Process> process)
{
  l_dir_data data;
  data.SetL(process->GetMaxlikelihood());
  CLHEP::Hep3Vector vector = process->GetMax3Direction();
  double costheta = vector.cosTheta();
  double phi = vector.phi();
  data.SetCosTheta(costheta);
  data.SetPhi(phi);
  l_dir_data* datain = likelihooddirectionrunaction->GetLikelihoodDirectiondata();
  datain->Setdata(data);
  TTree* tree = likelihooddirectionrunaction->GetTTree();
  tree->Fill();
}


#include "LikelihoodDirectionEvent.hh"
#include "LikelihoodDirectionEventAction.hh"
#include <CLHEP/Vector/ThreeVector.h>

void LikelihoodDirectionEventAction::EndOfEventAction(std::shared_ptr<VEvent> event)
{
  l_dir_data data;
  data.SetL((std::dynamic_pointer_cast<LikelihoodDirectionEvent>(event))->Getlikelihood());
  CLHEP::Hep3Vector vector = (std::dynamic_pointer_cast<LikelihoodDirectionEvent>(event))->Get3Vector();
  double costheta = vector.cosTheta();
  double phi = vector.phi();
  data.SetCosTheta(costheta);
  data.SetPhi(phi);
  l_dir_data* datain = likelihooddirectionrunaction->GetLikelihoodDirectiondata();
  datain->Setdata(data);
  TTree* tree = likelihooddirectionrunaction->GetTTree();
  tree->Fill();
}


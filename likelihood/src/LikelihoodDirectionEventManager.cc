// c++ STL
#include <iostream>
#include <cmath>
// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "LikelihoodDirectionEventManager.hh"
#include "LikelihoodDirectionCalculateManager.hh"
#include "LikelihoodDirectionManager.hh"
#include "LikelihoodDirectionCalculated.hh"

LikelihoodDirectionEventManager::LikelihoodDirectionEventManager()
{
  loop1manager = std::make_shared<LikelihoodDirectionCalculateManager>();
}

LikelihoodDirectionEventManager::~LikelihoodDirectionEventManager()
{
}

void LikelihoodDirectionEventManager::SetParameters()
{
  range = std::dynamic_pointer_cast<LikelihoodDirectionParameters>(LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetParameters())->GetAngleRange();
  loop1manager->SetParameters();
}


void LikelihoodDirectionEventManager::Doprocess()
{
  double costheta = range.GetCosthetamin();
  for(int i = 0; i < range.GetCosthetaNum(); ++i , costheta += range.GetCosthetawidth())
    {
      double phi = range.GetPhimin();
      for(int j = 0; j < range.GetPhiNum(); j++ , phi += range.GetPhiwidth())
	{
	  CLHEP::Hep3Vector vector;
	  vector.setRThetaPhi(1.,std::acos(costheta),phi);
	  Doloopin(vector);
	}
    }
}

void LikelihoodDirectionEventManager::Doloopin(CLHEP::Hep3Vector hvector)
{
  std::shared_ptr<LikelihoodDirectionCalculated> likelihooddirectioncalculated = std::make_shared<LikelihoodDirectionCalculated>();
  likelihooddirectioncalculated->SetLikelihood(0.);
  likelihooddirectioncalculated->Set3Vector(hvector);
  likelihooddirectioncalculated->Setfitted4Vector((std::dynamic_pointer_cast<LikelihoodDirectionEvent>(currentevent))->Getfitted4Vector());
  loop1manager->DoProcess(likelihooddirectioncalculated);
  double likelihood = likelihooddirectioncalculated->GetLikelihood();
  if((std::dynamic_pointer_cast<LikelihoodDirectionEvent>(currentevent))->Getlikelihood() < likelihood)
    {
      (std::dynamic_pointer_cast<LikelihoodDirectionEvent>(currentevent))->Setlikelihood(likelihood);
      (std::dynamic_pointer_cast<LikelihoodDirectionEvent>(currentevent))->Set3Vector(hvector);
    }
}


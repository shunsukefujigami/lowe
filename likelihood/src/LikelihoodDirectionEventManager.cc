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
  loop1manager = new LikelihoodDirectionCalculateManager();
}

LikelihoodDirectionEventManager::~LikelihoodDirectionEventManager()
{
  delete loop1manager;
}

void LikelihoodDirectionEventManager::SetParameters()
{
  range = dynamic_cast<LikelihoodDirectionParameters*>(LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetParameters())->GetAngleRange();
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
  LikelihoodDirectionCalculated* likelihooddirectioncalculated = new LikelihoodDirectionCalculated();
  likelihooddirectioncalculated->SetLikelihood(0.);
  likelihooddirectioncalculated->Set3Vector(hvector);
  likelihooddirectioncalculated->Setfitted4Vector((dynamic_cast<LikelihoodDirectionEvent*>(currentevent))->Getfitted4Vector());
  loop1manager->DoProcess(likelihooddirectioncalculated);
  double likelihood = likelihooddirectioncalculated->GetLikelihood();
  if((dynamic_cast<LikelihoodDirectionEvent*>(currentevent))->Getlikelihood() < likelihood)
    {
      (dynamic_cast<LikelihoodDirectionEvent*>(currentevent))->Setlikelihood(likelihood);
      (dynamic_cast<LikelihoodDirectionEvent*>(currentevent))->Set3Vector(hvector);
    }
  delete likelihooddirectioncalculated;
}


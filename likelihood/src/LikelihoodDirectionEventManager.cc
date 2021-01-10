// c++ STL
#include <iostream>
#include <cmath>
// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "LikelihoodDirectionEventManager.hh"

LikelihoodDirectionEventManager::LikelihoodDirectionEventManager()
{
}

LikelihoodDirectionEventManager::~LikelihoodDirectionEventManager()
{
}

void LikelihoodDirectionEventManager::Doprocess()
{
  WCSimRootTrigger* wcsimroottrigger = ProcessManager::GetProcessManager(0)->GetWCSimRootEvent()->GetTrigger(0);
  int ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  currentprocess->Setncherenkovdigihits(ncherenkovdigihits);
  currentprocess->onelikelihoodonretro = std::vector<double>(ncherenkovdigihits,0.);
  currentprocess->onelikelihoodnoretro = std::vector<double>(ncherenkovdigihits,0.);
  currentprocess->maxonelikelihoodonretro = std::vector<double>(ncherenkovdigihits,0.);
  currentprocess->maxonelikelihoodnoretro = std::vector<double>(ncherenkovdigihits,0.);
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
  currentprocess->SetCurrentlikelihood(0.);
  currentprocess->SetCurrent3Direction(hvector);
  nextmanager->ProcessOne(currentprocess);
  double likelihood = currentprocess->GetCurrentlikelihood();
  if(currentprocess->GetMaxlikelihood() < likelihood)
    {
      currentprocess->SetMaxlikelihood(likelihood);
      currentprocess->SetMax3Direction(hvector);
      currentprocess->SetMaxonelikelihood();
    }
}


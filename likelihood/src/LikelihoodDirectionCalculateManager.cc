// c++ STL
#include <iostream>
// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// WCSim library
#include "WCSimRootEvent.hh"
#include "WCSimRootGeom.hh"
// self-introduced library
#include "LikelihoodDirectionCalculateManager.hh"
#include "LikelihoodDirectionManager.hh"
#include "OneLikelihoodDirectionCalculated.hh"
#include "OneLikelihoodDirectionCalculateManager.hh"

LikelihoodDirectionCalculateManager::LikelihoodDirectionCalculateManager()
{
  loop2manager = new OneLikelihoodDirectionCalculateManager();
}

LikelihoodDirectionCalculateManager::~LikelihoodDirectionCalculateManager()
{
  delete loop2manager;
  delete loop1action;
}

void LikelihoodDirectionCalculateManager::SetParameters()
{
  loop2manager->SetParameters();
}

void LikelihoodDirectionCalculateManager::Doloop()
{
  wcsimroottrigger = LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetWCSimRootEvent()->GetTrigger(0);
  ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  CLHEP::Hep3Vector vector = (dynamic_cast<LikelihoodDirectionCalculated*>(currentloop1))->Get3Vector();
  for( int k = 0; k < ncherenkovdigihits; ++k)
    {
      OneLikelihoodDirectionCalculated* onelikelihooddirectioncalculated = new OneLikelihoodDirectionCalculated();
      onelikelihooddirectioncalculated->Set3Vector(vector);
      onelikelihooddirectioncalculated->Setfitted4Vector((dynamic_cast<LikelihoodDirectionCalculated*>(currentloop1))->Getfitted4Vector());
      static WCSimRootCherenkovDigiHit* hit;
      hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
      (dynamic_cast<OneLikelihoodDirectionCalculateManager*>(loop2manager))->SetHit(hit);
      loop2manager->DoProcess(onelikelihooddirectioncalculated);
      (dynamic_cast<LikelihoodDirectionCalculated*>(currentloop1))->AddLikelihoodDirection(onelikelihooddirectioncalculated);
    }  
}


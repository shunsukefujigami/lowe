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
  loop2manager = std::make_shared<OneLikelihoodDirectionCalculateManager>();
}

LikelihoodDirectionCalculateManager::~LikelihoodDirectionCalculateManager()
{
}

void LikelihoodDirectionCalculateManager::SetParameters()
{
  loop2manager->SetParameters();
}

void LikelihoodDirectionCalculateManager::Doloop()
{
  wcsimroottrigger = LikelihoodDirectionManager::GetLikelihoodDirectionManager()->GetWCSimRootEvent()->GetTrigger(0);
  ncherenkovdigihits = wcsimroottrigger->GetNcherenkovdigihits();
  CLHEP::Hep3Vector vector = (std::dynamic_pointer_cast<LikelihoodDirectionCalculated>(currentloop1))->Get3Vector();
  for( int k = 0; k < ncherenkovdigihits; ++k)
    {
      Doloopin(k,vector);
    }  
}

void LikelihoodDirectionCalculateManager::Doloopin(int k,CLHEP::Hep3Vector vector)
{
  std::shared_ptr<OneLikelihoodDirectionCalculated> onelikelihooddirectioncalculated = std::make_shared<OneLikelihoodDirectionCalculated>();
  onelikelihooddirectioncalculated->Set3Vector(vector);
  onelikelihooddirectioncalculated->Setfitted4Vector((std::dynamic_pointer_cast<LikelihoodDirectionCalculated>(currentloop1))->Getfitted4Vector());
  static WCSimRootCherenkovDigiHit* hit;
  hit = (WCSimRootCherenkovDigiHit*)(wcsimroottrigger->GetCherenkovDigiHits()->At(k));
  (std::dynamic_pointer_cast<OneLikelihoodDirectionCalculateManager>(loop2manager))->SetHit(hit);
  loop2manager->DoProcess(onelikelihooddirectioncalculated);
  (std::dynamic_pointer_cast<LikelihoodDirectionCalculated>(currentloop1))->AddLikelihoodDirection(onelikelihooddirectioncalculated);
}


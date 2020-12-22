// c++ STL
#include <iostream>
#include <cmath>
#include <memory>
// geant4 library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "OneLikelihoodDirectionCalculateManager.hh"
#include "LikelihoodDirectionManager.hh"
#include "hitinfo.hh"
#include "Reconstructdata.hh"

OneLikelihoodDirectionCalculateManager::OneLikelihoodDirectionCalculateManager()
{
}

OneLikelihoodDirectionCalculateManager::~OneLikelihoodDirectionCalculateManager()
{
}

void OneLikelihoodDirectionCalculateManager::SetParameters()
{
  wcsimrootgeom = ProcessManager::GetProcessManager(0)->GetWCSimRootGeom();
}

void OneLikelihoodDirectionCalculateManager::Doloop()
{
  hitinfo info;
  info.Sethit(hit,wcsimrootgeom);
  Reconstructdata data;
  data.Set4Vector(currentprocess->Getfitted4Vector());
  data.Setdirection(currentprocess->GetCurrent3Direction());
  lh->SetHitInfo(info);
  lh->SetReconstructdata(data);
  double l = lh->returnvalue();
  currentprocess->AddLikelihoodDirection(l);
}




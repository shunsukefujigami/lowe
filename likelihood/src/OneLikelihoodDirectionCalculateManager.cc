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

OneLikelihoodDirectionCalculateManager::OneLikelihoodDirectionCalculateManager(const char* likelihoodtype)
{
  ltype = likelihoodtype;
}

OneLikelihoodDirectionCalculateManager::~OneLikelihoodDirectionCalculateManager()
{
}

void OneLikelihoodDirectionCalculateManager::SetParameters()
{
  wcsimrootgeom = ProcessManager::GetProcessManager(0)->GetWCSimRootGeom();
}

void OneLikelihoodDirectionCalculateManager::Doprocess()
{
  hitinfo info;
  info.Sethit(hit,wcsimrootgeom);
  Reconstructdata data;
  data.Set4Vector(currentprocess->Getfitted4Vector());
  data.Setdirection(currentprocess->GetCurrent3Direction());
  ln->SetHitInfo(info);
  ln->SetReconstructdata(data);
  lo->SetHitInfo(info);
  lo->SetReconstructdata(data);
  ln->Setfdirectionnoretro(fn);
  lo->Setfdirectiononretro(fo);
  ln->Setafunctionnoretro(an);
  lo->Setafunctiononretro(ao);
  double lnoretro = ln->returnvalue();
  currentprocess->onelikelihoodnoretro.at(currentprocess->Gethitnumber()) = lnoretro;
  double lonretro = lo->returnvalue();
  currentprocess->onelikelihoodonretro.at(currentprocess->Gethitnumber()) = lonretro;
  if(ltype == "sum")
    currentprocess->AddLikelihoodDirection(lnoretro + lonretro);
  else if(ltype == "noretro")
    currentprocess->AddLikelihoodDirection(lnoretro);
  else
    {
      std::cout << "invaild ltype: " << ltype << std::endl;
      throw "void OneLikelihoodDirectionCalculateManager::Doprocess()";
    }
  
      
}




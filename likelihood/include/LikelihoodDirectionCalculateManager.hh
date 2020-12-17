#ifndef LIKELIHOODDIRECTIONCALCULATEMANAGER_HH
#define LIKELIHOODDIRECTIONCALCULATEMANAGER_HH
// geant4 library
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "VLoop1Manager.hh"
#include "LikelihoodDirectionCalculated.hh"
#include "OneLikelihoodDirectionCalculateManager.hh"

class LikelihoodDirectionCalculateManager : public VLoop1Manager
{
public:
  LikelihoodDirectionCalculateManager();
  virtual ~LikelihoodDirectionCalculateManager();
  void SetParameters();
  void Doloop();
  void Doloopin(int k,CLHEP::Hep3Vector vector);
  void LikelihoodDirectionNoRetro();
  void LikelihoodDirectionOnRetro();
  void LikelihoodDirectionSum();
private:
  int ncherenkovdigihits;
  WCSimRootTrigger* wcsimroottrigger = nullptr;
};

#endif

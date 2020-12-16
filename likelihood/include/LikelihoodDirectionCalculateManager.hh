#ifndef LIKELIHOODDIRECTIONCALCULATEMANAGER_HH
#define LIKELIHOODDIRECTIONCALCULATEMANAGER_HH

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
  void LikelihoodDirectionNoRetro();
  void LikelihoodDirectionOnRetro();
  void LikelihoodDirectionSum();
private:
  int ncherenkovdigihits;
  WCSimRootTrigger* wcsimroottrigger = nullptr;
};

#endif

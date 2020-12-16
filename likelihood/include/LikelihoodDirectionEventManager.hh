#ifndef LIKELIHOODDIRECTIONEVENTMANAGER_HH
#define LIKELIHOODDIRECTIONEVENTMANAGER_HH

// geant4 library
#include <CLHEP/Vector/ThreeVector.h>

// self-introduced library
#include "EventManager.hh"
#include "AngleRange.hh"

class LikelihoodDirectionEventManager : public EventManager
{
public:
  LikelihoodDirectionEventManager();
  virtual ~LikelihoodDirectionEventManager();
  void SetParameters();
  void Doprocess();
  void Doloopin(CLHEP::Hep3Vector hvector);
private:
  AngleRange range;
};

#endif

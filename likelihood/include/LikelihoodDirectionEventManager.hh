#ifndef LIKELIHOODDIRECTIONEVENTMANAGER_HH
#define LIKELIHOODDIRECTIONEVENTMANAGER_HH

// geant4 library
#include <CLHEP/Vector/ThreeVector.h>

// self-introduced library
#include "ProcessManager.hh"
#include "AngleRange.hh"

class LikelihoodDirectionEventManager : public ProcessManager
{
public:
  LikelihoodDirectionEventManager();
  virtual ~LikelihoodDirectionEventManager();  
  void Doprocess();
  void Doloopin(CLHEP::Hep3Vector hvector);
  void SetAngleRange(AngleRange rangein)
  {
    range = rangein;
  }
  
private:
  AngleRange range;
};

#endif

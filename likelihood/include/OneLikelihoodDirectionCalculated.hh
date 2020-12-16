#ifndef ONELIKELIHOODDIRECTIONCALCULATED_HH
#define ONELIKELIHOODDIRECTIONCALCULATED_HH

// geant4 library
#include <CLHEP/Vector/LorentzVector.h>

#include "VLoop2.hh"

class OneLikelihoodDirectionCalculated : public VLoop2
{
public:
  OneLikelihoodDirectionCalculated(){};
  virtual ~OneLikelihoodDirectionCalculated(){};
  void SetLikelihood(double l)
  {
    likelihood = l;
  }
  double GetLikelihood()
  {
    return likelihood;
  }
  CLHEP::HepLorentzVector Getfitted4Vector() const
  {
    return fitted4Vector;
  }
  void Setfitted4Vector(CLHEP::HepLorentzVector vector)
  {
    fitted4Vector = vector;
  }

  void Set3Vector(CLHEP::Hep3Vector vec)
  {
    direction = vec;
  }
  CLHEP::Hep3Vector Get3Vector()
  {
    return direction;
  }
  
private:
  double likelihood;
  CLHEP::HepLorentzVector fitted4Vector;
  CLHEP::Hep3Vector direction;
};

#endif

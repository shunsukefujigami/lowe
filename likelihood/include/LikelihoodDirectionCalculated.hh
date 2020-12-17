#ifndef LIKELIHOODDIRECTIONCALCULATED_HH
#define LIKELIHOODDIRECTIONCALCULATED_HH

// geant4 library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>
// self-introduced library
#include "VLoop1.hh"
#include "OneLikelihoodDirectionCalculated.hh"

class LikelihoodDirectionCalculated : public VLoop1
{
public:
  LikelihoodDirectionCalculated()
  {
  }
  
  virtual ~LikelihoodDirectionCalculated()
  {
  }
  void Set3Vector(CLHEP::Hep3Vector vec)
  {
    hvector = vec;
  }

  CLHEP::Hep3Vector Get3Vector()
  {
    return hvector;
  }
  double GetLikelihood()
  {
    return likelihood;
  }
  void SetLikelihood(double l)
  {
    likelihood = l;
  }
  
  CLHEP::HepLorentzVector Getfitted4Vector() const
  {
    return fitted4Vector;
  }

  void Setfitted4Vector(CLHEP::HepLorentzVector vector)
  {
    fitted4Vector = vector;
  }
  
  
  void AddLikelihoodDirection(std::shared_ptr<OneLikelihoodDirectionCalculated> onelikelihooddirectioncalculated)
  {
    likelihood += onelikelihooddirectioncalculated->GetLikelihood();
  }
  
  
  
private:
  CLHEP::Hep3Vector hvector;
  double likelihood;
  CLHEP::HepLorentzVector fitted4Vector;
};

  
#endif

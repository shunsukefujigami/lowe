#ifndef LIKELIHOODDIRECTIONEVENT_HH
#define LIKELIHOODDIRECTIONEVENT_HH

//geant4 library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>

// self-introduced library
#include <VEvent.hh>

class LikelihoodDirectionEvent :public VEvent
{
public:
  LikelihoodDirectionEvent(int i_event)
  {
    SetEventID(i_event);
  };
  virtual ~LikelihoodDirectionEvent(){};
  void Setfitted4Vector(CLHEP::HepLorentzVector vector)
  {
    fitted4Vector = vector;
  }
  CLHEP::HepLorentzVector Getfitted4Vector() const
  {
    return fitted4Vector;
  }
  void Setlikelihood(double l)
  {
    likelihood = l;
  }
  double Getlikelihood() const
  {
    return likelihood;
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
  CLHEP::HepLorentzVector fitted4Vector;
  CLHEP::Hep3Vector direction;
  double likelihood = -10000000.;
};

#endif
  

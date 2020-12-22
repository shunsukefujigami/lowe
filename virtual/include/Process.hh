#ifndef PROCESS_HH
#define PROCESS_HH

// geant4 library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>

class Process 
{
public:
  Process(){};
  virtual ~Process(){};
    void Setfitted4Vector(CLHEP::HepLorentzVector vector)
  {
    fitted4Vector = vector;
  }
  CLHEP::HepLorentzVector Getfitted4Vector() const
  {
    return fitted4Vector;
  }
  void SetCurrentlikelihood(double l)
  {
    currentlikelihood = l;
  }
  double GetCurrentlikelihood() const
  {
    return currentlikelihood;
  }
  void SetCurrent3Direction(CLHEP::Hep3Vector vec)
  {
    currentdirection = vec;
  }
  CLHEP::Hep3Vector GetCurrent3Direction()
  {
    return currentdirection;
  }
  void Set3PMTPosition(CLHEP::Hep3Vector vec)
  {
    pmtposition = vec;
  }
  CLHEP::Hep3Vector Get3PMTPosition()
  {
    return pmtposition;
  }
  
  void AddLikelihoodDirection(double l)
  {
    currentlikelihood +=l;
  }
  void SetnumberOfEvent(int n)
  {
    nevents = n;
  }
  int GetnumberOfEvent()
  {
    return nevents;
  }
  void SetMaxlikelihood(double l)
  {
    maxlikelihood = l;
  }
  int GetMaxlikelihood()
  {
    return maxlikelihood;
  }
  void SetMax3Direction(CLHEP::Hep3Vector vector)
  {
    maxdirection = vector;
  }
  CLHEP::Hep3Vector GetMax3Direction()
  {
    return maxdirection;
  }
  
private:
  CLHEP::HepLorentzVector fitted4Vector;
  CLHEP::Hep3Vector currentdirection;
  CLHEP::Hep3Vector pmtposition;
  double currentlikelihood = -10000000.;
  CLHEP::Hep3Vector maxdirection;
  double maxlikelihood = -10000000.;
  int nevents;
};


#endif
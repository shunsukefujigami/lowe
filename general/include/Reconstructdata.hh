#ifndef RECONSTRUCTDATA_HH
#define RECONSTRUCTDATA_HH

// geant4 library
#include <CLHEP/Vector/LorentzVector.h>
#include <CLHEP/Vector/ThreeVector.h>

class Reconstructdata
{
public:
  CLHEP::HepLorentzVector Get4Vector()
  {
    return vector;
  }
  void Set4Vector(CLHEP::HepLorentzVector vec)
  {
    vector = vec;
  }
  
  CLHEP::Hep3Vector Get3Position()
  {
    return vector.vect();
  }
  CLHEP::Hep3Vector Getdirection()
  {
    return direction;
  }
  void Setdirection(CLHEP::Hep3Vector vec)
  {
    direction = vec;
  }
  
  double Getenergy()
  {
    return energy;
  }
  
private:
  CLHEP::HepLorentzVector vector;
  CLHEP::Hep3Vector direction;
  double energy;
};
  
#endif

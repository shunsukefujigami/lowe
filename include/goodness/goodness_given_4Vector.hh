#ifndef GOODNESS_GIVEN_4VECTOR_HH
#define GOODNESS_GIVEN_4VECTOR_HH
// c++ STL
#include <memory>

// ROOT library
#include <TLorentzVector.h>

//self-introduced library
//#include "runoption.hh"

class runoption;

double goodness_given_4Vector(TLorentzVector vector,std::shared_ptr<runoption> option);

// in given 4-dimension vector (x,y,z,t), calculate goodness value.
// information abuout goodness for each hit is in runoption.

#endif

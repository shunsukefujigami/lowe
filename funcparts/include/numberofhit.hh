#ifndef NUMBEROFHIT_HH
#define NUMBEROFHIT_HH

#include <memory>
#include <TLorentzVector.h>
class runoption;

// a group of number of hit function

int numberofhit_noretro(TLorentzVector fitted4Vector,std::shared_ptr<runoption> option);

// number of hit in time window (-20 < t < 20)
// time is calculate in case of direct photon
// vertex and emitting time is given for fitted4Vector

int numberofhit_onretro(TLorentzVector fitted4Vector,std::shared_ptr<runoption> option);

// number of hit in time window (-20 < t < 20)
// time is calculate in case of reflect photon
// vertex and emitting time is given for fitted4Vector
#endif

#ifndef LIKELIHOOD_DIRECTION_HH
#define LIKELIHOOD_DIRECTION_HH
// C++ STL
#include <memory>
// ROOT library
#include <TLorentzVector.h>
// self-introduced library

class runoption;

// a group of likelihood direction calculation
// This is based on http://www-sk.icrr.u-tokyo.ac.jp/sk/_pdf/articles/ikeda-dron.pdf page32 (4.3).

double likelihood_direction_noretro(TLorentzVector fitted4Vector,double costheta,double phi,std::shared_ptr<runoption> option);

// likelihood direction in case of direct photon

double likelihood_direction_onretro(TLorentzVector fitted4Vector,double costheta,double phi,std::shared_ptr<runoption> option);

// likelihood direction in case of reflect photon

double likelihood_direction_sum(TLorentzVector fitted4Vector,double costheta,double phi,std::shared_ptr<runoption> option);

// sum of upper two

#endif

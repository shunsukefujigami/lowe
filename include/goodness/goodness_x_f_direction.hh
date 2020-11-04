#ifndef GOODNESS_X_F_DIRECTION_HH
#define GOODNESS_X_F_DIRECTION_HH

#include <TLorentzVector.h>
#include <memory>

class runoption;

// library to feedback reconstructed direction data to vertex
// the first try is simply calculate goodness times function of direction

double goodness_x_f_direction_noretro(TLorentzVector vector,double costheta,double phi,std::shared_ptr<runoption> option);

// multiply goodness in case of direct photon and function of direction in case of direct photon

double goodness_x_f_direction_onretro(TLorentzVector vector,double costheta,double phi,std::shared_ptr<runoption> option);

// multiply goodness in case of reflect photon and function of direction in case of reflect photon

double goodness_x_f_direction_sum(TLorentzVector vector,double costheta,double phi,std::shared_ptr<runoption> option);

// sum of upper two

#endif

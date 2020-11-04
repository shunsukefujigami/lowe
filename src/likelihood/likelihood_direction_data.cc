#include "likelihood_direction_data.hh"

l_dir_data::l_dir_data()
  :costheta(-10000.),phi(0.),likelihood(-1000000000.)
{}

l_dir_data::l_dir_data(double costheta,double phi,double likelihood)
  :costheta(costheta),phi(phi),likelihood(likelihood)
{}

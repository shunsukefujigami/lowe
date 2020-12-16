#ifndef LIKELIHOOD_DIRECTION_GRID_SEARCH_HH
#define LIKELIHOOD_DIRECTION_GRID_SEARCH_HH

// c++ STL
#include <memory>
// ROOT library
#include <TLorentzVector.h>
// self-introduced library
#include "likelihood_direction_data.hh"
#include "runoption.hh"

l_dir_data likelihood_direction_grid_search(TLorentzVector fitted4Vector,double costheta_width,double phi_width,std::shared_ptr<runoption> option);

// function for likelihood direction grid search

#endif

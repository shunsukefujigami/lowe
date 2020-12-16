// c++ STL
#include <memory>
#include <iostream>
// ROOT library
#include <TLorentzVector.h>

// self-introduced library
#include "constants.hh"
#include "likelihood_direction_data.hh"
#include "runoption.hh"

l_dir_data likelihood_direction_grid_search(TLorentzVector fitted4Vector,double costheta_width,double phi_width,std::shared_ptr<runoption> option){
  l_dir_data data;
  for(double costheta = -0.99;costheta < 1.;costheta += costheta_width){

    for(double phi = 0.; phi < 2*PI;phi += phi_width){
      double l = (option->lfunc)(fitted4Vector,costheta,phi,option);
      if(data.GetL() < l){
	data.SetL(l);
	data.SetCosTheta(costheta);
	data.SetPhi(phi);
      }
    }
  }
  return data;
}

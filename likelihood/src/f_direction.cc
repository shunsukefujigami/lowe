// c++ STL
#include <memory>
#include <cmath>

// self-introduced library
#include "runoption.hh"

double f_direction_prototype_noretro(double costheta){
  double a0 = 0.929027;
  double b0 = 4.69195;
  double a1 = 7.97348;
  double b1 = -0.310661;
  if(costheta < 0.75){
    return (1 + a0 * (std::exp(b0 * (costheta - 0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (costheta - 0.75 )) - 1));
  }
}

double f_direction_prototype_onretro(double costheta){
  return f_direction_prototype_noretro(-costheta);
}

double f_direction_bydata_noretro(double costheta){
  double a0 = 0.97648;
  double b0 = 3.51958;
  double a1 = 0.88353;
  double b1 = -3.52407;
  if(costheta < 0.75){
    return (1 + a0 * (std::exp(b0 * (costheta -0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (costheta - 0.75 )) - 1));
  }
}

double f_direction_bydata_onretro(double costheta){
  double a0 = 1.55324;
  double b0 = 1.53637;
  double a1 = 0.75423;
  double b1 = -2.31295;
  if(costheta < -0.75){
    return (1 + a0 * (std::exp(b0 * (costheta +0.75 )) -1));
  }
  else{
    return(1 + a1 * (std::exp(b1 * (costheta + 0.75 )) - 1));
  }
}

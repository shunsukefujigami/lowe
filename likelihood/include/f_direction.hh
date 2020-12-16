#ifndef F_DIRECTION_HH
#define F_DIRECTION_HH

// c++ STL
#include <memory>

// self-introduced library

class runoption;

// this library is a group of function to represent cherenkov angle dependency
// This is based on http://www-sk.icrr.u-tokyo.ac.jp/sk/_pdf/articles/ikeda-dron.pdf page32 (4.3).

double f_direction_prototype_noretro(double costheta);
// prototype of function of direction to assume direct photon
// it is created by fitting original paper graph

double f_direction_prototype_onretro(double costheta);
// prototype of function of direction to assume reflect photon
// it is created by reversing direct one

double f_direction_bydata_noretro(double costheta);
// function of direction to assume direct photon by data
// data is getted by fitting multi event costheta distribution restricted by time window

double f_direction_bydata_onretro(double costheta);
// function of direction to assume reflect photon by data
// data is getted by fitting multi event costheta distribution restricted by time window

#endif

#ifndef THETA_I_FUNC_HH
#define THETA_I_FUNC_HH

// ROOT library
#include <TVector3.h>

// WCSim library
#include "WCSimRootGeom.hh"

double theta_i_func(WCSimRootPMT pmt,TVector3 hminusv);

// return theta_i. theta_i is the vertex to hit direction angle against particle direction.
#endif

#ifndef DISTANCE_PMT_HH
#define DISTANCE_PMT_HH
#include <memory>
#include <TVector3.h>
#include "runoption.hh"
double distance_position_pmt(TVector3 position,TVector3 pmtposition);
// distance between given position and given pmt position
double distance_retro_pmt(TVector3 position,TVector3 pmtposition,std::shared_ptr<runoption> option);
// distance between given position and corresponding retro reflector
#endif

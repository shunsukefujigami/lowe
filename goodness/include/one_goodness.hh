#ifndef ONE_GOODNESS_HH
#define ONE_GOODNESS_HH
// c++ STL
#include <memory>

// ROOT library
#include <TLorentzVector.h>
#include <TVector3.h>

// self-introduced library
//#include "runoption.hh"

class runoption;

// a group of goodness for each hit  

double one_goodness_no_retro(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option);

// goodness in case of direct photon

double one_goodness_on_retro(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option);

// goodness in case of reflect photon

double one_goodness_sum(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option);

// sum of upper two

double one_goodness_compare(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option);

// choose maximum of direct goodness and reflect goodness

int dirorref(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option);

// return 0 in case of direct goodness is larger than reflect goodness
// return 1 in case of reflect goodness is larger than direct goodness

#endif

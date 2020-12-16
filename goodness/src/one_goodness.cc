// c++ STL
#include <cmath>
#include <memory>

// ROOT library
#include <TLorentzVector.h>
#include <TVector3.h>

// self-introduced library
#include "distance_pmt.hh"
#include "runoption.hh"
#include "tof.hh"

double one_goodness_no_retro(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option){
  double d1 = distance_position_pmt(vector.Vect(),pmt_position);
  double tof_no_retro = tof(time-vector.T()-option->offset,d1);
  double goodness = exp(-0.5*std::pow((tof_no_retro/option->sigma),2.0));
  return goodness;
}

double one_goodness_on_retro(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option){
  double d1 = distance_position_pmt(vector.Vect(),pmt_position);
  double d2 = distance_retro_pmt(vector.Vect(),pmt_position,option);
  double tof_retro = tof(time-vector.T()-option->offset,2*d2-d1);
  double goodness = exp(-0.5*std::pow((tof_retro/option->sigma),2.0));
  return goodness;
}

double one_goodness_sum(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option){
  double d1 = distance_position_pmt(vector.Vect(),pmt_position);
  double tof_nretro = tof(time-vector.T()-option->offset,d1);
  double goodness = exp(-0.5*std::pow((tof_nretro/option->sigma),2.0));
  double d2 = distance_retro_pmt(vector.Vect(),pmt_position,option);
  double tof_retro = tof(time-vector.T()-option->offset,2*d2-d1);
  goodness += exp(-0.5*std::pow((tof_retro/option->sigma),2.0));
  return goodness;
}

double one_goodness_compare(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option){
  double d1  = distance_position_pmt(vector.Vect(),pmt_position);
  double tof_nretro = tof(time-vector.T()-option->offset,d1);
  double goodness_noretro = exp(-0.5*std::pow((tof_nretro/option->sigma),2.0));
  double d2 = distance_retro_pmt(vector.Vect(),pmt_position,option);
  double tof_retro = tof(time-vector.T()-option->offset,2*d2-d1);
  double goodness_onretro = exp(-0.5*std::pow((tof_retro/option->sigma),2.0));
  double gmax;
  if( goodness_noretro > goodness_onretro){
    gmax = goodness_noretro;
  }
  else{
    gmax = goodness_onretro;
  }
  return gmax;
}

int dirorref(TLorentzVector vector,TVector3 pmt_position,double time,std::shared_ptr<runoption> option){
  double d1  = distance_position_pmt(vector.Vect(),pmt_position);
  double tof_nretro = tof(time-vector.T()-option->offset,d1);
  double goodness_noretro = exp(-0.5*std::pow((tof_nretro/option->sigma),2.0));
  double d2 = distance_retro_pmt(vector.Vect(),pmt_position,option);
  double tof_retro = tof(time-vector.T()-option->offset,2*d2-d1);
  double goodness_onretro = exp(-0.5*std::pow((tof_retro/option->sigma),2.0));
  if( goodness_noretro > goodness_onretro){
    return 0;
  }
  else{
    return 1;
  }
}
